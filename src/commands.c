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

#include <linux/limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "commands.h"
#include "files.h"
#include "window.h"

bool run_command(ApplicationData *app_data) {
    char *command;
    sscanf(app_data->command, "%ms", &command);

    bool valid_command = false;

    fprintf(stderr, "%s", command);

    if (strcmp(command, "newpanel") == 0) {
        valid_command = true;
        new_window(app_data);
    }
    else if (strcmp(command, "open") == 0) {
        char *file_name;
        sscanf(app_data->command, "open %ms", &file_name);

        if (app_data->windows != NULL) {
            char *path = realpath(file_name, NULL);

            FileData file_data = check_file(path);

            if (file_data.exists && file_data.is_file) {
                app_data->windows[app_data->window_focused]->filename = read_file(file_name, app_data->windows[app_data->window_focused]->tables_array);
            }

            free(path);
            path = NULL;

            valid_command = true;
        }

        free(file_name);
    }
    else if (strcmp(command, "panelcmd") == 0) {
        char *panel_command;
        sscanf(app_data->command, "panelcmd %ms", &panel_command);

        if (strcmp(panel_command, "j") == 0) {
            if (app_data->window_focused < app_data->windows_qtty - 1) {
                app_data->window_focused++;
            }
        }
        else if (strcmp(panel_command, "k") == 0) {
            if (app_data->window_focused > 0) {
                app_data->window_focused--;
            }
        }
    }
    else if (strcmp(command, "set") == 0) {
        char *option;
        char *value;
        sscanf(app_data->command, "set %ms %ms", &option, &value);

        if (strcmp(option, "bar_offset") == 0) {
            app_data->config.bar_offset = atoi(value);
        }
        else if (strcmp(option, "stage_width") == 0) {
            app_data->config.stage_width = atoi(value);
        }

        free(option);
        free(value);

        valid_command = true;
    }
    else if (strcmp(command, "panelsync") == 0) {
        app_data->windows_synced = !app_data->windows_synced;

        valid_command = true;
    }
    else if (strcmp(command, "paneldesync") == 0) {
        app_data->windows_synced = false;

        valid_command = true;
    }
    else if (strcmp(command, "quit") == 0 || strcmp(command, "q") == 0) {
        free(command);

        close_application(app_data);
    }

    free(command);

    return valid_command;
}
