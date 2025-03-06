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


enum MenuOpen_e {
    MAIN,
    FILES,
    CLOSED
};

typedef enum MenuOpen_e MenuOpen;

enum SelectedMenu_e {
    LOAD_FILE,
    QUIT
};

typedef enum SelectedMenu_e SelectedMenu;

struct MenuData_s {
    SelectedMenu selected;
};

typedef struct MenuData_s MenuData;

struct FileMenuData_s {
    DirectoryData directory_data;
    u_int64_t init_index;
    u_int64_t files_index;
    bool loaded;
    char *path;
};

typedef struct FileMenuData_s FileMenuData;

//void toggle_menu(MenuOpen *menu, );

void move_down_menu(MenuData *menu);

void move_up_menu(MenuData *menu);

#endif