#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "gpio.h"

/* Set the GPIO output to high*/
int gpio_set_output_high(int gpio) {
	FILE *fff;
	char string[BUFSIZ];

	sprintf(string,"/sys/class/gpio/gpio%d/value",gpio);

	fff=fopen(string,"w");
	if (fff==NULL)
	{
		fprintf(stderr, "\tError in setting output of GPIO%d!\n",gpio);
		return -1;
	}
	fprintf(fff,"1");
	fclose(fff);

	return 0;
}

/* Set the GPIO output to low*/
int gpio_set_output_low(int gpio) {
	FILE *fff;
	char string[BUFSIZ];

	sprintf(string,"/sys/class/gpio/gpio%d/value",gpio);

	fff=fopen(string,"w");
	if (fff==NULL)
	{
		fprintf(stderr,"\tError in setting output of GPIO%d!\n",gpio);
		return -1;
	}
	fprintf(fff,"0");
	fclose(fff);

	return 0;
}

/* Set the GPIO direction to be write */
int gpio_set_output(int gpio) {

        FILE *fff;
        char string[BUFSIZ];

        sprintf(string,"/sys/class/gpio/gpio%d/direction",gpio);

        fff=fopen(string,"w");
        if (fff==NULL) {
                fprintf(stderr,"\tError setting direction of GPIO%d!\n",gpio);
                return -1;
        }
        fprintf(fff,"out\n");
        fclose(fff);

        return 0;
}

/* Set the gpio direction to be read */
int gpio_set_input(int gpio) {

        FILE *fff;
        char string[BUFSIZ];

        sprintf(string,"/sys/class/gpio/gpio%d/direction",gpio);

        fff=fopen(string,"w");
        if (fff==NULL) {
                fprintf(stderr,"\tError setting direction of GPIO%d!\n",gpio);
                return -1;
        }
        fprintf(fff,"in\n");
        fclose(fff);

        return 0;
}



/* Enable the GPIO for user use */
int gpio_enable(int gpio) {

        FILE *fff;

	/* printf("Enabling GPIO%d for export\n",gpio); */
	fff=fopen("/sys/class/gpio/export","w");
	if (fff==NULL) {
		fprintf(stderr,"\tError enabling GPIO%d!\n",gpio);
		return -1;
	}
	fprintf(fff,"%d\n",gpio);
	fclose(fff);

	return 0;

}
