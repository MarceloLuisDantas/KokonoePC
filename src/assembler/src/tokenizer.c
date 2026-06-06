#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"

typedef struct Tokenizer {
    TokenList tokens;
    char* source;
    long position;
    long column;
    long line;
} Tokenizer;

Tokenizer* new_tokenizer(char* source) {
    Tokenizer* t = malloc(sizeof(Tokenizer));
    t->column = 1;
    t->line = 1;
    t->position = 0;
    t->source = source;
    t->tokens = new_token_list(200);
    return t;
}

char current(Tokenizer* self) {
    return self->source[self->position];
}

char next(Tokenizer* self) {
    return self->source[self->position + 1];
}

int advance(Tokenizer* self) {
    self->position++;
    self->column++;
    return self->source[self->position] == '\0';
}

char* get_slice(Tokenizer* self, long start, long end) {    
    int slice_size = end - start + 1;
    char* value = malloc(slice_size+1);
    for (int i = 0; i < slice_size; i++) {
        value[i] = self->source[start];
        start++;
    }
    value[slice_size] = '\0';
    return value;
}

void add_symbol(Tokenizer* self, TokenType t, char* value) {
    Token n = new_token(t, value, self->line, self->column);
    add_token(&self->tokens, n);
}

void add_source(Tokenizer* self) {
    long start = self->position;
    for (;;) {
        char nc = next(self);
        if (
            (nc >= 'a' && nc <= 'z') ||
            (nc >= 'A' && nc <= 'Z') ||
            (nc >= '0' && nc <= '9') ||
            (nc == '_') || (nc == '\\')
        ) {
            advance(self);
        } else {
            break;
        }
    }
    char* value = get_slice(self, start, self->position);
    add_symbol(self, SOURCE, value);
}

TokenList tokenize(Tokenizer* self) {
    add_symbol(self, BEG_OF_FILE, "BOG");
    for (;;) {
        char cr = current(self);
        switch (cr)
        {
        case '\n':
            add_symbol(self, NEW_LINE, "\\n");
            self->line++;
            self->column = 1;
            break;
        case ',':
            add_symbol(self, COMMA, ",");
            break;
        case '.':
            add_symbol(self, DIRECTIVE_NOTATION, ".");
            break;
        case ':':
            add_symbol(self, LABEL_DEF, ":");
            break;
        case '*':
            add_symbol(self, LABEL_REF, "*");
            break;
        case '"':
            add_symbol(self, QUOTATION, "\"");
            break;
        case '$':
            add_symbol(self, HEX_NUMBER, "$");
            break;
        case ';':
            while (next(self) != '\n')
                advance(self);
        case ' ':
            break;
        default:
            if (
                (cr >= 'a' && cr <= 'z') ||
                (cr >= 'A' && cr <= 'Z') ||
                (cr >= '0' && cr <= '9') ||
                cr == '_'
            ) {
                add_source(self);
            } else if (cr == 0) {
                printf("Empty file\n");
                exit(0);    
            } else {
                printf("Invalid character: '%c'\n", cr);
                printf("Line: %li, Column: %li.\n", self->line, self->column);
                exit(0);
            }
            break; 
        }

        if (advance(self)) {
            break;
        }
    }
    add_symbol(self, END_OF_FILE, "EOF");

    return self->tokens;
}