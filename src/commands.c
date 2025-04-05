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

#define _GNU_SOURCE

#include <linux/limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "files.h"
#include "window.h"
#include "finder.h"

bool newpanel_cb(ApplicationData *app_data) {
    new_window(app_data);
    return true;
}

bool open_cb(ApplicationData *app_data, const char * argv[]) {
    const char *file_name = argv[0];

    if (app_data->windows == NULL) {
        new_window(app_data);
    }

    char *path = realpath(file_name, NULL);
    FileData file_data = check_file(path);
    free(path);
    path = NULL;

    if (!file_data.exists || !file_data.is_file) return false;

    app_data->windows[app_data->window_focused]->filename = read_file(file_name, app_data->windows[app_data->window_focused]->tables_array);
    return true;
}

bool panelcmd_j_cb(ApplicationData *app_data) {
    if (app_data->window_focused < app_data->windows_qtty - 1) {
        app_data->window_focused++;
    }
    
    return true;
}

bool panelcmd_k_cb(ApplicationData *app_data) {
    if (app_data->window_focused > 0) {
        app_data->window_focused--;
    }

    return true;
}

bool set_cb(ApplicationData *app_data, const char * argv[]) {
    const char *option = argv[0];
    const char *value = argv[1];

    if (strcmp(option, "bar_offset") == 0) {
        app_data->config.bar_offset = atoi(value);
    }
    else if (strcmp(option, "stage_width") == 0) {
        app_data->config.stage_width = atoi(value);
    }
    else return false;

    return true;
}

bool panelsync_cb(ApplicationData *app_data) {
    app_data->windows_synced = true;
    return true;
}

bool paneldesync_cb(ApplicationData *app_data) {
    app_data->windows_synced = false;
    return true;
}

bool findpc_cb(ApplicationData *app_data, const char * argv[]) {
    const char *pattern = argv[0];
    
    if (app_data->windows == NULL) return false;

    FindResult result = find(app_data->windows[app_data->window_focused]->tables_array, pattern, PC, DOWN, app_data->windows[app_data->window_focused]->first_instruction);
    if (!result.valid) return false;
    
    app_data->windows[app_data->window_focused]->first_instruction = result.position;

    if (app_data->windows[app_data->window_focused]->last_search != NULL) {
        free(app_data->windows[app_data->window_focused]->last_search);
    }

    app_data->windows[app_data->window_focused]->last_search = malloc(strlen(app_data->command) + 1);

    strcpy(app_data->windows[app_data->window_focused]->last_search, app_data->command);

    return true;
}

bool findinst_cb(ApplicationData *app_data, const char * argv[]) {
    const char *pattern = argv[0];
    
    if (app_data->windows == NULL) return false;
    
    FindResult result = find(app_data->windows[app_data->window_focused]->tables_array, pattern, INST, DOWN, app_data->windows[app_data->window_focused]->first_instruction);
    if (!result.valid) return false;
    
    app_data->windows[app_data->window_focused]->first_instruction = result.position;

    if (app_data->windows[app_data->window_focused]->last_search != NULL) {
        free(app_data->windows[app_data->window_focused]->last_search);
    }

    app_data->windows[app_data->window_focused]->last_search = malloc(strlen(app_data->command) + 1);

    strcpy(app_data->windows[app_data->window_focused]->last_search, app_data->command);

    return true;
}

bool quit_cb(ApplicationData *app_data) {
    app_data->quit_requested = true;
    return true;
}
