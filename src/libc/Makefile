include /home/alex/workspace/operating-systems/osproj/kos/src/makefile

OBJ_DIR := $(ROOT_DIR)obj/libc/

AS_FLAGS := -O1 -gdwarf-4
C_FLAGS := -c -O1 -gdwarf-4 -ffreestanding -Wall -Wextra -std=gnu99

$(C_OBJECTS) : %.o : %.c
	$(CC) $(HEADERS) $(C_FLAGS) -o $(OBJ_DIR)$(notdir $@) $<

$(AS_OBJECTS) : %.o : %.S
	$(AS) $(HEADERS) $(AS_FLAGS) -o $(OBJ_DIR)$@ $<

all: $(C_OBJECTS) $(AS_OBJECTS)
