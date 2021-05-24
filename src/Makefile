CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic
LDLIBS  = -Lutils -lfileInput -lbinaryUtils
BUILD   = utilsLib assemble emulate

.SUFFIXES: .c .o

.PHONY: all clean

all: $(BUILD) 

clean:
	rm -f $(BUILD) *.o core 
	cd utils; make clean

utilsLib:
	cd utils; make

assemble: assemble.o
emulate: emulate.o 
emulate.o: binaryUtils.h fileInput.h

