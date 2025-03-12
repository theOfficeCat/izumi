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

#include<linux/limits.h>

#include "commands.h"
#include "files.h"
#include "parser.h"

void open_file(WindowData *data, char *command, InstructionTableArray *tables_array) {
    char * path = malloc(PATH_MAX);
    sscanf(data->command, "%64s %s", command, path);

    path = realpath(path, NULL);

    FileData file_data = check_file(path);

    if (file_data.exists && file_data.is_file) {
        fprintf(stderr, "Opening file %s\n", path);
        free_InstructionTableArray(tables_array);
        *tables_array = parse_file(path);
        data->file_loaded = true;
    }
    else {
        fprintf(stderr, "Error: Could not open file %s\n", path);
    }

    free(path);
    path = NULL;

}
