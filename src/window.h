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

/*
 * WindowData
 * 
 * This struct is used to store the data of the window.
 * 
 * x: The x position of the window.
 * y: The y position of the window.
 * width: The width of the window.
 * height: The height of the window.
 * first_instruction: The index of the first instruction to be displayed.
 * 
 * win: The window.
 * 
 * menu_data: The data of the open menu.
 * main_menu: The main menu data.
 * file_menu: The file menu data.
 * 
 * menu_win: The menu window.
 */
struct WindowData_s {
    u_int64_t x;
    u_int64_t y;
    u_int64_t width;
    u_int64_t height;
    u_int64_t first_instruction;

    WINDOW *win;

    //MenuOpen menu_data;
    bool command_mode;

    bool file_loaded;

    WINDOW *menu_win;

    char *command;
    u_int64_t command_size;
};

typedef struct WindowData_s WindowData;

/*
 * This function initializes the window.
 * 
 * data: The window data.
 */
void init_window(WindowData *data);

/*
 * This function closes the window.
 */
void close_window();

/*
 * This function is the main loop of the program.
 * 
 * data: The window data.
 * tables_array: The array of tables.
 */
void main_loop(WindowData *data, InstructionTableArray *tables_array);

/*
 * This function renders the window.
 * 
 * data: The window data.
 * tables_array: The array of tables.
 */
void render(WindowData *data, InstructionTableArray *tables_array);

/*
 * This function gets the window data.
 * 
 * data: The window data.
 */
void get_window_data(WindowData *data);

/*
 * This function moves down the menu.
 * 
 * menu: The menu data.
 */
void open_menu(WindowData *data);


#endif