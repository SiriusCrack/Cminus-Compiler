typedef struct TokenData {
    // Connections
    struct TokenData * child[3];
    struct TokenData * sibling;

    // Info
    int tokenClass;
    int lineNum;
    char *tokenStr;
    
    // Data
    union {
        char cvalue;
        int nvalue;
        char *svalue;
    } value;
};