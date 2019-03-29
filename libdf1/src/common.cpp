#include "df1.h"

extern int file;

/***********************************************************************/
word bytes2word(byte lowb, byte highb)
{
	word w;
	char c[2];//={lowb,highb};
	c[0] = lowb;
	c[1] = highb;
	memcpy(&w, c, sizeof(w));
	return w;
}

/***********************************************************************/
int add_word2buffer(TBuffer * buffer, word value) /* return new buffer size */
{
	memcpy(buffer->data + buffer->size, &value, sizeof(value));
	buffer->size += sizeof(value);
	return buffer->size;
}


/***********************************************************************/
int add_byte2buffer(TBuffer * buffer, byte value) /* return new buffer size */
{
	memcpy(buffer->data + buffer->size, &value, sizeof(value));
	buffer->size += sizeof(value);
	return buffer->size;
}

/***********************************************************************/
int add_data2buffer(TBuffer * buffer, void * data, byte size) /* return new buffer size */
{
	memcpy(buffer->data + buffer->size, data, size);
	buffer->size += size;
	return buffer->size;
}

/***********************************************************************/
/* Add DLE if DLE exist in buffer **************************************/
int add_data2bufferWithDLE(TBuffer * buffer, TMsg msg) /* return new buffer size */
{
	byte  i;
	byte databyte[262];
	memcpy(&databyte, &msg, sizeof(msg));
	for (i = 0; i < msg.size + 6; i++)
	{
		if (databyte[i] == DLE)
			add_byte2buffer(buffer, DLE);
		add_byte2buffer(buffer, databyte[i]);
	}
	return buffer->size;
}

/***********************************************************************/
int is_timeout(int start_time)
{
	if ((time((time_t *)0) - start_time) > TIME_OUT)
		return ERROR_TIMEOUT;
	else
		return SUCCES;
}

/***********************************************************************/
void print_symbol(byte c)
{
	switch (c)
	{
	case STX:
		puts("STX\n");
		break;
	case ETX:
		puts("ETX\n");
		break;
	case ENQ:
		puts("ENQ\n");
		break;
	case ACK:
		puts("ACK\n");
		break;
	case NAK:
		puts("NAK\n");
		break;
	case DLE:
		puts("DLE\n");
		break;
	default: printf("??:%02X\n", c);
	}
}


int calc_address(char *straddress, TThree_Address_Fields *address)
{
	int error = ERROR_CALC_ADDRESS;
	int x, l;
	bzero(address, sizeof(*address));
	address->size = 0;
	address->fileNumber = 0;
	address->fileType = 0;
	address->eleNumber = 0;
	address->s_eleNumber = 0;
	for (x = 0; x < strlen(straddress); x++)
	{
		switch (straddress[x])
		{
		case 'O':
			address->fileType = 0x8b;
			address->fileNumber = 0;
			address->size = 2;
			break;
		case 'I':
			address->fileType = 0x8c;
			address->fileNumber = 1;
			address->size = 2;
			break;
		case 'S':
			x++;
			address->fileType = 0x84;
			address->fileNumber = atoi(&straddress[x]);
			address->size = 2;
			break;
		case 'B':
			x++;
			address->fileType = 0x85;
			address->fileNumber = atoi(&straddress[x]);
			address->size = 2;
			break;
		case 'T':
			x++;
			address->fileType = 0x86;
			address->fileNumber = atoi(&straddress[x]);
			address->size = 2;
			break;
		case 'C':
			x++;
			address->fileType = 0x87;
			address->fileNumber = atoi(&straddress[x]);
			address->size = 2;
			break;
		case 'R':
			x++;
			address->fileType = 0x88;
			address->fileNumber = atoi(&straddress[x]);
			address->size = 2;
			break;
		case 'N':
			x++;
			address->fileType = 0x89;
			address->fileNumber = atoi(&straddress[x]);
			address->size = 2;
			break;
		case 'F':
			x++;
			address->fileType = 0x8a;
			address->fileNumber = atoi(&straddress[x]);
			address->size = 4;
			break;
		case ':':
			address->eleNumber = atoi(&straddress[++x]);
			break;
		case '.':
		case '/':
			x++;
			if (isdigit(straddress[x])) {
				address->s_eleNumber = atoi(&straddress[x]);
			}
			l = strlen(straddress) - x;
			if (strncasecmp(&straddress[x], "acc", l) == 0)
				address->s_eleNumber = 2;
			if (strncasecmp(&straddress[x], "pre", l) == 0)
				address->s_eleNumber = 1;
			if (strncasecmp(&straddress[x], "len", l) == 0)
				address->s_eleNumber = 1;
			if (strncasecmp(&straddress[x], "pos", l) == 0)
				address->s_eleNumber = 2;
			if (strncasecmp(&straddress[x], "en", l) == 0)
				address->s_eleNumber = 13;
			if (strncasecmp(&straddress[x], "tt", l) == 0)
				address->s_eleNumber = 14;
			if (strncasecmp(&straddress[x], "dn", l) == 0)
				address->s_eleNumber = 15;
			x = strlen(straddress) - 1;
		}
	}
	error = SUCCES;
	return error;
}
