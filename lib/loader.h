#include <stdlib.h>

#ifndef CONSTRUCT_LOADED
    #include "construct.h"
#endif


/*
    THE LOADER
    The Loader is in charge of loading instructions from source code. 
    It loads the instructions into an Instruction struct.

    It is also responsible for skipping characters that are not valid
    instruction types.



*/


char is_instruction(unsigned char c);
int count_instructions(Instruction * instruction);
Instruction * create_instruction(enum InstructionType instruction_type, unsigned long count, Instruction * last_instruction);
Instruction * backtrack_instructions(Instruction * tail);
Instruction * get_instruction_set(unsigned char * source, long n_chars);


Instruction * get_instruction_set(unsigned char * source, long n_chars) {

    Instruction * instruction, * last_instruction;
    enum InstructionType current_value, prev_value;

    last_instruction = NULL;
    instruction = NULL;

    for (long i = 0; i < n_chars; i++) {

        if (!is_instruction(*(source + i))) {
            continue;
        }

        // get current instruction
        current_value = (enum InstructionType)*(source + i);

        if (last_instruction == NULL) {

            last_instruction = create_instruction(current_value, 1, NULL);
            if (last_instruction == NULL) {
                // Without this, we get an infinite loop if system is out of memory
                break;
            }

            // only one instruction
            last_instruction = last_instruction;
            prev_value = current_value;
            continue;
        }

        // if the instruction is the same
        if ((char)prev_value == (char)current_value) {
            // just increase the instruction counter
            // TODO: fix this, it should increment the last element in linked list
            last_instruction->count++;
            continue;
        }

        instruction = create_instruction(current_value, 1, last_instruction);
        last_instruction = instruction;
        prev_value = current_value;
    }

    return backtrack_instructions(last_instruction);
}


char is_instruction(unsigned char c) {

    for (int i = 0; i < INSTRUCTION_TYPE_COUNT; i++) {
        if ((char)c == (char)*(instruction_types + i)) {
            return 1;
        }
    }

    return 0; // 1 means yes 0 means no
}


Instruction * create_instruction(enum InstructionType instruction_type, unsigned long count, Instruction * last_instruction) {

    Instruction * instruction = (Instruction *)malloc(sizeof(Instruction));

    if (instruction == NULL) {
        return NULL;
    }
    instruction->instruction_type = instruction_type;
    instruction->count = 1;
    instruction->nested_instructions = NULL;
    instruction->next_instruction = NULL;
    instruction->last_instruction = last_instruction;

    return instruction;
}


Instruction * backtrack_instructions(Instruction * tail) {

    Instruction * iterator = tail;

    while (iterator != NULL) {

        if (iterator->last_instruction == NULL) {
            return iterator;
        }

        iterator->last_instruction->next_instruction = iterator;
        iterator = iterator->last_instruction;
    }

    return NULL;
}


int count_instructions(Instruction * instruction) {
    if (instruction == NULL) {
        return 0;
    }

    return 1 + count_instructions(instruction->next_instruction);
}
