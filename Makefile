simulator.out : tools.o Optimal.o FIFO.o LIFO.o LRU.o LFU.o SC.o ESC.o display.o main.o
	gcc -o simulator.out tools.o Optimal.o FIFO.o LIFO.o LRU.o LFU.o SC.o ESC.o display.o main.o

tools.o : tools.c
	gcc -c -o tools.o tools.c

Optimal.o : Optimal.c 
	gcc -c -o Optimal.o Optimal.c

FIFO.o : FIFO.c
	gcc -c -o FIFO.o FIFO.c

LIFO.o : LIFO.c
	gcc -c -o LIFO.o LIFO.c

LRU.o : LRU.c
	gcc -c -o LRU.o LRU.c

LFU.o : LFU.c
	gcc -c -o LFU.o LFU.c

SC.o : SC.c
	gcc -c -o SC.o SC.c

ESC.o : ESC.c
	gcc -c -o ESC.o ESC.c

display.o : display.c
	gcc -c -o display.o display.c

main.o : main.c
	gcc -c -o main.o main.c
