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
struct Stage {
    char name[4];
};

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
struct Instruction {
    u_int64_t init_cycle;
    u_int64_t qtty_stages;
    struct Stage *stages;
    bool valid;
};

/*
 * InstructionTable
 * 
 * This struct is used to store the instructions that are read from the file.
 * 
 * level: The level of depth of the table.
 * qtty_content: The quantity of content that the table has.
 * content: An array of 256 instructions.
 */
struct InstructionTable {
    u_int8_t qtty_content;
    struct Instruction content[256];
};

