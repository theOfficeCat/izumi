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

#ifndef PARSER_H
#define PARSER_H

#include "data_structs.h"

/*
 * On cycle function on the input, increase the cycle count by the number of
 * cycles
 *
 * cycle: The current cycle count.
 * line: The input line.
 */
void cycle_increment(u_int64_t *cycle, char *line);

/*
 * On instruction function on the input, create a new instruction and store it
 * in the tables array.
 *
 * tables_array: The array of tables.
 * line: The input line.
 */
void new_instruction(InstructionTableArray *tables_array, char *line);

/*
 * On line function on the input, store the data of an instruction in
 * the tables array.
 *
 * tables_array: The array of tables.
 * line: The input line.
 */
void line_of_data(InstructionTableArray *tables_array, char *line);

/*
 * On stage function on the input, store a new stage of an instruction in
 * the tables array.
 *
 * tables_array: The array of tables.
 * cycle: The current cycle count.
 * line: The input line.
 */
void new_stage(InstructionTableArray *tables_array, u_int64_t cycle, char *line);

/*
 * On end stage function on the input, store the end of a stage of an
 * instruction in the tables array.
 *
 * tables_array: The array of tables.
 * cycle: The current cycle count.
 * line: The input line.
 */
void end_stage(InstructionTableArray *tables_array, u_int64_t cycle, char *line);

/*
 * On retire function on the input, treat the retire of the instruction.
 *
 * tables_array: The array of tables.
 * cycle: The current cycle count.
 * line: The input line.
 */
void retire_instruction(InstructionTableArray *tables_array, u_int64_t cycle, char *line);

/*
 * Parse the file and return the array of tables.
 *
 * file_name: The name of the file.
 */
InstructionTableArray parse_file(const char *file_name);

#endif
