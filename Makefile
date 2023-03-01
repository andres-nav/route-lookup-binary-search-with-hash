SRC = io.c utils.c tree.c main.c
CFLAGS = -Wall -g -O3
OUTPUT_FILE = my_route_lookup

all: compile

compile: $(SRC)
	gcc $(CFLAGS) $(SRC) -o $(OUTPUT_FILE) -lm

.PHONY: clean

clean:
	rm -f $(OUTPUT_FILE)

