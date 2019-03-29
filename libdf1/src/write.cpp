
#include "Df1.h"

extern word tns;

/***********************************************************************/
/* Cmd:0F Fnc:AA > write 3 address fields in SLC500                    */
/* Write Protected Typed Logical                                       */
/***********************************************************************/
int write_AA(TThree_Address_Fields address, void *value, byte size)
{
	TCmd cmd;
	TMsg sendMsg, rcvMsg;
	int error = ERROR_WRITE_AA;

	bzero(&sendMsg, sizeof(sendMsg));
	bzero(&rcvMsg, sizeof(rcvMsg));
	bzero(&cmd, sizeof(cmd));
	sendMsg.dst = DEST;
	sendMsg.src = SOURCE;
	sendMsg.cmd = 0x0F;
	sendMsg.sts = 0x00;
	sendMsg.tns = ++tns;
	cmd.fnc = 0xAA;
	cmd.size = address.size;
	cmd.fileNumber = address.fileNumber;
	cmd.fileType = address.fileType;
	cmd.eleNumber = address.eleNumber;
	cmd.s_eleNumber = address.s_eleNumber;
	memcpy(&sendMsg.data, &cmd, sizeof(cmd));
	sendMsg.size = sizeof(cmd);
	memcpy(&sendMsg.data[sendMsg.size], value, cmd.size);
	sendMsg.size += cmd.size;
	if ((error = send_DF1(sendMsg)) != 0)
		return error;
	if ((error = rcv_DF1(&rcvMsg)) != 0)
		return error;
	if (rcvMsg.tns != sendMsg.tns)
		return ERROR_TNS_MISMATCH;
	if (rcvMsg.sts != 0)
		return rcvMsg.sts;
	return SUCCES;
}


/***********************************************************************/
/* Cmd:0F Fnc:AB > write W/4 fields & mask in SLC500                   */
/* Write 1 bit in SLC                                                  */
/***********************************************************************/
int write_AB(TThree_Address_Fields address, word value, word mask)
{
	TCmd4 cmd;
	TMsg sendMsg, rcvMsg;
	int error = ERROR_WRITE_AB;

	bzero(&sendMsg, sizeof(sendMsg));
	bzero(&rcvMsg, sizeof(rcvMsg));
	bzero(&cmd, sizeof(cmd));
	sendMsg.dst = DEST;
	sendMsg.src = SOURCE;
	sendMsg.cmd = 0x0F;
	sendMsg.sts = 0x00;
	sendMsg.tns = ++tns;
	cmd.fnc = 0xAB;
	cmd.size = address.size;
	cmd.fileNumber = address.fileNumber;
	cmd.fileType = address.fileType;
	cmd.eleNumber = address.eleNumber;
	cmd.s_eleNumber = 0x00;
	cmd.maskbyte = mask;
	cmd.value = value;
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
	return SUCCES;
}


//*********************************************************
int write_boolean(int plctype, char *straddress, int *value)
{
	int error = ERROR_READ_INTEGER;
	TThree_Address_Fields address;
	byte posit;
	word valuebool;
	word mask;

	if ((error = calc_address(straddress, &address)) != SUCCES)
		return error;
	posit = address.s_eleNumber;
	if (plctype == SLC) {
		mask = 0x0001 << posit;
		if (*value)
			valuebool = 0x0001 << posit;
		else
			valuebool = 0x0000;
		error = write_AB(address, valuebool, mask);
	}
	return error;
}


//*********************************************************
int write_float(int plctype, char *straddress, float *value)
{
	int error = ERROR_WRITE;
	TThree_Address_Fields address;

	if ((error = calc_address(straddress, &address)) != SUCCES)
		return error;
	if (plctype == SLC)
		error = write_AA(address, value, sizeof(*value));
	return error;
}

//*********************************************************
int write_integer(int plctype, char *straddress, word *value)
{
	int error = ERROR_WRITE;
	TThree_Address_Fields address;

	if ((error = calc_address(straddress, &address)) != SUCCES)
		return error;
	if (plctype == SLC)
		error = write_AA(address, value, sizeof(*value));
	return error;
}




