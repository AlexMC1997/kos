SRC_DIR := "./src/"
SRC_DIRS := "./src/libc/" "./src/drivers/" "./src/kernel/"
BIN_DIR := ./bin/
OBJ_DIR := "./obj/"
DUMP_DIR := ./dumps/

CC := $$HOME/workspace/operating-systems/osproj/i686-gcc/bin/i686-elf-gcc
LD_FLAGS := -T linker.ld -ffreestanding -O0 -gdwarf-4 -gpubnames -g3 -nostdlib -lgcc

BIN_FILE := $(BIN_DIR)osproj.bin

QEMU := qemu-system-i386

QEMU_ARGS := -kernel $(BIN_FILE) -monitor stdio -smp 1 -m 256M
# try to generate a unique GDB port
GDBPORT = $(shell expr `id -u` % 5000 + 25000)
# QEMU's gdb stub command line changed in 0.11
QEMUGDB = $(shell if $(QEMU) -help | grep -q '^-gdb'; \
	then echo "-gdb tcp::$(GDBPORT)"; \
	else echo "-s -p $(GDBPORT)"; fi)

$(OBJ_DIR):
	make -C ./src/libc/ all $(MAKEFLAGS)
	make -C ./src/drivers/ all $(MAKEFLAGS)
	make -C ./src/kernel/ all $(MAKEFLAGS)

$(BIN_FILE): $(shell find $(SRC_DIR) -type f) linker.ld | $(OBJ_DIR)
	$(CC) $(LD_FLAGS) $(shell find $(OBJ_DIR) -name "*.o")
	grub-file --is-x86-multiboot $(BIN_FILE)
	objdump -x -d -S -s -dwarf $(BIN_FILE) > $(DUMP_DIR)osproj.asm

build: $(BIN_FILE)

rebuild: clean build

qemu: build
	$(QEMU) $(QEMU_ARGS)

qemu-gdb: build
	$(QEMU) $(QEMU_ARGS) -S $(QEMUGDB)

clean:
	-rm -f $(BIN_DIR)*.bin $(DUMP_DIR)*.asm
	-rm -r $(OBJ_DIR)/*

#backup of stdint.h

#ifndef _GCC_WRAP_STDINT_H
#if __STDC_HOSTED__
# if defined __cplusplus && __cplusplus >= 201103L
#  undef __STDC_LIMIT_MACROS
#  define __STDC_LIMIT_MACROS
#  undef __STDC_CONSTANT_MACROS
#  define __STDC_CONSTANT_MACROS
# endif
# include_next <stdint.h>
#else
# include "stdint-gcc.h"
#endif
#define _GCC_WRAP_STDINT_H
#endif