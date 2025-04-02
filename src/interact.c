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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interact.h"
#include "window.h"

bool parse_input(ApplicationData *app_data, int ch) {
    if (app_data->mode == NORMAL) {
        switch (ch) {
            case 'j':
                app_data->windows[app_data->window_focused]->first_instruction++;
                break;
            case 'k':
                if (app_data->windows[app_data->window_focused]->first_instruction > 0) {
                    app_data->windows[app_data->window_focused]->first_instruction--;
                }
                break;
            case ':':
                app_data->mode = COMMAND;

                if (app_data->command != NULL) {
                    free(app_data->command);
                }

                app_data->command = malloc(1);
                app_data->command[0] = '\0';
                break;
            default:
                break;
        }
    }
    else if (app_data->mode == COMMAND) {
        int len;
        switch (ch) {
            case 27: // Escape
                app_data->mode = NORMAL;
                break;
            case '\n': // Enter
                app_data->mode = NORMAL;
                break;
            case KEY_BACKSPACE: // Backspace
                if (strlen(app_data->command) > 0) {
                    int len = strlen(app_data->command);

                    app_data->command = realloc(app_data->command, sizeof(char) * len);
                    app_data->command[len - 1] = '\0';
                }
                break;
            default:
                len = strlen(app_data->command);

                app_data->command = realloc(app_data->command, sizeof(char) * (len + 2));
                app_data->command[len + 1] = '\0';
                app_data->command[len] = ch;
                break;
        }
    }

    return true;
}
