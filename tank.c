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

    int weatherPID = fork();                             //Forks to run both programs simulaniously

    if (weatherPID == 0) {                              // Child
        while(1) {
            system("/home/pi/RpiTank/./weather.py");    //Displays  new weather data every two minutes
            sleep(120);
        }
    }

    else {
        system("/home/pi/RpiTank/./meme.py");           //Parent runs Memes on Demand Button(trademark pending)
    }

    return 0;
}
