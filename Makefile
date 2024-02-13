CC = gcc
CFLAGS = -Wall -Wextra -pedantic
CVERSION = c99

all: main

main: main.c
	$(CC) -o main main.c $(CFLAGS) -std=$(CVERSION)

clean: 
	rm -f main
