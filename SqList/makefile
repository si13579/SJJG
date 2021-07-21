build : main.o list.o 
	gcc -o build main.o list.o -lm
main.o : main.c list.h
	gcc -g -c main.c 
List.o : list.c list.h
	gcc -g -c list.c
clean : 
	rm *.o