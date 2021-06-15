all: libs
	
clean:
	cd data_processing; make clean
	cd multiply; make clean
	cd single_data_transfer; make clean
	cd branch; make clean
	cd symbol_table; make clean
	cd special; make clean

libs: 
	cd data_processing; make
	cd multiply; make
	cd single_data_transfer; make
	cd branch; make
	cd symbol_table; make
	cd special; make

test: 
	cd test_utils; make
	#cd data_processing; make test
	#cd multiply; make test
	cd single_data_transfer; make test
	cd branch; make test
	cd symbol_table; make test
	#cd special; make test
