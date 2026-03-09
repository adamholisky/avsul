.DEFAULT_GOAL := all

ROOT_DIR = $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

CC = gcc
C_OPTS := -g -Iinclude

AVSUL_SOURCES := $(wildcard src/*.c)
AVSUL_OBJECTS := $(patsubst src/%.c,build/%.o,$(AVSUL_SOURCES))

EXAMPLES_SOURCES := $(wildcard examples/*.c)
EXAMPLES_BINARIES := $(patsubst examples/%.c,build-examples/%,$(EXAMPLES_SOURCES))

TESTS_SOURCES := $(wildcard tests/*.c)
TESTS_BINARIES = $(patsubst tests/%.c,build-tests/%,$(TESTS_SOURCES))
SPACE_CHAR = $() $()
TESTS_EXEC = $(subst $(SPACE_CHAR), && ,$(TESTS_BINARIES))

.PHONY: all clean

all: libavsul examples tests

libavsul: libavsul.so

libavsul.so: libavsul_build_msg $(AVSUL_OBJECTS)
	$(CC) $(C_OPTS) -fPIC -shared $(AVSUL_OBJECTS) -o $@
	@echo "========> Building libavsul : Done  <========"

libavsul_build_msg:
	@echo
	@echo "========> Building libavsul : Start <========"

examples: libavsul.so examples_build_msg $(EXAMPLES_BINARIES)
	cp libavsul.so build-examples/
	@echo "========> Building libavsul examples : Done  <========"

examples_build_msg:
	@echo
	@echo "========> Building libavsul examples : Start <========"

build/%.o: src/%.c
	$(CC) $(C_OPTS) -c $< -o $@

build-examples/%: examples/%.c
	$(CC) $(C_OPTS) $< -o $@ -L./ -lavsul -Wl,-rpath=./

tests: libavsul.so tests_build_msg $(TESTS_BINARIES)
	@echo "========> Building libavsul tests : Done  <========\n"
	$(TESTS_EXEC)

tests_build_msg:
	@echo
	@echo "========> Building libavsul tests : Start <========"

build-tests/%: tests/%.c
	$(CC) $(C_OPTS) $< -o $@ -L./ -lcmocka -lavsul -Wl,-rpath=./

docs: tools/Doxyfile
	doxygen tools/Doxyfile

build_debug:
	@echo $(AVSUL_SOURCES)
	@echo $(AVSUL_OBJECTS)
	@echo $(EXAMPLES_SOURCES)
	@echo $(EXAMPLES_BINARIES)
	@echo $(TESTS_SOURCES)
	@echo $(TESTS_BINARIES)
	@echo $(TESTS_EXEC)

clean:
	rm -rf build/*.o 
	rm -rf examples/*.o
	rm -rf build-examples/*
	rm -rf build-tests/*
	rm -rf libavsul.so