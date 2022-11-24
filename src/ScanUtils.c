#include "ScanUtils.h"
#include <string.h>

char CleanChar(char *inputString) {
    if(inputString[1] == '\\') {
        switch (inputString[2]) {
            case 'n':
                return '\n';
            break;
            case '0':
                return '\0';
            break;
            default:
                return inputString[2];
            break;
        }
    } else {
        return inputString[1];
    }
}

char* CleanString(char *inputString) {
    char *returnString = inputString;
    returnString += 1;
    returnString = strdup(returnString);
    returnString[strlen(returnString)-1] = '\0';
    int length = strlen(returnString);
    for(int i = 0; i < length; i++) {
        if(returnString[i] == '\\') {
            switch (returnString[i+1]) {
                case 'n':
                    returnString[i+1] = '\n';
                break;
                case '0':
                    returnString[i+1] = '\0';
                break;
                case '\\':
                    i++;
                break;
            }
            for(int j = i; j < length; j++) {
                returnString[j] = returnString[j+1];
            }
            i--;
            length--;
        }
    }
    return returnString;
}