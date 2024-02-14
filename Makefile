CC = gcc
CFLAGS = -Wall -Wextra -pedantic
CVERSION = c99
OBJ = carrot.c ops.c

all: carrot 

carrot: carrot.c
	$(CC) -o carrot $(OBJ) $(CFLAGS) -std=$(CVERSION)

clean: 
	rm -f carrot
