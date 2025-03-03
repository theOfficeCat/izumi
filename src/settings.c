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

void toggle_menu(StatusMenu *status) {
    if (*status == OPEN) {
        *status = CLOSED;
    }
    else {
        *status = OPEN;
    }
}

void move_down_menu(SelectedMenu *selected) {
    if (*selected == LOAD_FILE) {
        *selected = QUIT;
    }
}

void move_up_menu(SelectedMenu *selected) {
    if (*selected == QUIT) {
        *selected = LOAD_FILE;
    }
}

void use_menu(WindowData *data, InstructionTableArray *tables_array) {
    if (data->menu.selected == QUIT) {
        close_window();
        exit(0);
    }
}