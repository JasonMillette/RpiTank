#!/usr/bin/env python
import RPi.GPIO as GPIO  
import signal
import Image
import ST7735 as TFT
import Adafruit_GPIO.SPI as SPI

#Setting up hardware interupt on GPIO 23
GPIO.setmode(GPIO.BCM)
GPIO.setup(23, GPIO.IN, pull_up_down=GPIO.PUD_UP)

def my_callback(channel):           #on interrupt display a new meme to display 2
    display2.display(theLord)


GPIO.add_event_detect(23, GPIO.FALLING, callback = my_callback, bouncetime = 300)  

#displaying memes to SPI display
DC = 24
RST = 25

#opening display
display2 = TFT.ST7735(DC, rst = RST, spi = SPI.SpiDev(0, 1, max_speed_hz = 69000000))

#opening memes
theLord = Image.open('tachanka.jpeg').resize((128,128))


while 1:        #deadloop that stops using CPU
   signal.pause()
