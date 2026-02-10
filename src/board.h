#ifndef BOARD_H_
#define BOARD_H_

#include "cli.h"

extern const CliCmdType CMD_BOARD;
extern const CliCmdType CMD_LIST;

int doBoard(int argc, char *argv[]);
int doList(int argc, char *argv[]);

#endif /* BOARD_H_ */