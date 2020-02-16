pm0la : main.o list.o scanner.o token.o util.o
	gcc -o pm0la main.o list.o scanner.o token.o util.o

main.o : main.c util.o scanner.o list.o
	gcc -c main.c

util.o : util.c util.h list.h
	gcc -c util.c

list.o : list.c list.h token.h
	gcc -c list.c

token.o : token.c token.h
	gcc -c token.c

scanner.o : scanner.c scanner.h token.h list.h
	gcc -c scanner.c

clean:
	rm -f pm0la *.o
