struct Token {
    int tokenClass;
    int lineNum;
    char * literal;
    union TokenData {
        int integer;
        char character;
        char * str;
    } value;
};