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

#include "stage.h"

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

    // Initialization of the table
    struct InstructionTable *table = malloc(sizeof(struct InstructionTable));
    table->level = 0;
    table->qtty_content = 0;

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
                
                struct Instruction *instr_new = malloc(sizeof(struct Instruction));
                instr_new->init_cycle = cycle;
                instr_new->qtty_stages = 0;
                instr_new->stages = malloc(10 * sizeof(struct Stage));

                if (table->qtty_content == 256) {
                    // TODO: Implement new levels
                    printf("Error: Table is full\n");
                    return 1;
                } else {
                    table->qtty_content = id_file;
                    table->content[table->qtty_content] = instr_new;
                    // TODO: Implement new levels
                    table->qtty_content++;
                }

                break;
            case 'L':
                break;
            case 'S':
                char stage_name[4];
                u_int64_t instr_id, stage_id;

                if (sscanf(line, "S\t%d\t%d\t%s", &instr_id, &stage_id, stage_name) != 3) {
                    printf("Error: Could not read stage\n");
                    return 1;
                }

                struct Instruction *instr = table->content[instr_id%256];

                struct Stage *stage = &instr->stages[instr->qtty_stages];
                instr->qtty_stages++;

                strncpy(stage->name, stage_name, 4);

                break;
            default:
                break;
        }
    }

    fclose(file);

    // print instructions

    for (int i = 0; i < table->qtty_content; i++) {
        struct Instruction *instr = table->content[i];
        printf("Instruction %d\n", i);

        if (instr != NULL) {
            printf("Init cycle: %d\n", instr->init_cycle);
            printf("Quantity of stages: %d\n", instr->qtty_stages);

            for (int j = 0; j < instr->qtty_stages; j++) {
                struct Stage *stage = &instr->stages[j];
                printf("\tStage %d: %s\n", j, stage->name);
            }
        }
    }
}