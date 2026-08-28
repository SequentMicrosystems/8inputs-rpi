# Modbus

The [Eight HV Digital Inputs 8-Layer Stackable HAT for Raspberry Pi](https://sequentmicrosystems.com/products/eight-hv-digital-inputs-for-raspberry-pi) can be accessed through the Modbus RTU protocol over the RS-485 port.
You can configure the RS-485 port using the **8inputs** command.

Example:
```bash
~$ 8inputs 0 cfg485wr 1 1 9600 1 0
```
Set Modbus RTU, slave address offset = 1, baud rate 9600bps, one stop bit, parity none
```bash
~$ 8inputs -h cfg485wr
```
Displays the full set of options

### Default:
 38400 8N1 Modbus RTU Enabled.
 
## Slave Address
The slave address is set with the "stack level" DIP switches. For example, the DIP switch configuration for stack level 1 (one switch in position ID0 is ON) with a slave address offset of 1 corresponds to slave address 2.

## Modbus object types
All Modbus RTU object types with standard addresses are implemented: Coils, Discrete Inputs, Input registers, and Holding registers.

### Coils

Access level: Read/Write, Size: 1 bit

| Device function | Register Address | Modbus Address |
| --- | --- | --- |
|   COIL_LED1_MODE | 001 | 0x00 |
|   COIL_LED2_MODE | 002 | 0x01 |
|	COIL_LED3_MODE | 003 | 0x02 |
|	COIL_LED4_MODE | 004 | 0x03 |
|	COIL_LED5_MODE | 005 | 0x04 |
|	COIL_LED6_MODE | 006 | 0x05 |
|	COIL_LED7_MODE | 007 | 0x06 |
|	COIL_LED8_MODE | 008 | 0x07 |
|	COIL_LED1_MODE | 001 | 0x00 |
|	COIL_LED2_MODE | 002 | 0x01 |
|	COIL_LED3_MODE | 003 | 0x02 |
|	COIL_LED4_MODE | 004 | 0x03 |
|	COIL_LED5_MODE | 005 | 0x04 |
|	COIL_LED6_MODE | 006 | 0x05 |
|	COIL_LED7_MODE | 007 | 0x06 |
|	COIL_LED8_MODE | 008 | 0x07 |
|	COIL_IN1_COUNT_ENABLE | 009 | 0x08 |
|	COIL_IN2_COUNT_ENABLE | 010 | 0x09 |
|	COIL_IN3_COUNT_ENABLE | 011 | 0x0a |
|	COIL_IN4_COUNT_ENABLE | 012 | 0x0b |
|	COIL_IN5_COUNT_ENABLE | 013 | 0x0c |
|	COIL_IN6_COUNT_ENABLE | 014 | 0x0d |
|	COIL_IN7_COUNT_ENABLE | 015 | 0x0e |
|	COIL_IN8_COUNT_ENABLE | 016 | 0x0f |
|	COIL_ENCODER1_ENABLE | 017 | 0x10 |
|	COIL_ENCODER2_ENABLE | 018 | 0x11 |
|	COIL_ENCODER3_ENABLE | 019 | 0x12 |
|	COIL_ENCODER4_ENABLE | 020 | 0x13 |



### Discrete Inputs

Access level Read Only, Size 1 bit

| Device function | Register Address | Modbus Address | Description | Measurement Unit |
| --- | --- | --- | --- | --- |
| DI_IN1 | 10001 | 0x00 | Digital input 1 | |
| DI_IN2 | 10002 | 0x01 | Digital input 2 | |
| DI_IN3 | 10003 | 0x02 | Digital input 3 | |
| DI_IN4 | 10004 | 0x03 | Digital input 4 | |
| DI_IN5 | 10005 | 0x04 | Digital input 5 | |
| DI_IN6 | 10006 | 0x05 | Digital input 6 | |
| DI_IN7 | 10007 | 0x06 | Digital input 7 | |
| DI_IN8 | 10008 | 0x07 | Digital input 8 | |
| DI_AC_IN1 | 10009 | 0x08 | AC filtered input 1 | |
| DI_AC_IN2 | 10010 | 0x09 | AC filtered input 2 | |
| DI_AC_IN3 | 10011 | 0x0a | AC filtered input 3 | |
| DI_AC_IN4 | 10012 | 0x0b | AC filtered input 4 | |
| DI_AC_IN5 | 10013 | 0x0c | AC filtered input 5 | |
| DI_AC_IN6 | 10014 | 0x0d | AC filtered input 6 | |
| DI_AC_IN7 | 10015 | 0x0e | AC filtered input 7 | |
| DI_AC_IN8 | 10016 | 0x0f | AC filtered input 8 | |
| DI_BUTTON | 10017 | 0x10 | User button | |
| | | |


### Input registers

Access level Read Only, Size 16 bits

| Device function | Register Address | Modbus Address| Description | Measurement Unit |
| --- | --- | --- | --- | --- |
| IR_COUNT1_L| 30001 | 0x00 | Input count 1, Low 16 bits | |
| IR_COUNT1_H| 30002 | 0x01 | Input count 1, High 16 bits | |
| IR_COUNT2_L| 30003 | 0x02 | Input count 2, Low 16 bits | |
| IR_COUNT2_H| 30004 | 0x03 | Input count 2, High 16 bits | |
| IR_COUNT3_L| 30005 | 0x04 | Input count 3, Low 16 bits | |
| IR_COUNT3_H| 30006 | 0x05 | Input count 3, High 16 bits | |
| IR_COUNT4_L| 30007 | 0x06 | Input count 4, Low 16 bits | |
| IR_COUNT4_H| 30008 | 0x07 | Input count 4, High 16 bits | |
| IR_COUNT5_L| 30009 | 0x08 | Input count 5, Low 16 bits | |
| IR_COUNT5_H| 30010 | 0x09 | Input count 5, High 16 bits | |
| IR_COUNT6_L| 30011 | 0x0a | Input count 6, Low 16 bits | |
| IR_COUNT6_H| 30012 | 0x0b | Input count 6, High 16 bits | |
| IR_COUNT7_L| 30013 | 0x0c | Input count 7, Low 16 bits | |
| IR_COUNT7_H| 30014 | 0x0d | Input count 7, High 16 bits | |
| IR_COUNT8_L| 30015 | 0x0e | Input count 8, Low 16 bits | |
| IR_COUNT8_H| 30016 | 0x0f | Input count 8, High 16 bits | |
| IR_PPS1| 30017 | 0x10 | Pulses per second 1 | |
| IR_PPS2| 30018 | 0x11 | Pulses per second 2 | |
| IR_PPS3| 30019 | 0x12 | Pulses per second 3 | |
| IR_PPS4| 30020 | 0x13 | Pulses per second 4 | |
| IR_PPS5| 30021 | 0x14 | Pulses per second 5 | |
| IR_PPS6| 30022 | 0x15 | Pulses per second 6 | |
| IR_PPS7| 30023 | 0x16 | Pulses per second 7 | |
| IR_PPS8| 30024 | 0x17 | Pulses per second 8 | |
| IR_ENC_VAL1_L| 30025 | 0x18 | Encoder value 1, Low 16 bits | |
| IR_ENC_VAL1_H| 30026 | 0x19 | Encoder value 1, High 16 bits | |
| IR_ENC_VAL2_L| 30027 | 0x1a | Encoder value 2, Low 16 bits | |
| IR_ENC_VAL2_H| 30028 | 0x1b | Encoder value 2, High 16 bits | |
| IR_PWM1_FILL| 30029 | 0x1c | PWM 1 fill | % |
| IR_PWM2_FILL| 30030 | 0x1d | PWM 2 fill | % |
| IR_PWM3_FILL| 30031 | 0x1e | PWM 3 fill | % |
| IR_PWM4_FILL| 30032 | 0x1f | PWM 4 fill | % |
| IR_PWM1_FREQ| 30033 | 0x20 | PWM 1 frequency |Hz|
| IR_PWM2_FREQ| 30034 | 0x21 | PWM 2 frequency |Hz|
| IR_PWM3_FREQ| 30035 | 0x22 | PWM 3 frequency |Hz|
| IR_PWM4_FREQ| 30036 | 0x23 | PWM 4 frequency |Hz|
	


### Holding registers

Access level: Read/Write, Size 16 bits

| Device function | Register Address | Modbus Address | Range | Description |
| --- | --- | --- | --- | --- |
| HR_RESET_COUNT_CHANNEL | 40009 | 0x08  | 1..8 | Write 1..8 to reset respective channel|
| HR_RESET_ENCODER_CHANNEL | 40010 | 0x09 | 1..4 | Write 1..4 to reset respective encoder channel |




## Function codes implemented

* Read Coils (0x01)
* Read Discrete Inputs (0x02)
* Read Holding Registers (0x03)
* Read Input Registers (0x04)
* Write Single Coil (0x05)
* Write Single Register (0x06)
* Write Multiple Coils (0x0f)
* Write Multiple registers (0x10)
