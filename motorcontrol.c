#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "gpio.h"
#include "motorcontrol.h"

int main(int argc, char ** argv)//readdatabase.py call this function after it gets new values from the database
{
	init_motor();//start motor initlize first

	double x = atof(argv[1]);//converts arguments to double
	double y = atof(argv[2]);
	int i;

	for (i = 0; i < 100; i++)//do 100 steps then end 
		run_motor(x,y);

	return 0;
}
int init_motor(void)
{
	// Enables all GPIO pins needed for motors
	gpio_enable(dir1);
	gpio_enable(dir2);
	gpio_enable(step1);
	gpio_enable(step2);
	gpio_enable(ledfor);
	gpio_enable(ledback);
	gpio_set_output(dir1);
	gpio_set_output(dir2);
	gpio_set_output(step1);
	gpio_set_output(step2);
	gpio_set_output(ledfor);
	gpio_set_output(ledback);

	return 0;
}

int run_motor(double dx, double dy)
{
	// Sets initial delay for motor speed
	double udelay = 0;
	
	// Has issue with same values so quick fix
	if(dx == dy || dx == -dy)
	{
		return 0;
	}

	// 'normalizes' coordinates
	dx = dx / maxValue;
	dy = dy / maxValue;

	// Headlights on 
	if(dy >= 0)
	{
		gpio_set_output_high(ledfor);
		gpio_set_output_low(ledback);
	}
	// Backup lights
	else
	{
		gpio_set_output_high(ledback);
		gpio_set_output_low(ledfor);
	}

	// Forks to run both motors
	int PID = fork();

	// Left Motor
	if(PID == 0)
	{
		if(dy >= 0)
		{
			// Left Motor Quadrant 1 Math
			if(dx >= 0)
			{
				udelay = (sqrt(dx * dx + dy * dy)); 
			}
			// Left Motor Quadrant 2 Math
			else
			{
				udelay = ((dy * dy - dx * dx) / sqrt(dy * dy + dx * dx));
			}
		}

		if(dy < 0)
		{
			// Left Motor Quadrant 3 Math
			if(dx < 0)
			{
				udelay = -(sqrt(dx * dx + dy * dy));
			}
			// Left Motor Quadrant 4 Math
			else
			{
				udelay = -((dy * dy - dx * dx) / sqrt(dy * dy + dx * dx));
			}	
		}
		
		// Makes delay positive and makes motor go backwards
		if(udelay < 0)
		{
			gpio_set_output_high(dir1);
			udelay *= -1;
		}

		// Makes motor go forward
		else{
			gpio_set_output_low(dir1);
		}

		// Caps delay
		if(udelay > 1)
		{
			udelay = 1;
		}

		// Delay Math for motor speed
		if(udelay != 0)
		{
			udelay = maxDelay - coDelay * udelay;
			gpio_set_output_high(step1);
			gpio_set_output_low(step1);
			usleep(udelay);
		}
		// Exits fork
		exit(0);
	}

	// Right Motor
	else
	{
		if(dy >= 0)
		{	
			// Right Motor Quadrant 1 Math
			if(dx >= 0)
			{
				udelay = ((dy * dy - dx * dx) / sqrt(dy * dy + dx * dx));
			}
			// Right Motor Quadrant 2 Math
			else
			{
				udelay = (sqrt(dx * dx + dy * dy));
			}
		}
		if(dy < 0)
		{
			// Right Motor Quadrant 3 Math
			if(dx < 0)
			{
				udelay = -((dy * dy - dx * dx) / sqrt(dy * dy + dx * dx));
			}
			// Right Motor Quadrant 4 Math
			else
			{
				udelay = -(sqrt(dx * dx + dy * dy));
			}
		}
		
		// Makes delay positive and motor go backwards 
		if(udelay < 0)
		{
			gpio_set_output_low(dir2);
			udelay *= -1;
		}

		// Makes motor go forwards
		else{
			gpio_set_output_high(dir2);
		}

		// Caps delay
		if(udelay > 1)
		{
			udelay = 1;
		}

		// Motor delay math for motor speed
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
