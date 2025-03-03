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
#include "config.h"

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


    data->x = 0;
    data->y = 0;

    get_window_data(data);
    data->win = newwin(data->height, data->width, data->y, data->x);
    data->first_instruction = 0;
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

        switch (ch) {
            case 'q':
                return;
                break;
            case KEY_DOWN:
                data->first_instruction++;
                break;
            case KEY_UP:
                if (data->first_instruction > 0) {
                    data->first_instruction--;
                }
                break;
            default:
                break;
        }
        render(data, tables_array);
    }
}

void render(WindowData *data, InstructionTableArray *tables_array) {
    // clear screen
    werase(data->win);

    box(data->win, 0, 0);

    char title[32];

    sprintf(title, "Izumi v%s", VERSION);

    mvwprintw(data->win, 0, 0, title);

    // verical bar on 48 px for instruction info
    mvwvline(data->win, 1, 32, ACS_VLINE, data->height - 2);

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

    for (u_int64_t i = 0; i < data->height/2; i++) {
        u_int64_t index = data->first_instruction + i;
        Instruction instr = tables_array->tables[index/256]->content[index%256];

        if (instr.valid) {
            if (instr.mem_addr != NULL && (2*i + 1) < data->height - 1) {
                mvwprintw(data->win, 2*i + 1, 1, "%lu\t%s", index, instr.mem_addr);
            }
            if (instr.instruction != NULL && (2*i + 2) < data->height - 1) {
                mvwprintw(data->win, 2*i + 2, 5, "%s", instr.instruction);


            }

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


    wrefresh(data->win);
}
