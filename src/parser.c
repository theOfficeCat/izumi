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

#include "parser.h"

int integer_length(u_int64_t number) {
    int length = 0;

    while (number > 0) {
        number /= 10;
        length++;
    }

    return length;
}

void cycle_increment(u_int64_t *cycle, char *line) {
    u_int64_t qtty_cycles;

    if (sscanf(line, "C\t%lu", &qtty_cycles) != 1) {
        printf("Error: Could not read cycles\n");
        exit(1);
    }

    *cycle += qtty_cycles;    
}

void new_instruction(InstructionTableArray *tables_array, u_int64_t cycle, 
    char *line) {
    u_int64_t id_file, id_sim, id_thread;

    if (sscanf(line, "I\t%lu\t%lu\t%lu", &id_file, &id_sim, &id_thread) != 3) {
        printf("Error: Could not read instruction\n");
        exit(1);
    }

    // Create a new instruction
    Instruction instr_new;
    instr_new.qtty_stages = 0;
    instr_new.data = NULL;
    instr_new.stages = malloc(10 * sizeof(Stage));
    instr_new.valid = true;

    // Create table if instruction needs to be in a new one
    if (id_file/256 >= tables_array->qtty_tables) {
        // Resize the tables array if necessary
        if (id_file/256 >= tables_array->avail_tables) {
            tables_array->avail_tables *= 2;
            tables_array->tables = realloc(tables_array->tables, 
                tables_array->avail_tables * sizeof(InstructionTable*));

            for (int i = tables_array->qtty_tables; i < tables_array->avail_tables; i++) {
                tables_array->tables[i] = NULL;
            }
        }

        tables_array->tables[id_file/256] = malloc(sizeof(InstructionTable));

        for (int i = 0; i < 256; i++) {
            tables_array->tables[id_file/256]->content[i].valid = false;
        }

        tables_array->qtty_tables = id_file/256 + 1;
    }

    tables_array->tables[id_file/256]->content[id_file%256] = instr_new;
}

void line_of_data(InstructionTableArray *tables_array, char *line) {
    u_int64_t id, type;
    char data[128];

    int chars_read = 0;

        if ((chars_read = sscanf(line, "L\t%lu\t%lu\t", &id, &type)) != 2) {
        printf("Error: Could not read data\n");
        exit(1);
    }

    // Skip the first part of the line to get only the data
    int init = 5 + integer_length(id) + integer_length(type);

    strcpy(data, line + init);

    Instruction *instruct = &tables_array->tables[id/256]->content[id%256];

    instruct->data = malloc(strlen(data) + 1);
    strcpy(instruct->data, data);
}

void new_stage(InstructionTableArray *tables_array, u_int64_t cycle, 
    char *line) {
    char stage_name[4];
    u_int64_t instr_id, stage_id;

    if (sscanf(line, "S\t%lu\t%lu\t%s", &instr_id, &stage_id, stage_name) != 3) {
        printf("Error: Could not read stage\n");
        exit(1);
    }

    // Get the instruction
    Instruction *instr = 
        &tables_array->tables[instr_id/256]->content[instr_id%256];

    // Resize the stages array if necessary
    if (instr->qtty_stages % 10 == 0) {
        instr->stages = realloc(instr->stages, 
            (instr->qtty_stages + 10) * sizeof(Stage));
    }

    Stage *stage = &instr->stages[instr->qtty_stages];
    instr->qtty_stages++;

    strncpy(stage->name, stage_name, 4);
    stage->cycle = cycle;
}


InstructionTableArray parse_file(char *file_name) {
    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        printf("Error: Could not open file %s\n", file_name);
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Initialization of the tables array
    InstructionTableArray tables_array;
    tables_array.qtty_tables = 1;
    tables_array.avail_tables = 4;
    tables_array.tables = malloc(4 * sizeof(InstructionTable*));

    // Initialization of the first table    
    tables_array.tables[0] = malloc(sizeof(InstructionTable));

    for (int i = 0; i < 256; i++) {
        tables_array.tables[0]->content[i].valid = false;
    }

    for (int i = 1; i < 4; i++) {
        tables_array.tables[i] = NULL;
    }

    u_int64_t cycle = 0;

    // Parse the file
    while ((read = getline(&line, &len, file)) != -1) {
        char command;

        if (sscanf(line, "%c", &command) != 1) {
            printf("Error: Could not read command\n");
            exit(1);
        }

        switch (command) {
            case 'C':
                cycle_increment(&cycle, line);
                break;
            case 'I':
                new_instruction(&tables_array, cycle, line);
                break;
            case 'L':
                line_of_data(&tables_array, line);
                break;
            case 'S':
                new_stage(&tables_array, cycle, line);
                break;
            default:
                break;
        }
    }

    fclose(file);

    return tables_array;
}