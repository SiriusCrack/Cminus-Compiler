typedef struct TokenData {
    int tokenClass;
    int linenum;
    char *tokenstr;
    char cvalue;
    int nvalue;
    char *svalue;
} *tokenPtr;
