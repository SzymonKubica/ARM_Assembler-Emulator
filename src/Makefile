CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic 

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

