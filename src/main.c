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

    struct InstructionBlock first_block;
    first_block.instr_count = 0;
    first_block.next_block = NULL;

    struct InstructionBlock *current_block = &first_block;

    while ((read = getline(&line, &len, file)) != -1) {
        char command;

        if (sscanf(line, "%c", &command) != 1) {
            printf("Error: Could not read command\n");
            return 1;
        }

        switch (command) {
            case 'C':
                printf("Cycles\n");
                break;
            case 'I':
                printf("Instruction\n");
                int id_file, id_sim, id_thread;
                if (sscanf(line, "I\t%d\t%d\t%d", &id_file, &id_sim, &id_thread) != 3) {
                    printf("Error: Could not read instruction\n");
                    return 1;
                }

                struct Instruction *instr = &current_block->instructions[current_block->instr_count];
                instr->instr_id = id_file;
                instr->first_stage = NULL;
                instr->last_stage = NULL;

                if (current_block->instr_count++ == 999)
                {
                    struct InstructionBlock *new_block = malloc(sizeof(struct InstructionBlock));
                    new_block->instr_count = 0;
                    new_block->next_block = NULL;
                    current_block->next_block = new_block;
                    current_block = new_block;
                }

                break;
            case 'L':
                printf("Text\n");
                break;
            case 'S':
                printf("New stage\n");

                char stage_name[4];
                int instr_id, stage_id;

                if (sscanf(line, "S\t%d\t%d\t%s", instr_id, stage_id, stage_name) != 3) {
                    printf("Error: Could not read stage\n");
                    return 1;
                }

                struct Stage *stage = malloc(sizeof(struct Stage));
                stage->name = malloc(4);
                strcpy(stage->name, stage_name);
                stage->next_stage = NULL;

                struct Instruction *instr = &current_block->instructions[instr_id%1000];

                if (instr->first_stage == NULL) {
                    instr->first_stage = stage;
                    instr->last_stage = stage;
                } else {
                    instr->last_stage->next_stage = stage;
                    instr->last_stage = stage;
                }

                break;
            default:
                break;
        }
    }
}