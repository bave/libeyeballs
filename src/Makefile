
UNAME := $(shell uname -s)

all: libeyeballs

libeyeballs: eyeballs.cpp eyeballs.hpp test.cpp
	/bin/sh ./create.sh libeyeballs

debug: eyeballs.cpp eyeballs.hpp test.cpp
	/bin/sh ./create.sh debug

clean:
	rm -rf *.dSYM libeyeballs.* test
