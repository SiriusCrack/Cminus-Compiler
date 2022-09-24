typedef struct TokenData {
    int tokenClass;
    int linenum;
    char *tokenstr;
    union {
        char cvalue;
        int nvalue;
        char *svalue;
    } value;
} *tokenPtr;