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
#include <sys/types.h>

#include "window.h"
#include "config.h"
#include "commands.h"

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

    win_data->tables_array = NULL;
}

void close_application(ApplicationData *app_data) {
    for (uint64_t i = 0; i < app_data->windows_qtty; i++) {
        if (app_data->windows[i] != NULL) {
            if (app_data->windows[i]->tables_array != NULL) {
                free_InstructionTableArray(app_data->windows[i]->tables_array);
                app_data->windows[i]->tables_array = NULL;
            }

            if (app_data->windows[i]->win != NULL) {
                delwin(app_data->windows[i]->win);
                app_data->windows[i]->win = NULL;
            }

            if (app_data->windows[i]->filename != NULL) {
                free(app_data->windows[i]->filename);
                app_data->windows[i]->filename = NULL;
            }

            free(app_data->windows[i]);
            app_data->windows[i] = NULL;
        }
    }

    app_data->windows_qtty = 0;
    free(app_data->windows);
    app_data->windows = NULL;

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
}

void main_loop(ApplicationData *app_data) {
    while (1) {

        render(app_data);
    }
}

void open_menu(ApplicationData *app_data) {
}

void render_window(ApplicationData *app_data, WindowData *win_data) {
    get_window_data(win_data, app_data);

    wresize(win_data->win, win_data->height, win_data->width);
    mvwin(win_data->win, win_data->y, win_data->x);

    werase(win_data->win);
    box(win_data->win, 0, 0);

    wrefresh(win_data->win);
}

void render_status_bar(void) {
    char *version = VERSION;

    uint64_t length = strlen(version);

    attron(A_BOLD);
    attron(COLOR_PAIR(16));
    mvprintw(getmaxy(stdscr)-1, getmaxx(stdscr) - 7 - length, "Izumi v%s", version);
    attroff(COLOR_PAIR(16));
    attroff(A_BOLD);
}

void render(ApplicationData *app_data) {
    for (uint64_t i = 0; i < app_data->windows_qtty; i++) {
        if (app_data->windows[i] != NULL && app_data->windows[i]->win != NULL) {
            render_window(app_data, app_data->windows[i]);
        }
    }

    render_status_bar();

    refresh();
}
