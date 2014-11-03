#-------------------------------------------------
#
# Project created by QtCreator 2014-11-04T03:03:39
#
#-------------------------------------------------
cache();
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Masing
TEMPLATE = app


HEADERS += frequencycompare.h \
    history.h \
    piano.h \
    inputwaveplotter.h \
    frequencymonitor.h \
    fft/_kiss_fft_guts.h \
    fft/kiss_fft.h \
    fft/kiss_fftr.h \
    amplitudemonitor.h \
    autocorrelation.h \
    mainwindow.h
SOURCES += frequencycompare.cpp \
    history.cpp \
    piano.cpp \
    inputwaveplotter.cpp \
    frequencymonitor.cpp \
    fft/kiss_fft.c \
    fft/kiss_fftr.c \
    amplitudemonitor.cpp \
    autocorrelation.cpp \
    mainwindow.cpp \
    main.cpp
FORMS += frequencycompare.ui\
    history.ui\
    Piano.ui \
    inputwaveplotter.ui \
    mainwindow.ui
FORMS    += mainwindow.ui


#DEPENDPATH += ./MinGW/msys/1.0/lib/portaudio
#DEPENDPATH += ./MinGW/msys/1.0/lib/libsndfile-1.0.25
#INCLUDEPATH += 'C:/MinGW/msys/1.0/lib/libsndfile-1.0.25/src'
#LIBS = -L'C:/MinGW/msys/1.0/lib/libsndfile-1.0.25/src/.libs' \
#    -lsndfile-1
#INCLUDEPATH += 'C:/MinGW/msys/1.0/lib/portaudio/include'
#LIBS += -Llibs/portaudio \
#	-lportaudio

#include(3rdParties/portaudio)
INCLUDEPATH += '3rdParties/portaudio/include'
LIBS += -L/usr/local/lib -lportaudio


#include(3rdParties/portaudio)
INCLUDEPATH += '3rdParties/libsndfile/include'
LIBS += -L/usr/local/lib -lsndfile


