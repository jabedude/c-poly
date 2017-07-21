CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline -lm

all: polynomial test

test: test.c
	$(CC) $(CFLAGS) $< polynomial.o -o $@

polynomial: polynomial.c
	$(CC) $(CFLAGS) -D_GNU_SOURCE $< -c -o polynomial.o

debug: CFLAGS += -DDEBUG -g -fstack-usage
debug: all

clean:
	rm -f *.o *.out *.su .gdb_history polynomial test
