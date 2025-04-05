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

#include <stdbool.h>
#include <stdint.h>

#include "data_structs.h"

struct FindResult_s {
    bool valid;
    uint64_t position;
};

typedef struct FindResult_s FindResult;

enum FindDataKind_e {
    PC,
    INST
};

typedef enum FindDataKind_e FindDataKind;

enum SearchDirection_e {
    UP,
    DOWN
};

typedef enum SearchDirection_e SearchDirection;

FindResult find(InstructionTableArray *tables_array, const char *pattern, FindDataKind kind_of_data, SearchDirection dir, uint64_t init_pos);

#endif
