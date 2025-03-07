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

/*
 * DirectoryData
 * 
 * This struct is used to store the data of a directory.
 * 
 * files_qtty: The quantity of files in the directory.
 * files: The names of the files in the directory.
 * is_directory: An array of booleans that indicates if the file is a directory.
 */
struct DirectoryData_s {
    u_int64_t files_qtty;
    char **files;
    bool *is_directory;
};

typedef struct DirectoryData_s DirectoryData;

/*
 * FileUsage
 * 
 * This enum is used to store the usage of a file.
 * 
 * FILE_READ: The selected element is a file to read.
 * DIRECTORY_READ: The selected element is a directory to read.
 */
enum FileUsage_e {
    FILE_READ,
    DIRECTORY_READ
};

typedef enum FileUsage_e FileUsage;

/*
 * This function reads the files in a directory.
 *
 * path: The path of the directory.
 * 
 * Returns: The data of the directory.
 */
DirectoryData read_directory(char *path);

/*
 * This function uses a file or directory.
 * 
 * directory_data: The data of the directory.
 * index: The index of the selected file.
 * path: The path of the directory.
 * tables_array: The array of tables.
 * 
 * Returns: The kind of element read.
 */
FileUsage use_file(DirectoryData *directory_data, u_int64_t index, char **path, InstructionTableArray *tables_array);

/*
 * This function changes the directory when finding files.
 *
 * directory_data: The data of the directory.
 * path: The path of the directory.
 * add_path: Part to add to the path.
 */
void use_directory(DirectoryData *directory_data, char **path, char *add_path);

#endif