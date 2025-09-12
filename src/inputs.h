#ifndef INPUTS_H
#define INPUTS_H

#include <stdint.h>
#include "cli.h"

#define IN_CH_NR_MAX 8
#define CHANNEL_NR_MIN 1

typedef uint8_t u8;

typedef enum
{
    OFF = 0,
    ON,
    STATE_COUNT
} OutStateEnumType;

// Error codes
#define OK 0
#define ERROR -1
#define FAIL -1
#define ARG_CNT_ERR -2
#define ARG_ERR -3
#define ARG_RANGE_ERROR -4

// Command declarations
extern const CliCmdType CMD_HELP;
extern const CliCmdType CMD_VERSION;
extern const CliCmdType CMD_WAR;
extern const CliCmdType CMD_IN_READ;
extern const CliCmdType CMD_IN_SPEED_SET;
extern const CliCmdType CMD_IN_SPEED_GET;

// Function declarations
int doHelp(int argc, char *argv[]);
int doVersion(int argc, char *argv[]);
int doWarranty(int argc, char *argv[]);
int doInRead(int argc, char *argv[]);
int doHiSpeedSet(int argc, char *argv[]);
int doHiSpeedGet(int argc, char *argv[]);

// Helper functions
int doBoardInit(int stack);
int boardCheck(int hwAdd);
int inChGet(int dev, u8 channel, OutStateEnumType* state);
int inGet(int dev, int* val);
u8 IOToIn(u8 io);

#endif /* INPUTS_H */