CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic -Iemulator/data_processing -Iemulator/multiply -Iemulator/branch -Iemulator/single_data_transfer -Ilib -Iemulator/cond 
LDLIBS  = -Lemulator/data_processing -lopcode -Lemulator/multiply -lmultiply -Lemulator/branch -lbranch -Lemulator/single_data_transfer -lsingle_data_transfer -Lemulator/cond -lcond
BUILD   = libs assemble emulate

.SUFFIXES: .c .o

.PHONY: all clean

all: $(BUILD)  

clean:
	/bin/rm -f $(BUILD) *.o core
	cd emulator; make clean
	cd lib; make clean

libs:
	cd emulator; make
	cd lib; make

assemble: assemble.o

emulate: emulate.o

