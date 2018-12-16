#!/usr/bin/env python
#Jason Millette
#11/23/18

#uses weather api to get current weather data for Bangor ME
#then create an 128x128 image for display on an SPI device

import requests
import Image
import ImageDraw
import ST7735 as TFT
import Adafruit_GPIO.SPI as SPI

#Getting weather data
address = 'http://api.openweathermap.org/data/2.5/weather?appid=62ab759f6e4188d80f57fbbd854be303&q=Bangor'
jsonData = requests.get(address).json()     # gets current weather information
weather = jsonData['weather'][0]['description'] # current weather condition
temperature = jsonData['main']['temp'] #current temperature in Kelvin
temperature = (temperature - 273.15) * (9/5.) + 32 #convert Kelvin to Fahrenheit
wind = jsonData['wind']['speed'] #current wind speed mi/h
pressure = jsonData['main']['pressure'] #current pressure hpa
humidity = jsonData['main']['humidity'] #current humidity %
wind = 'Wind speed: %2.1fmi/h' %wind 
temperature = 'Temperature: %2.2fF' %temperature
pressure = 'Pressure: %dhpa' %pressure
humidity = 'Humidity: %d' %humidity + '%'

#Creating weather image for SPI display
image = Image.new('RGB', (128,128), (0, 0, 255))    #RGB, size, color => Blue was chosen for the background
draw = ImageDraw.Draw(image)                        #creates image
draw.text((20,9), 'Current weather', fill=(0, 0, 0))#(x,y), text, (R, G, B)
draw.text((35, 18), 'Bangor, ME', fill=(0, 0, 0))    #Bangor was chosen as it is the closest availabel city 
draw.text((6, 36), weather, fill=(0, 0, 0))
draw.text((6, 45), wind, fill=(0, 0, 0))
draw.text((6, 54), temperature, fill=(0, 0, 0))
draw.text((6, 63), pressure, fill=(0, 0, 0))
draw.text((6, 72), humidity, fill=(0, 0, 0))

#displaying images to spi devices
DC = 24
RST = 25

#Displaying weather data
display1 = TFT.ST7735(DC, rst=RST, spi=SPI.SpiDev(0, 0, max_speed_hz=8000000)) # display initalized in initDisplay.py
display1.display(image) #displays image

