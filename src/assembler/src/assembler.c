#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <strings.h>
#include "files.h"
#include "tokenizer.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Use: kasm [file_name.kasm]\n");
        return 0;
    }

    char* file_name = argv[1];
    
    char* file = load_file(file_name);
    if (file == NULL) {
        return 0;
    }
    
    Tokenizer* t = new_tokenizer(file);
    if (t == NULL) {
        return 0;
    }
    
    TokenList tokens = tokenize(t);
    for (int i = 0; i < tokens.len; i++) {
        print_token(tokens.array[i]);
    }

    return 0;
}