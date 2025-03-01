/*
 * This file is part of Izumi.
 * 
 * Foobar is free software: you can redistribute it and/or modify it under the
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
    char name[4];
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
    char *data;
    Stage *stages;
    bool valid;
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