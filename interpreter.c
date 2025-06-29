#include <stdio.h>
#include <stdlib.h>

#include "lib/loader.h"
#include "lib/executor.h"

long get_file_size(FILE *file) {
    if (file == NULL) {
        perror("File Size: Error opening file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);
    return filesize;
}

int load_file(FILE *file, unsigned char *buffer, long filesize) {
    size_t bytesRead = fread(buffer, 1, filesize, file);
    if (bytesRead != filesize) {
        perror("Error reading file");
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    long filesize = get_file_size(file);
    if (filesize < 0) {
        fclose(file);
        return 1;
    }

    unsigned char *buffer = malloc(filesize);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }

    if (load_file(file, buffer, filesize) != 0) {
        free(buffer);
        fclose(file);
        return 1;
    }

    fclose(file);

    for (long i = 0; i < filesize; ++i) {
        printf("%02x ", buffer[i]);
    }

    Instruction *instruction_set = get_instruction_set(buffer, filesize);
    printf("\nNumber of instructions: %d\n", count_instructions(instruction_set));

    Instruction *iterator = instruction_set;
    while (iterator != NULL) {
        printf("%c executed %d times\n", (char)iterator->instruction_type, (int)iterator->count);
        iterator = iterator->next_instruction;
    }

    iterator = instruction_set;
    init_instruction_handlers();
    process_instructions(iterator);

    free(buffer);
    return 0;
}
