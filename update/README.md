
# update

This is the Eight HV Inputs Card firmware update tool.

## Usage

```bash
git clone https://github.com/SequentMicrosystems/8inputs-rpi.git
cd 8inputs-rpi/update/
./update 0
```


If you clone the repository already, skip the first step. 
The command will download the newest firmware version from our server and write it  to the board.
The stack level of the board must be provided as a parameter. 
During firmware update we strongly recommend to stop all the program/scripts tha use I2C port.
