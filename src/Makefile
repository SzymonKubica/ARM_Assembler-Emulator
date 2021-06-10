CC      = gcc
EMULATOR_DIRECTORIES = $(sort $(dir $(wildcard ./emulator/*/)))
ASSEMBLER_DIRECTORIES = $(sort $(dir $(wildcard ./assembler/*/)))
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic $(foreach EMULATOR_DIRECTORIES, $(EMULATOR_DIRECTORIES), -I$(EMULATOR_DIRECTORIES)) -o -Iemulate $(foreach ASSEMBLER_DIRECTORIES, $(ASSEMBLER_DIRECTORIES), -I$(ASSEMBLER_DIRECTORIES)) -Iassembler
LDLIBS  = -Lemulator/data_processing -ldata_processing -Lemulator/multiply -lmultiply -Lemulator/branch -lbranch -Lemulator/single_data_transfer -lsingle_data_transfer -Lemulator/cond -lcond -Lemulator/common_functions -lcommon -Lemulator/gpio -lgpio -Lassembler/data_processing -ldata_processing -Lassembler/multiply -lmultiply -Lassembler/single_data_transfer -lsingle_data_transfer -Lassembler/branch -lbranch 
BUILD   = libs emulate assemble

.SUFFIXES: .c .o

.PHONY: all clean

all: $(BUILD)  

clean:
	/bin/rm -f $(BUILD) *.o core
	cd emulator; make clean
	cd assembler; make clean

libs:
	cd assembler; make
	cd emulator; make


assemble: assembler_defs.o assemble.o
assembler_defs.o: assembler_defs.h
assemble.o: assembler_defs.h assembler/assembly_functions.h

emulate: emulate.o
emulate.o: defns.h emulator/emulator_functions.h

# $(CC) $(CFLAGS) $(LDLIBS) 
