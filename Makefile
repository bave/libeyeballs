
all: src
.PHONY : all

src:
	make -C src
.PHONY : src

clean:
	make -C src clean
.PHONY : clean

