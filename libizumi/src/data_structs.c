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
#include <stdlib.h>
#include <sys/types.h>

#include <izumi/data_structs.h>


void init_InstructionTableArray(InstructionTableArray *array) {
    array->qtty_tables = 1;
    array->avail_tables = 4;
    array->tables = malloc(4 * sizeof(InstructionTable*));

    array->tables[0] = malloc(sizeof(InstructionTable));

    init_InstructionTable(array->tables[0]);

    for (int i = 1; i < 4; i++) {
        array->tables[i] = NULL;
    }
}

void init_InstructionTable(InstructionTable *table) {
    for (int i = 0; i < 256; i++) {
        table->content[i].valid = false;
    }
}

void increase_InstructionTableArray(InstructionTableArray *array) {
    array->tables = realloc(array->tables, 2 * array->avail_tables * sizeof(InstructionTable*));

    for (uint64_t i = array->avail_tables; i < 2 * array->avail_tables; i++) {
        array->tables[i] = NULL;
    }

    array->avail_tables *= 2;
}

void init_Instruction(Instruction *instruction) {
    instruction->qtty_stages = 0;
    instruction->mem_addr = NULL;
    instruction->instruction = NULL;
    instruction->stages = malloc(10 * sizeof(Stage));
    instruction->valid = true;
    instruction->finished = false;
    instruction->flushed = false;
}

void free_InstructionTableArray(InstructionTableArray *array) {
    if (array->tables != NULL) {
        for (u_int64_t i = 0; i < array->qtty_tables; i++) {
            free_InstructionTable(array->tables[i]);
        }
        free(array->tables);
    }
}

void free_InstructionTable(InstructionTable *table) {
    for (u_int64_t i = 0; i < 256; i++) {
        if (table->content[i].valid) {
            free_Instruction(&table->content[i]);
        }
    }
    free(table);
}

void free_Instruction(Instruction *instruction) {
    for (u_int64_t i = 0; i < instruction->qtty_stages; ++i) {
        free_Stage(&instruction->stages[i]);
    }
    free(instruction->stages);
    free(instruction->mem_addr);
    free(instruction->instruction);
}

void free_Stage(Stage *stage) {
    free(stage->name);
}
