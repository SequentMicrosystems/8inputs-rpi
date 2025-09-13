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
#include "data.h"
#include "comm.h"

#define VERSION_BASE	(int)1
#define VERSION_MAJOR	(int)1
#define VERSION_MINOR	(int)0

#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */
#define CMD_ARRAY_SIZE	8

// I2C register definitions
#define RELAY8_INPORT_REG_ADD 0x00
#define RELAY8_CFG_REG_ADD 0x03
#define RELAY8_HW_I2C_BASE_ADD 0x20
#define RELAY8_OUTPORT_REG_ADD 0x01

#define I2C_MEM_HS_ENABLE 0x10
#define I2C_MEM_HS_DISABLE 0x11
#define I2C_MEM_HS_MODE_VAL 0x12

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

const CliCmdType CMD_WAR =
{
    "-warranty",
    1,
    &doWarranty,
    "  -warranty        Display the warranty\n",
    "  Usage:           "PROGRAM_NAME" -warranty\n"
    "",
    "  Example:         "PROGRAM_NAME" -warranty  Display the warranty text\n"
};

const CliCmdType CMD_IN_READ =
{
    "read",
    2,
    &doInRead,
    "  read             Read inputs status\n",
    "  Usage:           "PROGRAM_NAME" <id> read <channel>\n"
    "  Usage:           "PROGRAM_NAME" <id> read\n",
    "  Example:         "PROGRAM_NAME" 0 read 2; Read Status of Input #2 on Board #0\n"
};

const CliCmdType CMD_IN_SPEED_SET =
{
    "spdwr",
    2,
    &doHiSpeedSet,
    "  spdwr            Set input speed for individual channel 0 = low speed; 1 = high speed\n",
    "  Usage:           "PROGRAM_NAME" <id> spdwr <channel> <value>\n"
    "",
    "  Example:         "PROGRAM_NAME" 0 spdwr 2 0; Set Low Speed of Input #2 on Board #0\n"
};

const CliCmdType CMD_IN_SPEED_GET =
{
    "spdrd",
    2,
    &doHiSpeedGet,
    "  spdrd            Get input speed for individual channel 0 = low speed; 1 = high speed\n",
    "  Usage:           "PROGRAM_NAME" <id> spdrd <channel>\n"
    "",
    "  Example:         "PROGRAM_NAME" 0 spdrd 2; Get Speed of Input #2 on Board #0\n"
};

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



int inChGet(int dev, u8 channel, State* state)
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




/*
 * doInRead:
 *	Read inputs state
 ******************************************************************************************
 */
int doInRead(int argc, char *argv[])
{
    int pin = 0;
    int val = 0;
    int dev = 0;
    State state = STATE_COUNT;

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
            return ARG_RANGE_ERROR;
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

int doHiSpeedSet(int argc, char *argv[])
{
    int dev = 0;
    int channel = 0;
    int speed = 0;

    if (argc != 5)
    {
        return ARG_CNT_ERR;
    }

    dev = doBoardInit(atoi(argv[1]));
    if (dev <= 0)
    {
        return ERROR;
    }

    channel = atoi(argv[3]);
    speed = atoi(argv[4]);

    if ( (channel < CHANNEL_NR_MIN) || (channel > IN_CH_NR_MAX))
    {
        printf("Input channel number value out of range!\n");
        return ARG_RANGE_ERROR;
    }

    if (speed < 0 || speed > 1)
    {
        printf("Invalid speed value! Use 0 for low speed and 1 for high speed.\n");
        return ARG_RANGE_ERROR;
    }
    uint8_t buff[1];
    buff[0] = (uint8_t)(channel); // 
    // Set the speed for the specified channel
    if(speed == 1)
    {

        if(OK != i2cMem8Write(dev, I2C_MEM_HS_ENABLE, buff, 1)) // High speed enable
        {
            printf("Fail to set high speed!\n");
            return ERROR;
        }
    }
    else
    {
        if(OK != i2cMem8Write(dev, I2C_MEM_HS_DISABLE, buff, 1)) // High speed disable
        {
            printf("Fail to set low speed!\n");
            return ERROR;
        }
    }
    return OK;

}

int doHiSpeedGet(int argc, char *argv[])
{
    int dev = 0;
    int channel = 0;
    uint8_t buff[1];

    if (argc != 4)
    {
        return ARG_CNT_ERR;
    }

    dev = doBoardInit(atoi(argv[1]));
    if (dev <= 0)
    {
        return ERROR;
    }

    channel = atoi(argv[3]);

    if ( (channel < CHANNEL_NR_MIN) || (channel > IN_CH_NR_MAX))
    {
        printf("Input channel number value out of range!\n");
        return ARG_RANGE_ERROR;
    }

    // Get the speed for the specified channel
    if(OK != i2cMem8Read(dev, I2C_MEM_HS_MODE_VAL, buff, 1)) // High speed enable
    {
        printf("Fail to get speed!\n");
        return ERROR;
    }
    if(buff[0] & (1 << (channel - 1)))
    {
        printf("1\n"); // High speed
    }
    else
    {
        printf("0\n"); // Low speed
    }
    return OK;

}

int doWarranty(int argc, char* argv[])
{
    UNUSED(argc);
    UNUSED(argv);
    printf("%s\n", warranty);
    return OK;
}