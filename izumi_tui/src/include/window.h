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

#ifndef WINDOW_H
#define WINDOW_H

#include <izumi/finder.h>
#include "system_curses.h"
#include <stdint.h>
#include <unistd.h>
#include <stdint.h>

#include <izumi/data_structs.h>

struct ColorData_s {
    short fg;
    short bg;
    bool bold;
};

typedef struct ColorData_s ColorData;

#define COLORS_AMOUNT 10
#define COLOR_COMMANDS 0
#define COLOR_BOX 1
#define COLOR_TEXT 2
#define COLOR_STATUS 3
#define COLOR_STAGES 4

struct Configuration_s {
    uint64_t bar_offset;
    uint64_t stage_width;

    // 0: commands, 1: box, 2: text, 3: status, 4-9: stages
    ColorData colors[COLORS_AMOUNT];
};

typedef struct Configuration_s Configuration;

enum Mode_e {
    NORMAL,
    COMMAND
};

typedef enum Mode_e Mode;

struct SearchData_s {
    char *pattern;
    FindDataKind data_kind;
};

typedef struct SearchData_s SearchData;

struct WindowData_s {
    uint64_t x;
    uint64_t y;
    uint64_t width;
    uint64_t height;

    WINDOW *win;
    uint64_t index;

    InstructionTableArray *tables_array;

    uint64_t first_instruction;

    char *filename;

    SearchData last_search; // used for next appearance of searched element
};

typedef struct WindowData_s WindowData;

struct ApplicationData_s {
    WindowData **windows;
    uint64_t windows_qtty;
    uint64_t window_focused;

    Configuration config;

    Mode mode;

    char *command;
    uint64_t number;

    bool windows_synced;

    bool quit_requested;
};

typedef struct ApplicationData_s ApplicationData;

void new_window(ApplicationData *app_data);

void init_application(ApplicationData *app_data);

void main_loop(ApplicationData *app_data);

void render_status_bar(ApplicationData *app_data);

void render(ApplicationData *app_data);

void render_window(ApplicationData *app_data, WindowData *win_data);

void print_instruction(ApplicationData *app_data, WindowData *win_data, Configuration *config, Instruction *inst, uint64_t y, uint64_t *first_cycle, uint64_t index);

void get_window_data(WindowData *win_data, ApplicationData *app_data);

void open_menu(ApplicationData *app_data);

void close_window(WindowData *win_data);

void close_application(ApplicationData *app_data);

void close_panel(ApplicationData *app_data, uint64_t panel_id);

void close_all_panels(ApplicationData *app_data);

void set_color(ApplicationData *app_data, uint64_t index, short fg, short bg, bool bold);

void apply_colors(ApplicationData *app_data);

void enable_colors_app(ApplicationData *app_data, uint64_t index);

void disable_colors_app(ApplicationData *app_data, uint64_t index);

void enable_colors_win(ApplicationData *app_data, WindowData *win_data, uint64_t index);

void disable_colors_win(ApplicationData *app_data, WindowData *win_data, uint64_t index);

#endif
