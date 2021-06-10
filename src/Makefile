CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic -Iemulator/data_processing -Iemulator/multiply -Iemulator/branch -Iemulator/single_data_transfer -Iemulator/cond -Iemulator/common_functions -Iemulator/gpio -Iassembler/data_processing -Iassembler/multiply -Iassembler/single_data_transfer -Iassembler/branch
LDLIBS  = -Lemulator/data_processing -ldata_processing -Lemulator/multiply -lmultiply -Lemulator/branch -lbranch -Lemulator/single_data_transfer -lsingle_data_transfer -Lemulator/cond -lcond -Lemulator/common_functions -lcommon -Lemulator/gpio -lgpio -Lassembler/data_processing -ldata_processing -Lassembler/mulitply -lmultiply -Lassembler/single_data_transfer -lsingle_data_transfer -Lassembler/branch -lbranch
BUILD   = libs assemble emulate

.SUFFIXES: .c .o

.PHONY: all clean

all: $(BUILD)  

clean:
	/bin/rm -f $(BUILD) *.o core
	cd emulator; make clean
	cd assembler; make clean

libs:
	cd emulator; make
	cd assembler; make

assemble: assemble.o
assemble.o: assembler_defs.h

emulate: emulate.o
emulate.o: defns.h

