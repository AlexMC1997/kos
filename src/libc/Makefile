include /home/alex/workspace/operating-systems/osproj/kos/src/makefile

OBJ_DIR := $(ROOT_DIR)obj/libc/

AS_FLAGS := -O0
DBG_FLAGS := -O0 -gdwarf-4 -gpubnames -g3
OPT_FLAGS := -O2
C_FLAGS := -c -O0 -ffreestanding -Wall -Wextra -std=gnu99

all: $(addprefix $(OBJ_DIR), $(OBJ)) $(addprefix $(OBJ_DIR), $(AS_OBJ))

-include $(wildcard $(OBJ_DIR)*.d)

$(OBJ_DIR)%.o: %.c
	-mkdir -p $(dir $@) 
	$(CC) $(HEADERS) $(C_FLAGS) $(DBG_FLAGS) -MMD -o $@ $<

$(OBJ_DIR)asm/%.o: ./asm/%.S
	-mkdir -p $(dir $@) 
	$(AS) $(HEADERS) $(AS_FLAGS) $(DBG_FLAGS) -o $@ $<
