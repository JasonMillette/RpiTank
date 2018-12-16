#!/usr/bin/env python
#Jason Millette
#11/23/18

#Finds and displays IP address to SPI device

import socket
import Image
import ImageDraw
import ST7735 as TFT
import Adafruit_GPIO as GPIO
import Adafruit_GPIO.SPI as SPI

#Gets IP address
socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
socket.connect(('8.8.8.8', 0))
IP = socket.getsockname()[0]

#Makes image for second SPI display
image = Image.new('RGB', (128, 128), (0, 0, 255))   #RGB, size, color
draw = ImageDraw.Draw(image)                        #Draws image
draw.text((35, 9), 'IP address', fill = (0, 0, 0))
draw.text((25, 18), IP, fill = (0, 0, 0))

#Displays image on second SPI device
display2 = TFT.ST7735(24, rst = 25, spi = SPI.SpiDev(0, 1, max_speed_hz = 420000000)) #4420MHz clock speed
#display2._init()
display2.display(image)
