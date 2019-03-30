#include "Df1.h"


// 1 : read_integer
// 2 : read_boolean
// 3 : read_float
// 11: write_integer
// 12: write_boolean
// 13: write_float
int select_fnct(char *strquery, char *address, char *value) {
    int result = ERROR;
    int x;
    char filetype[] = "OISBTCRNF";
    int writequery = false;
    char *varaddress;
    char *varvalue;

    const char delimiters[] = "=\n\r";

    // begin by alphafile ?
    if(strchr(filetype, toupper(strquery[0])) == NULL) {
        return ERROR_BAD_QUERY;
    }

    // find : in query ?
    if(strchr(strquery, 58)==NULL) {
        return ERROR_BAD_QUERY;
    }

    // find = in query ?
    if(strchr(strquery,61)!=NULL) {
        writequery = TRUE;
    }

    varaddress = strsep(&strquery,delimiters);
    
    // upper ALL
    for(x=0;x<strlen(varaddress);x++) {
        if(isalpha(varaddress[x])) {
            varaddress[x] = toupper(varaddress[x]);
        }
    }
    printf("substring=%i=%s\n",strlen(varaddress),varaddress);
    strcpy(address,varaddress);

    if(writequery) {
        varvalue = strsep(&strquery,delimiters);
        printf("substring=%i=%s\n",strlen(varvalue),varvalue);
        strcpy(value,varvalue);
    }

    switch (toupper(varaddress[0]))
    {
        case '0':
        case 'I':
        case 'S':
        case 'B':
        case 'T':
        case 'C':
        case 'R':
        case 'N':
            result = 1;
            break;
        case 'F':
            result = 3;
    }
    /*
    // find '.' in query ?
    if (strchr(varaddress,'.')!=NULL) {
        result = 2;
    }

    // find '/' in query ?
    if (strchr(varaddress,'/')!=NULL) {
        result = 2;
    }


    // find ACC in query ?
    if (strchr(varaddress,'ACC')!=NULL) {
        result = 1;
    }


    // find PRE in query ?
    if (strchr(varaddress,'PRE')!=NULL) {
        result = 1;
    }


    // find LEN in query ?
    if (strchr(varaddress,'LEN')!=NULL) {
        result = 1;
    }


    // find POS in query ?
    if (strchr(varaddress,'POS')!=NULL) {
        result = 1;
    }


    // find EN  in query ?
    if (strchr(varaddress,'EN')!=NULL) {
        result = 2;
    }

   
    // find TT  in query ?
    if (strchr(varaddress,'TT')!=NULL) {
        result = 2;
    }


    // find DN  in query ?
    if (strchr(varaddress,'DN')!=NULL) {
        result = 2;
    }
    */
    if(writequery) {
        result += 10;
    }

    return result;


}