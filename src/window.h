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

#include <ncurses.h>
#include <stdint.h>
#include <unistd.h>
#include <stdint.h>

#include "data_structs.h"
#include "commands.h"

struct Configuration_s {
    uint64_t bar_offset;
};

enum Mode_e {
    NORMAL,
    COMMAND
};

typedef enum Mode_e Mode;

typedef struct Configuration_s Configuration;

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
};

typedef struct WindowData_s WindowData;

struct ApplicationData_s {
    WindowData **windows;
    uint64_t windows_qtty;
    uint64_t window_focused;

    Configuration config;

    Mode mode;

    char *command;
};

typedef struct ApplicationData_s ApplicationData;

void new_window(ApplicationData *app_data);

void init_application(ApplicationData *app_data);

void main_loop(ApplicationData *app_data);

void render_status_bar(ApplicationData *app_data);

void render(ApplicationData *app_data);

void render_window(ApplicationData *app_data, WindowData *win_data);

void print_instruction(WindowData *win_data, Configuration *config, Instruction *inst, uint64_t y, uint64_t *first_cycle);

void get_window_data(WindowData *win_data, ApplicationData *app_data);

void open_menu(ApplicationData *app_data);

void close_window(WindowData *win_data);

void close_application(ApplicationData *app_data);

#endif
