CC = gcc
CFLAG = -g -Wall -ansi -pedantic
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-lstack_fp
# -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread

all: p3_e1 p3_e2 p3_e3 p3_e3_c

######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':' (dependencias)
########################################################################

p3_e1: p3_e1.o node.o graph.o queue_fp.o


	$(CC) $(CFLAGS) p3_e1.o node.o graph.o queue_fp.o -o p3_e1

p3_e2: p3_e2.o node.o graph.o queue_fp.o


	$(CC) $(CFLAGS) p3_e2.o node.o graph.o queue_fp.o -o p3_e2

p3_e3: p3_e3.o node.o graph.o queue_fp.o

	$(CC) $(CFLAGS) p3_e3.o node.o graph.o queue_fp.o -o p3_e3

p3_e3_c: p3_e3_c.o node.o graph.o queue_fp.o libstack_fp.a

	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(LIBS)

node.o: node.c node.h types.h

	$(CC) $(CFLAGS) -c node.c

p3_e1.o: p3_e1.c types.h

	$(CC) $(CFLAGS) -c p3_e1.c

p3_e2.o: p3_e2.c types.h

	$(CC) $(CFLAGS) -c p3_e2.c

p3_e3.o: p3_e3.c types.h

	$(CC) $(CFLAGS) -c p3_e3.c

p3_e3_c.o: p3_e3_c.c types.h

	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)


graph.o: graph.c graph.h node.h types.h

	$(CC) $(CFLAGS) -c graph.c


queue_fp.o: queue_fp.c queue_fp.h types.h 

	$(CC) $(CFLAGS) -c queue_fp.c

clean: 
	rm -f *.o p3_e1 p3_e2 p3_e3 p3_e3_c