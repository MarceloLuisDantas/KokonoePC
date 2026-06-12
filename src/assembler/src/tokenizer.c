#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "tokens.h"

bool ok = true;

typedef struct Tokenizer {
    TokenList tokens;
    TokenList labels;
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

TokenType last_token_type(Tokenizer* self) {
    return self->tokens.array[self->tokens.len-1].type;
}

void add_label(Tokenizer *self, char* value) {
    for (int i = 0; i < self->labels.len; i++) {
        Token label = self->labels.array[i];
        if (strcmp(label.value, value)) {
            printf("\n");
            printf("Label \"%s\" defined multiple times.\n", value);
            printf("First defined in line: %li.\n", label.line);
            return;
        }
    }
    Token l = new_token(LABEL, value, self->line, self->column);
    add_token(&self->tokens, l);
    add_token(&self->labels, l);
}

char* read_source(Tokenizer* self) {
    long start = self->position;
    for (;;) {
        char nc = next(self);
        if (
            (nc >= 'a' && nc <= 'z') ||
            (nc >= 'A' && nc <= 'Z') ||
            (nc >= '0' && nc <= '9') ||
            (nc == '_')
        ) {
            advance(self);
        } else if (
            (nc == ',') || (nc == ' ') || (nc == '\n')
        ) {
            break;
        } else {
            printf("Invalid character: \'%c\'\n", nc);
            printf("Line: %li, Column: %li\n", self->line, self->column);
            ok = false;
            return NULL;
        }
    }
    char* value = get_slice(self, start, self->position);
    return value;
}

void add_source(Tokenizer* self) {
    long start = self->position;
    for (;;) {
        char nc = next(self);
        if (
            (nc >= 'a' && nc <= 'z') ||
            (nc >= 'A' && nc <= 'Z') ||
            (nc >= '0' && nc <= '9') ||
            (nc == '_')
        ) {
            advance(self);
        } else {
            break;
        }
    }
    char* value = get_slice(self, start, self->position);
    TokenType ltt = last_token_type(self);
    if (ltt == LABEL_REF) {
        char* n_value = malloc(strlen(value)+2);
        n_value[0] = '*';
        for (size_t i = 1; i < strlen(value)+2; i++) {
            n_value[i] = value[i-1];
        }
        free(self->tokens.array[self->tokens.len-1].value);
        self->tokens.array[self->tokens.len-1].value = n_value;
        return;
    } 

    if (strlen(value) == 1) {
        if (
            (value[0] == 'a') || 
            (value[0] == 'x') || 
            (value[0] == 'y') || 
            (value[0] == 'z')
        ) {
            add_symbol(self, REGISTER, value);
            return;
        } 
    } else if (strlen(value) == 2) {
        if (strcmp(value, "sp") == 0) {
            add_symbol(self, REGISTER, value);
            return;
        }
    }
    

    add_symbol(self, SOURCE, value);
}

TokenType get_token_type(TokenList* self, int i) {
    return self->array[i].type;
}

void set_token_type(TokenList* self, int i, TokenType type) {
    self->array[i].type = type;
}

void read_directive(Tokenizer* self) {
    char* source = read_source(self);
    if (strcmp(".define", source) == 0) {
        add_symbol(self, DIRECTIVE_DEFINE, source);
    } else if (strcmp(".int8", source) == 0) {
        add_symbol(self, DIRECTIVE_INT8, source);
    } else if (strcmp(".int16", source) == 0) {
        add_symbol(self, DIRECTIVE_INT16, source);
    } else if (strcmp(".string", source) == 0) {
        add_symbol(self, DIRECTIVE_STRING, source);
    } else if (strcmp(".text", source) == 0) {
        add_symbol(self, DIRECTIVE_TEXT, source);
    } else if (strcmp(".data", source) == 0) { 
        add_symbol(self, DIRECTIVE_DATA, source);
    } else if (strcmp(".global", source) == 0) { 
        add_symbol(self, DIRECTIVE_GLOBAL, source);
    } else {
        printf("Invalid directive: %s\n", source);
        printf("Line: %li.\n", self->line);
    }
}

void read_label_ref(Tokenizer* self) {
    char* source = read_source(self);
    add_symbol(self, LABEL_REF, source);
}

void read_string(Tokenizer* self) {
    long start = self->position;
    if (advance(self)) {
        printf("File ended during string declaration.\n");
        exit(0);
    }
    bool valid = true;
    for (;;) {
        char nc = next(self);
        if (nc == '\"') {
            advance(self);
            break;
        } else if (nc == '\n') {
            printf("Missing terminating \".\n");
            printf("Line: %li, Column: %li\n", self->line, self->column);
            return;
        } else if (nc == '\\') {
            advance(self);
            char scape = next(self);
            if (!((scape == '0') || (scape == 'n'))) {
                printf("Invalid scape chracater: \'%c\'\n", scape);
                valid = false;
            }
        }
        if (advance(self)) {
            printf("File ended during string declaration.\n");
            exit(0);
        }
    }
    if (valid) {
        char* str = get_slice(self, start, self->position);
        add_symbol(self, STRING, str);
    } else {
        ok = false;
    }
}

void read_hexa(Tokenizer* self) {
    long start = self->position;
    bool valid = true;
    for (;;) {
        char nc = next(self);
        if ((nc == '\n') || (nc == 0) || (nc == ',') || (nc == ' ')) {
            break;
        } 
        
        if (!(
            (nc >= 'A' && nc <= 'F') ||
            (nc >= '0' && nc <= '9') 
        )) {
            printf("Invalid hexadecimal chracater: \'%c\'\n", nc);
            printf("Line: %li, Column: %li\n", self->line, self->column);
            valid = false;
        }

        if (advance(self)) {
            printf("File ended abruptly.\n");
            exit(0);
        }
    }
    if (self->position - start == 0) {
        printf("Empty hexadecimal number.\n");
        printf("Line: %li, Column: %li\n", self->line, self->column);
        valid = false;
    }

    if (valid) {
        char* str = get_slice(self, start, self->position);
        add_symbol(self, HEX_NUMBER, str);
    } else {
        ok = false;
    }
}

void read_binarie(Tokenizer* self) {
    long start = self->position;
    bool valid = true;
    for (;;) {
        char nc = next(self);
        if ((nc == '\n') || (nc == 0)) {
            break;
        } 
        
        if (!(nc == '1' || nc == '0')) {
            printf("Invalid binarie chracater: \'%c\'\n", nc);
            printf("Line: %li, Column: %li\n", self->line, self->column);
            valid = false;
        }

        if (advance(self)) {
            printf("File ended abruptly.\n");
            exit(0);
        }
    }
    if (self->position - start == 0) {
        printf("Empty binarie number.\n");
        printf("Line: %li, Column: %li\n", self->line, self->column);
        valid = false;
    }

    if (valid) {
        char* str = get_slice(self, start, self->position);
        add_symbol(self, BIN_NUMBER, str);
    } else {
        ok = false;
    }
}

TokenList tokenize(Tokenizer* self) {
    add_symbol(self, BEG_OF_FILE, "BOG");
    for (;;) {
        TokenType ltt = last_token_type(self);
        char cr = current(self);
        switch (cr)
        {
        case '\n':
            add_symbol(self, NEW_LINE, "\\n");
            self->line++;
            self->column = 1;
            break;
        case ',':
            if (
                ltt == REGISTER || 
                ltt == BIN_NUMBER ||
                ltt == DEC_NUMBER ||
                ltt == HEX_NUMBER 
            ) {
                add_symbol(self, COMMA, ",");
            } else {
                printf("Bad use of ','.\n");
                printf("Line: %li, Column: %li\n", self->line, self->column);
            }
            break;
        case '.':
            read_directive(self);
            break;
        case ':':
            TokenType ltt = last_token_type(self);
            if (ltt == SOURCE) {
                set_token_type(&self->tokens, self->tokens.len-1, LABEL_DEF);
                char* og_str = self->tokens.array[self->tokens.len-1].value;
                long og_len = strlen(og_str) + 1;
                char* c = malloc(sizeof(char) * (og_len + 1));
                strcpy(c, og_str);
                c[og_len-1] = ':';
                c[og_len] = '\0';
                free(og_str);
                self->tokens.array[self->tokens.len-1].value = c;
            }
            break;
        case '*':
            read_label_ref(self);
            break;
        case '"':
            read_string(self);
            break;
        case '$':
            read_hexa(self);
            break;
        case '%':
            read_binarie(self);
        case ' ':
            break;
        case ';':
            if (next(self) == 0)
                goto ended;
            while (next(self) != '\n') 
                if (advance(self)) 
                    goto ended;        
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

ended:
    add_symbol(self, END_OF_FILE, "EOF");

    if (!ok) {
        exit(0);
    }

    return self->tokens;
}