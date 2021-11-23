all: mem

mem: mem.c main.c mem.h
	gcc -Wall -Wextra -g -pthread main.c mem.c -o mem

test_mem:
	./mem

clean:
	rm -r mem