CC     = gcc
CFLAGS = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic -I../test_utils
LIB    = libdata_processing.a
LIBOBJ = data_processing.o 
LDLIBS = -L../test_utils -ltest_utils
BUILD  = $(LIB)

all: $(BUILD)

clean: 
	/bin/rm -f $(BUILD) *.o core

$(LIB): $(LIBOBJ)
	ar rcs $(LIB) $(LIBOBJ)

test: data_processing_test

data_processing.o: data_processing.h ../../assembler_defs.h
data_processing_test: data_processing.o data_processing_test.o ../../assembler_defs.o
data_processing_test.o: data_processing.h ../../assembler_defs.h

