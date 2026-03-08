.DEFAULT_GOAL := all

ROOT_DIR = $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

CC = gcc
C_OPTS := -g -Iinclude

AVSUL_SOURCES := $(wildcard src/*.c)
AVSUL_OBJECTS := $(patsubst src/%.c,build/%.o,$(AVSUL_SOURCES))

EXAMPLES_SOURCES := $(wildcard examples/*.c)
EXAMPLES_OBJECTS := $(patsubst examples/%.c,build-examples/%.o,$(EXAMPLES_SOURCES))
EXAMPLES_BINARIES := $(patsubst examples/%.c,build-examples/%,$(EXAMPLES_SOURCES))

TESTS_SOURCES := $(wildcard tests/*.c)
TESTS_BINARIES = $(patsubst tests/%.c,build-tests/%,$(TESTS_SOURCES))
SPACE_CHAR = $() $()
TESTS_EXEC = $(subst $(SPACE_CHAR), && ,$(TESTS_BINARIES))

.PHONY: all clean

all: build_debug libavsul examples

libavsul: libavsul.so

libavsul.so: $(AVSUL_OBJECTS)
	$(CC) $(C_OPTS) -fPIC -shared $^ -o $@

examples: libavsul.so $(EXAMPLES_BINARIES)

build/%.o: src/%.c
	$(CC) $(C_OPTS) -c $< -o $@

build-examples/%: examples/%.c
	$(CC) $(C_OPTS) $< -o $@ -L./ -lavsul -Wl,-rpath=./

tests: libavsul.so $(TESTS_BINARIES)
	$(TESTS_EXEC)

build-tests/%: tests/%.c
	$(CC) $(C_OPTS) $< -o $@ -L./ -lcmocka -lavsul -Wl,-rpath=./

docs: tools/Doxyfile
	doxygen tools/Doxyfile

build_debug:
	@echo $(AVSUL_SOURCES)
	@echo $(AVSUL_OBJECTS)
	@echo $(EXAMPLES_SOURCES)
	@echo $(EXAMPLES_OBJECTS)
	@echo $(EXAMPLES_BINARIES)
	@echo $(TESTS_SOURCES)
	@echo $(TESTS_BINARIES)
	@echo $(TESTS_EXEC)

clean:
	rm -rf build/*.o 
	rm -rf examples/*.o
	rm -rf build-examples/*
	rm -rf libavsul.so