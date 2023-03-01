SRC = io.c utils.c table.c tree.c main.c
CFLAGS = -Wall -g -O3
OUTPUT_FILE = my_route_lookup
RESOURCES_FOLDER = resources
FIB_FILE = $(RESOURCES_FOLDER)/routing_table_custom.txt
INPUT_FILE = $(RESOURCES_FOLDER)/prueba_custom.txt

all: compile run

compile: $(SRC)
	gcc $(CFLAGS) $(SRC) -o $(OUTPUT_FILE) -lm

run:
	./$(OUTPUT_FILE) $(FIB_FILE) $(INPUT_FILE)

valgrind: compile
	valgrind -s --leak-check=full ./$(OUTPUT_FILE) $(FIB_FILE) $(INPUT_FILE)
	
gdb: compile
	gdb --args ./$(OUTPUT_FILE) $(FIB_FILE) $(INPUT_FILE)

.PHONY: clean
clean:
	rm -f $(OUTPUT_FILE)

