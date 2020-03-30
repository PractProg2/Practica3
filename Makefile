CC = gcc
CFLAG = -g -Wall -ansi -pedantic


all: p3_e1 p3_e2

p3_e1: p3_e1.o node.o graph.o queue_fp.o


	$(CC) $(CFLAGS) p3_e1.o node.o graph.o queue_fp.o -o p3_e1

p3_e2: p3_e2.o node.o graph.o queue_fp.o


	$(CC) $(CFLAGS) p3_e2.o node.o graph.o queue_fp.o -o p3_e2



node.o: node.c node.h types.h

	$(CC) $(CFLAGS) -c node.c

p3_e1.o: p3_e1.c types.h

	$(CC) $(CFLAGS) -c p3_e1.c

p3_e2.o: p3_e2.c types.h

	$(CC) $(CFLAGS) -c p3_e2.c


graph.o: graph.c graph.h node.h types.h

	$(CC) $(CFLAGS) -c graph.c


queue_fp.o: queue_fp.c queue_fp.h types.h 

	$(CC) $(CFLAGS) -c queue_fp.c

clean: 
	rm -f *.o p3_e1 p3_e2