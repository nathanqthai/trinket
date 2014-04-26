PROG=main

# compile parameters
CC=avr-gcc
F_CPU=8000000UL # 8Mhz
MCU=attiny85
CFLAGS=-Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)

# object creation paramters
OBJCOPY=avr-objcopy
BIN_FORMAT=ihex

# flashing parameters
AVRDUDE=avrdude
PROTOCOL=usbtiny
PART=attiny85
PORT=usb

RM=rm -f

.SUFFIXES: .elf .hex

.c.elf:
	$(CC) $(CFLAGS) -o $@ $^ -I.

.elf.hex:
	$(OBJCOPY) -O $(BIN_FORMAT) -R .eeprom $< $@

.PHONY: all
all: ${PROG}.hex

${PROG}.hex: ${PROG}.elf

${PROG}.elf: ${PROG}.c USI_TWI_Master.c

.PHONY: clean
clean:
	$(RM) ${PROG}.elf ${PROG}.hex

.PHONY: upload
upload: ${PROG}.hex
	$(AVRDUDE) -c $(PROTOCOL) -p $(PART) -P $(PORT) -U flash:w:${PROG}.hex
