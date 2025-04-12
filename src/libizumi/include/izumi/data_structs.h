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

/**
 * SECTION:data_structs
 * @title: izumi/data_structs.h
 * @short_description: Data structures used when interacting with libizumi.
 *
 * Data structures used when interacting with libizumi.
 */

#include <stdint.h>
#include <stdbool.h>

/**
 * Stage:
 * @cycle: Cycle where the stage starts.
 * @duration: Duration of the stage in cycles.
 * @name: The name of the stage.
 *
 * This struct is used to store the information of a stage.
 */
typedef struct {
    uint64_t cycle;
    uint64_t duration;
    char *name;
} Stage;

/**
 * Instruction:
 * @qtty_stages: The quantity of stages that the instruction has.
 * @mem_addr: Memory address of the instruction.
 * @instruction: Instruction in assembly.
 * @stages: The stages that the instruction has.
 * @valid: True if the instruction is valid.
 * @finished: True if the instruction has finished.
 *
 * This struct is used to store the information of an instruction.
 */
typedef struct {
    uint64_t qtty_stages;
    char *mem_addr;
    char *instruction;
    Stage *stages;
    bool valid;
    bool finished;
} Instruction;

/**
 * InstructionTable:
 * @content: An array of 256 instructions.
 *
 * This struct is used to store the instructions that are read from the file.
 */
typedef struct {
    Instruction content[256];
} InstructionTable;

/**
 * InstructionTableArray:
 * @qtty_tables: The quantity of tables that the array has in usage.
 * @avail_tables: The quantity of tables that are available in the array.
 * @tables: An array of tables.
 *
 * This struct is used to store the tables that are read from the file.
 */
typedef struct {
    uint64_t qtty_tables;
    uint64_t avail_tables;
    InstructionTable* *tables;
} InstructionTableArray;

/**
 * init_InstructionTableArray:
 * @array: The InstructionTableArray to be initialized.
 *
 * This function initializes the InstructionTableArray.
 */
void init_InstructionTableArray(InstructionTableArray *array);

/**
 * init_InstructionTable:
 * @table: The InstructionTable to be initialized.
 *
 * This function initializes the InstructionTable.
 */
void init_InstructionTable(InstructionTable *table);

/**
 * increase_InstructionTableArray:
 * @array: The InstructionTableArray to be increased.
 *
 * This function increases the size of the InstructionTableArray.
 */
void increase_InstructionTableArray(InstructionTableArray *array);

/**
 * init_Instruction:
 * @instruction: The Instruction to be initialized.
 *
 * This function initializes the Instruction.
 */
void init_Instruction(Instruction *instruction);

/**
 * free_InstructionTableArray:
 * @array: The InstructionTableArray to be freed.
 *
 * This function frees the memory allocated for the InstructionTableArray.
 */
void free_InstructionTableArray(InstructionTableArray *array);

/**
 * free_InstructionTable:
 * @table: The InstructionTable to be freed.
 *
 * This function frees the memory allocated for the InstructionTable.
 */
void free_InstructionTable(InstructionTable *table);

/**
 * free_Instruction:
 * @instruction: The Instruction to be freed.
 *
 * This function frees the memory allocated for the Instruction.
 */
void free_Instruction(Instruction *instruction);

/**
 * free_Stage:
 * @stage: The Stage to be freed.
 *
 * This function frees the memory allocated for the Stage.
 */
void free_Stage(Stage *stage);

#endif
