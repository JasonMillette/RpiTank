//ECE471 Project
//Raspberry pi tank weather station beer getting beast

//Jason Millette
//11/26/18

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

int main() {

    system("/home/pi/RpiTank/./initDisplay.py");         //Initialize the SPI displays
    system("/home/pi/RpiTank/./IP.py");                  //Displays the IP address for webpage

    int weatherPID = fork();

    if (weatherPID == 0) {
        while(1) {
            system("/home/pi/RpiTank/./weather.py");
            sleep(120);
        }
    }

    else {
        system("/home/pi/RpiTank/./meme.py");
    }

    return 0;
}
