#!/usr/bin/env python

#Initializes the two 128x128 SPI displays for use with the tank
#Jason Millette 11/15/18

import ST7735 as TFT
import Adafruit_GPIO as GPIO
import Adafruit_GPIO.SPI as SPI

DC = 24
RST = 25

#Creates and initializes first display for weather forcast
display1 = TFT.ST7735(DC, rst = RST, spi = SPI.SpiDev(0, 0, max_speed_hz = 420000000))  #420MHz clock speed
display1.begin()

#Creates and initializes second display for IP and memes
display2 = TFT.ST7735(DC, rst = RST, spi = SPI.SpiDev(0, 1, max_speed_hz = 420000000))
display2._init()
