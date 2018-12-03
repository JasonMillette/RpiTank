#!/usr/bin/env python
#Jason Millette
#11/23/18

#uses information from the website to display
#then create an 128x128 image for display on an SPI device

import requests
import Image
import ImageDraw
import sys
import ST7735 as TFT
import Adafruit_GPIO.SPI as SPI

#Getting weather data


#Creating weather image for SPI display
image = Image.new('RGB', (128,128), (0, 0, 255))    #RGB, size, color
draw = ImageDraw.Draw(image)                        #creates image
draw.text((10,9), sys.argv[1], fill=(0, 0, 0))#(x,y), text, (R, G, B)
#draw.text((35, 18), 'sys.argv[2]', fill=(0, 0, 0))

#displaying images to spi devices
DC = 24
RST = 25

#Displaying website data
display2 = TFT.ST7735(DC, rst=RST, spi=SPI.SpiDev(0, 1, max_speed_hz=8000000)) # display initalized in initDisplay.py
display2.display(image) #displays image

