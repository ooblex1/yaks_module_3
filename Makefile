CFLAGS=-Wall -pedantic -std=c11 -I. -g

all:	qtest1 qtest2 qtest3

%.o:	%.c %.h
			gcc $(CFLAGS) -c $<

qtest1:	qtest1.o queue.o
				gcc $(CFLAGS) qtest1.o queue.o -o qtest1

qtest2:	qtest2.o queue.o
				gcc $(CLFAGS) qtest2.o queue.o -o qtest2

qtest3:	qtest3.o queue.o
				gcc $(CFLAGS) qtest3.o queue.o -o qtest3

clean:	
				rm -f *.o qtest1 qtest2 qtest3
