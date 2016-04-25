BIN=watch
OBJS=watch.o

CC=avr-gcc
OBJCOPY=avr-objcopy

CFLAGS=-Os -DF_CPU=1000000UL -mmcu=atmega328p

${BIN}.hex: ${BIN}.elf
	${OBJCOPY} -O ihex -R .eeprom $< $@

${BIN}.elf: ${OBJS}
	${CC} -o $@ $^

install: ${BIN}.hex
	avrdude -F -V -c dragon_isp -p m328p -U flash:w:$<

clean:
	rm -f ${BIN}.elf ${BIN}.hex ${OBJS}
