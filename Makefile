
all: src
.PHONY : all

src:
	make -C src
.PHONY : src

install:
	make -C src install
.PHONY : install

deinstall:
	make -C src deinstall
.PHONY : deinstall

clean:
	make -C src clean
.PHONY : clean

