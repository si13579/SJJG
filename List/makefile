build : main.o List.o 
	gcc -o build main.o List.o -lm
main.o : main.c List.h
	gcc -g -c main.c 
List.o : List.c List.h
	gcc -g -c List.c
clean : 
	rm *.o