default: run
clean: 
	@rm -f *.o prog
compile prog: test.o library.o
	@gcc -o prog test.o library.o
test.o: test.c library.h
	@gcc -c test.c
library.o: library.c library.h
	@gcc -c library.c
run: prog
	@./prog
