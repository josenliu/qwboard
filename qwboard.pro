#-------------------------------------------------
#
# Project created by QtCreator 2019-03-06T22:17:35
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qwboard
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    leftpanel.cpp \
    toolbar.cpp \
    pageview.cpp \
    propertyview.cpp \
    drawview.cpp \
    drawscene.cpp \
    drawshape.cpp \
    dLine.cpp \
    drect.cpp \
    statusbar.cpp

HEADERS += \
        mainwindow.h \
    leftpanel.h \
    toolbar.h \
    pageview.h \
    propertyview.h \
    drawview.h \
    consdefine.h \
    drawscene.h \
    drawshape.h \
    dline.h \
    drect.h \
    statusbar.h

FORMS += \
        mainwindow.ui \
    leftpanel.ui \
    toolbar.ui \
    pageview.ui \
    propertyview.ui \
    drawview.ui \
    statusbar.ui

RESOURCES += \
    icon.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
