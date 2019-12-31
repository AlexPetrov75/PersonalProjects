CC = gcc

CFLAGS = -Wall -pedantic -Wextra -g -c -o

LDFLAGS = -Wall -pedantic -Wextra -g -o

all: sudoku

sudoku: sudoku.o
	$(CC) $(LDFLAGS) sudoku sudoku.o

sudoku.o: sudoku.c
	$(CC) $(CFLAGS) sudoku.o sudoku.c

clean:
	rm -f *.o
