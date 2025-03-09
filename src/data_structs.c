#include "data_structs.h"

void init_InstructionTableArray(InstructionTableArray *array) {
    array->qtty_tables = 1;
    array->avail_tables = 4;
    array->tables = malloc(4 * sizeof(InstructionTable*));

    array->tables[0] = malloc(sizeof(InstructionTable));

    init_InstructionTable(array->tables[0]);

    for (int i = 1; i < 4; i++) {
        array->tables[i] = NULL;
    }
}

void init_InstructionTable(InstructionTable *table) {
    for (int i = 0; i < 256; i++) {
        table->content[i].valid = false;
    }
}

void increse_InstructionTableArray(InstructionTableArray *array) {
    array->tables = realloc(array->tables, 2 * array->avail_tables * sizeof(InstructionTable*));

    for (int i = array->avail_tables; i < 2 * array->avail_tables; i++) {
        array->tables[i] = NULL;
    }

    array->avail_tables *= 2;
}

void free_InstructionTableArray(InstructionTableArray *array) {
    for (u_int64_t i = 0; i < array->qtty_tables; i++) {
        free_InstructionTable(array->tables[i]);
    }
    free(array->tables);
    free(array);
}

void free_InstructionTable(InstructionTable *table) {
    for (u_int64_t i = 0; i < 256; i++) {
        if (table->content[i].valid) {
            free_Instruction(&table->content[i]);
        }
    }
}

void free_Instruction(Instruction *instruction) {
    for (u_int64_t i = 0; i < instruction->qtty_stages; i++) {
        free_Stage(&instruction->stages[i]);
    }
    free(instruction->stages);
    free(instruction->mem_addr);
    free(instruction->instruction);
}

void free_Stage(Stage *stage) {
    free(stage->name);
}