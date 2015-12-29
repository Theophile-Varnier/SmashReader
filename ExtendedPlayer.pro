
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp \
    cqlabel.cpp \
    smashvideo.cpp \
    smat.cpp \
    progresswidget.cpp

HEADERS  += mainwindow.h \
    player.h \
    cqlabel.h \
    smashvideo.h \
    smat.h \
    progresswidget.h
FORMS    += mainwindow.ui

# Opencv Library
INCLUDEPATH += "/usr/local/include/opencv2"
LIBS += `pkg-config --cflags --libs opencv`

#Boost Library
INCLUDEPATH += "/usr/local/include/boost"

# Qwt library
# CONFIG += qwt
# INCLUDEPATH +="/usr/local/qwt-6.1.0-rc3/include"
# LIBS += -L/usr/local/qwt-6.1.0-rc3/lib -lqwt

