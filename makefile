CFLAGS=-std=c99 -Wall -Wextra -pedantic -O2
CXXFLAGS=-Wall -Wextra -pedantic -O2

.PHONY: all default run test clean


default all: cpp c

run test: cpp c
	@echo "C Version"
	./c
	@echo "C++ Version"
	./cpp

c.o: c.c localely.h makefile
	${CC} ${CFLAGS} $< -c -o $@

cpp.o: cpp.cpp localely.h makefile
	${CXX} ${CXXFLAGS} $< -c -o $@

clean:
	git clean -dffx

%.htm: %.md
	markdown < $< > $@
