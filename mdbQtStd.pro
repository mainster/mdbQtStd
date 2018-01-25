#-------------------------------------------------
#
# Project created by QtCreator 2018-01-24T23:03:44
#
#-------------------------------------------------

QT+= widgets core gui

TARGET= mdbQtStd
TEMPLATE= lib
CONFIG+= staticlib
DESTDIR= ../mdLibs

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
debug.cpp \
globals.cpp \
#mdbqtstd.cpp \
mdstatebar.cpp \
types.cpp \
	globalsui.cpp

HEADERS += \
types.h \
debug.h \
globals.h \
#mdbqtstd.h \
mdstatebar.h \
	globalsui.h

unix {
target.path = /usr/lib
INSTALLS += target
}

SUBDIRS += \
mdbQtStd.pro

DISTFILES +=

