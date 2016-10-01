all:
	ino build -m pro5v328

upload:
	avrdude -c usbtiny -p atmega328p -U flash:w:.build/pro5v328/firmware.hex
