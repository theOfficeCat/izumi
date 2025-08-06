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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <izumi/finder.h>

const char WHITESPACE[] = " \t\n\r";

FindResult check_instruction(InstructionTableArray *tables_array, const char* pattern, FindDataKind kind_of_data, uint64_t i, uint64_t j) {
    FindResult return_data;
    return_data.position = 0;
    return_data.valid = false;

    Instruction inst = tables_array->tables[i]->content[j];
    if (inst.valid) {
        char *to_check = NULL;
        unsigned int to_check_len = 0;

        switch (kind_of_data) {
            case PC:
                to_check = inst.mem_addr;
                if (inst.mem_addr == NULL) break;
                to_check_len = strlen(to_check);
                break;
            case INST:
                if (inst.instruction != NULL) {
                    to_check = inst.instruction;
                    
                    // Trim whitespace
                    to_check += strspn(inst.instruction, WHITESPACE);
                    to_check_len = strcspn(to_check, WHITESPACE);
                }
                break;
        }

        if (to_check != NULL && strncmp(to_check, pattern, to_check_len) == 0) {
            return_data.valid = true;
            return_data.position = i*256+j;
        }
    }
    return return_data;
}

FindResult find(InstructionTableArray *tables_array, const char *pattern, FindDataKind kind_of_data, SearchDirection dir, uint64_t init_pos) {
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
        for (uint64_t i = init_pos/256; i < UINT64_MAX; --i) {
            for (uint64_t j = (i == init_pos/256) ? init_pos%256 : 255; j < UINT64_MAX; --j) {
                FindResult inst_result = check_instruction(tables_array, pattern, kind_of_data, i, j);

                if (inst_result.valid) {
                    return inst_result;
                }
            }
        }
    }

    return return_data;
}
