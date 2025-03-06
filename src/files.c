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

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

DirectoryData read_directory(char *path) {
    DirectoryData directory_data;

    directory_data.files = malloc(10 * sizeof(char*));
    directory_data.is_directory = malloc(10 * sizeof(bool));
    directory_data.files_qtty = 0;

    DIR *dir;
    struct dirent *ent;

    dir = opendir(path);
    if (dir) {
        while ((ent = readdir(dir)) != NULL) {
            if (directory_data.files_qtty % 10 == 0) {
                directory_data.files = realloc(directory_data.files, (directory_data.files_qtty + 10) * sizeof(char*));
                directory_data.is_directory = realloc(directory_data.is_directory, (directory_data.files_qtty + 10) * sizeof(bool));
            }

            directory_data.files[directory_data.files_qtty] = malloc(strlen(ent->d_name) + 1);
            strcpy(directory_data.files[directory_data.files_qtty], ent->d_name);

            directory_data.files_qtty++;
        }
        closedir(dir);
    }

    qsort(directory_data.files, directory_data.files_qtty, sizeof(char*), compare_strings);

    for (u_int64_t i = 0; i < directory_data.files_qtty; i++) {
        struct stat s;
        stat(directory_data.files[i], &s);

        directory_data.is_directory[i] = S_ISDIR(s.st_mode);
    }

    return directory_data;
}

FileUsage use_file(DirectoryData *directory_data, u_int64_t index, char **path, InstructionTableArray *tables_array) {
    if (directory_data->is_directory[index]) {
        char *new_path = malloc(strlen(*path) + strlen(directory_data->files[index]) + 2);
        strcpy(new_path, *path);
        strcat(new_path, "/");
        strcat(new_path, directory_data->files[index]);

        *directory_data = read_directory(new_path);

        free(*path);

        *path = realpath(new_path, NULL);
        free(new_path);

        return DIRECTORY_READ;
    }
    else {
        char *full_path = malloc(strlen(*path) + strlen(directory_data->files[index]) + 2);
        strcpy(full_path, *path);
        strcat(full_path, "/");
        strcat(full_path, directory_data->files[index]);

        *tables_array = parse_file(full_path);

        return FILE_READ;
    }
}