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

enum StatusMenu_e {
    OPEN,
    CLOSED
};

typedef enum StatusMenu_e StatusMenu;

enum SelectedMenu_e {
    LOAD_FILE,
    QUIT
};

typedef enum SelectedMenu_e SelectedMenu;

struct MenuData_s {
    StatusMenu status;
    SelectedMenu selected;
};

typedef struct MenuData_s MenuData;


void toggle_menu(StatusMenu *status);

void move_down_menu(SelectedMenu *selected);

void move_up_menu(SelectedMenu *selected);

#endif