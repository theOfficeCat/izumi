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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <linux/limits.h>

#include "data_structs.h"
#include "parser.h"
#include "window.h"
#include "files.h"

int main(int argc, char *argv[]) {
    // print instructions
    InstructionTableArray tables_array;
    tables_array.tables = NULL;
    tables_array.avail_tables = 0;
    tables_array.qtty_tables = 0;

    WindowData data;

    init_window(&data);

    if (argc > 1) {
        fprintf(stderr, "%s\n", argv[1]);

        char *path = malloc(PATH_MAX);
        path = realpath(argv[1], NULL);

        fprintf(stderr, "%s\n", path);

        FileData file_data = check_file(path);

        if (file_data.exists && file_data.is_file) {
            read_file(argv[1], &tables_array);
            data.file_loaded = true;
        }

        free(path);
        path = NULL;
    }

    main_loop(&data, &tables_array);

    close_window();
}

