#ifndef INPUTS_H
#define INPUTS_H

#include <stdint.h>
#include "cli.h"
#include "data.h"

#define IN_CH_NR_MAX 8
#define CHANNEL_NR_MIN 1

typedef uint8_t u8;

// Command declarations
extern const CliCmdType CMD_WAR;
extern const CliCmdType CMD_IN_READ;
extern const CliCmdType CMD_IN_SPEED_SET;
extern const CliCmdType CMD_IN_SPEED_GET;

// Function declarations
int doWarranty(int argc, char *argv[]);
int doInRead(int argc, char *argv[]);
int doHiSpeedSet(int argc, char *argv[]);
int doHiSpeedGet(int argc, char *argv[]);

// Helper functions
int inChGet(int dev, u8 channel, State* state);
int inGet(int dev, int* val);
u8 IOToIn(u8 io);

#endif /* INPUTS_H */