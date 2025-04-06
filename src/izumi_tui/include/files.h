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

#include <izumi/data_structs.h>

struct FileData_s {
    bool exists;
    bool is_file;
};

typedef struct FileData_s FileData;

/*
 * This function checks if a file exists and if it is a file.
 *
 * path: The path of the file.
 *
 */
FileData check_file(const char *path);

/*
 * This function reads a file and stores the data in the tables array.
 *
 * path: The path of the file.
 * tables_array: The array of tables.
 */
char *read_file(const char *path, InstructionTableArray *tables_array);

#endif
