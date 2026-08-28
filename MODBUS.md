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

## Slave Address
The slave address is added with the "stack level" DIP switches. For example, the DIP switch configuration for stack level 1 (one switch in position ID0 is ON) with a slave address offset of 1 corresponds to slave address 2.

## Modbus object types
All Modbus RTU object types with standard addresses are implemented: Coils, Discrete Inputs, Input registers, and Holding registers.

### Coils

Access level: Read/Write, Size: 1 bit

| Device function | Register Address | Modbus Address |
| --- | --- | --- |
| COIL_LED1_MODE| 001 | 0x00|
|	COIL_LED2_MODE
	COIL_LED3_MODE,
	COIL_LED4_MODE,
	COIL_LED5_MODE,
	COIL_LED6_MODE,
	COIL_LED7_MODE,
	COIL_LED8_MODE,
	COIL_LED1,
	COIL_LED2,
	COIL_LED3,
	COIL_LED4,
	COIL_LED5,
	COIL_LED6,
	COIL_LED7,
	COIL_LED8,
	COIL_IN1_COUNT_ENABLE,
	COIL_IN2_COUNT_ENABLE,
	COIL_IN3_COUNT_ENABLE,
	COIL_IN4_COUNT_ENABLE,
	COIL_IN5_COUNT_ENABLE,
	COIL_IN6_COUNT_ENABLE,
	COIL_IN7_COUNT_ENABLE,
	COIL_IN8_COUNT_ENABLE,
	COIL_ENCODER1_ENABLE,
	COIL_ENCODER2_ENABLE,
	COIL_ENCODER3_ENABLE,
	COIL_ENCODER4_ENABLE,
| COIL_LED1 | 0001 | 0x00 |
| COIL_LED2 | 0002 | 0x01 |
| COIL_LED3 | 0003 | 0x02 |
| COIL_LED4 | 0004 | 0x03 |
| COIL_LED5 | 0005 | 0x04 |
| COIL_LED6 | 0006 | 0x05 |
| COIL_LED7 | 0007 | 0x06 |
| COIL_LED8 | 0008 | 0x07 |


### Discrete Inputs

Access level Read Only, Size 1 bit

| Device function | Register Address | Modbus Address |
| --- | --- | --- |
| | | |


### Input registers

Access level Read Only, Size 16 bits

| Device function | Register Address | Modbus Address| Description | Measurement Unit |
| --- | --- | --- | --- | --- |
| IR_VIN_H1| 30001 | 0x00 | In voltage, High 16 bits of IEEE 754 number | V |
| IR_VIN_L1| 30002 | 0x01 | In voltage, Low 16 bits of IEEE 754 number | V |
| IR_VIN_H2| 30003 | 0x02 | In voltage, High 16 bits of IEEE 754 number | V |
| IR_VIN_L2| 30004 | 0x03 | In voltage, Low 16 bits of IEEE 754 number | V |
| IR_VIN_H3| 30005 | 0x04 | In voltage, High 16 bits of IEEE 754 number | V |
| IR_VIN_L3| 30006 | 0x05 | In voltage, Low 16 bits of IEEE 754 number | V |
| IR_VIN_H4| 30007 | 0x06 | In voltage, High 16 bits of IEEE 754 number | V |
| IR_VIN_L4| 30008 | 0x07 | In voltage, Low 16 bits of IEEE 754 number | V |
| IR_VIN_H5| 30009 | 0x0a | In voltage, High 16 bits of IEEE 754 number | V |
| IR_VIN_L5| 30010 | 0x0b | In voltage, Low 16 bits of IEEE 754 number | V |
| IR_VIN_H6| 30011 | 0x0c | In voltage, High 16 bits of IEEE 754 number | V |
| IR_VIN_L6| 30012 | 0x0d | In voltage, Low 16 bits of IEEE 754 number | V |
| IR_VIN_H7| 30013 | 0x0e | In voltage, High 16 bits of IEEE 754 number | V |
| IR_VIN_L7| 30014 | 0x0f | In voltage, Low 16 bits of IEEE 754 number | V |
| IR_VIN_H8| 30015 | 0x10 | In voltage, High 16 bits of IEEE 754 number | V |
| IR_VIN_L8| 30016 | 0x11 | In voltage, Low 16 bits of IEEE 754 number | V |


### Holding registers

Access level Read/Write, Size 16 bits

| Device function | Register Address | Modbus Address | Range | Description |
| --- | --- | --- | --- | --- |
| HR_GAIN_1 | 40001 | 0x00 | 0..7 | Gain Settings for CH1 |
| HR_GAIN_2 | 40002 | 0x01 | 0..7 | Gain Settings for CH2 |
| HR_GAIN_3 | 40003 | 0x02 | 0..7 | Gain Settings for CH3 |
| HR_GAIN_4 | 40004 | 0x03 | 0..7 | Gain Settings for CH4 |
| HR_GAIN_5 | 40005 | 0x04 | 0..7 | Gain Settings for CH5 |
| HR_GAIN_6 | 40006 | 0x05 | 0..7 | Gain Settings for CH6 |
| HR_GAIN_7 | 40007 | 0x06 | 0..7 | Gain Settings for CH7 |
| HR_GAIN_8 | 40008 | 0x07 | 0..7 | Gain Settings for CH8 |

Gain settings:
|Code | Full scale |
| --- | --- |
| 0 | ±24 V|
| 1 | ±12 V|
| 2 | ±6 V|
| 3 | ±3 V|
| 4 | ±1.5 V|
| 5 | ±750 mV|
| 6 | ±370 mV|
| 7 | ±180 mV|



## Function codes implemented

* Read Coils (0x01)
* Read Discrete Inputs (0x02)
* Read Holding Registers (0x03)
* Read Input Registers (0x04)
* Write Single Coil (0x05)
* Write Single Register (0x06)
* Write Multiple Coils (0x0f)
* Write Multiple registers (0x10)
