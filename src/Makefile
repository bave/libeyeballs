
all: libeyeballs

libeyeballs: eyeballs.cpp eyeballs.hpp test.cpp
	/bin/sh ./create.sh libeyeballs

debug: eyeballs.cpp eyeballs.hpp test.cpp
	/bin/sh ./create.sh debug

install:
	/bin/sh ./create.sh install

clean:
	rm -rf *.dSYM libeyeballs.* test
