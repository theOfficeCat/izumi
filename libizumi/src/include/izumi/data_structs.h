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

/** @file data_structs.h
 *
 * Data structures used when interacting with libizumi.
 */

#include <stdint.h>
#include <stdbool.h>

/** This struct is used to store the information of a stage.
 */
typedef struct {
    uint64_t cycle;     /**< Cycle where the stage starts. */
    uint64_t duration;  /**< Duration of the stage in cycles. */
    char *name;         /**< The name of the stage. */
} Stage;

/** This struct is used to store the information of an instruction.
 */
typedef struct {
    uint64_t qtty_stages;   /**< The quantity of stages that the instruction
                              has. */
    char *mem_addr;         /**< Memory address of the instruction. */
    char *instruction;      /**< Instruction in assembly. */
    Stage *stages;          /**< The stages that the instruction has. */
    bool valid;             /**< True if the instruction is valid. */
    bool finished;          /**< True if the instruction has finished. */
    bool flushed;           /**< True if the instruction has been flushed. */
} Instruction;

/** This struct is used to store the instructions that are read from the file.
 */
typedef struct {
    Instruction content[256];   /**< An array of 256 instructions. */
} InstructionTable;

/** This struct is used to store the tables that are read from the file.
 */
typedef struct {
    uint64_t qtty_tables;      /**< The quantity of tables that the array has
                                 in usage. */
    uint64_t avail_tables;     /**< The quantity of tables that are available
                                 in the array. */
    InstructionTable* *tables; /**< An array of tables. */
} InstructionTableArray;

/** This function initializes the InstructionTableArray.
 *
 * @param array The InstructionTableArray to be initialized.
 */
void init_InstructionTableArray(InstructionTableArray *array);

/** This function initializes the InstructionTable.
 *
 * @param table The InstructionTable to be initialized.
 */
void init_InstructionTable(InstructionTable *table);

/** This function increases the size of the InstructionTableArray.
 *
 * @param array The InstructionTableArray to be increased.
 */
void increase_InstructionTableArray(InstructionTableArray *array);

/** This function initializes the Instruction.
 *
 * @param instruction The Instruction to be initialized.
 */
void init_Instruction(Instruction *instruction);

/** This function frees the memory allocated for the InstructionTableArray.
 *
 * @param array The InstructionTableArray to be freed.
 */
void free_InstructionTableArray(InstructionTableArray *array);

/** This function frees the memory allocated for the InstructionTable.
 *
 * @param table The InstructionTable to be freed.
 */
void free_InstructionTable(InstructionTable *table);

/** This function frees the memory allocated for the Instruction.
 *
 * @param instruction The Instruction to be freed.
 */
void free_Instruction(Instruction *instruction);

/** This function frees the memory allocated for the Stage.
 *
 * @param stage The Stage to be freed.
 */
void free_Stage(Stage *stage);

#endif
