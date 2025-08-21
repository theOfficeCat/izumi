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

#include <izumi/parser.h>

#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <limits.h>
#include <libgen.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "files.h"


FileData check_file(const char *path) {
    FileData file_data = { .exists = false };
    
    if (path == NULL) return file_data;

    struct stat s;
    if (stat(path, &s) == 0) {
        file_data.exists = true;
        file_data.is_file = S_ISREG(s.st_mode);
    }

    return file_data;
}

char *read_file(const char * path, InstructionTableArray *tables_array) {
    FileData file_data = check_file(path);

    if (file_data.exists && file_data.is_file) {
        free_InstructionTableArray(tables_array);

        *tables_array = parse_file(path);

        // basename() may modify the input string, so we need to make a copy
        char *scratchpad_path = strdup(path);
        
        char *filename_basename = basename(scratchpad_path);
        char *filename = strdup(filename_basename);
        
        free(scratchpad_path);

        return filename;
    }

    return NULL;
}
