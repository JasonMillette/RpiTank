#!/usr/bin/env python
#Jason Millette
#11/15/18

from PIL import Image
import Image
import ImageDraw
import ImageFont
import sys

img = Image.new('RGB', (128, 128), (255, 255, 255))  #RGB, size, color
d = ImageDraw.Draw(img)
d.text((6, 9), sys.argv[1], fill=(0, 0, 0))
print sys.argv[1]
img.save('/home/pi/Documents/ECE471/project/RpiTank/test.png')
