CC     = gcc
CFLAGS = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic -Idata_processing -Imultiply -Isingle_data_processing -Ibranch
LDLIBS = -Ldata_processing -lopcode -Lmultiply -lmultiply -Lsingle_data_processing -lsingle_data_processing -Lbranch -lbranch
BUILD  = libs cond.o 

all: $(BUILD) 

clean: 
	/bin/rm -f $(BUILD) *.o core
	cd data_processing; make clean
	cd multiply; make clean
	cd single_data_processing; make clean
	cd branch; make clean
	
libs: 
	cd data_processing; make 
	cd multiply; make 
	cd single_data_processing; make 
	cd branch; make 

cond.o: cond.h
