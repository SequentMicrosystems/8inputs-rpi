#include "board.h"
#include "cli.h"
#include "comm.h"
#include "data.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const CliCmdType CMD_BOARD = {
        "board",
        2,
        &doBoard,
        "  board            Display the board status and firmware version number\n",
        "  Usage:           "PROGRAM_NAME" <stack> board\n",
        "  Example:         "PROGRAM_NAME" 0 board  Display vcc, temperature, firmware version \n"

};
int doBoard(int argc, char *argv[]) {
        if(argc != 3) {
                return ARG_CNT_ERR;
        }
        int dev = doBoardInit(atoi(argv[1]));
        if(dev <= 0) {
                return ERROR;
        }
        uint8_t buf[3];
		/*
        if(OK != i2cMem8Read(dev, I2C_MEM_DIAG_TEMPERATURE_ADD, buf, 3)) {
                printf("Fail to read board info!\n");
                return ERROR;
        }
        uint8_t temperature = buf[0];
		*/
        int16_t resp;
        memcpy(&resp, &buf[1], 2);
        float vIn = (float)resp / VOLT_TO_MILIVOLT;
        if(ERROR == i2cMem8Read(dev, I2C_MEM_REVISION_MAJOR_ADD, buf, 2)) {
                printf("Fail to read board info!\n");
                return ERROR;
        }
		/*
        printf("Firmware version %d.%d, CPU temperature %d C, Power source %0.2f V\n",
                (int)buf[0], (int)buf[1], temperature, vIn);
		*/
        printf("Firmware version %d.%d, Power source %0.2f V\n",
                (int)buf[0], (int)buf[1], vIn);
        return OK;
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

const CliCmdType CMD_LIST =
	{
		"-list",
		1,
		&doList,
		"  -list:           List all 8inputs boards connected, returns\n"
		"                   nr of boards and stack level for every board\n",
		"  Usage:           8inputs -list\n",
		"  Example:         8inputs -list display: 1,0 \n"};

int doList(int argc, char *argv[])
{
	int ids[8];
	int i;
	int cnt = 0;
	u8 st = 0;

	(void)argc;
	(void)argv;

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