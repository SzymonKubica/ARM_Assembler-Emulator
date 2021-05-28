CC     = gcc
CFLAGS = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic -I../../lib -I../common_functions
LDLIBS = -L../../lib -lbinaryString -L../common_functions/common -lcommon
LIB    = libsingle_data_transfer.a
LIBOBJ = single_data_transfer.o
BUILD  = $(LIB)

all: $(BUILD)

clean: 
	/bin/rm -f $(BUILD) *.o core

$(LIB): $(LIBOBJ)
	ar rcs $(LIB) $(LIBOBJ)

