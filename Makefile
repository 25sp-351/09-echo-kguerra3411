CC = gcc
CFLAGS = -Wall -pthread

all: echo_server

echo_server: main.o setup.o handler.o
	$(CC) $(CFLAGS) -o echo_server main.o setup.o handler.o

main.o: main.c setup.h handler.h
	$(CC) $(CFLAGS) -c main.c

setup.o: setup.c setup.h handler.h
	$(CC) $(CFLAGS) -c setup.c

handler.o: handler.c handler.h
	$(CC) $(CFLAGS) -c handler.c

clean:
	rm -f *.o echo_server
