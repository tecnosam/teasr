#ifndef CONSTRUCT_LOADED
    #include "construct.h"
#endif

#ifndef UTILS_LOADED
    #include "utils.h"
#endif


#include "myio.h"


typedef void (*InstructionHandler)(Instruction* instruction);
InstructionHandler instruction_handlers[256] = {NULL};


void handle_shift_left(Instruction* instruction);
void handle_shift_right(Instruction* instruction);
void handle_increment(Instruction* instruction);
void handle_decrement(Instruction* instruction);
void handle_input(Instruction* instruction);
void handle_output(Instruction* instruction);
void handle_open_loop(Instruction* instruction);
void handle_close_loop(Instruction* instruction);



void init_instruction_handlers() {
    instruction_handlers[(char)SHIFT_LEFT] = handle_shift_left;
    instruction_handlers[(char)SHIFT_RIGHT] = handle_shift_right;
    instruction_handlers[(char)INCREMENT] = handle_increment;
    instruction_handlers[(char)DECREMENT] = handle_decrement;
    instruction_handlers[(char)INPUT] = handle_input;
    instruction_handlers[(char)OUTPUT] = handle_output;
    instruction_handlers[(char)OPEN_LOOP] = handle_open_loop;
    instruction_handlers[(char)CLOSE_LOOP] = handle_close_loop;
}


void process_instructions(Instruction* instruction) {
    enum InstructionType * instruction_type;
    InstructionHandler handler;
    
    while (instruction != NULL) {
        instruction_type = instruction->instruction_type;
        handler = instruction_handlers[*(char *)instruction_type];
        if (handler != NULL) {
            handler(instruction);
        }
        instruction = instruction->next_instruction;
    }
}


void handle_shift_left(Instruction* instruction) {
    shift_pointer(-instruction->count);
}

void handle_shift_right(Instruction* instruction) {
    shift_pointer(instruction->count);
}


void handle_increment(Instruction* instruction) {
    adjust_byte(instruction->count);
}


void handle_decrement(Instruction* instruction) {
    adjust_byte(-instruction->count);
}

void handle_input(Instruction* instruction) {
    char c = readc();
    set_current_byte(c);
}


void handle_output(Instruction* instruction) {

    char * c = get_current_byte();

    printc(*c);
}


void handle_open_loop(Instruction* instruction) {
    // TODO
    return;
}


void handle_close_loop(Instruction* instruction){
    // TODO
    return;
}