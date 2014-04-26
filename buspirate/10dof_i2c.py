#!usr/bin/env python
import sys
from pyBusPirateLite.I2Chigh import *

if __name__ == '__main__':
    try:
        i2c = I2Chigh("/dev/buspirate", 115200, 5)
    except Exception, e:
        print "error", e
        sys.exit()

    print "Entering binmode: ",
    if i2c.BBmode():
        print "OK."
    else:
        print "failed."
        sys.exit()

    print "Entering raw I2C mode: ",
    if i2c.enter_I2C():
        print "OK."
    else:
        print "failed."
        sys.exit()

    print "Configuring I2C."
    if not i2c.cfg_pins(I2CPins.POWER | I2CPins.PULLUPS):
        print "Failed to set I2C peripherals."
        sys.exit()
    if not i2c.set_speed(I2CSpeed._50KHZ):
        print "Failed to set I2C Speed."
        sys.exit()
    i2c.timeout(0.2)

    print i2c.get_word(0x77, 0xaa)

    i2c.resetBP()
