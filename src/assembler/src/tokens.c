#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum {
    NEW_LINE,           // \n
    COMMA,              // ,
    SOURCE,             // any string without symbol
    DIRECTIVE_NOTATION, // .
    DIRECTIVE_DEFINE,   //
    DIRECTIVE_GLOBAL,   //
    DIRECTIVE_TEXT,   //
    DIRECTIVE_DATA,   //
    DIRECTIVE_INT8,   //
    DIRECTIVE_INT16,   //
    DIRECTIVE_STRING,   //
    CONSTANT_LABEL,     //
    INSTRUCTION,        //
    REGISTER,           //
    LABEL,              // 
    LABEL_DEF,          // foo:
    LABEL_REF,          // *foo 
    DEC_NUMBER,         // 123123             
    BIN_NUMBER,         // b0110111             
    HEX_NUMBER,         // $AA             
    QUOTATION,          // "
    STRING,             // 
    BEG_OF_FILE,        //
    END_OF_FILE         //
} TokenType;

typedef struct Token {
    TokenType type;
    long line;
    long column;
    char* value;
} Token;

Token new_token(TokenType type, char* value, long line, long column) {
    Token t = {
        .type = type,
        .value = value,
        .line = line,
        .column = column
    };
    return t;
}

void print_token(Token t) {
    printf("{");
    switch (t.type)
    {
    case NEW_LINE:
        printf("NEW_LINE, ");
        break;
    case COMMA:
        printf("COMMA, ");
        break;
    case SOURCE:
        printf("SOURCE, ");
        break;
    case DIRECTIVE_NOTATION:
        printf("DIRECTIVE_NOTATION, ");
        break;
    case DIRECTIVE_DEFINE:
        printf("DIRECTIVE_DEFINE, ");
        break;
    case DIRECTIVE_GLOBAL:
        printf("DIRECTIVE_GLOBAL, ");
        break;
    case DIRECTIVE_TEXT:
        printf("DIRECTIVE_TEXT, ");
        break;
    case DIRECTIVE_DATA:
        printf("DIRECTIVE_DATA, ");
        break;
    case DIRECTIVE_INT8:
        printf("DIRECTIVE_INT8, ");
        break;
    case DIRECTIVE_INT16:
        printf("DIRECTIVE_INT16, ");
        break;
    case DIRECTIVE_STRING:
        printf("DIRECTIVE_STRING, ");
        break;
    case INSTRUCTION:
        printf("INSTRUCTION, ");
        break;
    case REGISTER:
        printf("REGISTER, ");
        break;
    case LABEL_DEF:
        printf("LABEL_DEF, ");
        break;
    case LABEL_REF:
        printf("LABEL_REF, ");
        break;
    case DEC_NUMBER:
        printf("DEC_NUMBER, ");
        break;
    case BIN_NUMBER:
        printf("BIN_NUMBER, ");
        break;
    case HEX_NUMBER:
        printf("HEX_NUMBER, ");
        break;
    case QUOTATION:
        printf("QUOTATION, ");
        break;
    case STRING:
        printf("STRING, ");
        break;
    
    default:
        break;
    }
    printf("\'%s\', ", t.value);
    printf("line: %li, ", t.line);
    printf("column: %li}\n", t.column);
}

typedef struct TokenList {
    Token* array;
    long len;
    long capacity;
} TokenList;

TokenList new_token_list(long initial_capacity) {
    TokenList tl = {
        .array = malloc(sizeof(Token) * initial_capacity),
        .capacity = initial_capacity,
        .len = 0
    };
    return tl;
}

void add_token(TokenList* self, Token value) {
    if (self->len == self->capacity) {
        long new_capacity = self->capacity + (self->capacity/2);
        Token* new_array = malloc(sizeof(Token) * new_capacity);
        if (new_array == NULL) {
            printf("Not enough memory\n");
            exit(0);
        }

        memcpy(new_array, self->array, sizeof(Token) * self->capacity);
        free(self->array);
        self->array = new_array;
        self->capacity = new_capacity;
    }

    self->array[self->len] = value;
    self->len++;
}

// '\n' or ','
void add_divider_token(TokenList* self, char value, long line, long column) {
    char* nl = malloc(2);
    nl[0] = value;
    nl[1] = '\0';
    Token t = new_token(NEW_LINE, nl, line, column);
    add_token(self, t);
}