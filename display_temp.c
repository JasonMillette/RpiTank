#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/ioctl.h>

#include <linux/i2c-dev.h>

#include "sensor_name.h"
#include "temp_cool.h"

#define E 0x79 // E
#define C 0x39 // C
#define R 0x50 // R
#define O 0x5C // O
#define Point 0x80 // .
#define Negative 0x40 // -
#define Degree 0x63 // o
#define o 0x00 // O
#define Zero 0x3F // 0
#define One 0x06 // 1
#define Two 0x5B // 2
#define Three 0x4F // 3
#define Four 0x66// 4
#define Five 0x6D // 5
#define Six 0x7D // 6
#define Seven 0x07 // 7
#define Eight 0x7F // 8
#define Nine 0x67 // 9

int main(int argc, char **argv)
{

	int fd, result, i, j;

	double temp;	// Temperature

	int count = 0; // Location in string counter

	char i2c_device[]="/dev/i2c-1";

	unsigned char buffer[17];	// Buffer for scrolling
	unsigned char number[10] = {Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine};	// Buffer to make easy digit to display conversion
	unsigned char class[7] = {o, o, o, o, o, o, o}; // Buffer for display

	/* Open i2c device */
	fd = open(i2c_device, O_RDWR);
	if(fd < 0) // Error Checking
	{
		fprintf(stderr, " Error!\n");
		return 2;
	}

// YOUR CODE HERE

	/* Set slave address */
	result = ioctl(fd, I2C_SLAVE, 0x70);
	if(result < 0) // Error Checking
	{
		fprintf(stderr, " Error!\n");
		return 2;
	}

// YOUR CODE HERE

	/* Turn on oscillator */
	buffer[0] = (0x2<<4) | (0x1);
	result = write(fd, buffer, 1);
	if(result < 0) // Error Checking
	{
		fprintf(stderr, " Error!\n");
		return 2;
	}

// YOUR CODE HERE

	/* Turn on Display, No Blink */
	buffer[0] = (0x8<<4) | (0x1);
	result = write(fd, buffer, 1);
	if(result < 0) // Error Checking
	{
		fprintf(stderr, " Error!\n");
		return 2;
	}

// YOUR CODE HERE

	/* Set Brightness */
	buffer[0] = (0xE<<4) | 0xC;
	result = write(fd, buffer, 1);
	if(result < 0) // Error Checking
	{
		fprintf(stderr, " Error!\n");
		return 2;
	}

// YOUR CODE HERE
	while(1)
	{
		temp = 1.8 * read_temp(SENSOR_NAME) + 32;	// Collects temperature
		if(temp >= 10 && temp < 100)	// Displays numbers in the Tens
		{
			class[0] = number[((int)temp)/10];	// Gets Digits
			class[1] = Point | number[((int)temp % 10)/1];
			class[2] = number[((int)(temp * 10) % 10)/1];
			class[3] = Degree;
			class[4] = C;
		}
		else if(temp >= 0 && temp < 10)	// Gets rid of leading zeros
		{
			class[0] = Point | number[((int)temp % 10)/1];	// Gets Digits
			class[1] = number[((int)(temp * 10) % 10)/1];
			class[2] = number[((int)(temp * 100) % 10)/1];
			class[3] = Degree;
			class[4] = C;
		}
		else if(temp > -10 && temp < 0)	// Gets rid of leading zeros
		{
			class[0] = Negative;	// Gets Digits
			class[1] = Point | number[(((int)temp * -1) % 10)/1];
			class[2] = number[((int)(temp * -10) % 10)/1];
			class[3] = Degree;
			class[4] = C;
		}
		else if(temp > -100 && temp <= -10) // Displays Numbers in the Tens
		{
			class[0] = Negative;	// Gets Digits
			class[1] = number[((int)temp * -1)/10];
			class[2] = number[(((int)temp * -1) % 10)/1];
			class[3] = Degree;
			class[4] = C;
		}
		else if(temp > 100 && temp < 1000)	// Displays Numbers in the Hundreds
		{
			class[0] = number[((int)temp)/100];	// Gets Digits
			class[1] = number[((int)temp % 100)/10];
			class[2] = number[((int)temp % 10)/1];
			class[3] = Degree;
			class[4] = C;
		}
		else{
			class[0] = E;	// If none of the above print error
			class[1] = R;
			class[2] = R;
			class[3] = O;
			class[4] = R;
		}
		printf("%.2lf\n",temp);
		for(j = 0; j < 8; j++)	// Scrolling Text
		{
			for(i = 0; i < 16; i++)
			{
				buffer[i] = 0x00; // If can't assign a character, make zero
				if(i == 1 || i == 3 || i == 7 || i == 9)
				{
					buffer[i] = class[count]; // Assigns the next character
					count++; // Increments to next character in the string
					if(count > 6) // Resets string 
					{
						count = 0; 
					}
				}
			}
			count -= 3; // Starts write at next letter of the string
			if(count < 0) // Makes string wrap around
			{
				count += 7;
			}
			result = write(fd, buffer, 17); // Write the string
			if(result < 0)
			{
				fprintf(stderr, " Error!\n");
				return 2;
			}
			usleep(1000000); // Wait a second
		}
	}

// YOUR CODE HERE

	/* Close device */
	close(fd);

// YOUR CODE HERE

	return 0;
}
