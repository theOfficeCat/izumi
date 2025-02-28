#include <sys/types.h>

struct Stage {
    char *name;
    struct Stage *next_stage;
};

struct Instruction {
    char *comment;
    int instr_id;
    struct Stage *first_stage;
    struct Stage *last_stage;
};

struct InstructionBlock {
    struct Instruction instructions[1000];
    int instr_count;

    struct InstructionBlock *next_block;
};