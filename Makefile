all: main.o grafo.o
	@gcc main.o grafo.o -o exe
main.o: main.c
	@gcc main.c -c -Wall
grafo.o: grafo.c
	@gcc grafo.c -c -Wall
run:
	@./exe
