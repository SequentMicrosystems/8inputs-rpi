/*
 * relay.c:
 *	Command-line interface to the Raspberry
 *	Pi's 4-Relay board.
 *	Copyright (c) 2016-2021 Sequent Microsystem
 *	<http://www.sequentmicrosystem.com>
 ***********************************************************************
 *	Author: Alexandru Burcea
 ***********************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "inputs.h"
#include "comm.h"

#define VERSION_BASE	(int)1
#define VERSION_MAJOR	(int)0
#define VERSION_MINOR	(int)0

#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */
#define CMD_ARRAY_SIZE	8

const u8 inMaskRemap[IN_CH_NR_MAX] =
{
	0x08,
	0x04,
	0x02,
	0x01,
	0x10,
	0x20,
	0x40,
	0x80};

const int inChRemap[IN_CH_NR_MAX] =
{
	3,
	2,
	1,
	0,
	4,
	5,
	6,
	7};


u8 IOToIn(u8 io);

int doHelp(int argc, char *argv[]);
const CliCmdType CMD_HELP =
	{
		"-h",
		1,
		&doHelp,
		"\t-h          Display the list of command options or one command option details\n",
		"\tUsage:      8inputs -h    Display command options list\n",
		"\tUsage:      8inputs -h <param>   Display help for <param> command option\n",
		"\tExample:    8inputs -h write    Display help for \"write\" command option\n"};

static int doVersion(int argc, char *argv[]);
const CliCmdType CMD_VERSION =
{
	"-v",
	1,
	&doVersion,
	"\t-v              Display the version number\n",
	"\tUsage:          8inputs -v\n",
	"",
	"\tExample:        8inputs -v  Display the version number\n"};

static int doWarranty(int argc, char* argv[]);
const CliCmdType CMD_WAR =
{
	"-warranty",
	1,
	&doWarranty,
	"\t-warranty       Display the warranty\n",
	"\tUsage:          8inputs -warranty\n",
	"",
	"\tExample:        8inputs -warranty  Display the warranty text\n"};

static int doList(int argc, char *argv[]);
const CliCmdType CMD_LIST =
	{
		"-list",
		1,
		&doList,
		"\t-list:       List all 8inputs boards connected,\n\treturn       nr of boards and stack level for every board\n",
		"\tUsage:       8inputs -list\n",
		"",
		"\tExample:     8inputs -list display: 1,0 \n"};

static int doInRead(int argc, char *argv[]);
const CliCmdType CMD_IN_READ =
{
	"read",
	2,
	&doInRead,
	"\tread:        Read inputs status\n",
	"\tUsage:       8inputs <id> read <channel>\n",
	"\tUsage:       8inputs <id> read\n",
	"\tExample:     8inputs 0 read 2; Read Status of Input #2 on Board #0\n"};



char *warranty =
	"	       Copyright (c) 2016-2020 Sequent Microsystems\n"
		"                                                             \n"
		"		This program is free software; you can redistribute it and/or modify\n"
		"		it under the terms of the GNU Leser General Public License as published\n"
		"		by the Free Software Foundation, either version 3 of the License, or\n"
		"		(at your option) any later version.\n"
		"                                    \n"
		"		This program is distributed in the hope that it will be useful,\n"
		"		but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
		"		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
		"		GNU Lesser General Public License for more details.\n"
		"			\n"
		"		You should have received a copy of the GNU Lesser General Public License\n"
		"		along with this program. If not, see <http://www.gnu.org/licenses/>.";

void usage(void)
{
	int i = 0;
	while (gCmdArray[i] != NULL)
	{
		if (gCmdArray[i]->name != NULL)
		{
			if (strlen(gCmdArray[i]->usage1) > 2)
			{
				printf("%s", gCmdArray[i]->usage1);
			}
			if (strlen(gCmdArray[i]->usage2) > 2)
			{
				printf("%s", gCmdArray[i]->usage2);
			}
		}
		i++;
	}
	printf("Where: <id> = Board level id = 0..7\n");
	printf("Type 8inputs -h <command> for more help\n");
}


u8 IOToIn(u8 io)
{
	u8 i;
	u8 val = 0;
	for (i = 0; i < IN_CH_NR_MAX; i++)
	{
		if ( (io & inMaskRemap[i]) == 0)
		{
			val += 1 << i;
		}
	}
	return val;
}



int inChGet(int dev, u8 channel, OutStateEnumType* state)
{
	u8 buff[2];

	if (NULL == state)
	{
		return ERROR;
	}

	if ( (channel < CHANNEL_NR_MIN) || (channel > IN_CH_NR_MAX))
	{
		printf("Invalid relay nr!\n");
		return ERROR;
	}

	if (FAIL == i2cMem8Read(dev, RELAY8_INPORT_REG_ADD, buff, 1))
	{
		return ERROR;
	}

	if ( (buff[0] & (inMaskRemap[channel - 1])) == 0)
	{
		*state = ON;
	}
	else
	{
		*state = OFF;
	}
	return OK;
}

int inGet(int dev, int* val)
{
	u8 buff[2];

	if (NULL == val)
	{
		return ERROR;
	}
	if (FAIL == i2cMem8Read(dev, RELAY8_INPORT_REG_ADD, buff, 1))
	{
		return ERROR;
	}
	*val = IOToIn(buff[0]);
	return OK;
}

int doBoardInit(int stack)
{
	int dev = 0;
	int add = 0;
	uint8_t buff[8];

	if ( (stack < 0) || (stack > 7))
	{
		printf("Invalid stack level [0..7]!");
		return ERROR;
	}
	add = (stack + RELAY8_HW_I2C_BASE_ADD) ^ 0x07;
	dev = i2cSetup(add);
	if (dev == -1)
	{
		return ERROR;
	}
	if (ERROR == i2cMem8Read(dev, RELAY8_CFG_REG_ADD, buff, 1))
	{
		printf("4-RELAY_PLUS card id %d not detected\n", stack);
		return ERROR;
	}
//	if (buff[0] != 0x0f) //non initialized I/O Expander
//	{
//		// make 4 I/O pins input and 4 output
//		buff[0] = 0x0f;
//		if (0 > i2cMem8Write(dev, RELAY8_CFG_REG_ADD, buff, 1))
//		{
//			return ERROR;
//		}
//		// put all pins in 0-logic state
//		buff[0] = 0;
//		if (0 > i2cMem8Write(dev, RELAY8_OUTPORT_REG_ADD, buff, 1))
//		{
//			return ERROR;
//		}
//	}

	return dev;
}



int boardCheck(int hwAdd)
{
	int dev = 0;
	uint8_t buff[8];

	hwAdd ^= 0x07;
	dev = i2cSetup(hwAdd);
	if (dev == -1)
	{
		return FAIL;
	}
	if (ERROR == i2cMem8Read(dev, RELAY8_CFG_REG_ADD, buff, 1))
	{
		return ERROR;
	}
	return OK;
}

/*
 * doInRead:
 *	Read inputs state
 ******************************************************************************************
 */
static int doInRead(int argc, char *argv[])
{
	int pin = 0;
	int val = 0;
	int dev = 0;
	OutStateEnumType state = STATE_COUNT;

	dev = doBoardInit(atoi(argv[1]));
	if (dev <= 0)
	{
		return ERROR;
	}

	if (argc == 4)
	{
		pin = atoi(argv[3]);
		if ( (pin < CHANNEL_NR_MIN) || (pin > IN_CH_NR_MAX))
		{
			printf("Input channel number value out of range!\n");
			return ARG_ERR;
		}

		if (OK != inChGet(dev, pin, &state))
		{
			printf("Fail to read!\n");
			return ERROR;
		}
		if (state != 0)
		{
			printf("1\n");
		}
		else
		{
			printf("0\n");
		}
	}
	else if (argc == 3)
	{
		if (OK != inGet(dev, &val))
		{
			printf("Fail to read!\n");
			exit(1);
		}
		printf("%d\n", val);
	}
	else
	{
		return ARG_CNT_ERR;
	}
	return OK;
}

int doHelp(int argc, char *argv[])
{
	int i = 0;
	if (argc == 3)
	{
		while (NULL != gCmdArray[i])
		{
			if (gCmdArray[i]->name != NULL)
			{
				if (strcasecmp(argv[2], gCmdArray[i]->name) == 0)
				{
					printf("%s%s%s%s", gCmdArray[i]->help, gCmdArray[i]->usage1,
						gCmdArray[i]->usage2, gCmdArray[i]->example);
					break;
				}
			}
			i++;
		}
		if (NULL == gCmdArray[i])
		{
			printf("Option \"%s\" not found\n", argv[2]);
			i = 0;
			while (NULL != gCmdArray[i])
			{
				if (gCmdArray[i]->name != NULL)
				{
					printf("%s", gCmdArray[i]->help);
					break;
				}
				i++;
			}
		}
	}
	else
	{
		i = 0;
		while (NULL != gCmdArray[i])
		{
			if (gCmdArray[i]->name != NULL)
			{
				printf("%s", gCmdArray[i]->help);
			}
			i++;
		}
	}
	return OK;
}

static int doVersion(int argc, char *argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	printf("8inputs v%d.%d.%d Copyright (c) 2016 - 2021 Sequent Microsystems\n",
	VERSION_BASE, VERSION_MAJOR, VERSION_MINOR);
	printf("\nThis is free software with ABSOLUTELY NO WARRANTY.\n");
	printf("For details type: 8inputs -warranty\n");
	return OK;

}

static int doList(int argc, char *argv[])
{
	int ids[8];
	int i;
	int cnt = 0;
	u8 st = 0;

	UNUSED(argc);
	UNUSED(argv);

	for (i = 0; i < 8; i++)
	{
		st = i;
		if (boardCheck(RELAY8_HW_I2C_BASE_ADD + st) == OK)
		{
			ids[cnt] = i;
			cnt++;
		}
	}
	printf("%d board(s) detected\n", cnt);
	if (cnt > 0)
	{
		printf("Id:");
	}
	while (cnt > 0)
	{
		cnt--;
		printf(" %d", ids[cnt]);
	}
	printf("\n");
	return OK;
}



static int doWarranty(int argc, char* argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	printf("%s\n", warranty);
	return OK;
}



const CliCmdType *gCmdArray[] =
{
	&CMD_VERSION,
	&CMD_HELP,
	&CMD_WAR,
	&CMD_LIST,
	&CMD_IN_READ,
	NULL
};

int main(int argc, char *argv[])
{
	int i = 0;
	int ret = OK;

	if (argc == 1)
	{
		usage();
		return -1;
	}
	while (NULL != gCmdArray[i])
	{
		if ( (gCmdArray[i]->name != NULL) && (gCmdArray[i]->namePos < argc))
		{
			if (strcasecmp(argv[gCmdArray[i]->namePos], gCmdArray[i]->name) == 0)
			{
				ret = gCmdArray[i]->pFunc(argc, argv);
				if (ret == ARG_CNT_ERR)
				{
					printf("Invalid parameters number!\n");
					printf("%s", gCmdArray[i]->usage1);
					if (strlen(gCmdArray[i]->usage2) > 2)
					{
						printf("%s", gCmdArray[i]->usage2);
					}
				}
				return ret;
			}
		}
		i++;
	}
	printf("Invalid command option\n");
	usage();

	return -1;
}
