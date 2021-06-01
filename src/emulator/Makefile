all: libs

clean: 
	/bin/rm -f $(BUILD) *.o core
	cd ../lib; make clean
	cd cond; make clean
	cd data_processing; make clean
	cd branch; make clean
	cd single_data_transfer; make clean
	cd multiply; make clean
	cd common_functions; make clean
	cd gpio; make clean
	
libs: 
	cd ../lib; make
	cd common_functions; make
	cd cond; make
	cd branch; make
	cd single_data_transfer; make
	cd multiply; make
	cd data_processing; make
	cd gpio; make



