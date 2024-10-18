# Project settings
PROJECT_NAME = arduino_memory_game
MCU = atmega328p
F_CPU = 16000000UL
PROGRAMMER = arduino
PORT = /dev/ttyUSB0
BAUD = 115200

# Toolchain settings
AVRDUDE = avrdude
CC = avr-gcc
OBJCOPY = avr-objcopy

# Compiler flags
CFLAGS = -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -std=c99
CFLAGS += -I./src/config
CFLAGS += -I./src/game
CFLAGS += -I./src/input
CFLAGS += -I./src/output
CFLAGS += -I./src/sound
CFLAGS += -I./src/hal

# Source files
SRC = src/main.c \
      src/game/game_logic.c \
      src/input/input.c \
      src/output/output.c \
      src/sound/melody.c \
      src/sound/speaker.c \
	  src/hal/hal_gpio.c \
      src/hal/hal_delay.c \
      src/hal/hal_adc.c


# Object files
OBJ = $(SRC:.c=.o)

# Build targets
all: $(PROJECT_NAME).hex

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PROJECT_NAME).elf: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(PROJECT_NAME).hex: $(PROJECT_NAME).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Upload to Arduino
upload: $(PROJECT_NAME).hex
	$(AVRDUDE) -v -patmega328p -carduino -P$(PORT) -b$(BAUD) -D -Uflash:w:$(PROJECT_NAME).hex:i

# Clean build files
clean:
	rm -f src/**/*.o
	rm -f $(PROJECT_NAME).elf $(PROJECT_NAME).hex

# Phony targets
.PHONY: all clean upload
