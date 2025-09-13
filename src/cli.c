#include "board.h"
#include "button.h"
#include "cli.h"
#include "comm.h"
#include "help.h"
#include "inputs.h"
#include "led.h"
#include "opto.h"
#include "rs485.h"
#include "wdt.h"

const CliCmdType *gCmdArray[] =
{
    // Help and version commands
    &CMD_VERSION,
    &CMD_HELP,
    &CMD_WAR,
    
    // Board commands
    &CMD_BOARD,
    &CMD_LIST,
    
    // Input commands
    &CMD_IN_READ,
    &CMD_IN_SPEED_SET,
    &CMD_IN_SPEED_GET,
    
    // LED commands
    &CMD_LED_READ,
    &CMD_LED_WRITE,
    
    // Opto commands
    &CMD_OPTO_READ,
    &CMD_OPTO_EDGE_WRITE,
    &CMD_OPTO_EDGE_READ,
    &CMD_OPTO_CNT_READ,
    &CMD_OPTO_CNT_RESET,
    &CMD_OPTO_ENC_WRITE,
    &CMD_OPTO_ENC_READ,
    &CMD_OPTO_ENC_CNT_READ,
    &CMD_OPTO_ENC_CNT_RESET,
    &CMD_OPTO_FREQUENCY_READ,
    &CMD_OPTO_PWM_READ,
    
    // RS485 commands
    &CMD_CFG485_READ,
    &CMD_CFG485_WRITE,
    
    // Watchdog timer commands
    &CMD_WDT_RELOAD,
    &CMD_WDT_SET_PERIOD,
    &CMD_WDT_GET_PERIOD,
    &CMD_WDT_SET_INIT_PERIOD,
    &CMD_WDT_GET_INIT_PERIOD,
    &CMD_WDT_SET_OFF_PERIOD,
    &CMD_WDT_GET_OFF_PERIOD,
    &CMD_WDT_GET_RESET_COUNT,
    &CMD_WDT_CLR_RESET_COUNT,
    
    0
};