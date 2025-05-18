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
} Instruction;



char is_instruction(unsigned char c) {
    return 1; // 1 means yes 0 means 0
}


Instruction * create_instruction(enum InstructionType * instruction_type, unsigned long count) {

    Instruction * instruction = (Instruction *)malloc(sizeof(Instruction));

    if (instruction == NULL) {
        return NULL;
    }
    instruction->instruction_type = instruction_type;
    instruction->count = 1;
    instruction->nested_instructions = NULL;
    instruction->next_instruction = NULL;

    return instruction;
}


Instruction * append_to_instruction(Instruction * head, Instruction * next) {

    if (next == NULL) {
        return head;
    }
    if (head == NULL) {
        return next;
    }

    head->next_instruction = append_to_instruction(head->next_instruction, next);
    return head;
}


Instruction * get_instruction_set(unsigned char * source, long n_chars) {

    Instruction * instruction, * next_instruction;
    enum InstructionType * iterator, * prev_value;

    instruction = NULL;
    next_instruction = NULL;
    iterator = NULL;
    prev_value = NULL;

    for (long i = 0; i < n_chars; i++) {

        if (*(source + i) == '\n') {
            continue;
        }

        // get current instruction
        iterator = (enum InstructionType *)(source + i);

        if (instruction == NULL) {

            instruction = create_instruction(iterator, 1);
            if (instruction == NULL) {
                // Without this, we get an infinite loop if system is out of memory
                break;
            }
            printf("\nFirst instruction set up\n");
            prev_value = iterator;
            continue;

        }

        // if the instruction is the same
        if ((char)*prev_value == (char)*iterator) {
            // just increase the instruction counter
            printf("Increasing count of current instruction\n\n");
            instruction->count++;
            continue;
        }

        printf("Need to pipe %c %c \n\n", (char)*iterator, (char)*prev_value);
        append_to_instruction(instruction, create_instruction(iterator, 1));
        prev_value = iterator;
    }

    return instruction;
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
