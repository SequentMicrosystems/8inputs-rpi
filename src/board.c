#include "board.h"
#include "cli.h"
#include "data.h"

const CliCmdType CMD_LIST =
	{
		"-list",
		1,
		&doList,
		"\t-list:       List all 8inputs boards connected,\n\treturn       nr of boards and stack level for every board\n",
		"\tUsage:       8inputs -list\n",
		"\tExample:     8inputs -list display: 1,0 \n"};

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