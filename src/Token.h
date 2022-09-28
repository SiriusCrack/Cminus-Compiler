#ifndef _TOKEN_GUARD
#define _TOKEN_GUARD
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