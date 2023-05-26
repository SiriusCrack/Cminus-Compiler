#ifndef _TOKEN_H_
#define _TOKEN_H_
typedef struct Token Token;
struct Token {
    int tokenClass;
    int lineNum;
    char * literal;
    union {
        int integer;
        char character;
        char * str;
    } value;
};
#endif