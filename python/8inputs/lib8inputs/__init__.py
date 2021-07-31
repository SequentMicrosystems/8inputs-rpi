import smbus

# bus = smbus.SMBus(1)    # 0 = /dev/i2c-0 (port I2C0), 1 = /dev/i2c-1 (port I2C1)

DEVICE_ADDRESS = 0x20  # 7 bit address (will be left shifted to add the read write bit)

RELAY4_INPORT_REG_ADD = 0x00
RELAY4_OUTPORT_REG_ADD = 0x01
RELAY4_POLINV_REG_ADD = 0x02
RELAY4_CFG_REG_ADD = 0x03


optoMaskRemap = [0x08, 0x04, 0x02, 0x01, 0x10, 0x20, 0x40, 0x80]
optoChRemap = [3, 2, 1, 0, 4, 5, 6, 7]


def __IOToOpto(iov):
    val = 0
    for i in range(0, 8):
        if (iov & optoMaskRemap[i]) == 0:
            val = val + (1 << i)
    return val


def __optoToIO(opto):
    val = 0
    for i in range(0, 8):
        if (opto & (1 << i)) == 0:
            val = val + optoMaskRemap[i]
    return val


def __check(bus, add):
    cfg = bus.read_byte_data(add, RELAY4_CFG_REG_ADD)
    if cfg != 0xff:
        bus.write_byte_data(add, RELAY4_CFG_REG_ADD, 0xff)
    return bus.read_byte_data(add, RELAY4_INPORT_REG_ADD)





def get_opto(stack, channel):
    if stack < 0 or stack > 7:
        raise ValueError('Invalid stack level')
    stack = 0x07 ^ stack
    if channel < 1:
        raise ValueError('Invalid opto channel number')
    if channel > 8:
        raise ValueError('Invalid opto channel number')
    bus = smbus.SMBus(1)
    try:
        val = __check(bus, DEVICE_ADDRESS + stack)
        bus.close()
    except Exception as e:
        bus.close()
        raise RuntimeError("Unable to communicate with 4relind with exception " + str(e))
    val = __IOToOpto(val)
    val = val & (1 << (channel - 1))
    if val == 0:
        return 0
    return 1


def get_opto_all(stack):
    if stack < 0 or stack > 7:
        raise ValueError('Invalid stack level')
    bus = smbus.SMBus(1)
    stack = 0x07 ^ stack
    try:
        val = __check(bus, DEVICE_ADDRESS + stack)
        bus.close()
    except Exception as e:
        bus.close()
        raise RuntimeError("Unable to communicate with 4relind with exception " + str(e))
    val = __IOToOpto(val)
    return val
