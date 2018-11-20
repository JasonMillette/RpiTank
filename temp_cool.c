#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define SENSOR_NAME "/sys/bus/w1/devices/28-0416563c6cff/w1_slave"

static double read_temp(char *filename) {

	double result=0.0;
        char rawInput[256], crc[256];       //strings for input
        FILE *W1;

	/* Your code here */
        W1 = fopen(SENSOR_NAME, "r");       //opens one wire device
        if (W1 < 0) {
            printf("error opening W1\n");
            return -1000;
        }

        fscanf(W1, " %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %s %*s %*s %*s %*s %*s %*s %*s %*s %*s %s",crc , rawInput);    //assigns the wanted strings and ignores the rest

        if (strcmp(crc, "YES")) {       //checks the CRC
            printf("crc failed");
            return -1001;
        }

        result = (atoi(rawInput + 2)) / 1000.0;     //Converts string to degrees C

        fclose(W1);

	return result;
}

int main(int argc, char **argv) {

	volatile double temp1;
        char output[20], command[255] = "./textToImage.py";

	while(1) {

		temp1=read_temp(SENSOR_NAME);
                if (temp1 <= -1000) printf("Error in reading from device.\n");
                else {
                    strcpy(output, "");
                    strcpy(command, "./textToImage.py");
                    temp1 = (temp1 * (9.0/5)) + 32;     //convert C to F
                    sprintf(output, " %lf", temp1);
                    printf("temp program: %s \n", output);
                    strcat(command, output);
                    system(command);
                    printf("command: %s\n", command);
                    system("./initDisplay.py");
                    system("./display.py");
                }
		sleep(1);
	}

	return 0;
}
