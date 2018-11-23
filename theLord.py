#!/usr/bin/env python
#Jason Millette
#11/26/18

#uses weather api to get current weather data for Bangor ME
#then create an 128x128 image for display

from PIL import Image
import Image
import ImageDraw
import ImageFont
import ST7735 as TFT
import Adafruit_GPIO as GPIO
import Adafruit_GPIO.SPI as SPI

#displaying image to spi device
DC = 24
RST = 25

image = Image.open('tachanka.jpeg').resize((128, 128))
display2 = TFT.ST7735(DC, rst=RST, spi=SPI.SpiDev(0, 1, max_speed_hz=8000000))
display2.begin()
display2.display(image)

