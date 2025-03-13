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

#include<linux/limits.h>

#include "commands.h"
#include "files.h"
#include "parser.h"

void open_file(WindowData *data, char *command, InstructionTableArray *tables_array) {
    char * path = malloc(PATH_MAX);
    sscanf(data->command, "%64s %s", command, path);

    path = realpath(path, NULL);

    FileData file_data = check_file(path);

    if (file_data.exists && file_data.is_file) {
        free_InstructionTableArray(tables_array);
        *tables_array = parse_file(path);
        data->file_loaded = true;
    }

    free(path);
    path = NULL;

}


u_int64_t find_pc(char *command, InstructionTableArray *tables_array, u_int64_t index_to_start, char **pc, Direction direction) {
    *pc = malloc(19);
    char command_name[64];
    sscanf(command, "%64s %18s", command_name, *pc);

    if (direction == DOWN) {
        for (u_int64_t i = index_to_start/256; i < tables_array->qtty_tables; ++i) {
            if (tables_array->tables[i] != NULL) {
                u_int64_t j;

                if (i == index_to_start/256) {
                    j = index_to_start%256;
                }
                else {
                    j = 0;
                }

                for (; j < 256; ++j) {
                    if (tables_array->tables[i]->content[j].valid) {
                        if (tables_array->tables[i]->content[j].mem_addr != NULL) {
                            if (strcmp(tables_array->tables[i]->content[j].mem_addr, *pc) == 0) {
                                return i * 256 + j;
                            }
                        }
                    }
                }
            }
        }
        return index_to_start-1;
    }
    else {
        for (u_int64_t i = index_to_start/256; i != UINT64_MAX; --i) { // use of UINT64_MAX to control the loop because the underflow
            if (tables_array->tables[i] != NULL) {
                u_int64_t j;

                if (i == index_to_start/256) {
                    j = index_to_start%256;
                }
                else {
                    j = 255;
                }

                for (; j != UINT64_MAX; --j) {
                    if (tables_array->tables[i]->content[j].valid) {
                        if (tables_array->tables[i]->content[j].mem_addr != NULL) {
                            if (strcmp(tables_array->tables[i]->content[j].mem_addr, *pc) == 0) {
                                return i * 256 + j;
                            }
                        }
                    }
                }
            }
        }
        return index_to_start+1;
    }
}