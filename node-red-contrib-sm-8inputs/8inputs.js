module.exports = function(RED) {
    "use strict";
    var I2C = require("i2c-bus");
    const DEFAULT_HW_ADD = 0x20;
    const INPUT_REG = 0x00;
    const OUT_REG = 0x01;
    const CFG_REG = 0x03;
    
    const inMask = new ArrayBuffer(4);
    inMask[0] = 0x08;
    inMask[1] = 0x04;
    inMask[2] = 0x02;
    inMask[3] = 0x01;
    inMask[4] = 0x10;
    inMask[5] = 0x20;
    inMask[6] = 0x40;
    inMask[7] = 0x80;
    
   

    // The opto-in read Node
    function OptoReadNode(n) {
        RED.nodes.createNode(this, n);
        this.stack = parseInt(n.stack);
        this.channel = parseInt(n.channel);
        this.payload = n.payload;
        this.payloadType = n.payloadType;
        var node = this;
 
        node.port = I2C.openSync( 1 );
        node.on("input", function(msg) {
            var myPayload;
            var stack = node.stack;
            if (isNaN(stack)) stack = msg.stack;
            stack = parseInt(stack);
            var channel = node.channel;
            if (isNaN(channel + 1)) channel = msg.channel;
            channel = parseInt(channel);
            //var buffcount = parseInt(node.count);
            if (isNaN(stack + 1)) {
                this.status({fill:"red",shape:"ring",text:"Stack level ("+stack+") value is missing or incorrect"});
                return;
            } else if (isNaN(channel + 1) ) {
                this.status({fill:"red",shape:"ring",text:"Channel number  ("+channel+") value is missing or incorrect"});
                return;
            } else {
                this.status({});
            }
            var hwAdd = DEFAULT_HW_ADD;
            var found = 1;
            if(stack < 0){
                stack = 0;
            }
            if(stack > 7){
              stack = 7;
            }
            //check the type of io_expander
            hwAdd += stack ^ 0x07;
            var direction = 0xaa;
            try{
                direction = node.port.readByteSync(hwAdd, CFG_REG );
            }catch(err) {               
                found = 0;
                this.error(err,msg);
            }
            
            if(1 == found){
            try {
                if (this.payloadType == null) {
                    myPayload = this.payload;
                } else if (this.payloadType == 'none') {
                    myPayload = null;
                } else {
                    myPayload = RED.util.evaluateNodeProperty(this.payload, this.payloadType, this,msg);
                }
                
                if(direction != 0x0ff){                 
                    node.port.writeByteSync(hwAdd, CFG_REG, 0xff);
                }
                var relayVal = 0;    
                relayVal = node.port.readByteSync(hwAdd, INPUT_REG);
                if(channel < 0){
                  channel = 0;
                }
                if(channel > 8){
                  channel = 8;
                }
                if(channel == 0){
                    var i = 0;
                    var newRelayVal = 0;
                    for(i = 0; i<8; i++){
                      if(( inMask[i] & relayVal) == 0){// inverted input
                        newRelayVal |= 1<<i ;
                      }
                    }
                    msg.payload = newRelayVal;  
                }
                else{
                  channel-= 1;//zero based
                  if(relayVal & inMask[channel])
                  {
                    msg.payload = 0;
                  }
                  else
                  {
                    msg.payload = 1;
                  }
                }
                node.send(msg);
               
            } catch(err) {
                this.error(err,msg);
            }
          }
        });

        node.on("close", function() {
            node.port.closeSync();
        });
    }
    RED.nodes.registerType("8inputs", OptoReadNode);
}
