include /home/alex/workspace/operating-systems/osproj/kos/src/makefile

OBJ_DIR := $(ROOT_DIR)obj/libc/

AS_FLAGS := -O2 -gdwarf-4
C_FLAGS := -c -O2 -gdwarf-4 -ffreestanding -Wall -Wextra -std=gnu99

all: $(addprefix $(OBJ_DIR), $(OBJ)) $(AS_OBJECTS)

$(OBJ_DIR)%.o: %.c
	-mkdir -p $(dir $@) 
	$(CC) $(HEADERS) $(C_FLAGS) -o $@ $<

$(AS_OBJECTS) : %.o : %.S
	$(AS) $(HEADERS) $(AS_FLAGS) -o $(OBJ_DIR)$(notdir $@) $<
