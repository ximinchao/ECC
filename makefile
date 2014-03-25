ECCTest: ECCTest.o util.o BigNum.o
	g++ -g ECCTest.o util.o BigNum.o -o ECCTest

ECCTest.o: ECCTest.c util.h ECCType.h
	g++ -g -c ECCTest.c

util.o: util.c util.h ECCType.h
	g++ -g -c util.c

BigNum.o: BigNum.cpp BigNum.h ECCType.h
	g++ -g -c BigNum.cpp

.PHONY: clean

clean:
	-rm -f ECCTest ECCTest.o util.o BigNum.o
