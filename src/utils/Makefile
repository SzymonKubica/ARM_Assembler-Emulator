CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic 
LIB1    = libfileInput.a
LIB2    = libbinaryUtils.a
LIBOBJ1 = fileInput.o 
LIBOBJ2 = binaryUtils.o
BUILD   = $(LIB1) $(LIB2) 

all: $(BUILD)

clean: 
			/bin/rm -f $(BUILD) *.o core

$(LIB1): $(LIBOBJ1)
	    ar rcs $(LIB1) $(LIBOBJ1)

$(LIB2): $(LIBOBJ2)
	    ar rcs $(LIB2) $(LIBOBJ2)

fileInput.o: fileInput.h
binaryUtils.o: binaryUtils.h

