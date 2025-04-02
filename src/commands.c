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

#include <linux/limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdint.h>

#include "commands.h"
#include "files.h"

bool open_file(char *user_command, char *command, InstructionTableArray *tables_array) {

}


u_int64_t find_pc(char *command, InstructionTableArray *tables_array, u_int64_t index_to_start, char **pc, Direction direction) {
}

u_int64_t find_inst(char *command, InstructionTableArray *tables_array, u_int64_t index_to_start, char **inst, Direction direction) {
}
