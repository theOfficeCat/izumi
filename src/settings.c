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

#include "settings.h"
#include "window.h"
#include "data_structs.h"
#include "parser.h"


void move_down_menu(MenuData *menu) {
    if (menu->selected != MENU_QTTY-1) {
        menu->selected = (menu->selected + 1);
    }
}

void move_up_menu(MenuData *menu) {
    if (menu->selected != 0) {
        menu->selected = (menu->selected - 1);
    }
}

void use_menu(WindowData *data, InstructionTableArray *tables_array) {
    if (data->main_menu.selected == QUIT) {
        close_window();
        exit(0);
    }
    else if (data->main_menu.selected == LOAD_FILE) {
        char *init_path = ".";
        data->file_menu.path = malloc(strlen(init_path));
        strcpy(data->file_menu.path, init_path);
        data->file_menu.directory_data = read_directory(data->file_menu.path);
        data->file_menu.files_index = 0;
        data->file_menu.init_index = 0;
        data->menu_data = FILES;
    }
    else if (data->main_menu.selected == CLOSE_FILE) {
        free_InstructionTableArray(tables_array);
        data->file_menu.loaded = false;
        data->menu_data = CLOSED;
    }
}