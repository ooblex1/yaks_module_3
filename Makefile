CFLAGS=-Wall -pedantic -std=c11 -I. -g

all: test1 test2

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

test1: test1.o list.o
	gcc $(CFLAGS) test1.o list.o -o test1

test2: test2.o list.o
	gcc $(CFLAGS) test2.o list.o -o test2

clean:
	rm -f *.o test1 test2
