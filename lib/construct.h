enum InstructionType {
    SHIFT_LEFT = '<',
    SHIFT_RIGHT = '>',
    INCREMENT = '+',
    DECREMENT = '-',
    INPUT = ',',
    OUTPUT = '.',
    OPEN_LOOP = '[',
    CLOSE_LOOP = ']'
};


typedef struct Instruction {
    enum InstructionType * instruction_type;
    unsigned long count;  // number of times to execute instruction
    struct Instruction * nested_instructions;
    struct Instruction * next_instruction;
    struct Instruction * last_instruction;
} Instruction;



char is_instruction(unsigned char c) {
    return 1; // 1 means yes 0 means 0
}


Instruction * create_instruction(enum InstructionType * instruction_type, unsigned long count, Instruction * last_instruction) {

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


Instruction * get_instruction_set(unsigned char * source, long n_chars) {

    Instruction * instruction, * last_instruction;
    enum InstructionType * current_value, * prev_value;

    last_instruction = NULL;
    instruction = NULL;

    current_value = NULL;
    prev_value = NULL;

    for (long i = 0; i < n_chars; i++) {

        if (*(source + i) == '\n') {
            continue;
        }

        // get current instruction
        current_value = (enum InstructionType *)(source + i);

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
        if ((char)*prev_value == (char)*current_value) {
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


int count_instructions(Instruction * instruction) {
    if (instruction == NULL) {
        return 0;
    }

    if (instruction->instruction_type == NULL) {
        return 0;
    }

    return 1 + count_instructions(instruction->next_instruction);
}
