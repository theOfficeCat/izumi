/*
 * This file is part of Izumi.
 * 
 * Izumi is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 * 
 * Izumi is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * Izumi. If not, see <https://www.gnu.org/licenses/>. 
 */

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "window.h"
#include "files.h"
#include "parser.h"
#include "config.h"
#include "commands.h"

void get_window_data(WindowData *data) {
    data->width = getmaxx(stdscr);
    data->height = getmaxy(stdscr);
}

void init_window(WindowData *data) {
    initscr();
    cbreak();
    noecho();
    refresh();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();

    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(6, COLOR_BLACK, COLOR_CYAN);

    init_pair(9,  COLOR_WHITE, COLOR_BLUE);
    init_pair(10, COLOR_WHITE, COLOR_RED);
    init_pair(11, COLOR_WHITE, COLOR_GREEN);
    init_pair(12, COLOR_WHITE, COLOR_YELLOW);
    init_pair(13, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(14, COLOR_WHITE, COLOR_CYAN);

    init_pair(16, COLOR_WHITE, COLOR_BLACK);
    init_pair(17, COLOR_BLUE, COLOR_BLACK);
    init_pair(18, COLOR_RED, COLOR_BLACK);
    init_pair(19, COLOR_GREEN, COLOR_BLACK);
    init_pair(20, COLOR_YELLOW, COLOR_BLACK);
    init_pair(21, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(22, COLOR_CYAN, COLOR_BLACK);


    data->x = 0;
    data->y = 0;

    get_window_data(data);
    data->win = newwin(data->height, data->width, data->y, data->x);
    data->first_instruction = 0;
    data->command_mode = false;
    data->command = NULL;
    data->file_loaded = false;

    data->menu_win = newwin(3, data->width, data->height-3, 0);
}

void close_window() {
    endwin();
}

void main_loop(WindowData *data, InstructionTableArray *tables_array) {
    int ch;

    render(data, tables_array);
    while (1) {
        get_window_data(data);

        ch = getch();

        if (data->command_mode) {
            fprintf(stderr, "Command: %s\n", data->command);

            if (ch == 27) {
                data->command_mode = false;
                free(data->command);
                data->command = NULL;
                data->command_size = 0;
            }
            else if (ch == KEY_BACKSPACE) {
                if (data->command_size > 1) {
                    data->command[data->command_size - 1] = '\0';
                    data->command_size--;
                }
            }
            else if (ch == '\n') {
                char command[64];
                sscanf(data->command, "%64s", command);

                fprintf(stderr, "Command detected: %s, size %d\n", command, strlen(command));

                if (strcmp(command, ":q") == 0 || strcmp(command, ":quit") == 0) {
                    close_window();
                    exit(0);
                }
                else if (strcmp(command, ":open") == 0) {
                    open_file(data, command, tables_array);
                }
                data->command_mode = false;
                free(data->command);
                data->command = NULL;
                data->command_size = 0;

            }
            else {
                data->command = realloc(data->command, data->command_size + 2);
                data->command_size++;
                data->command[data->command_size - 1] = ch;
                data->command[data->command_size] = '\0';
            }

        }

        switch (ch) {
            case 'q':
                break;
            case KEY_DOWN:
            case 'j':
                data->first_instruction++;
                break;
            case KEY_UP:
            case 'k':
                if (data->first_instruction > 0) {
                    data->first_instruction--;
                }
                break;
            case KEY_LEFT:
                break;
            case KEY_RIGHT:
                break;
            case '\n': // Enter
                break;
            case ':':
                if (!data->command_mode) {
                    data->command_mode = true;
                    char *comm = ":";
                    data->command_size = 1;
                    data->command = malloc(data->command_size + 1);
                    strcpy(data->command, comm);
                }
                break;
            default:
                break;
        }
        render(data, tables_array);
    }
}

void open_menu(WindowData *data) {
    werase(data->menu_win);

    box(data->menu_win, 0, 0);  

    wbkgd(data->menu_win, COLOR_PAIR(16));

    mvwprintw(data->menu_win, 1, 1, "%s", data->command);

    wrefresh(data->menu_win);
}

void render(WindowData *data, InstructionTableArray *tables_array) {
    // clear screen
    werase(data->win);

    box(data->win, 0, 0);

    mvwprintw(data->win, 0, 0, "Izumi v%s", VERSION);

    // verical bar on 32 px for instruction info
    mvwvline(data->win, 1, 32, ACS_VLINE, data->height - 2);

    if (data->file_loaded) {
        // print instructions data

        u_int64_t first_cycle = -1;

        //build grid
        for (u_int64_t i = 1; i < data->height - 1; i++) {
            for (u_int64_t j = 0; j < data->width - 1; j++) {
                if (j >32 && j%3 == 0) {
                    mvwprintw(data->win, i, j, "|");
                }
            }
        }

        // print instructions
        for (u_int64_t i = 0; i < data->height/2; i++) {
            u_int64_t index = data->first_instruction + i;
            Instruction instr = tables_array->tables[index/256]->content[index%256];

            // memory address and instruction
            if (instr.valid) {
                if (instr.mem_addr != NULL && (2*i + 1) < data->height - 1) {
                    mvwprintw(data->win, 2*i + 1, 1, "%lu\t%s", index, instr.mem_addr);
                }
                if (instr.instruction != NULL && (2*i + 2) < data->height - 1) {
                    mvwprintw(data->win, 2*i + 2, 5, "%s", instr.instruction);
                }

                // stages
                if ((2*i + 2) < data->height - 1) {
                    for (u_int64_t j = 0; j < instr.qtty_stages; j++) {
                        if (instr.stages[j].cycle < first_cycle) {
                            first_cycle = instr.stages[j].cycle;
                        }
                        Stage *stage = &instr.stages[j];

                        wattron(data->win, A_BOLD);

                        if (33 + 3*(stage->cycle - first_cycle) + 3 < data->width - 1) {
                            mvwprintw(data->win, 2*i + 2, 33 + 3*(stage->cycle - first_cycle), "|");
                            wattron(data->win, COLOR_PAIR((j%6)+1));
                            mvwprintw(data->win, 2*i + 2, 33 + 3*(stage->cycle - first_cycle) + 1, "%s", stage->name);

                            if (strlen(stage->name) == 1) {
                                mvwprintw(data->win, 2*i + 2, 33 + 3*(stage->cycle - first_cycle) + 2, " ");
                            }
                            wattroff(data->win, COLOR_PAIR((j%6)+1));
                        }

                        // extra cycles
                        if (stage->duration > 1) {
                            for (u_int64_t k = 0; k < stage->duration - 1; k++) {
                                if (33 + 3*(stage->cycle - first_cycle) + 3*(k+1) < data->width - 4) {
                                    wattron(data->win, COLOR_PAIR(8+(j%6)+1));
                                    mvwprintw(data->win, 2*i + 2, 33 + 3*(stage->cycle - first_cycle) + 3*(k+1), "|");
                                    wattroff(data->win, COLOR_PAIR(8+(j%6)+1));

                                    wattron(data->win, COLOR_PAIR((j%6)+1));
                                    mvwprintw(data->win, 2*i + 2, 33 + 3*(stage->cycle - first_cycle) + 3*(k+1) + 1, "  ");
                                    wattroff(data->win, COLOR_PAIR((j%6)+1));

                                }
                            }
                        }

                        wattroff(data->win, A_BOLD);
                    }
                }

            }
        }
    }

    wrefresh(data->win);

    if (data->command_mode) {
        open_menu(data);
    }
}
