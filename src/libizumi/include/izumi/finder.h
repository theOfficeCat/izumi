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

#ifndef FINDER_H
#define FINDER_H

/**
 * SECTION:finder
 * @title: izumi/finder.h
 * @short_description: Tools for searching and matching the contents of a dump.
 *
 * Tools for searching and matching the contents of a dump.
 */

#include <stdbool.h>
#include <stdint.h>

#include <izumi/data_structs.h>


/**
 * FindResult
 * @valid: True if the result is valid.
 * @position: Position of the found element.
 *
 * This struct is used to store the result of a search.
 */
typedef struct FindResult {
    bool valid;
    uint64_t position;
} FindResult;

/**
 * FindDataKind
 * @PC: Program Counter.
 * @INST: Instruction.
 *
 * This enum is used to specify the type of data to be searched.
 */
typedef enum FindDataKind {
    PC,
    INST
} FindDataKind;

/**
 * SearchDirection
 * @UP: Search upwards.
 * @DOWN: Search downwards.
 *
 * This enum is used to specify the direction of the search.
 */
typedef enum SearchDirection {
    UP,
    DOWN
} SearchDirection;

/**
 * find:
 * @tables_array: The array of tables.
 * @pattern: The pattern to be searched.
 * @kind_of_data: The type of data to be searched.
 * @dir: The direction of the search.
 * @init_pos: The initial position of the search.
 *
 * This function searches for a pattern in the tables array and returns the
 * result.
 *
 * Returns: A FindResult struct with the result of the search.
 */
FindResult find(InstructionTableArray *tables_array, const char *pattern, FindDataKind kind_of_data, SearchDirection dir, uint64_t init_pos);

#endif
