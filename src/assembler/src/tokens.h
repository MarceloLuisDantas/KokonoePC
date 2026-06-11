#ifndef TOKENS_H
#define TOKENS_H

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

    typedef struct TokenList {
        Token* array;
        long len;
        long capacity;
    } TokenList;

    Token new_token(TokenType type, char* value, long line, long column);
    TokenList new_token_list(long initial_capacity);    
    void add_divider_token(TokenList* self, char value, long line, long column);
    void add_token(TokenList* self, Token value);
    void print_token(Token t);

#endif