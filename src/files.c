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

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <limits.h>

#include "files.h"
#include "window.h"
#include "data_structs.h"
#include "parser.h"


FileData check_file(char *path) {
    FileData file_data;

    struct stat s;
    if (stat(path, &s) == 0) {
        file_data.exists = true;
        file_data.is_file = S_ISREG(s.st_mode);
    }
    else {
        file_data.exists = false;
    }

    return file_data;
}