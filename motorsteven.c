#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "gpio.h"
#include "motorcontrol.h"

int main(int argc, char **argv)
{
	init_motor();
	double x = atof(argv[1]);
	double y = atof(argv[2]);
	int i = 0;
	for (i = 0; i < 60; i++)
	{
		run_motor(x,y);
	}
}

int init_motor(void)
{
	gpio_enable(dir1);
	gpio_enable(dir2);
	gpio_enable(step1);
	gpio_enable(step2);
	gpio_set_output(dir1);
	gpio_set_output(dir2);
	gpio_set_output(step1);
	gpio_set_output(step2);

	return 0;
}

int run_motor(double dx, double dy)
{
	double udelay = 0;
	
	if(dx == dy || dx == -dy)
	{
		return 0;
	}

	dx = dx / maxValue;
	dy = dy / maxValue;

	int PID = fork();

	if(PID == 0)
	{
		if(dy >= 0)
		{
			if(dx >= 0)
			{
				udelay = (sqrt(dx * dx + dy * dy)); 
			}
			else
			{
				udelay = ((dy * dy - dx * dx) / sqrt(dy * dy + dx * dx));
			}
		}
		if(dy < 0)
		{
			if(dx < 0)
			{
				udelay = -(sqrt(dx * dx + dy * dy));
			}
			else
			{
				udelay = -((dy * dy - dx * dx) / sqrt(dy * dy + dx * dx));
			}	
		}
		if(udelay < 0)
		{
			gpio_set_output_high(dir1);
			udelay *= -1;
		}
		else{
			gpio_set_output_low(dir1);
		}
		if(udelay > 1)
		{
			udelay = 1;
		}
		if(udelay != 0)
		{
			udelay = maxDelay - coDelay * udelay;
			gpio_set_output_high(step1);
			gpio_set_output_low(step1);
			usleep(udelay);
		}
		exit(0);
	}

	else
	{
		if(dy >= 0)
		{
			if(dx >= 0)
			{
				udelay = ((dy * dy - dx * dx) / sqrt(dy * dy + dx * dx));
			}
			else
			{
				udelay = (sqrt(dx * dx + dy * dy));
			}
		}
		if(dy < 0)
		{
			if(dx < 0)
			{
				udelay = -((dy * dy - dx * dx) / sqrt(dy * dy + dx * dx));
			}
			else
			{
				udelay = -(sqrt(dx * dx + dy * dy));
			}
		}
		if(udelay < 0)
		{
			gpio_set_output_low(dir2);
			udelay *= -1;
		}
		else{
			gpio_set_output_high(dir2);
		}
		if(udelay > 1)
		{
			udelay = 1;
		}
		if(udelay != 0)
		{
			udelay = maxDelay - coDelay * udelay;
			gpio_set_output_high(step2);
			gpio_set_output_low(step2);
			usleep(udelay);
		}
	}

	return 0;
}
