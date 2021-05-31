CC     = gcc
CFLAGS = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic -I../../lib
LDLIBS = -L../../lib -lbinaryString
LIB    = libbranch.a
LIBOBJ = branch.o
BUILD  = $(LIB)

all: $(BUILD)

test: branch_test

clean: 
	/bin/rm -f $(BUILD) *.o core

$(LIB): $(LIBOBJ)
	ar rcs $(LIB) $(LIBOBJ)

branch_test: branch_test.o branch.o
branch_test.o: branch.h
branch.o: branch.h



