GCC=g++
STD=-std=c++11
# OPT=-DNDEBUG -g3 -O2 -Wall -Wextraa
OPT=-D CRYPTOPP_ENABLE_NAMESPACE_WEAK=1
LIB=-l:libcryptopp.a

all: core file hash rom xml main

main: src/main.cpp build/core.o build/file.o build/hash.o build/rom.o build/xml.o
	$(GCC) $(STD) $(OPT) build/core.o build/file.o build/hash.o $(LIB) build/rom.o build/xml.o src/main.cpp -o build/rom-check

core: src/core.h src/file.h src/hash.h src/rom.h src/xml.h src/core.cpp
	$(GCC) $(STD) $(OPT) src/core.cpp -c -o build/core.o

file: src/file.h src/file.cpp
	$(GCC) $(STD) src/file.cpp -c -o build/file.o

hash: src/hash.h src/hash.cpp
	$(GCC) $(STD) $(OPT) src/hash.cpp -c -o build/hash.o $(LIB)

rom: src/rom.h src/rom.cpp
	$(GCC) $(STD) src/rom.cpp -c -o build/rom.o

xml: src/xml.h src/xml.cpp
	$(GCC) $(STD) src/xml.cpp -c -o build/xml.o

clean:
	rm -rf build/*

run:
	./build/rom-check
