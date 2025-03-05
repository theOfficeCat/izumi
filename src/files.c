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

#include "files.h"

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

DirectoryData read_directory(char *path) {
    DirectoryData directory_data;

    directory_data.files = malloc(10 * sizeof(char*));
    directory_data.files_qtty = 0;

    DIR *dir;
    struct dirent *ent;

    dir = opendir(path);
    if (dir) {
        while ((ent = readdir(dir)) != NULL) {
            if (directory_data.files_qtty % 10 == 0) {
                directory_data.files = realloc(directory_data.files, (directory_data.files_qtty + 10) * sizeof(char*));
            }

            directory_data.files[directory_data.files_qtty] = malloc(strlen(ent->d_name) + 1);
            strcpy(directory_data.files[directory_data.files_qtty], ent->d_name);

            directory_data.files_qtty++;
        }
        closedir(dir);
    }

    qsort(directory_data.files, directory_data.files_qtty, sizeof(char*), compare_strings);

    return directory_data;
}