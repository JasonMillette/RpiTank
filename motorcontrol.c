#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "gpio.h"

int init_motor(int dir, int step);
int turn_left(int dir);
int turn_right(int dir);
int run_motor(int step, int udelay);

int main(int argc, char **argv)
{
	int speed = 15000 - 1500 * atoi(argv[2]);

	if(speed > 15000 || speed < 1500)
	{
		printf("Error, Speed should be 0-9!\n");
		return -1;	
	}

	if(init_motor(23,24) != 0)
	{
		printf("Error!\n");
		return -1;		
	}
	
	if(strcmp(argv[1],"left") == 0)
	{
		if(turn_left(23) != 0)
		{
			printf("Error!\n");
			return -1;	
		}
	}
	else
	{
		if(turn_right(23) != 0)
		{
			printf("Error!\n");
			return -1;
		}
	}

	usleep(500000);
	
	while(1)
	{
		run_motor(24,speed);
	}

	return 0;
}

int init_motor(int dir, int step)
{
	gpio_enable(dir);
	gpio_enable(step);
	gpio_set_output(dir);
	gpio_set_output(step);

	return 0;
}

int turn_left(int dir)
{
	gpio_set_output_high(dir);

	return 0;
}

int turn_right(int dir)
{
	gpio_set_output_low(dir);

	return 0;
}

int run_motor(int step, int udelay)
{
	gpio_set_output_high(step);
	gpio_set_output_low(step);
	usleep(udelay);

	return 0;
}
