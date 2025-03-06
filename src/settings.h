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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <sys/types.h>
#include <stdbool.h>

#include "files.h"

/*
 * MenuOpen
 * 
 * This enum is used to store the state of the menu.
 * 
 * MAIN: The main menu is open.
 * FILES: The files menu is open.
 * CLOSED: The menu is closed.
 */
enum MenuOpen_e {
    MAIN,
    FILES,
    CLOSED
};

typedef enum MenuOpen_e MenuOpen;

/*
 * SelectedMenu
 * 
 * This enum is used to store the selected menu option.
 * 
 * LOAD_FILE: The load file option is selected.
 * QUIT: The quit option is selected.
 */
enum SelectedMenu_e {
    LOAD_FILE,
    QUIT
};

typedef enum SelectedMenu_e SelectedMenu;

/*
 * MenuData
 * 
 * This struct is used to store the data of the menu.
 * 
 * selected: The selected menu option.
 */
struct MenuData_s {
    SelectedMenu selected;
};

typedef struct MenuData_s MenuData;

/*
 * FileMenuData
 * 
 * This struct is used to store the data of the file menu.
 * 
 * directory_data: The data of the directory.
 * init_index: The index of the first file to be displayed.
 * files_index: The index of the selected file.
 * loaded: A flag that indicates if the file menu is loaded.
 * path: The path of the directory.
 */
struct FileMenuData_s {
    DirectoryData directory_data;
    u_int64_t init_index;
    u_int64_t files_index;
    bool loaded;
    char *path;
};

typedef struct FileMenuData_s FileMenuData;

/*
 * This function moves the data of the menu down.
 * 
 * menu: The menu data.
 */
void move_down_menu(MenuData *menu);

/*
 * This function moves the data of the menu up.
 * 
 * menu: The menu data.
 */
void move_up_menu(MenuData *menu);

#endif