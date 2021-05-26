CC     = gcc
CFLAGS = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic -I../../lib
LDLIBS = -L../../lib -lbinaryString
LIB    = libsingle_data_processing.a
LIBOBJ = single_data_processing.o
BUILD  = libs $(LIB)

all: $(BUILD)

clean: 
	/bin/rm -f $(BUILD) *.o core

$(LIB): $(LIBOBJ)
	ar rcs $(LIB) $(LIBOBJ)

libs: 
	cd ../../lib; make

