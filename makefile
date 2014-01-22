ECCTest: ECCTest.o util.o
	g++ -g ECCTest.o util.o -o ECCTest

ECCTest.o: ECCTest.c util.h
	g++ -g -c ECCTest.c

util.o: util.c util.h
	g++ -g -c util.c

.PHONY: clean

clean:
	-rm -f ECCTest ECCTest.o util.o
