all: myfactorial 

myfactorial: main.o readline.o factorial.o
	gcc -o myfactorial main.o readline.o factorial.o

main.o: main.c factorial.h readline.h
	gcc -c main.c

readline.o: readline.c readline.h
	gcc -c readline.c

factorial.o: factorial.c factorial.h
	gcc -c factorial.c

clean:
	rm -f *.o myfactorial
