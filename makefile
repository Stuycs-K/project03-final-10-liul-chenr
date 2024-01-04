default: run
clean: 
	@rm -f *.o prog
compile prog: main.o library.o
	@gcc -o prog main.o library.o
main.o: main.c library.h
	@gcc -c main.c
library.o: library.c library.h
	@gcc -c library.c
run: prog
	@./prog
