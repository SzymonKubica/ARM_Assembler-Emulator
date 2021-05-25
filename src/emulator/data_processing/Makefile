CC     = gcc
CFLAGS = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic
BUILD  = opcode.o

all: $(BUILD)

clean: 
	/bin/rm -f $(BUILD) *.o core

opcode.o: opcode.c ../../defns.h
