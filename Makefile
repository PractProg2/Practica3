CC = gcc
CFLAG = -g -Wall -ansi -pedantic


all: p3_e1

p3_e1: p3_e1.o node.o graph.o element.o queue.o


	$(CC) $(CFLAGS) p3_e1.o node.o graph.o element.o queue.o -o p3_e1



node.o: node.c node.h types.h

	$(CC) $(CFLAGS) -c node.c

p3_e1.o: p3_e1.c types.h

	$(CC) $(CFLAGS) -c p3_e1.c


graph.o: graph.c graph.h node.h types.h

	$(CC) $(CFLAGS) -c graph.c

element.o: element.c element.h types.h

	$(CC) $(CFLAGS) -c element.c

queue.o: queue.c queue.h types.h element.h

	$(CC) $(CFLAGS) -c queue.c

clean: 
	rm -f *.o p3_e1