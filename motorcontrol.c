#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "gpio.h"
#include "motorcontrol.h"

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

int run_motor(int dx, int dy)
{
	int udelay;
	dx = dx / 750;
	dy = dy / 750;

	if(dy == 0 && dx == 0)
	{
		return 0;
	}
	
        int PID = fork();

	if(PID == 0)
	{
		if(dy >= 0)
		{
			gpio_set_output_high(dir1);
		}
		if(dy < 0)
		{
			gpio_set_output_low(dir1);
		}
		if(dx > 0)
		{
			udelay = 15000 - 10000 * sqrt(dx * dx + dy * dy) / sqrt(2);
		}
		if(dx < 0)
		{
			udelay = 15000 - 10000 * (dy * dy - dx * dx) / (dy * dy + dx * dx); 
		}
	        gpio_set_output_high(step1);
	        gpio_set_output_low(step1);
	        usleep(udelay);
                exit(0);
	}

        else
	{
		if(dy > 0)
		{
			gpio_set_output_low(dir2);
		}
		if(dy < 0)
		{
			gpio_set_output_high(dir2);
		}
		if(dx > 0)
		{
			udelay = 15000 - 10000 * (dy * dy - dx * dx) / (dy * dy + dx * dx);
		}
		if(dx < 0)
		{
			udelay = 15000 - 10000 * sqrt(dx * dx + dy * dy) / sqrt(2);
		}
	

		gpio_set_output_high(step2);
		gpio_set_output_low(step2);
		usleep(udelay);
	
		return 0;
        }
}
