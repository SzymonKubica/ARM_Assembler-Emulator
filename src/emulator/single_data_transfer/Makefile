CC     = gcc
CFLAGS = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic -I../../lib -I../common_functions
LDLIBS = -L../../lib -lbinaryString -L../common_functions/ -lcommon
LIB    = libsingle_data_transfer.a
LIBOBJ = single_data_transfer.o
BUILD  = $(LIB) single_data_transfer_test

all: $(BUILD)

clean: 
	/bin/rm -f $(BUILD) *.o core

$(LIB): $(LIBOBJ)
	ar rcs $(LIB) $(LIBOBJ)

single_data_transfer_test: single_data_transfer_test.o single_data_transfer.o 
single_data_transfer_test.o: single_data_transfer.h
single_data_transfer.o: single_data_transfer.h
