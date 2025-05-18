#define MEMORY_CELL_SIZE 30000


unsigned char MEMORY_CELL[MEMORY_CELL_SIZE+1];
int universal_pointer = 0;


void initialize_cell() {
    // Set all characters in cell to 0

    for (int i = 0; i < MEMORY_CELL_SIZE; i++) {
        MEMORY_CELL[i] = 0;
    }
}


void shift_pointer(int count) {
    // TODO: dont handle this silently, raise exceptions

    if (universal_pointer + count >= MEMORY_CELL_SIZE) {
        universal_pointer = MEMORY_CELL_SIZE -1;
        return;
    }
    else if (universal_pointer + count < 0) {
        universal_pointer = 0;
        return;
    }

    universal_pointer += count;
}


void adjust_byte(int count) {

    *(MEMORY_CELL + universal_pointer) += count;
}


char * get_current_byte() {
    return (char *)(MEMORY_CELL + universal_pointer);
}


void set_current_byte(char * c) {
    // TODO: this might not make so much sense if variable c is signed
    *(MEMORY_CELL + universal_pointer) = *((unsigned char *)c);
}
