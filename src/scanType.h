struct NumConst {
    int lineNum;
    char * tokenStr;
    int value;
};
struct ID {
    int lineNum;
    char * tokenStr;
    char * value;
};
struct CharConst {
    int lineNum;
    char * tokenStr;
    char value;
};
struct StringConst {
    int lineNum;
    char * tokenStr;
    char * value;
};
struct BoolConst {
    int lineNum;
    char * tokenStr;
    int value;
};
struct Operand {
    int lineNum;
    char * tokenStr;
    char * value;
};