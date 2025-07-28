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

#include "system_curses.h"
#define _GNU_SOURCE

#include <linux/limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <izumi/finder.h>

#include "files.h"
#include "window.h"

bool newpanel_cb(ApplicationData *app_data) {
    new_window(app_data);
    return true;
}

bool closepanel_cb(ApplicationData *app_data, const int argc, const char * argv[]) {
    uint64_t panel_id;

    if (argc == 1) {
        panel_id = atoi(argv[0]);
    }
    else {
        panel_id = app_data->window_focused;
    }

    close_panel(app_data, panel_id);

    return true;
}

bool closeallpanels_cb(ApplicationData *app_data) {
    close_all_panels(app_data);

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


    if (app_data->windows[app_data->window_focused]->filename != NULL) {
        free(app_data->windows[app_data->window_focused]->filename);
    }

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

bool set_cb(ApplicationData *app_data, const int argc, const char *argv[]) {
    const char *config = argv[0];

    if (strcmp(config, "bar_offset") == 0) { // :set bar_offset (number)
        if (argc != 2) return false;
        const char *value = argv[1];
        app_data->config.bar_offset = atoi(value);
    }
    else if (strcmp(config, "stage_width") == 0) { // :set stage_width (number)
        if (argc != 2) return false;
        const char* value = argv[1];
        app_data->config.stage_width = atoi(value);
    }
    else if (strcmp(config, "color") == 0) { // :set color (element) blue|red|yellow|green|white|black|cyan|magenta blue|red|yellow|green|white|black|cyan|magenta <bold>
        if (argc != 4 && argc != 5) return false;

        const char* element = argv[1];
        const char* fg = argv[2];
        const char* bg = argv[3];

        bool set_bold = false;

        if (argc == 5) {
            const char* bold = argv[4];

            if (strcmp(bold, "bold") == 0) {
                set_bold = true;
            }
            else return false;
        }

        int color_idx = 0;

        if (strcmp(element, "commands")      == 0) color_idx = COLOR_COMMANDS;
        else if (strcmp(element, "box")      == 0) color_idx = COLOR_BOX;
        else if (strcmp(element, "text")     == 0) color_idx = COLOR_TEXT;
        else if (strcmp(element, "status")   == 0) color_idx = COLOR_STATUS;
        else if (strcmp(element, "stage1")   == 0) color_idx = COLOR_STAGES + 0;
        else if (strcmp(element, "stage2")   == 0) color_idx = COLOR_STAGES + 1;
        else if (strcmp(element, "stage3")   == 0) color_idx = COLOR_STAGES + 2;
        else if (strcmp(element, "stage4")   == 0) color_idx = COLOR_STAGES + 3;
        else if (strcmp(element, "stage5")   == 0) color_idx = COLOR_STAGES + 4;
        else if (strcmp(element, "stage6")   == 0) color_idx = COLOR_STAGES + 5;
        else return false;

        short set_fg = COLOR_BLACK;

        if (strcmp(fg, "black")        == 0) set_fg = COLOR_BLACK;
        else if (strcmp(fg, "white")   == 0) set_fg = COLOR_WHITE;
        else if (strcmp(fg, "red")     == 0) set_fg = COLOR_RED;
        else if (strcmp(fg, "green")   == 0) set_fg = COLOR_GREEN;
        else if (strcmp(fg, "yellow")  == 0) set_fg = COLOR_YELLOW;
        else if (strcmp(fg, "blue")    == 0) set_fg = COLOR_BLUE;
        else if (strcmp(fg, "cyan")    == 0) set_fg = COLOR_CYAN;
        else if (strcmp(fg, "magenta") == 0) set_fg = COLOR_MAGENTA;
        else return false;

        short set_bg = COLOR_BLACK;

        if (strcmp(bg, "black")        == 0) set_bg = COLOR_BLACK;
        else if (strcmp(bg, "white")   == 0) set_bg = COLOR_WHITE;
        else if (strcmp(bg, "red")     == 0) set_bg = COLOR_RED;
        else if (strcmp(bg, "green")   == 0) set_bg = COLOR_GREEN;
        else if (strcmp(bg, "yellow")  == 0) set_bg = COLOR_YELLOW;
        else if (strcmp(bg, "blue")    == 0) set_bg = COLOR_BLUE;
        else if (strcmp(bg, "cyan")    == 0) set_bg = COLOR_CYAN;
        else if (strcmp(bg, "magenta") == 0) set_bg = COLOR_MAGENTA;
        else return false;

        set_color(app_data, color_idx, set_bg, set_fg, set_bold);
        apply_colors(app_data);
    }


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

    if (app_data->windows[app_data->window_focused]->last_search.pattern != NULL) {
        free(app_data->windows[app_data->window_focused]->last_search.pattern);
    }

    app_data->windows[app_data->window_focused]->last_search.pattern = malloc(strlen(pattern) + 1);

    strcpy(app_data->windows[app_data->window_focused]->last_search.pattern, pattern);

    app_data->windows[app_data->window_focused]->last_search.data_kind = PC;

    return true;
}

bool findinst_cb(ApplicationData *app_data, const char * argv[]) {
    const char *pattern = argv[0];

    if (app_data->windows == NULL) return false;

    FindResult result = find(app_data->windows[app_data->window_focused]->tables_array, pattern, INST, DOWN, app_data->windows[app_data->window_focused]->first_instruction);
    if (!result.valid) return false;

    app_data->windows[app_data->window_focused]->first_instruction = result.position;

    if (app_data->windows[app_data->window_focused]->last_search.pattern != NULL) {
        free(app_data->windows[app_data->window_focused]->last_search.pattern);
    }

    app_data->windows[app_data->window_focused]->last_search.pattern = malloc(strlen(pattern) + 1);

    strcpy(app_data->windows[app_data->window_focused]->last_search.pattern, pattern);

    app_data->windows[app_data->window_focused]->last_search.data_kind = INST;

    return true;
}

bool next_cb(ApplicationData *app_data) {
    if (app_data->windows == NULL) return false;

    if (app_data->windows[app_data->window_focused]->last_search.pattern == NULL) return false;

    char *pattern = app_data->windows[app_data->window_focused]->last_search.pattern;

    FindResult result = find(app_data->windows[app_data->window_focused]->tables_array, pattern, app_data->windows[app_data->window_focused]->last_search.data_kind, DOWN, app_data->windows[app_data->window_focused]->first_instruction + 1);
    if (!result.valid) return false;

    app_data->windows[app_data->window_focused]->first_instruction = result.position;

    return true;
}

bool prev_cb(ApplicationData *app_data) {
    if (app_data->windows == NULL) return false;

    if (app_data->windows[app_data->window_focused]->last_search.pattern == NULL) return false;

    char *pattern = app_data->windows[app_data->window_focused]->last_search.pattern;

    if (app_data->windows[app_data->window_focused]->first_instruction <= 0) return false;

    FindResult result = find(app_data->windows[app_data->window_focused]->tables_array, pattern, app_data->windows[app_data->window_focused]->last_search.data_kind, UP, app_data->windows[app_data->window_focused]->first_instruction - 1);
    if (!result.valid) return false;

    app_data->windows[app_data->window_focused]->first_instruction = result.position;

    return true;
}

bool quit_cb(ApplicationData *app_data) {
    app_data->quit_requested = true;
    return true;
}
