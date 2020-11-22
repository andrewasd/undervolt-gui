TEMPLATE = app
TARGET = undervolt

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES +=  main.cpp \
    options.cpp \
    verticaloption.cpp \
    window.cpp

HEADERS += \
    options.h \
    verticaloption.h \
    window.h
