[![8inputs-rpi](../../readmeres/sequent.jpg)](https://sequentmicrosystems.com)

# lib8inputs

This is the python library to control the [4-RELAYS Heavy Duty Stackable Card for Raspberry Pi](https://sequentmicrosystems.com/product/raspberry-pi-relays-heavy-duty-hat/).

## Install

```bash
~$ sudo apt-get update
~$ sudo apt-get install build-essential python-pip python-dev python-smbus git
~$ git clone https://github.com/SequentMicrosystems/8inputs-rpi.git
~$ cd 8inputs-rpi/python/8inputs/
~/8inputs-rpi/python/8inputs$ sudo python setup.py install
```
## Update

```bash
~$ cd 8inputs-rpi/
~/8inputs-rpi$ git pull
~$ cd 8inputs-rpi/python/8inputs/
~/8inputs-rpi/python/8inputs$ sudo python setup.py install
```

## Usage 

Now you can import the megaio library and use its functions. To test, read relays status from the board with stack level 0:

```bash
~$ python
Python 2.7.9 (default, Sep 17 2016, 20:26:04)
[GCC 4.9.2] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> import lib8inputs
>>> lib8inputs.get_opto_all(0)
0
>>>
```

## Functions

### get_opto(stack, channel)
Get one input state.

stack - stack level of the 8-Inputs card (selectable from address jumpers [0..7])

channel - opto input channel number (id) [1..8]

return 0 == opto off; 1 - opto on

### get_opto_all(stack)
Return the state of all opto inputs.

stack - stack level of the 8-Inputs card (selectable from address jumpers [0..7])

return - [0..255]
