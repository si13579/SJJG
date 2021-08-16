build : main.o maze.o sqstack.o
	gcc -o build main.o maze.o sqstack.o -lm
main.o : main.c maze.h
	gcc -g -c main.c 
maze.o : maze.c maze.h
	gcc -g -c maze.c
sqstack.o : sqstack.c sqstack.h
	gcc -g -c sqstack.c
clean : 
	rm *.o