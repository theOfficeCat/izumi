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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "data_structs.h"
#include "settings.h"

struct WindowData_s {
    u_int64_t x;
    u_int64_t y;
    u_int64_t width;
    u_int64_t height;
    u_int64_t first_instruction;
    WINDOW *win;

    MenuData menu;
    WINDOW *menu_win;
};

typedef struct WindowData_s WindowData;

void init_window(WindowData *data);

void close_window();

void main_loop(WindowData *data, InstructionTableArray *tables_array);

void render(WindowData *data, InstructionTableArray *tables_array);

void get_window_data(WindowData *data);

void open_menu(WindowData *data);

void use_menu(WindowData *data, InstructionTableArray *tables_array);

#endif