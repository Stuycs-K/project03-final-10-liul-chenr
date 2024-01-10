default: compile
clean: 
	@rm -f *.o *.txt client server
compile server client: main.o user.o library.o network.o
	@gcc -o server main.c library.o network.o
	@gcc -o client user.c library.o network.o
main.o: main.c library.h network.h
	@gcc -c main.c
user.o: user.c library.h network.h
	@gcc -c user.c
library.o: library.c library.h
	@gcc -c library.c
network.o: network.c network.h
	@gcc -c network.c
run_server: server
	@./server
run_client: client
	@./client
