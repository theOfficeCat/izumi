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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "window.h"
#include "config.h"
#include "commands.h"

void get_window_data(WindowData *win_data, ApplicationData *app_data, bool first) {
    uint64_t new_width = getmaxx(stdscr);
    uint64_t new_height = getmaxy(stdscr)/app_data->windows_qtty;

    if (new_width != win_data->width || new_height != win_data->height) {
        win_data->width = new_width;
        win_data->height = new_height;

        // TODO: redo this on a better way
        //if (!first) {
        //    wresize(win_data->win, win_data->height, win_data->width);
        //}
    }

    win_data->x = 0;
    win_data->y = win_data->height * app_data->window_focused;
}

void init_window(WindowData *win_data, ApplicationData *app_data) {
    win_data->x = 0;
    win_data->y = 0;

    get_window_data(win_data, app_data, true);

    win_data->win = newwin(win_data->height, win_data->width, win_data->y, win_data->x);
    win_data->first_instruction = 0;
    win_data->file_loaded = false;
    win_data->last_pc = malloc(19);
    win_data->last_pc_index = -1;

    win_data->last_inst = malloc(64);
    win_data->last_inst_index = -1;

    win_data->search_mode = NONE;
}

void close_window() {
    endwin();
}

void init_application(ApplicationData *app_data) {
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

    app_data->windows = NULL;
    app_data->windows_qtty = 0;
    app_data->window_focused = 0;

    app_data->menu_win = newwin(3, getmaxx(stdscr), getmaxy(stdscr) - 3, 0);

    app_data->command = NULL;
    app_data->command_size = 0;
    app_data->command_mode = false;
}

void add_window(ApplicationData *app_data, WindowData *win_data) {
    app_data->windows_qtty++;
    app_data->windows = realloc(app_data->windows, app_data->windows_qtty * sizeof(WindowData*));
    app_data->windows[app_data->windows_qtty - 1] = win_data;
    app_data->window_focused = app_data->windows_qtty - 1;

    init_window(win_data, app_data);

    for (uint64_t i = 0; i < app_data->windows_qtty; ++i) {
        wresize(app_data->windows[i]->win, getmaxy(stdscr)/app_data->windows_qtty, getmaxx(stdscr));
    }

}

void main_loop(ApplicationData *app_data, WindowData *win_data, InstructionTableArray *tables_array) {
    int ch;

    render(app_data, win_data, tables_array);
    while (1) {
        get_window_data(win_data, app_data, false);

        ch = getch();

        if (app_data->command_mode) {
            if (ch == 27) {
                app_data->command_mode = false;
                free(app_data->command);
                app_data->command = NULL;
                app_data->command_size = 0;
            }
            else if (ch == KEY_BACKSPACE) {
                if (app_data->command_size > 1) {
                    app_data->command[app_data->command_size - 1] = '\0';
                    app_data->command_size--;
                }
            }
            else if (ch == '\n') {
                char command[65];
                sscanf(app_data->command, "%64s", command);

                if (strcmp(command, ":q") == 0 || strcmp(command, ":quit") == 0) {
                    close_window();
                    exit(0);
                }
                else if (strcmp(command, ":open") == 0) {
                    if (open_file(app_data->command, command, tables_array)) {
                        win_data->file_loaded = true;
                    }
                }
                else if (strcmp(command, ":fpc") == 0) {
                    char *pc = NULL;
                    win_data->first_instruction = find_pc(app_data->command, tables_array, win_data->first_instruction + 1, &pc, DOWN);

                    strcpy(win_data->last_pc, pc);

                    win_data->last_pc_index = win_data->first_instruction;

                    win_data->search_mode = PC;
                }
                else if (strcmp(command, ":finst") == 0) {
                    char *inst = NULL;
                    win_data->first_instruction = find_inst(app_data->command, tables_array, win_data->first_instruction + 1, &inst, DOWN);

                    strcpy(win_data->last_inst, inst);

                    win_data->last_inst_index = win_data->first_instruction;

                    win_data->search_mode = INST;
                }
                else if (strcmp(command, ":newpanel") == 0) {
                    WindowData *win_data = malloc(sizeof(WindowData));
                    init_window(win_data, app_data);
                    add_window(app_data, win_data);
                }

                app_data->command_mode = false;
                free(app_data->command);
                app_data->command = NULL;
                app_data->command_size = 0;

            }
            else {
                app_data->command = realloc(app_data->command, app_data->command_size + 2);
                app_data->command_size++;
                app_data->command[app_data->command_size - 1] = ch;
                app_data->command[app_data->command_size] = '\0';
            }

        }

        switch (ch) {
            case 'q':
                break;
            case KEY_DOWN:
            case 'j':
                win_data->first_instruction++;
                break;
            case KEY_UP:
            case 'k':
                if (win_data->first_instruction > 0) {
                    win_data->first_instruction--;
                }
                break;
            case KEY_LEFT:
                break;
            case KEY_RIGHT:
                break;
            case '\n': // Enter
                break;
            case ':':
                if (!app_data->command_mode) {
                    app_data->command_mode = true;
                    char *comm = ":";
                    app_data->command_size = 1;
                    app_data->command = malloc(app_data->command_size + 1);
                    strcpy(app_data->command, comm);
                }
                break;
            case 'n':
                if (win_data->search_mode == PC) {
                    if (win_data->last_pc_index != UINT64_MAX) {
                        char dummy_command[24] = ":fpc ";
                        strcat(dummy_command, win_data->last_pc);

                        win_data->first_instruction = find_pc(dummy_command, tables_array, win_data->last_pc_index + 1, &win_data->last_pc, DOWN);
                        win_data->last_pc_index = win_data->first_instruction;
                    }
                }
                else if (win_data->search_mode == INST) {
                    if (win_data->last_inst_index != UINT64_MAX) {
                        char dummy_command[128] = ":finst ";
                        strcat(dummy_command, win_data->last_inst);

                        win_data->first_instruction = find_inst(dummy_command, tables_array, win_data->last_inst_index + 1, &win_data->last_inst, DOWN);
                        win_data->last_inst_index = win_data->first_instruction;
                    }
                }
                break;
            case 'N':
                if (win_data->search_mode == PC) {
                    if (win_data->last_pc_index != UINT64_MAX) {
                        char dummy_command[24] = ":fpc ";
                        strcat(dummy_command, win_data->last_pc);

                        win_data->first_instruction = find_pc(dummy_command, tables_array, win_data->last_pc_index - 1, &win_data->last_pc, UP);
                        win_data->last_pc_index = win_data->first_instruction;
                    }
                }
                else if (win_data->search_mode == INST) {
                    if (win_data->last_inst_index != UINT64_MAX) {
                        char dummy_command[128] = ":finst ";
                        strcat(dummy_command, win_data->last_inst);

                        win_data->first_instruction = find_inst(dummy_command, tables_array, win_data->last_inst_index - 1, &win_data->last_inst, UP);
                        win_data->last_inst_index = win_data->first_instruction;
                    }
                }
                break;
            default:
                break;
        }
        fprintf(stderr, "rendering\n");
        for (u_int64_t i = 0; i < app_data->windows_qtty; ++i) {
            fprintf(stderr, "%lu\n", i);
            fprintf(stderr, "pointers: &app_data->windows[i] = %p; win_data = %p\n", app_data->windows[i], win_data);
            app_data->window_focused = i;
            render(app_data, app_data->windows[i], tables_array);
        }
    }
}

void open_menu(ApplicationData *app_data) {
    werase(app_data->menu_win);

    box(app_data->menu_win, 0, 0);

    //wbkgd(win_data->menu_win, COLOR_PAIR(16));

    mvwprintw(app_data->menu_win, 1, 1, "%s", app_data->command);

    wrefresh(app_data->menu_win);
}

void render(ApplicationData *app_data, WindowData *win_data, InstructionTableArray *tables_array) {
    // clear screen
    werase(win_data->win);

    box(win_data->win, 0, 0);

    mvwprintw(win_data->win, 0, 0, "Izumi v%s", VERSION);

    // verical bar on 32 px for instruction info
    mvwvline(win_data->win, 1, 32, ACS_VLINE, win_data->height - 2);

    if (win_data->file_loaded) {
        // print instructions data

        u_int64_t first_cycle = -1;

        //build grid
        for (u_int64_t i = 1; i < win_data->height - 1; i++) {
            for (u_int64_t j = 0; j < win_data->width - 1; j++) {
                if (j >32 && j%3 == 0) {
                    mvwprintw(win_data->win, i, j, "|");
                }
            }
        }

        // print instructions
        for (u_int64_t i = 0; i < win_data->height/2; i++) {
            u_int64_t index = win_data->first_instruction + i;
            Instruction instr = tables_array->tables[index/256]->content[index%256];

            // memory address and instruction
            if (instr.valid) {
                if (instr.mem_addr != NULL && (2*i + 1) < win_data->height - 1) {
                    mvwprintw(win_data->win, 2*i + 1, 1, "%lu\t%s", index, instr.mem_addr);
                }
                if (instr.instruction != NULL && (2*i + 2) < win_data->height - 1) {
                    mvwprintw(win_data->win, 2*i + 2, 5, "%s", instr.instruction);
                }

                // stages
                if ((2*i + 2) < win_data->height - 1) {
                    for (u_int64_t j = 0; j < instr.qtty_stages; j++) {
                        if (instr.stages[j].cycle < first_cycle) {
                            first_cycle = instr.stages[j].cycle;
                        }
                        Stage *stage = &instr.stages[j];

                        wattron(win_data->win, A_BOLD);

                        if (33 + 3*(stage->cycle - first_cycle) + 3 < win_data->width - 1) {
                            mvwprintw(win_data->win, 2*i + 2, 33 + 3*(stage->cycle - first_cycle), "|");
                            wattron(win_data->win, COLOR_PAIR((j%6)+1));
                            mvwprintw(win_data->win, 2*i + 2, 33 + 3*(stage->cycle - first_cycle) + 1, "%s", stage->name);

                            if (strlen(stage->name) == 1) {
                                mvwprintw(win_data->win, 2*i + 2, 33 + 3*(stage->cycle - first_cycle) + 2, " ");
                            }
                            wattroff(win_data->win, COLOR_PAIR((j%6)+1));
                        }

                        // extra cycles
                        if (stage->duration > 1) {
                            for (u_int64_t k = 0; k < stage->duration - 1; k++) {
                                if (33 + 3*(stage->cycle - first_cycle) + 3*(k+1) < win_data->width - 4) {
                                    wattron(win_data->win, COLOR_PAIR(8+(j%6)+1));
                                    mvwprintw(win_data->win, 2*i + 2, 33 + 3*(stage->cycle - first_cycle) + 3*(k+1), "|");
                                    wattroff(win_data->win, COLOR_PAIR(8+(j%6)+1));

                                    wattron(win_data->win, COLOR_PAIR((j%6)+1));
                                    mvwprintw(win_data->win, 2*i + 2, 33 + 3*(stage->cycle - first_cycle) + 3*(k+1) + 1, "  ");
                                    wattroff(win_data->win, COLOR_PAIR((j%6)+1));

                                }
                            }
                        }

                        wattroff(win_data->win, A_BOLD);
                    }
                }

            }
        }
    }

    wrefresh(win_data->win);

    if (app_data->command_mode) {
        open_menu(app_data);
    }
}
