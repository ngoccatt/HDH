all: pi_serial code pi_multi-thread

code: code.c
	gcc -Wall -Wextra -g -pthread code.c -o code

pi_serial: pi_serial.c
	gcc -Wall -Wextra -g pi_serial.c -o pi_serial

pi_multi-thread: pi_multi-thread.c
	gcc -Wall -Wextra -g -pthread pi_multi-thread.c -o pi_multi-thread
clean:
	rm -f *.o pi_serial code pi_multi-thread