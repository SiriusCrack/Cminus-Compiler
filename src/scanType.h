#ifndef TOKEN_GUARD
#define TOKEN_GUARD
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