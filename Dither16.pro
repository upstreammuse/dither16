TEMPLATE = app
CONFIG += warn_on
HEADERS += \
   dither16.h \
   ditherer.h \
   ditherthread.h
SOURCES += \
   dither16.cpp \
   ditherer.cpp \
   ditherthread.cpp
ICON = dither16.icns
RC_FILE = dither16.rc
TARGET = Dither16
