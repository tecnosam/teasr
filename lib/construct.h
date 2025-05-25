#define CONSTRUCT_LOADED 1

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
    enum InstructionType instruction_type;
    unsigned long count;  // number of times to execute instruction
    struct Instruction * nested_instructions;
    struct Instruction * next_instruction;
    struct Instruction * last_instruction;
} Instruction;


const enum InstructionType instruction_types[] = {
    SHIFT_LEFT,
    SHIFT_RIGHT,
    INCREMENT,
    DECREMENT,
    INPUT,
    OUTPUT,
    OPEN_LOOP,
    CLOSE_LOOP
};

#define INSTRUCTION_TYPE_COUNT (sizeof(instruction_types) / sizeof(instruction_types[0]))