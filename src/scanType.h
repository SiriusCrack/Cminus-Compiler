#ifndef _TOKEN_GUARD
#define _TOKEN_GUARD
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

typedef struct Token Token;
#endif