#!/usr/bin/env python

"""
WS4 Configuration Manager

Edit configuration values and parameters for WS4 using a GUI.
"""

from PySide6.QtUiTools import *
from PySide6.QtWidgets import *
from PySide6.QtCore import *
from PySide6.QtGui import *
from sys import argv, exit
from PIL import Image
import json


CFG_PATH = r'../data/config.json'
UI_PATH = r'configure.ui'
BASEMAP_PATH = r'../graphics/maps/Basemap.png'
RES_PATH = r'../data/map.png'
MAP_W = 640
MAP_H = 308


def cutout_region(x, y, w, h, im_path, res_path):
    im = Image.open(im_path)

    left = x
    top = y
    right = left + w
    bottom = top + h

    im_cropped = im.crop((left, top, right, bottom))
    im_cropped.save(res_path)


def load_UI(path):
    # Open UI file at given path
    ui_file = QFile(path)
    if not ui_file.open(QIODevice.ReadOnly):
        print(f'Cannot open {path}: {ui_file.errorString()}')
        exit(-1)

    # Load the UI into a window object
    loader = QUiLoader()
    window = loader.load(ui_file)
    ui_file.close()
    if not window:
        print(loader.errorString())
        exit(-1)

    return window


def load_basemap(win, x, y):
    pix = QPixmap(BASEMAP_PATH)
    scene = QGraphicsScene()
    scene.addPixmap(pix)
    win.mapView.setScene(scene)
    win.mapView.centerOn(x, y)


if __name__ == '__main__':
    QCoreApplication.setAttribute(Qt.AA_ShareOpenGLContexts)
    app = QApplication(argv)

    win = load_UI(UI_PATH)
    win.setFixedSize(win.width(), win.height())

    load_basemap(win, 2000, 430)

    win.show()
    win.activateWindow()
    win.raise_()
    exit(app.exec())
