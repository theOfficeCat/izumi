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

#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

#include <sys/types.h>
#include <stdbool.h>

/*
 * Stage
 *
 * This struct is used to store the information of a stage.
 *
 * name: The name of the stage.
 */
struct Stage_s {
    u_int64_t cycle;
    u_int64_t duration;
    char *name;
};

typedef struct Stage_s Stage;

/*
 * Instruction
 *
 * This struct is used to store the information of an instruction.
 *
 * init_cycle: The cycle in which the instruction was initialized.
 * qtty_stages: The quantity of stages that the instruction has.
 * stages: The stages that the instruction has.
 *
 * The stages are stored in an array of Stage structs, which will be resized
 * by 10 elements each time it is full.
 */
struct Instruction_s {
    u_int64_t qtty_stages;
    char *mem_addr;
    char *instruction;
    Stage *stages;
    bool valid;
    bool finished;
};

typedef struct Instruction_s Instruction;

/*
 * InstructionTable
 *
 * This struct is used to store the instructions that are read from the file.
 *
 * content: An array of 256 instructions.
 */
struct InstructionTable_s {
    Instruction content[256];
};

typedef struct InstructionTable_s InstructionTable;

/*
 * InstructionTableArray
 *
 * This struct is used to store the tables that are read from the file.
 *
 * qtty_tables: The quantity of tables that the array has in usage.
 * avail_tables: The quantity of tables that are available in the array.
 * tables: An array of tables.
 */
struct InstructionTableArray_s {
    u_int64_t qtty_tables;
    u_int64_t avail_tables;
    InstructionTable* *tables;
};

typedef struct InstructionTableArray_s InstructionTableArray;

/*
 * This function initializes the InstructionTableArray.
 *
 * array: The InstructionTableArray to be initialized.
 */
void init_InstructionTableArray(InstructionTableArray *array);

/*
 * This function initializes the InstructionTable.
 *
 * table: The InstructionTable to be initialized.
 */
void init_InstructionTable(InstructionTable *table);

/*
 * This function increases the size of the InstructionTableArray.
 *
 * array: The InstructionTableArray to be increased.
 */
void increase_InstructionTableArray(InstructionTableArray *array);

/*
 * This function initializes the Instruction.
 *
 * instruction: The Instruction to be initialized.
 */
void init_Instruction(Instruction *instruction);

/*
 * This function frees the memory allocated for the InstructionTableArray.
 *
 * array: The InstructionTableArray to be freed.
 */
void free_InstructionTableArray(InstructionTableArray *array);

/*
 * This function frees the memory allocated for the InstructionTable.
 *
 * table: The InstructionTable to be freed.
 */
void free_InstructionTable(InstructionTable *table);

/*
 * This function frees the memory allocated for the Instruction.
 *
 * instruction: The Instruction to be freed.
 */
void free_Instruction(Instruction *instruction);

/*
 * This function frees the memory allocated for the Stage.
 *
 * stage: The Stage to be freed.
 */
void free_Stage(Stage *stage);

#endif
