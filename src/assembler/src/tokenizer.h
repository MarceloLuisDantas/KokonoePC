#ifndef TOKENIZER_H
#define TOKENIZER_H

    #include "tokens.h"
    typedef struct Tokenizer {
        TokenList tokens;
        char* source;
        long position;
        long column;
        long line;
    } Tokenizer;

    Tokenizer* new_tokenizer(char* source);
    TokenList tokenize(Tokenizer* self);

#endif