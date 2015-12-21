#-------------------------------------------------
#
# Project created by QtCreator 2015-12-20T15:42:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtGUI
TEMPLATE = app

LIBS += -lSDL2

QMAKE_CXXFLAGS += -std=c++14 -Wall -Wextra
CONFIG(release, debug|release){
    QMAKE_CXXFLAGS += -O3 -march=native -Winline
}

SOURCES += main.cpp\
        mainwindow.cpp \
    chip8emulator.cpp \
    ../src/utility/log.cpp \
    ../src/Chip8.cpp \
    ../src/SdlInput.cpp \
    ../src/SdlRenderer.cpp

HEADERS  += mainwindow.h \
    chip8emulator.h \
    ../src/interfaces/iInput.h \
    ../src/interfaces/iRenderer.h \
    ../src/utility/dynamic_assert.h \
    ../src/utility/log.h \
    ../src/Chip8.h \
    ../src/resolution_t.h \
    ../src/SdlInput.h \
    ../src/SdlRenderer.h

FORMS    += mainwindow.ui
