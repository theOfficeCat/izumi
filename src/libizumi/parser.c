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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include <izumi/parser.h>

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
        fprintf(stderr, "Error: Could not read cycles\n");
        exit(1);
    }

    *cycle += qtty_cycles;
}

void new_instruction(InstructionTableArray *tables_array, char *line) {
    u_int64_t id_file, id_sim, id_thread;

    if (sscanf(line, "I\t%lu\t%lu\t%lu", &id_file, &id_sim, &id_thread) != 3) {
        fprintf(stderr, "Error: Could not read instruction\n");
        exit(1);
    }

    // Create a new instruction
    Instruction instr_new;
    init_Instruction(&instr_new);

    // Create table if instruction needs to be in a new one
    if (id_file/256 >= tables_array->qtty_tables) {
        // Resize the tables array if necessary
        if (id_file/256 >= tables_array->avail_tables) {
            increase_InstructionTableArray(tables_array);
        }

        tables_array->tables[id_file/256] = malloc(sizeof(InstructionTable));

        init_InstructionTable(tables_array->tables[id_file/256]);

        tables_array->qtty_tables = id_file/256 + 1;
    }

    tables_array->tables[id_file/256]->content[id_file%256] = instr_new;
}

void line_of_data(InstructionTableArray *tables_array, char *line) {
    u_int64_t id, type;
    char data[128];

    int chars_read = 0;

    char mem_addr[19];

    if ((chars_read = sscanf(line, "L\t%lu\t%lu\t%18s", &id, &type, mem_addr)) != 3) {
        fprintf(stderr, "Error: Could not read data\n");
        exit(1);
    }

    Instruction *instruct = &tables_array->tables[id/256]->content[id%256];

    instruct->mem_addr = malloc(19);
    strcpy(instruct->mem_addr, mem_addr);
    instruct->mem_addr[18] = '\0';

    // Skip the first part of the line to get only the data
    int init = 24 + integer_length(id) + integer_length(type);

    strcpy(data, line + init);

    data[strlen(data) - 1] = '\0';

    instruct->instruction = malloc(strlen(data) + 1);
    strcpy(instruct->instruction, data);
}

void new_stage(InstructionTableArray *tables_array, u_int64_t cycle, char *line) {
    char *stage_name;
    u_int64_t instr_id, stage_id;

    if (sscanf(line, "S\t%lu\t%lu\t%ms", &instr_id, &stage_id, &stage_name) != 3) {
        fprintf(stderr, "Error: Could not read stage\n");
        exit(1);
    }

    // Get the instruction
    Instruction *instr = &tables_array->tables[instr_id/256]->content[instr_id%256];

    // Resize the stages array if necessary
    if (instr->qtty_stages % 10 == 0) {
        instr->stages = realloc(instr->stages, (instr->qtty_stages + 10) * sizeof(Stage));
    }

    Stage *stage = &instr->stages[instr->qtty_stages];
    instr->qtty_stages++;

    stage->name = stage_name;
    stage->cycle = cycle;
    stage ->duration = 0;
}

void end_stage(InstructionTableArray *tables_array, u_int64_t cycle, char *line) {
    u_int64_t instr_id, stage_id;

    char stage_name[4];

    if (sscanf(line, "E\t%lu\t%lu\t%s", &instr_id, &stage_id, stage_name) != 3) {
        fprintf(stderr, "Error: Could not read end stage\n");
        exit(1);
    }

    // Get the instruction
    Instruction *instr = &tables_array->tables[instr_id/256]->content[instr_id%256];

    // Get the stage
    Stage *stage = NULL;

    for (uint64_t i = 0; i < instr->qtty_stages; i++) {
        if (strcmp(instr->stages[i].name, stage_name) == 0) {
            stage = &instr->stages[i];
            break;
        }
    }

    if (stage != NULL) {
        stage->duration = cycle - stage->cycle;
    }

}

void retire_instruction(InstructionTableArray *tables_array, u_int64_t cycle, char *line) {
    u_int64_t instr_id, retire_id, type;

    if (sscanf(line, "R\t%lu\t%lu\t%lu", &instr_id, &retire_id, &type) != 3) {
        fprintf(stderr, "Error: Could not read retire\n");
        exit(1);
    }


    // Get the instruction
    Instruction *instr = &tables_array->tables[instr_id/256]->content[instr_id%256];

    if (!instr->finished) {
        Stage *stage = &instr->stages[instr->qtty_stages - 1];
        stage->duration = cycle - stage->cycle;
        instr->finished = true;
        instr->flushed = (type == 1);
    }
}


InstructionTableArray parse_file(const char *file_name) {
    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", file_name);
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Initialization of the tables array
    InstructionTableArray tables_array;

    init_InstructionTableArray(&tables_array);

    u_int64_t cycle = 0;

    // Parse the file
    while ((read = getline(&line, &len, file)) != -1) {
        char command;

        if (sscanf(line, "%c", &command) != 1) {
            fprintf(stderr, "Error: Could not read command\n");
            exit(1);
        }

        switch (command) {
            case 'C':
                cycle_increment(&cycle, line);
                break;
            case 'I':
                new_instruction(&tables_array, line);
                break;
            case 'L':
                line_of_data(&tables_array, line);
                break;
            case 'S':
                new_stage(&tables_array, cycle, line);
                break;
            case 'E':
                end_stage(&tables_array, cycle, line);
                break;
            case 'R':
                retire_instruction(&tables_array, cycle, line);
                break;
            default:
                break;
        }
    }

    fclose(file);

    free(line);
    line = NULL;

    return tables_array;
}
