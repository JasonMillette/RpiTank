#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "sensor_name.h"
#include "temp_cool.h"

double read_temp(char *filename)
{
	
	char string1[256], string2[256];	// Strings for device
	FILE *fd;
	double result=0.0;	// Result to return
	int counter = 0;	// These 2 variables for string to double conversion
	int powTen = 1;

	/* Your code here */
	fd = fopen(filename,"r");	// Opens the file and checks errors
	if(fd == NULL || fd < 0)
	{
		fprintf(stderr, "\tError");
		return -1;
	}

	fscanf(fd, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %s %*s %*s %*s %*s %*s %*s %*s %*s %*s %s", string1, string2);	// Reads the appropriate strings from the file
	if(strcmp(string1,"YES") != 0)		// Makes sure CRC is YES
	{
		fprintf(stderr, "\tError!");
		return -1;
	}

	// Used to convert string to a double for celcius
	for(int i = 0; i < strlen(string2); i++)	// Goes through each character in the string
	{
		if(string2[i] > 47 && string2[i] < 58)	// Looks at ASCII numbers
		{
			for(int j = strlen(string2) - 3; j > counter; j--)	// Makes sure digit is in right place (Thousands, hundreds, tens, etc)
			{
				powTen *= 10;
			}
			result += (string2[i] - 48) * powTen;	// Put the digits together
			counter += 1;
			powTen = 1;
		}
	}
	return result / 1000;	// Returns the correct celcius measurement
}

