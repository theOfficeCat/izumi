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

#include <complex.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include "window.h"
#include "config.h"
#include "interact.h"

void get_window_data(WindowData *win_data, ApplicationData *app_data) {
    win_data->width = getmaxx(stdscr);
    win_data->height = (getmaxy(stdscr)-1)/app_data->windows_qtty; // one pixel for the status bar

    win_data->x = 0;
    win_data->y = win_data->height * win_data->index;
}

void new_window(ApplicationData *app_data) {
    WindowData *win_data = malloc(sizeof(WindowData));
    win_data->index = app_data->windows_qtty;

    app_data->windows_qtty++;
    app_data->windows = realloc(app_data->windows, app_data->windows_qtty * sizeof(WindowData *));
    app_data->windows[app_data->windows_qtty - 1] = win_data;

    get_window_data(win_data, app_data);

    win_data->win = newwin(win_data->height, win_data->width, win_data->y, win_data->x);

    win_data->filename = NULL;
    win_data->first_instruction = 0;

    win_data->tables_array = malloc(sizeof(InstructionTableArray));
    win_data->tables_array->qtty_tables = 0;
    win_data->tables_array->avail_tables = 0;
    win_data->tables_array->tables = NULL;

    win_data->last_search.pattern = NULL;
    win_data->last_search.data_kind = PC;

    app_data->window_focused = app_data->windows_qtty - 1;
}

void close_window(WindowData *win_data) {
    if (win_data->tables_array != NULL) {
        free_InstructionTableArray(win_data->tables_array);
        free(win_data->tables_array);
        win_data->tables_array = NULL;
    }

    if (win_data->win != NULL) {
        delwin(win_data->win);
        win_data->win = NULL;
    }

    if (win_data->filename != NULL) {
        free(win_data->filename);
        win_data->filename = NULL;
    }

    if (win_data->last_search.pattern != NULL) {
        free(win_data->last_search.pattern);
        win_data->last_search.pattern = NULL;
    }

    free(win_data);
    win_data = NULL;
}

void close_application(ApplicationData *app_data) {
    for (uint64_t i = 0; i < app_data->windows_qtty; i++) {
        if (app_data->windows[i] != NULL) {
            close_window(app_data->windows[i]);
        }
    }

    app_data->windows_qtty = 0;
    free(app_data->windows);
    app_data->windows = NULL;

    endwin();
    exit(0);
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

    app_data->mode = NORMAL;
    app_data->command = NULL;
    app_data->windows_synced = false;

    app_data->config.bar_offset = 32;
    app_data->config.stage_width = 3;

    app_data->quit_requested = false;
}

void main_loop(ApplicationData *app_data) {
    render(app_data);
    while (!app_data->quit_requested) {

        parse_input(app_data, getch());
        render(app_data);
    }
}

void print_instruction(WindowData *win_data, Configuration *config, Instruction *inst, uint64_t y, uint64_t *first_cycle) {
    if (inst != NULL && inst->valid) {
        if (inst->mem_addr != NULL) {
            mvwprintw(win_data->win, y, 1, "%lu\t%s", *first_cycle, inst->mem_addr);
        }
        if (inst->instruction != NULL) {
            mvwprintw(win_data->win, y+1, 1, "\t%s", inst->instruction);
        }
    }

    mvwprintw(win_data->win, y,   config->bar_offset, "|");
    mvwprintw(win_data->win, y+1, config->bar_offset, "|");

    if (inst != NULL && inst->valid && inst->stages != NULL) {
        for (uint64_t i = 0; i < inst->qtty_stages; ++i) {
            Stage *stage = &inst->stages[i];

            if (stage->cycle < *first_cycle) {
                *first_cycle = stage->cycle;
            }

            uint64_t stage_offset = config->bar_offset + 2 + (config->stage_width + 1)*(stage->cycle - *first_cycle);

            wattron(win_data->win, COLOR_PAIR(i%6 + 1));


            if (strlen(stage->name) < config->stage_width) {
                mvwprintw(win_data->win, y+1, stage_offset, "%s", stage->name);

                for (uint64_t j = strlen(stage->name); j < config->stage_width; ++j) {
                    mvwprintw(win_data->win, y+1, stage_offset+j, " ");
                }
            }
            else {
                char *name_short = malloc(sizeof(char) * (config->stage_width + 1));

                strncpy(name_short, stage->name, config->stage_width);
                name_short[config->stage_width] = '\0';

                mvwprintw(win_data->win, y+1, stage_offset, "%s", name_short);
            }

            if (stage->duration > 1) {
                for (uint64_t j = 1; j < stage->duration; ++j) {
                    for (uint64_t k = 0; k < config->stage_width + 1; ++k) {
                        mvwprintw(win_data->win, y+1, stage_offset+(config->stage_width+1)*j - 1+k, " ");
                    }
                }
            }

            wattroff(win_data->win, COLOR_PAIR(i%6 + 1));
        }
    }
}

void render_window(ApplicationData *app_data, WindowData *win_data) {
    werase(win_data->win);

    get_window_data(win_data, app_data);

    wresize(win_data->win, win_data->height, win_data->width);
    mvwin(win_data->win, win_data->y, win_data->x);

    for (uint64_t i = app_data->config.bar_offset + 1; i < win_data->width; i += app_data->config.stage_width + 1) {
        for (uint64_t j = 0; j < win_data->height; ++j) {
            mvwprintw(win_data->win, j, i, "|");
        }
    }

    uint64_t cycle = UINT64_MAX;

    if (win_data->tables_array != NULL) {
        for (uint64_t i = 0; i < (win_data->height-1)/2; ++i) {
            Instruction *inst = NULL;

            uint64_t index = win_data->first_instruction + i;

            if (index/256 < win_data->tables_array->qtty_tables) {
                if (win_data->tables_array->tables[index/256] != NULL) {
                    inst = &win_data->tables_array->tables[index/256]->content[index%256];
                }
            }

            print_instruction(win_data, &app_data->config, inst, i*2+1, &cycle);
        }
    }

    box(win_data->win, 0, 0);

    if (win_data->filename != NULL) {
        if (win_data->index == app_data->window_focused) {
            wattron(win_data->win, A_BOLD);
        }

        mvwprintw(win_data->win, 0, 1, "%s", win_data->filename);

        if (win_data->index == app_data->window_focused) {
            wattroff(win_data->win, A_BOLD);
        }
    }

    wrefresh(win_data->win);
}

void render_status_bar(ApplicationData *app_data) {
    // TODO: find a better way
    char clear_status_bar[getmaxx(stdscr) + 1];

    for (int i = 0; i < getmaxx(stdscr); ++i) {
        clear_status_bar[i] = ' ';
    }

    clear_status_bar[getmaxx(stdscr)] = '\0';

    mvprintw(getmaxy(stdscr)-1, 0, "%s", clear_status_bar);

    char *version = VERSION;

    uint64_t length = strlen(version);

    attron(A_BOLD);
    attron(COLOR_PAIR(16));
    mvprintw(getmaxy(stdscr)-1, getmaxx(stdscr) - 7 - length, "Izumi v%s", version);
    attroff(COLOR_PAIR(16));

    attron(COLOR_PAIR(1));
    char *mode;

    switch (app_data->mode) {
        case NORMAL:
            mode = "NORMAL";
            break;
        case COMMAND:
            mode = "COMMAND";
            break;
    }

    mvprintw(getmaxy(stdscr)-1, 0, " %s ", mode);
    attroff(COLOR_PAIR(1));
    attroff(A_BOLD);

    if (app_data->mode == COMMAND) {
        mvprintw(getmaxy(stdscr)-1, 11, ":%s", app_data->command);
    }

}

void render(ApplicationData *app_data) {
    for (uint64_t i = 0; i < app_data->windows_qtty; i++) {
        if (app_data->windows[i] != NULL && app_data->windows[i]->win != NULL) {
            render_window(app_data, app_data->windows[i]);
        }
    }

    render_status_bar(app_data);

    refresh();
}
