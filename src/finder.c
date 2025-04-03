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

#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "finder.h"
#include "src/data_structs.h"

FindResult check_instruction(InstructionTableArray *tables_array, char* pattern, FindDataKind kind_of_data, uint64_t i, uint64_t j) {
    FindResult return_data;
    return_data.position = 0;
    return_data.valid = false;

    Instruction inst = tables_array->tables[i]->content[j];
    if (inst.valid) {
        char *to_check = NULL;

        switch (kind_of_data) {
            case PC:
                to_check = inst.mem_addr;
                break;
            case INST:
                if (inst.instruction != NULL) {
                    sscanf(inst.instruction, "%ms", &to_check);
                }
                break;
        }

        if (to_check != NULL && strcmp(to_check, pattern) == 0) {
            return_data.valid = true;
            return_data.position = i*256+j;
        }
    }
    return return_data;
}

FindResult find(InstructionTableArray *tables_array, char *pattern, FindDataKind kind_of_data, SearchDirection dir, uint64_t init_pos) {
    FindResult return_data;
    return_data.valid = false;
    return_data.position = 0;

    if (tables_array->tables == NULL) {
        return return_data;
    }

    if (dir == DOWN) {
        for (uint64_t i = init_pos/256; i < tables_array->qtty_tables; ++i) {
            uint64_t j = (i == init_pos/256) ? init_pos%256 : 0;

            for (; j < 256; ++j) {
                FindResult inst_result = check_instruction(tables_array, pattern, kind_of_data, i, j);

                if (inst_result.valid) {
                    return inst_result;
                }
            }
        }
    }
    else {
        for (uint64_t i = init_pos/256; i >= 0; --i) {
            for (uint64_t j = (i == init_pos/256) ? init_pos%256 : 255; j >= 0; --j) {
                FindResult inst_result = check_instruction(tables_array, pattern, kind_of_data, i, j);

                if (inst_result.valid) {
                    return inst_result;
                }
            }
        }

    }
}
