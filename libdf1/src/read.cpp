#include "Df1.h"

extern word tns;

/***********************************************************************/
/* Cmd:0F Fnc:A2 > Read 3 address fields in SLC500                     */
/* Read Protected Typed Logical                                        */
/***********************************************************************/
int read_A2(TThree_Address_Fields address, void *value, byte size)
{
	TCmd cmd;
	TMsg sendMsg, rcvMsg;

	int error = ERROR_READ_A2;

	bzero(value, size);
	bzero(&sendMsg, sizeof(sendMsg));
	bzero(&rcvMsg, sizeof(rcvMsg));
	bzero(&cmd, sizeof(cmd));
	sendMsg.dst = DEST;
	sendMsg.src = SOURCE;
	sendMsg.cmd = 0x0F;
	sendMsg.sts = 0x00;
	sendMsg.tns = ++tns;
	cmd.fnc = 0xA2;
	cmd.size = address.size;
	cmd.fileNumber = address.fileNumber;
	cmd.fileType = address.fileType;
	cmd.eleNumber = address.eleNumber;
	cmd.s_eleNumber = address.s_eleNumber;
	memcpy(&sendMsg.data, &cmd, sizeof(cmd));
	sendMsg.size = sizeof(cmd);
	if ((error = send_DF1(sendMsg)) != 0)
		return error;
	if ((error = rcv_DF1(&rcvMsg)) != 0)
		return error;
	if (rcvMsg.tns != sendMsg.tns)
		return ERROR_TNS_MISMATCH;
	if (rcvMsg.sts != 0)
		return rcvMsg.sts;
	memcpy(value, rcvMsg.data, address.size);
	return SUCCES;
}

//*********************************************************
int read_boolean(int plctype, char *straddress, int *value)
{
	int error = ERROR_READ_INTEGER;
	TThree_Address_Fields address;
	byte posit;
	int temp = 1;
	int tempvalue;

	tempvalue = 0;//init to 0
	if ((error = calc_address(straddress, &address)) != SUCCES)
		return error;
	posit = address.s_eleNumber;
	address.s_eleNumber = 0;
	if (plctype == SLC)
		error = read_A2(address, &tempvalue, sizeof(tempvalue));
	*value = (temp&(tempvalue >> posit));
	return error;
}

//*********************************************************
int read_float(int plctype, char *straddress, float *value)
{
	int error = ERROR_READ_INTEGER;
	TThree_Address_Fields address;

	*value = 0;//init to 0
	if ((error = calc_address(straddress, &address)) != SUCCES)
		return error;
	if (plctype == SLC)
		error = read_A2(address, value, sizeof(*value));
	return error;
}

//*********************************************************
int read_integer(int plctype, char *straddress, word *value)
{
	int error = ERROR_READ_INTEGER;
	TThree_Address_Fields address;

	*value = 0;//init to 0
	if ((error = calc_address(straddress, &address)) != SUCCES)
		return error;
	if (plctype == SLC)
		error = read_A2(address, value, sizeof(*value));
	return error;
}
