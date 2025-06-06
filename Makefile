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
exe: build/main.o build/arguments.o build/file.o build/hash.o build/rom.o build/patch.o build/ups.o build/verify.o build/xml.o
	$(GCC) $(STD) $(CRYPTPP) $^ -o build/$(EXE) -I$(INC) $(LIB)

exe-mt: build/main.o build/arguments.o build/file.o build/hash-mt.o build/rom.o build/patch.o build/ups.o build/verify.o build/xml.o
	$(GCC) $(STD) $(CRYPTPP) $(MT_OPT) $^ -o build/$(EXE) -I$(INC) $(LIB)


# Targets for individual source files
build/main.o: inc/arguments.hpp inc/patch.hpp inc/verify.hpp
	$(GCC) $(STD) $(CRYPTPP) src/main.cpp $(CFLAGS) -o $@ -I$(INC)

build/arguments.o: inc/arguments.hpp src/arguments.cpp
	$(GCC) $(STD) src/arguments.cpp $(CFLAGS) -o $@ -I$(INC)

build/file.o: inc/file.hpp src/file.cpp
	$(GCC) $(STD) src/file.cpp $(CFLAGS) -o $@ -I$(INC)

build/hash.o: inc/hash.hpp src/hash.cpp
	$(GCC) $(STD) $(CRYPTPP) src/hash.cpp $(CFLAGS) -o $@ -I$(INC) $(LIB)

build/hash-mt.o: inc/hash.hpp src/hash.cpp
	$(GCC) $(STD) $(CRYPTPP) $(MT_OPT) src/hash.cpp $(CFLAGS) -o $@ -I$(INC) $(LIB)

build/patch.o: inc/patch.hpp src/patch.cpp inc/arguments.hpp
	$(GCC) $(STD) src/patch.cpp $(CFLAGS) -o $@ -I$(INC)

build/ups.o: inc/ups.hpp src/ups.cpp
	$(GCC) $(STD) src/ups.cpp $(CFLAGS) -o $@ -I$(INC) $(LIB)

build/rom.o: inc/rom.hpp src/rom.cpp
	$(GCC) $(STD) src/rom.cpp $(CFLAGS) -o $@ -I$(INC)

build/verify.o: inc/verify.hpp src/verify.cpp
	$(GCC) $(STD) src/verify.cpp $(CFLAGS) -o $@ -I$(INC)

build/xml.o: inc/xml.hpp src/xml.cpp inc/file.hpp
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
