GCC=g++
CFLAGS=-Wall -c
STD=-std=c++11
CRYPTPP=-D CRYPTOPP_ENABLE_NAMESPACE_WEAK=1
MT_OPT=-pthread -D MULTITHREAD_ENABLE
LIB=-l:libcryptopp.a


# Generic targets to compile executables
all: exe

all-mt: exe-mt


# Actual executable targets
exe: build/main.o build/core.o build/file.o build/hash.o build/rom.o build/xml.o
	$(GCC) $(STD) $(CRYPTPP) $^ -o build/rom-check $(LIB)

exe-mt: build/main.o build/core.o build/file.o build/hash-mt.o build/rom.o build/xml.o
	$(GCC) $(STD) $(CRYPTPP) $(MT_OPT) $^ -o build/rom-check $(LIB)


# Targets for individual source files
build/main.o: src/file.h src/hash.h src/rom.h src/xml.h src/main.cpp
	$(GCC) $(STD) $(CRYPTPP) src/main.cpp $(CFLAGS) -o $@

build/core.o: src/core.h src/file.h src/hash.h src/rom.h src/xml.h src/core.cpp
	$(GCC) $(STD) $(OPT) $(CRYPTPP) src/core.cpp $(CFLAGS) -o $@

build/file.o: src/file.h src/file.cpp
	$(GCC) $(STD) src/file.cpp $(CFLAGS) -o $@

build/hash.o: src/hash.h src/hash.cpp
	$(GCC) $(STD) $(CRYPTPP) src/hash.cpp $(CFLAGS) -o $@ $(LIB)

build/hash-mt.o: src/hash.h src/hash.cpp
	$(GCC) $(STD) $(CRYPTPP) $(MT_OPT) src/hash.cpp $(CFLAGS) -o $@ $(LIB)

build/rom.o: src/rom.h src/rom.cpp
	$(GCC) $(STD) src/rom.cpp $(CFLAGS) -o $@

build/xml.o: src/xml.h src/xml.cpp
	$(GCC) $(STD) src/xml.cpp $(CFLAGS) -o $@


# Utility functions for cleaning and execution
clean:
	rm -rf build/*

run:
	./build/rom-check

run-silent:
	./build/rom-check -s