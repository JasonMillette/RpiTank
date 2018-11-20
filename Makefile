CC = gcc
CFLAGS = -g -O2 -Wall
LFLAGS =


all:	temp_cool

###

temp_cool:	temp_cool.o
	$(CC) $(LFLAGS) -o temp_cool temp_cool.o

temp_cool.o:	temp_cool.c 
	$(CC) $(CFLAGS) -c temp_cool.c

###

clean:	
	rm -f *~ *.o temp_cool

