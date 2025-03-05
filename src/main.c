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

#include "data_structs.h"
#include "parser.h"
#include "window.h"
#include "files.h"

int main(int argc, char *argv[]) {
    /*if (argc < 2) {
        printf("Usage: %s <file name> [-p]\n", argv[0]);
        return 1;
    }

    InstructionTableArray tables_array = parse_file(argv[1]);

    bool print = false;

    if ((argc == 3) && (strcmp(argv[2], "-p") == 0)) {
        print = true;
    }*/

    bool print = false;

    // print instructions
    if (print) {
        /*for (int i = 0; i < tables_array.qtty_tables; i++) {
            for (int j = 0; j < 256; j++) {
                Instruction instr = tables_array.tables[i]->content[j];

                if (instr.valid) {
                    printf("I\t%d\t%s\t%s\n", i*256+j, instr.mem_addr, instr.instruction);

                    for (int k = 0; k < instr.qtty_stages; k++) {
                        Stage *stage = &instr.stages[k];
                        printf("\t%s\t on %lu\tduration: %lu\n", stage->name, stage->cycle, stage->duration);
                    }
                }
            }
        }*/
    }
    else {
        InstructionTableArray tables_array;


        WindowData data;

        init_window(&data);

        main_loop(&data, &tables_array);

        close_window();
    }
}

