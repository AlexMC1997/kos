OBJ_DIR := ../obj/
C_OBJECTS := $(patsubst %.c, %.o, $(shell find *.c))
AS_OBJECTS := $(patsubst %.S, %.o, $(shell find *.S))

AS := $$HOME/workspace/operating-systems/osproj/i686-gcc/bin/i686-elf-as
AS_FLAGS := -O0 -gdwarf-4

CC := $$HOME/workspace/operating-systems/osproj/i686-gcc/bin/i686-elf-gcc
C_FLAGS := -c -O0 -gdwarf-4 -ffreestanding -Wall -Wextra -std=gnu99

all: $(C_OBJECTS) $(AS_OBJECTS)

$(C_OBJECTS) : %.o : %.c
	$(CC) $(C_FLAGS) -o $(OBJ_DIR)$@ $<

$(AS_OBJECTS) : %.o : %.S
	$(AS) $(AS_FLAGS) -o $(OBJ_DIR)$@ $<