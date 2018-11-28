#!/usr/bin/env python
import RPi.GPIO as GPIO  
GPIO.setmode(GPIO.BCM)  
GPIO.setup(23, GPIO.IN, pull_up_down=GPIO.PUD_UP)  

def pushed(channel):
    print "let the memes begin\n"

print "waiting for button press\n"
GPIO.add_event_detect(23, GPIO.FALLING, callback=pushed, bouncetime=300)  

try:
    GPIO.wait_for_edge(23, GPIO.FALLING)
    print "MEME\n"
except KeyboardInterrupt:  
    GPIO.cleanup()       # clean up GPIO on CTRL+C exit  
GPIO.cleanup()           # clean up GPIO on normal exit
