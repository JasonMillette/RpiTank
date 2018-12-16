CC = gcc
CFLAGS = -g -O2 -Wall


all:	temp_cool tank motorcontrol gpio

###

temp_cool:	temp_cool.o
	$(CC) -o temp_cool temp_cool.o

temp_cool.o:	temp_cool.c 
	$(CC) $(CFLAGS) -c temp_cool.c

tank:		tank.o
	$(CC) -o tank tank.c

tank.o:		tank.c
	$(CC) $(CFLAGS) -c tank.c

motorcontrol:		motorcontrol.o
	$(CC) -lm -o motorcontrol motorcontrol.o gpio.o 

motorcontrol.o:		motorcontrol.c
	$(CC) $(CFLAGS) -c motorcontrol.c 

gpio:		gpio.o
	$(CC) -o gpio gpio.o

gpio.o:		gpio.c
	$(CC) $(CFLAGS) -c gpio.c
###
###

clean:	
	rm -f *~ *.o temp_cool tank motorcontrol gpio

