MODULES = io.c utils.c table.c tree.c
SRC = $(MODULES) main.c
OUTPUT_FILE = my_route_lookup

TESTS_FOLDER = tests
SRC_TESTS = $(MODULES) $(wildcard $(TESTS_FOLDER)/*.c) 
OUTPUT_FILE_TESTS = $(TESTS_FOLDER)/test

CFLAGS = -Wall -g -O3
VFLAGS = -s --leak-check=full --show-leak-kinds=all --track-origins=yes 

RESOURCES_FOLDER = resources
FIB_FILE = $(RESOURCES_FOLDER)/routing_table_custom.txt
INPUT_FILE = $(RESOURCES_FOLDER)/prueba_custom.txt
COMMAND = ./$(OUTPUT_FILE) $(FIB_FILE) $(INPUT_FILE)

all: valgrind

compile: $(SRC)
	gcc $(CFLAGS) $(SRC) -o $(OUTPUT_FILE) -lm

run: compile
	$(COMMAND)

valgrind: compile
	valgrind $(VFLAGS) $(COMMAND)
	
gdb: compile
	gdb --args $(COMMAND)

.PHONY: clean
clean:
	rm -f $(OUTPUT_FILE)

compile_tests: $(SRC_TESTS) 
	gcc $(CFLAGS) $(SRC_TESTS) -o $(OUTPUT_FILE_TESTS) -lm

test: compile_tests
	./$(OUTPUT_FILE_TESTS)
