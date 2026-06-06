#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

char *load_file(char *file_path) { 
    FILE *fptr = fopen(file_path, "r");
    if (fptr == NULL) {
        printf("Error while loading file: %s\n", file_path);
        return NULL;
    }

    fseek(fptr, 0, SEEK_END);
    long file_len = ftell(fptr);
    rewind(fptr);

    char *file = malloc(file_len + 1);
    if (file == NULL) {
        printf("Not enough memory.\n");
        return NULL;
    }

    fread(file, 1, file_len, fptr);
    file[file_len] = '\0';
    
    return file;
}