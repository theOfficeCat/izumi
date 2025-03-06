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

#ifndef FILES_H
#define FILES_H

#include <sys/types.h>
#include <stdbool.h>

#include "data_structs.h"

struct DirectoryData_s {
    u_int64_t files_qtty;
    char **files;
    bool *is_directory;
};

typedef struct DirectoryData_s DirectoryData;

enum FileUsage_e {
    FILE_READ,
    DIRECTORY_READ
};

typedef enum FileUsage_e FileUsage;

DirectoryData read_directory(char *path);

FileUsage use_file(DirectoryData *directory_data, u_int64_t index, char **path, InstructionTableArray *tables_array);

#endif