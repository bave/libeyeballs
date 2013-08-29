
UNAME := $(shell uname -s)

ifeq ($(UNAME),Darwin)

all: libeyeballs test

libeyeballs: eyeballs.cpp eyeballs.hpp
	g++ -O3 -Wall -shared eyeballs.cpp -o libeyeballs.dylib

test: test.cpp
	g++ -g -Wall -o test test.cpp -L./ -leyeballs

else
ifeq ($(UNAME),Linux)

all: test

test: test.cpp
	g++ -g -Wall -o test test.cpp eyeballs.cpp

else

all:
	echo $(uname)

endif
endif

clean:
	rm -rf *.dSYM libeyeballs.* test
