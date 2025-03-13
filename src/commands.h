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

#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdbool.h>

#include "data_structs.h"

/*
 * This function is used to open a file.
 * 
 * data: The window data.
 * command: The command to be executed.
 * tables_array: The array of instruction tables.
 */
bool open_file(char *user_command, char *command, InstructionTableArray *tables_array);

enum Direction_e {
    UP,
    DOWN
};

typedef enum Direction_e Direction;

enum SearchMode_e {
    PC,
    INST,
    NONE
};

typedef enum SearchMode_e SearchMode;

u_int64_t find_pc(char *command, InstructionTableArray *tables_array, u_int64_t index_to_start, char **pc, Direction direction);

u_int64_t find_inst(char *command, InstructionTableArray *tables_array, u_int64_t index_to_start, char **inst, Direction direction);

#endif