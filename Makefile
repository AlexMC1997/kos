SRC_DIRS := "./src/libc/" "./src/drivers/" "./src/kernel/"
BIN_DIR := ./bin/
OBJ_DIRS := "./obj/libc/" "./obj/drivers/" "./obj/kernel/"
DUMP_DIR := ./dumps/

CC := $$HOME/workspace/operating-systems/osproj/i686-gcc/bin/i686-elf-gcc
LD_FLAGS := -T linker.ld -ffreestanding -O1 -gdwarf-4 -nostdlib -lgcc

BIN_FILE := $(BIN_DIR)osproj.bin

QEMU := qemu-system-i386

QEMU_ARGS := -kernel $(BIN_FILE) -monitor stdio -smp 1 -m 256M
# try to generate a unique GDB port
GDBPORT = $(shell expr `id -u` % 5000 + 25000)
# QEMU's gdb stub command line changed in 0.11
QEMUGDB = $(shell if $(QEMU) -help | grep -q '^-gdb'; \
	then echo "-gdb tcp::$(GDBPORT)"; \
	else echo "-s -p $(GDBPORT)"; fi)

$(OBJ_DIRS): 
	mkdir $@
	make -C $(subst obj,src,$@) all $(MAKEFLAGS)

build: $(OBJ_DIRS)
	$(CC) $(LD_FLAGS) $(addsuffix *.o, $(OBJ_DIRS))
	grub-file --is-x86-multiboot $(BIN_FILE)
	objdump -x -d -S -s -dwarf $(BIN_FILE) > $(DUMP_DIR)osproj.asm

qemu: build
	$(QEMU) $(QEMU_ARGS)

qemu-gdb: build
	$(QEMU) $(QEMU_ARGS) -S $(QEMUGDB)

clean:
	rm -f $(BIN_DIR)*.bin $(DUMP_DIR)*.asm
	rm -r $(OBJ_DIRS)