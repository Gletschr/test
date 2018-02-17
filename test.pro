QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app

win32:LIBS += -lOpenGL32

DEFINES += QT_DEPRECATED_WARNINGS
INCLUDEPATH += include/

SOURCES += \
        src/main.cpp \
        src/Utils.cpp \
        src/TestGLWindow.cpp

HEADERS += \
        include/Utils.h \
        include/TestGLWindow.h

RESOURCES += \
        resources.qrc
