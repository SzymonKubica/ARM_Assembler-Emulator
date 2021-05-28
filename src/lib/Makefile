CC     = gcc
CFLAGS = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic 
LIB    = libbinaryString.a
LIBOBJ = binaryString.o
BUILD  =  $(LIB) 

all: $(BUILD)

clean: 
	/bin/rm -f $(BUILD) *.o core

$(LIB): $(LIBOBJ)
	ar rcs $(LIB) $(LIBOBJ)

test: binaryString_test

binaryString.o: binaryString.h
binaryString_test: binaryString_test.o binaryString.o
binaryString_test.o: binaryString.h

