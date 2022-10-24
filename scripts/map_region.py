#!/usr/bin/env python

"""
WS4 Map Region Creator

Locate, scale and cut out the appropriate map region for given location.
Result saved as ./data/map.png
"""

from sys import argv, exit
from PIL import Image


BASEMAP_PATH = r'../graphics/maps/Basemap.png'
RES_PATH = r'../data/map.png'
MAP_W = 640
MAP_H = 308


if __name__ == '__main__':
    if len(argv) < 3:
        print('Usage: $ ./map_region.py <x> <y>')
        exit(1)

    x, y = argv[1:]

    im = Image.open(BASEMAP_PATH)
    left = int(x)
    top = int(y)
    right = left + MAP_W
    bottom = top + MAP_H

    im_cropped = im.crop((left, top, right, bottom))
    im_cropped.save(RES_PATH)
