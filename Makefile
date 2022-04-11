all: 2048

2048: fonction.o main.o OperationPlateau.o
	gcc -o 2048 fonction.o main.o OperationPlateau.o -lSDL -lSDL_ttf -lm

OperationPlateau.o: OperationPlateau.c fonctions_de_base.h 
	gcc -o OperationPlateau.o -c OperationPlateau.c -W -Wall -ansi -pedantic

fonction.o: fonction.c fonctions_de_base.h OperationPlateau.h
	gcc -o fonction.o -c fonction.c -W -Wall -ansi -pedantic

main.o: main.c fonction.h fonctions_de_base.h OperationPlateau.h
	gcc -o main.o  -c main.c -W -Wall -ansi -pedantic 

clean:
	rm -rf *.o

exe:
	make
	rm -rf *.o
	./2048