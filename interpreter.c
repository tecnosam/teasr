
#include <stdlib.h>

#include "lib/loader.h"
#include "lib/executor.h"


long get_file_size(FILE *file) {

    if (file == NULL) {
        perror("File Size: Error opening file");
        return -1;
    }
    // Move to end of file to get size
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);  // Go back to the beginning

    return filesize;
}


int load_file(FILE *file, unsigned char *buffer, long filesize) {

    // Read into buffer
    size_t bytesRead = fread(buffer, 1, filesize, file);
    if (bytesRead != filesize) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return 1;
    }

    return 0;
}



int main() {

    char filename[100];
    printf("Enter filename: ");
    scanf("%99s", filename);

    // Open in binary mode
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    long filesize = get_file_size(file);
    if (filesize < 0) {
        perror("Could not get file size!");
        return 1;
    }

    // Allocate buffer
    unsigned char *buffer = malloc(filesize);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    load_file(file, buffer, filesize);

    // close file
    fclose(file);

    // // Example usage: print as hex
    for (long i = 0; i < filesize; ++i) {
        printf("%02x ", buffer[i]);
    }
    Instruction * instruction_set = get_instruction_set(buffer, filesize);
    printf("\nNumber of instructions: %d\n", count_instructions(instruction_set));

    Instruction * iterator;
    iterator = instruction_set;

    while (iterator != NULL) {
        printf("%c executed %d times\n", (char)iterator->instruction_type, (int) iterator->count);
        iterator = iterator->next_instruction;
    }

    iterator = instruction_set;
    init_instruction_handlers();
    process_instructions(iterator);

    free(buffer);
    return 0;

}
