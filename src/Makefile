CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic
BUILD   = assemble emulate

.SUFFIXES: .c .o

.PHONY: all clean

all: $(BUILD) 

clean:
	rm -f $(BUILD) *.o core 

assemble: assemble.o

emulate: emulate.o

