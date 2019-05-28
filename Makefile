

CC=gcc
all: projekt3.o function.o shell.o list.o
	$(CC) projekt3.o function.o shell.o list.o -o projekt3

projekt3.o: projekt3.c structures.h function.h shell.h
	$(CC) projekt3.c -c -o projekt3.o

function.o: function.c structures.h function.h shell.h list.h
	$(CC) function.c -c -o function.o

shell.o: shell.c structures.h function.h shell.h
	$(CC) shell.c -c -o shell.o

list.o: list.c list.h structures.h function.h shell.h
	$(CC) list.c -c -o list.o
clean:
	rm -f *.o projekt3
