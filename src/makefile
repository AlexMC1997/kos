ROOT_DIR := $$HOME/workspace/operating-systems/osproj/kos/

HEADERS = -I$(ROOT_DIR)src/libc -I$(ROOT_DIR)src/drivers -I$(ROOT_DIR)src/kernel
C_OBJECTS := $(patsubst %.c, %.o, $(shell find *.c */*.c))
AS_OBJECTS := $(patsubst %.S, %.o, $(shell find *.S */*.S))

AS := $$HOME/workspace/operating-systems/osproj/i686-gcc/bin/i686-elf-as
CC := $$HOME/workspace/operating-systems/osproj/i686-gcc/bin/i686-elf-gcc
