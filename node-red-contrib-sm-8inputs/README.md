[![8inputs-rpi](../readmeres/sequent.jpg)](https://sequentmicrosystems.com)

# node-red-contrib-sm-8inputs

This is the node-red node to control Sequent Microsystems [Eight Universal Inputs 8-Layer Stackable HAT for Raspberry Pi](https://sequentmicrosystems.com/collections/all-io-cards/products/eight-universal-inputs-br-8-layer-stackable-card-br-for-raspberry-pi-1).

## Install

Clone or update the repository, follow the instrutions fron the [first page.](https://github.com/SequentMicrosystems/8inputs-rpi)

In your node-red user directory, tipicaly ~/.node-red,

```bash
~$ cd ~/.node-red
```

Run the fallowing command:

```bash
~/.node-red$ npm install ~/8inputs-rpi/node-red-contrib-sm-8inputs
```

In order to see the node in the palette and use-it you need to restart node-red. If you run node-red as a service:
 ```bash
 ~$ node-red-stop
 ~& node-red-start
 ```

## Usage

After install and restart the node-red you will see on the node palete, under Sequent Microsystems category the fallowing node:

### 8inputs
This node reads the status of a optically isolated input.
The card stack level and input channel number can be set in the dialog screen or dinamicaly thru ``` msg.stack``` and ``` msg.channel ```.
This node will output the state of one input channel if the channel number is [1..8] or the state of all inputs if the channel number is 0

## Important note

This node is using the I2C-bus package from @fivdi, you can visit his work on github [here](https://github.com/fivdi/i2c-bus). 
The inspiration for this node came from @nielsnl68 work with [node-red-contrib-i2c](https://github.com/nielsnl68/node-red-contrib-i2c).Thank both for the great job.
