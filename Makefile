SRC = io.c utils.c tree.c main.c
CFLAGS = -Wall -g -O3
OUTPUT_FILE = my_route_lookup

all: compile run

compile: $(SRC)
	gcc $(CFLAGS) $(SRC) -o $(OUTPUT_FILE) -lm

run:
	./$(OUTPUT_FILE)

valgrind: compile
	valgrind --leak-check=full ./$(OUTPUT_FILE)

.PHONY: clean
clean:
	rm -f $(OUTPUT_FILE)

