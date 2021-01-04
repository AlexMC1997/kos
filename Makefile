SRC_DIR = ./kernel/
BIN_DIR = ./bin/
OBJ_DIR = ./obj/
DUMP_DIR = ./dumps/


AS = $$HOME/workspace/operating-systems/osproj/i686-gcc/bin/i686-elf-as
AS_FLAGS = -O0 -gdwarf-4
AS_FILES = $(SRC_DIR)boot.S

LD_FLAGS = -T linker.ld -ffreestanding -O0 -gdwarf-4 -nostdlib -lgcc

CC = $$HOME/workspace/operating-systems/osproj/i686-gcc/bin/i686-elf-gcc
C_FLAGS = -c -O0 -gdwarf-4 -ffreestanding -Wall -Wextra -std=gnu99
C_FILES = kernel.c

IS_MULTI = $(shell if grub_file --is-x86-multiboot $(BIN_FILE); \
			then echo "Multiboot not found."; \
			else echo "Multiboot found."; fi)

BIN_FILE = $(BIN_DIR)osproj.bin
OBJ_FILES = $(OBJ_DIR)boot.o

QEMU = qemu-system-i386

QEMU_ARGS = -kernel $(BIN_FILE) -monitor stdio
# try to generate a unique GDB port
GDBPORT = $(shell expr `id -u` % 5000 + 25000)
# QEMU's gdb stub command line changed in 0.11
QEMUGDB = $(shell if $(QEMU) -help | grep -q '^-gdb'; \
	then echo "-gdb tcp::$(GDBPORT)"; \
	else echo "-s -p $(GDBPORT)"; fi)

kernel: clean
	$(AS) $(AS_FLAGS) -o $(OBJ_DIR)boot.o $(AS_FILES)
	$(CC) $(C_FLAGS) $(SRC_DIR)kernel.c -o $(OBJ_DIR)kernel.o
	$(CC) $(LD_FLAGS)
	objdump -x -d -S -s -dwarf $(BIN_FILE) > $(DUMP_DIR)osproj.asm

qemu: kernel
	$(QEMU) $(QEMU_ARGS)

qemu-gdb: kernel
	$(QEMU) $(QEMU_ARGS) -S $(QEMUGDB)

clean:
	rm -f $(BIN_DIR)*.bin $(OBJ_DIR)*.o $(DUMP_DIR)*.asm