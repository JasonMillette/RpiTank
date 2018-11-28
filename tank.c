//ECE471 Project
//Raspberry pi tank weather station beer getting beast

//Jason Millette
//11/26/18

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include "tank.h"
#include "motorcontrol.h"

int main() {

    system("./initDisplay.py");         //Initialize the SPI displays
    system("./IP.py");                  //Displays the IP address for webpage

    int parentPID = getpid();
    int weatherPID = fork();

    if (weatherPID == 0) {
        while(1) {
            system("./weather.py");
            sleep(120);
        }
    }
}
