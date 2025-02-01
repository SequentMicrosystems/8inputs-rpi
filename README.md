[![8inputs-rpi](readmeres/sequent.jpg)](https://www.sequentmicrosystems.com)

# 8inputs-rpi


This is the command to control [Eight Universal Inputs 8-Layer Stackable HAT for Raspberry Pi](https://sequentmicrosystems.com/products/eight-hv-digital-inputs-for-raspberry-pi)

Don't forget to enable I2C communication, instructions [here](https://www.raspberrypi-spy.co.uk/2014/11/enabling-the-i2c-interface-on-the-raspberry-pi/)


## Install

```bash
~$ git clone https://github.com/SequentMicrosystems/8inputs-rpi.git
~$ cd 8inputs-rpi/
~/8inputs-rpi$ sudo make install
```
## Usage
Now you can access all the functions of the card through the command "8inputs". Use -h option for help:
```bash
~$ 8inputs -h
```
## Update
If you clone the repository any update can be made with the following commands:

```bash
~$ cd 8inputs-rpi/  
~/8inputs-rpi$ git pull
~/8inputs-rpi$ sudo make install
```  

Diferent software interfaces and examples are available:
* [Python Library](https://github.com/SequentMicrosystems/8inputs-rpi/tree/main/python)
* [Python Example](https://github.com/SequentMicrosystems/8inputs-rpi/blob/main/python/tests.py)
* [Node-Red Nodes](https://github.com/SequentMicrosystems/8inputs-rpi/tree/main/node-red-contrib-sm-8inputs) 
* [Node-Red Example](https://github.com/SequentMicrosystems/8inputs-rpi/tree/main/node-red-contrib-sm-8inputs/example)
