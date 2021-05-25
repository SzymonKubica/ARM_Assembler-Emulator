CC     = gcc
CFLAGS = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic -Ilib
BUILD  = libs cond.o 

all: $(BUILD) 

clean: 
	/bin/rm -f $(BUILD) *.o core
	cd data_processing; make clean
	cd multiply; make clean
	cd single_data_processing; make clean
	cd branch; make clean

cond.o: cond.h
