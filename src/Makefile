
all: libeyeballs

libeyeballs: eyeballs.cpp eyeballs.hpp test.cpp
	/bin/sh ./create.sh libeyeballs

debug: eyeballs.cpp eyeballs.hpp test.cpp
	/bin/sh ./create.sh debug

install:
	/bin/sh ./create.sh install

deinstall:
	/bin/sh ./create.sh deinstall

clean:
	rm -rf *.dSYM libeyeballs.* test
