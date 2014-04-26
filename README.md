#trinket
an adafruit trinket project

##setup
list of parts and documentation
###parts list
####hardware
* [adafruit trinket w/ 3.3v logic](http://www.adafruit.com/products/1500)
* [dangerous prototypes bus pirate v3.6](http://dangerousprototypes.com/docs/Bus_Pirate)
* [adafruit 10dof imu breakout](https://www.adafruit.com/products/1604)
   * [L3GD20 triple axis gyro](http://www.adafruit.com/products/1032)
   * [LSM303 triple axis accelerometer+magnetometer](http://www.adafruit.com/products/1120)
   * [BMP180 barometer+thermometer+altimeter](http://www.adafruit.com/products/1603)
* [bus pirate probe set](https://www.adafruit.com/products/238)
* [6ft usb mini-b cable](https://www.sparkfun.com/products/11301)
* [mini breadboard](https://www.sparkfun.com/products/12044)
* [6' female/male jumpers](https://www.adafruit.com/products/826)

####software
* [Ubuntu 14.04](http://www.ubuntu.com/download/desktop)
* [avrdude](http://www.nongnu.org/avrdude/)
* [avr-gcc](http://gcc.gnu.org/wiki/avr-gcc)
* [minicom](http://en.wikipedia.org/wiki/Minicom)
* [pyBusPirateLite](http://dangerousprototypes.com/docs/Bus_Pirate_Scripting_in_Python)

###getting started
install your tools:
```
sudo apt-get install minicom avrdude avr-gcc
```

set the udev rules for buspirate and trinket
```
sudo echo 'SUBSYSTEM=="tty", ATTRS{idVendor}=="0403", ATTRS{idProduct}=="6001", GROUP="dialout", MODE="0660", SYMLINK+="buspirate"' | sudo tee /etc/udev/rules.d/47-buspirate.rules
sudo echo 'SUBSYSTEM=="usb", ATTRS{idVendor}=="1781", ATTRS{idProduct}=="0c9f", MODE="0660", GROUP="plugdev"' | sudo tee /etc/udev/rules.d/47-usbtiny.rules
sudo echo 'SUBSYSTEM=="usb", ATTRS{idVendor}=="16c0", ATTRS{idProduct}=="05df", MODE="0660", GROUP="plugdev"' | sudo tee -a /etc/udev/rules.d/47-usbtiny.rules
sudo echo 'SUBSYSTEM=="usb", ATTRS{idVendor}=="16c0", ATTRS{idProduct}=="05dc", MODE="0660", GROUP="plugdev"' | sudo tee -a /etc/udev/rules.d/47-usbtiny.rules
```

buspirate is a modem so we must be part of the dialout group
trinket is an external storage device so we must be part of the plugdev group
```
sudo adduser <username> dialout
sudo adduser <username> plugdev
```

replace the default avrdude.conf file with adafruits
the avrdude.conf file from adafruit must be modified if you are running the newest avrdude (6.0+)
```
wget http://learn.adafruit.com/system/assets/assets/000/010/752/original/avrdude.conf?1378151630
mv avrdude.conf?1378151630 avrdude.conf
sed -i.bak 's/\(type\s*=\s\)\([^;]*\)/\1"\2"/g' avrdude.conf
sudo mv /etc/avrdude.conf /etc/avrdude.conf.bak
sudo cp avrdude.conf /etc/avrdude.conf
```

test minicom with buspirate plugged in
```
minicom -b 115200 -8 -D /dev/buspirate
```
