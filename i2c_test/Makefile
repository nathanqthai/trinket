include make.vars

#ISP=avrdude -c avrispmkII -p $(MCU) -P usb
ISP=avrdude -c usbtiny -p $(MCU) -P usb

CFLAGS+=-I.

TARGET=main
SRC=main.c

all: $(TARGET).hex

program : $(TARGET).hex
	$(ISP) -e -U flash:w:$(TARGET).hex
#program : $(TARGET).hex
#	$(ISP) -e -U flash:w:$(TARGET).hex -U lfuse:w:0xF1:m -U hfuse:w:0xD5:m -U efuse:w:0xFE:m

getfuse:
	$(ISP) -U hfuse:r:fuse-h.txt:b -U lfuse:r:fuse-l.txt:b \
         -U efuse:r:fuse-e.txt:b

$(TARGET).elf: $(SRC:.c=.o) USI_TWI_Master/USI_TWI_Master.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

USI_TWI_Master/USI_TWI_Master.a: USI_TWI_Master/*.[ch]
	make -C USI_TWI_Master

%.hex : %.elf
	avr-objcopy -R .eeprom -O ihex $< $@
	avr-size $@

include make.rules

clean::
	rm -f *.hex *.elf fuse-*.txt $(TARGET)
	make -C USI_TWI_Master clean
