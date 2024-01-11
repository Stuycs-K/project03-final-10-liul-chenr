compile: server.o user.o network.o library.o test.o
	@gcc -o user user.o network.o library.o
	@gcc -o server server.o network.o library.o
	@gcc -o test test.o library.o
	
test.o: test.c library.h
	@gcc -c test.c

user.o: user.c network.h library.h
	@gcc -c user.c

server.o: server.c network.h library.h
	@gcc -c server.c

network.o: network.c network.h library.h
	@gcc -c network.c
	
library.o: library.c library.h
	@gcc -c library.c

clean: 
	@rm *.o server user test *.txt
