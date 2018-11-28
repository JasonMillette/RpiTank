CC = gcc
CFLAGS = -g -O2 -Wall


all:	temp_cool tank meme motorcontrol gpio

###

temp_cool:	temp_cool.o
	$(CC) -o temp_cool temp_cool.o

temp_cool.o:	temp_cool.c 
	$(CC) $(CFLAGS) -c temp_cool.c

tank:		tank.o
	$(CC) -o tank tank.c

tank.o:		tank.c
	$(CC) $(CFLAGS) -c tank.c

meme:		meme.o
	$(CC) -o meme meme.c

meme.o:		meme.c
	$(CC) $(CFLAGS) -c meme.c

motorcontrol:		motorcontrol.o
	$(CC) -o motorcontrol motorcontrol.c 

motorcontrol.o:		motorcontrol.c
	$(CC) $(CFLAGS) -c motorcontrol.c 

gpio:		gpio.o
	$(CC) -o gpio gpio.c

gpio.o:		gpio.c
	$(CC) $(CFLAGS) -c gpio.c
###
###

clean:	
	rm -f *~ *.o temp_cool tank meme motorcontrol gpio

