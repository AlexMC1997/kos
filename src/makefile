ROOT_DIR := /home/alex/workspace/operating-systems/osproj/kos/

HEADERS = -I$(ROOT_DIR)src/libc -I$(ROOT_DIR)src/drivers -I$(ROOT_DIR)src/kernel
OBJ = $(patsubst %.c, %.o, $(shell find *.c */*.c 2>/dev/null))
AS_OBJ := $(patsubst %.S, %.o, $(shell find *.S */*.S 2>/dev/null))

AS := $$HOME/workspace/operating-systems/osproj/i686-gcc/bin/i686-elf-as
CC := $$HOME/workspace/operating-systems/osproj/i686-gcc/bin/i686-elf-gcc
