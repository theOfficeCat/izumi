/*
 * This file is part of Izumi.
 * 
 * Foobar is free software: you can redistribute it and/or modify it under the
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

int integer_length(int n) {
    int length = 0;

    while (n > 0) {
        n /= 10;
        length++;
    }

    return length;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file name>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Initialization of the table array

    InstructionTableArray tables_array;
    tables_array.qtty_tables = 1;
    tables_array.avail_tables = 4;
    tables_array.tables = malloc(4 * sizeof(InstructionTable*));



    tables_array.tables[0] = malloc(sizeof(InstructionTable));

    for (int i = 0; i < 256; i++) {
        tables_array.tables[0]->content[i].valid = false;
    }

    for (int i = 1; i < 4; i++) {
        tables_array.tables[i] = NULL;
    }

    u_int64_t cycle = 0;

    while ((read = getline(&line, &len, file)) != -1) {
        char command;

        if (sscanf(line, "%c", &command) != 1) {
            printf("Error: Could not read command\n");
            return 1;
        }

        switch (command) {
            case 'C':
                u_int64_t qtty_cycles;

                if (sscanf(line, "C\t%d", &qtty_cycles) != 1) {
                    printf("Error: Could not read cycles\n");
                    return 1;
                }

                cycle += qtty_cycles;
                break;

            case 'I':
                u_int64_t id_file, id_sim, id_thread;
                if (sscanf(line, "I\t%d\t%d\t%d", &id_file, &id_sim, &id_thread) != 3) {
                    printf("Error: Could not read instruction\n");
                    return 1;
                }
                Instruction instr_new;
                instr_new.qtty_stages = 0;
                instr_new.data = NULL;
                instr_new.stages = malloc(10 * sizeof(Stage));
                instr_new.valid = true;

                if (id_file/256 >= tables_array.qtty_tables) {
                    if (id_file/256 >= tables_array.avail_tables) {
                        tables_array.avail_tables *= 2;
                        tables_array.tables = realloc(tables_array.tables, tables_array.avail_tables * sizeof(InstructionTable*));
                    }

                    tables_array.tables[id_file/256] = malloc(sizeof(InstructionTable));

                    for (int i = 0; i < 256; i++) {
                        tables_array.tables[id_file/256]->content[i].valid = false;
                    }

                    tables_array.qtty_tables = id_file/256 + 1;
                }

                tables_array.tables[id_file/256]->content[id_file%256] = instr_new;

                break;
            case 'L':
                u_int64_t id, type;
                char data[128];

                int chars_read = 0;

                    if ((chars_read = sscanf(line, "L\t%d\t%d\t", &id, &type)) != 2) {
                    printf("Error: Could not read data\n");
                    return 1;
                }

                int init = 5 + integer_length(id) + integer_length(type);

                strcpy(data, line + init);

                Instruction *instruct = &tables_array.tables[id/256]->content[id%256];

                instruct->data = malloc(strlen(data) + 1);
                strcpy(instruct->data, data);

                break;
            case 'S':
                char stage_name[4];
                u_int64_t instr_id, stage_id;

                if (sscanf(line, "S\t%d\t%d\t%s", &instr_id, &stage_id, stage_name) != 3) {
                    printf("Error: Could not read stage\n");
                    return 1;
                }

                Instruction *instr = &tables_array.tables[instr_id/256]->content[instr_id%256];

                if (instr->qtty_stages % 10 == 0) {
                    instr->stages = realloc(instr->stages, (instr->qtty_stages + 10) * sizeof(Stage));
                }

                Stage *stage = &instr->stages[instr->qtty_stages];
                instr->qtty_stages++;

                strncpy(stage->name, stage_name, 4);
                stage->cycle = cycle;

                break;
            default:
                break;
        }
    }

    fclose(file);

    // print instructions
    for (int i = 0; i < tables_array.qtty_tables; i++) {
        for (int j = 0; j < 256; j++) {
            Instruction instr = tables_array.tables[i]->content[j];

            if (instr.valid) {
                printf("I\t%d\t%s", i*256+j, instr.data);

                for (int k = 0; k < instr.qtty_stages; k++) {
                    Stage *stage = &instr.stages[k];
                    printf("\t%s\t on %d\n", stage->name, stage->cycle);
                }
            }
        }
    }
}

