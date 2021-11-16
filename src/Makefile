C_FLAGS = -Wall -Werror -pedantic
PATH_OUT = ../out/
PATH_BIN = ../bin/

main: main.o file_loader.o
	gcc $(C_FLAGS) -o main $(PATH_OUT)main.o $(PATH_OUT)file_loader.o -g
	mv ./main $(PATH_BIN)

main.o: main.c file_loader.h
	gcc $(C_FLAGS) -c main.c
	mv ./main.o $(PATH_OUT)

file_loader.o: file_loader.c file_loader.h
	gcc $(C_FLAGS) -c file_loader.c
	mv ./file_loader.o $(PATH_OUT)

clean:
	rm -f $(PATH_OUT)*.o $(PATH_BIN)*
 

