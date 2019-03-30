#include "Df1.h"

int read_socket(const char *rcvmsg, char* response) {
    char* message = new char[255];
    strcpy(message,rcvmsg);

    int error=ERROR;

    int fnct;
    int plctype=SLC;

    word value;
    int varbool;
    float varfloat;

    char Address[20];
    char writevalue[20];

    fnct=select_fnct(message,Address,writevalue);
    switch (fnct)
    {
        case 1:
            if ((error=read_integer(plctype,Address,&value))==SUCCES) {
                sprintf(response,"%d",value);
            }
            break;
        case 2:
            if ((error=read_boolean(plctype,Address,&varbool))==SUCCES) {
                sprintf(response,"%i",varbool);
            }
            break;
        case 3:
            if ((error=read_float(plctype,Address,&varfloat))==SUCCES) {
                sprintf(response,"%d",value);
            }
            break;
        case 11:
            value = atoi(writevalue);
            if((error=write_integer(plctype,Address,&value))==SUCCES) {
                sprintf(response,"%d",value);
            }
            break;
        case 12:
            varbool = atoi(writevalue);
            if((error=write_boolean(plctype,Address,&varbool))==SUCCES) {
                sprintf(response,"%d",value);
            }
            break;
        case 13:
            varfloat = atoi(writevalue);
            if((error=write_float(plctype,Address,&varfloat))==SUCCES) {
                sprintf(response,"%d",value);
            }
            break;
        default:
            error=fnct;
            break;
    }
    return error;
}