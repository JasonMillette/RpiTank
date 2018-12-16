#!/usr/bin/env python
#MEMES on Demand(Trademark Pending)
#Jason Millette
#12/6/18
#uses hardware interupt to display some spicy custom memes on demand
import RPi.GPIO as GPIO  
import signal
import Image
import ST7735 as TFT
import Adafruit_GPIO.SPI as SPI

#Setting up hardware interupt on GPIO 23
GPIO.setmode(GPIO.BCM)
GPIO.setup(23, GPIO.IN, pull_up_down=GPIO.PUD_UP)

picture = 0

def my_callback(channel):           #on interrupt display a new meme to display 2

    global picture

    if picture == 0:
        display2.display(theLord)
    
    if picture == 1:
        display2.display(boyfriend)
    
    if picture == 2:
        display2.display(dispicable)
    
    if picture == 3:
        display2.display(brain)
    
    if picture == 4:
        display2.display(whoWouldWin)
    
    if picture == 5:
        display2.display(chopper)
    
    if picture == 6:
        display2.display(drake)
    
    if picture == 7:
        display2.display(spongebob)
    
    if picture == 8:
        display2.display(buttons)
        picture = -1
    
    picture += 1    #increment to pick a new meme every loop

GPIO.add_event_detect(23, GPIO.FALLING, callback = my_callback, bouncetime = 300)  

#displaying memes to SPI display
DC = 24
RST = 25

#opening display
display2 = TFT.ST7735(DC, rst = RST, spi = SPI.SpiDev(0, 1, max_speed_hz = 69000000))

#opening all the memes
theLord = Image.open('memes/tachanka.jpeg').resize((128,128))
boyfriend = Image.open('memes/boyfriend.png').resize((128,128))
dispicable = Image.open('memes/dispicableMe.jpg').resize((128,128))
brain = Image.open('memes/Expanding-Brain.jpg').resize((128,128))
whoWouldWin = Image.open('memes/whoWouldWin.jpg').resize((128,128))
chopper = Image.open('memes/chopper.png').resize((128,128))
drake = Image.open('memes/drake.jpg').resize((128,128))
spongebob = Image.open('memes/spongebob.jpg').resize((128,128))
buttons = Image.open('memes/Two-Buttons.jpg').resize((128,128))

while 1:        #deadloop that stops using CPU
   signal.pause()
