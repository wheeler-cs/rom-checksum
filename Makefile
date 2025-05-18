GCC=g++
CFLAGS=-Wall -c
STD=-std=c++11
CRYPTPP=-D CRYPTOPP_ENABLE_NAMESPACE_WEAK=1
MT_OPT=-pthread -D MULTITHREAD_ENABLE
LIB=-l:libcryptopp.a
INC=./inc
EXE=rom-check


# Generic targets to compile executables
all: exe

all-mt: exe-mt


# Targets for compiling the executable
exe: build/main.o build/arguments.o build/core.o build/file.o build/hash.o build/rom.o build/ups.o build/xml.o
	$(GCC) $(STD) $(CRYPTPP) $^ -o build/$(EXE) -I$(INC) $(LIB)

exe-mt: build/main.o build/arguments.o build/core.o build/file.o build/hash-mt.o build/rom.o build/ups.o build/xml.o
	$(GCC) $(STD) $(CRYPTPP) $(MT_OPT) $^ -o build/$(EXE) -I$(INC) $(LIB)


# Targets for individual source files
build/main.o: inc/file.hpp inc/hash.hpp inc/rom.hpp inc/ups.hpp inc/xml.hpp src/main.cpp
	$(GCC) $(STD) $(CRYPTPP) src/main.cpp $(CFLAGS) -o $@ -I$(INC)

build/arguments.o: inc/arguments.hpp src/arguments.cpp
	$(GCC) $(STD) src/arguments.cpp $(CFLAGS) -o $@ -I$(INC)

build/core.o: inc/core.hpp inc/file.hpp inc/hash.hpp inc/rom.hpp inc/xml.hpp src/core.cpp
	$(GCC) $(STD) $(OPT) $(CRYPTPP) src/core.cpp $(CFLAGS) -o $@ -I$(INC)

build/file.o: inc/file.hpp src/file.cpp
	$(GCC) $(STD) src/file.cpp $(CFLAGS) -o $@ -I$(INC)

build/hash.o: inc/hash.hpp src/hash.cpp
	$(GCC) $(STD) $(CRYPTPP) src/hash.cpp $(CFLAGS) -o $@ -I$(INC) $(LIB)

build/hash-mt.o: inc/hash.hpp src/hash.cpp
	$(GCC) $(STD) $(CRYPTPP) $(MT_OPT) src/hash.cpp $(CFLAGS) -o $@ -I$(INC) $(LIB)

build/ups.o: inc/ups.hpp src/ups.cpp
	$(GCC) $(STD) src/ups.cpp $(CFLAGS) -o $@ -I$(INC)

build/rom.o: inc/rom.hpp src/rom.cpp
	$(GCC) $(STD) src/rom.cpp $(CFLAGS) -o $@ -I$(INC)

build/xml.o: inc/xml.hpp src/xml.cpp
	$(GCC) $(STD) src/xml.cpp $(CFLAGS) -o $@ -I$(INC)


# Utility functions for cleaning and execution
.PHONY: clean
clean:
	rm -rf build/*

.PHONY: run
run:
	./build/$(EXE)

.PHONY: run-silent
run-silent:
	./build/$(EXE) -s
