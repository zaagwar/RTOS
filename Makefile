.PHONY: std, release-build
.PHONY: dbg, debug-build
.PHONY: clean, install

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
AS = arm-none-eabi-as
CP = arm-none-eabi-objcopy

SOURCE-REGEX = -regextype posix-extended -regex .*\.[cs]$$
SOURCE-FILES = $(shell find -L kernel/ -type f $(SOURCE-REGEX))

STD-CFLAGS = \
	-Wall -Wextra -pedantic -fanalyzer \
	-Wno-unused \
	-Wl,--no-warn-rwx-segments \
	-ffunction-sections \
	-ffinite-loops \
	-O1 \
	-std=c23 \
	-Iinclude\
	-fwhole-program -fpeephole2 \
	-flto -ffat-lto-objects -flto-partition=balanced -fuse-linker-plugin \
	-falign-functions=2 -falign-loops=2 -falign-labels=2 -falign-jumps=2 \
	-finline-small-functions -finline-functions-called-once \
	-fno-tree-dse -fno-tree-loop-distribute-patterns \
	-mcpu=cortex-m0plus -mthumb \
	-ffreestanding -nostdlib -nolibc -fno-builtin
DBG-CFLAGS = \
	-Wall -Wextra -pedantic -fanalyzer \
	-Wl,--no-warn-rwx-segments \
	-Og -g \
	-std=c23 \
	-ffinite-loops -ffunction-sections \
	-falign-functions=2 -falign-loops=2 -falign-labels=2 -falign-jumps=2 \
	-finline-small-functions -finline-functions-called-once \
	-fno-tree-dse -fno-tree-loop-distribute-patterns \
	-Iinclude\
	-mcpu=cortex-m0plus -mthumb \
	-ffreestanding -nostdlib -nolibc -fno-builtin

LFLAGS = --no-warn-rwx-segments -nostdlib -marmelf -Tkernel/ceres.ld
AFLAGS = --warn --fatal-warnings -mcpu=cortex-m0plus

std: release-build clean install
dbg: debug-build install

build-bootloader:
	@$(AS) $(AFLAGS) boot/boot.s -o boot.o
	@$(CP) -O binary boot.o boot.bin

	@printf "\tBuilding bootloader..."
	@tools/pad boot.bin boot.img
	@$(CP) -I binary -O elf32-littlearm \
		   --rename-section .data=.boot \
		   boot.img boot.o
	@printf " \x1b[1;92mdone\x1b[0m\n"

release-build: build-bootloader
	@printf "\tBuilding kernel..."
	@$(CC) $(STD-CFLAGS) -c $(SOURCE-FILES)
	@$(CC) $(STD-CFLAGS) -Tkernel/ceres.ld *.o -o main.elf
	@printf " \x1b[1;92mdone\x1b[0m\n"

	@printf "\tCreating UF2 image..."
	@tools/elf2uf2 main.elf -o main.uf2
	@printf " \x1b[1;92mdone\x1b[0m\n"

debug-build: build-bootloader
	@printf "\tBuilding kernel..."
	@$(CC) $(DBG-CFLAGS) -c $(SOURCE-FILES)
	@$(LD) $(LFLAGS) *.o -o main.elf
	@printf " \x1b[1;92mdone\x1b[0m\n"

	@printf "\tCreating UF2 image..."
	@tools/elf2uf2 main.elf -o main.uf2
	@printf " \x1b[1;92mdone\x1b[0m\n"

install:
	@GREP_COLORS='ms=1;92' tools/upload

clean:
	@rm *.o
	@rm boot.*
