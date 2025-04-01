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
    uint64_t x;
    uint64_t y;
    uint64_t width;
    uint64_t height;

    WINDOW *win;
    uint64_t index;

    InstructionTableArray *tables_array;

    char *filename;
};

typedef struct WindowData_s WindowData;

struct ApplicationData_s {
    WindowData **windows;
    uint64_t windows_qtty;
};

typedef struct ApplicationData_s ApplicationData;

/*
 * This function creates a new window.
 *
 * app_data: The application data.
 */
void new_window(ApplicationData *app_data);

/*
 * This function initializes the application.
 *
 * app_data: The application data.
 */
void init_application(ApplicationData *app_data);

void main_loop(ApplicationData *app_data);

void render_status_bar(void);

void render(ApplicationData *app_data);

void render_window(ApplicationData *app_data, WindowData *win_data);

/*
 * This function gets the window data.
 *
 * win_data: The window data.
 * app_data: The application data.
 */
void get_window_data(WindowData *win_data, ApplicationData *app_data);

/*
 * This function moves down the menu.
 *
 * menu: The menu data.
 */
void open_menu(ApplicationData *app_data);

void close_application(ApplicationData *app_data);

#endif
