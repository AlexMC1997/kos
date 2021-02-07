SRC_DIR := "./src/"
SRC_DIRS := "./src/libc/" "./src/drivers/" "./src/kernel/"
BIN_DIR := ./bin/
OBJ_DIR := "./obj/"
DUMP_DIR := ./dumps/

CC := $$HOME/workspace/operating-systems/osproj/i686-gcc/bin/i686-elf-gcc
LD_FLAGS := -T linker.ld -ffreestanding -O0 -gdwarf-4 -gpubnames -g3 -nostdlib -lgcc

BIN_FILE := $(BIN_DIR)osproj.bin

QEMU := qemu-system-i386

QEMU_ARGS := -kernel $(BIN_FILE) -monitor stdio -smp 2 -m 256M
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
	objdump -x -d -S -s -dwarf $(BIN_FILE) > $(DUMP_DIR)osproj.asm
	grub-file --is-x86-multiboot $(BIN_FILE)

build: $(BIN_FILE)

rebuild: clean | build

qemu: build
	$(QEMU) $(QEMU_ARGS)

qemu-gdb: build
	$(QEMU) $(QEMU_ARGS) -S $(QEMUGDB)

clean:
	-safe-rm $(BIN_DIR)*.bin $(DUMP_DIR)*.asm 2>/dev/null
	-safe-rm -r $(OBJ_DIR)/* 2>/dev/null