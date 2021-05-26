CC     = gcc
CFLAGS = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic -I../../lib
LDLIBS = -L../../lib -lbinaryString
LIB    = libopcode.a
LIBOBJ = opcode.o
BUILD  = opcode $(LIB)

all: $(BUILD)

clean: 
	/bin/rm -f $(BUILD) *.o core

$(LIB): $(LIBOBJ)
	ar rcs $(LIB) $(LIBOBJ)

opcode: opcode.o


