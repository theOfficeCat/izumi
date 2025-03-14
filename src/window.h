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
#include "commands.h"

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
 * 
 * command: The command that the user is typing.
 * command_size: The size of the command.
 * 
 * last_pc: The last PC searched.
 * last_pc_index: The index of the last PC searched.
 * 
 * last_inst: The last instruction searched.
 * last_inst_index: The index of the last instruction searched.
 * 
 * search_mode: The mode of the search.
 */
struct WindowData_s {
    u_int64_t x;
    u_int64_t y;
    u_int64_t width;
    u_int64_t height;
    u_int64_t first_instruction;

    WINDOW *win;

    bool file_loaded;

    char *last_pc;
    u_int64_t last_pc_index;

    char *last_inst;
    u_int64_t last_inst_index;

    SearchMode search_mode;
};

typedef struct WindowData_s WindowData;

struct ApplicationData_s {
    WindowData *windows;
    u_int64_t windows_qtty;
    u_int64_t window_focused;

    WINDOW *menu_win;

    char *command;
    u_int64_t command_size;

    bool command_mode;
};

typedef struct ApplicationData_s ApplicationData;

/*
 * This function initializes the window.
 * 
 * data: The window data.
 */
void init_window(WindowData *win_data);

/*
 * This function closes the window.
 */
void close_window();

/*
 * This function initializes the application.
 * 
 * app_data: The application data.
 */
void init_application(ApplicationData *app_data);

/*
 * This function adds a window to the application.
 * 
 * app_data: The application data.
 * win_data: The window data.
 */
void add_window(ApplicationData *app_data, WindowData *win_data);

/*
 * This function is the main loop of the program.
 * 
 * data: The window data.
 * tables_array: The array of tables.
 */
void main_loop(ApplicationData *app_data, WindowData *win_data, InstructionTableArray *tables_array);

/*
 * This function renders the window.
 * 
 * data: The window data.
 * tables_array: The array of tables.
 */
void render(ApplicationData *app_data, WindowData *win_data, InstructionTableArray *tables_array);

/*
 * This function gets the window data.
 * 
 * data: The window data.
 */
void get_window_data(WindowData *win_data);

/*
 * This function moves down the menu.
 * 
 * menu: The menu data.
 */
void open_menu(ApplicationData *app_data);


#endif