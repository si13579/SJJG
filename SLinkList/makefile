build : main.o slinklist.o 
	gcc -o build main.o slinklist.o -lm
main.o : main.c slinklist.h
	gcc -g -c main.c 
slinklist.o : slinklist.c slinklist.h
	gcc -g -c slinklist.c
clean : 
	rm *.o