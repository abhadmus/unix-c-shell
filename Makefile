CC = gcc
CFLAGS = -Wall -g
OBJS = main.o functions.o

head: $(OBJS)
	$(CC) $(CFLAGS) -o head $(OBJS)

main.o: main.c shell.h
	$(CC) $(CFLAGS) -c main.c

functions.o: functions.c shell.h
	$(CC) $(CFLAGS) -c functions.c

clean:
	rm -f *.o head

dist:
	tar -czvf head.tar.gz main.c functions.c shell.h Makefile
