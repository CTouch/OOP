QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simple_ps
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#QT += charts

SOURCES += \
    dialogchecktosave.cpp \
    dialognoselected.cpp \
    drawingboard.cpp \
    histwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    myellipse.cpp \
    myimage.cpp \
    mypolygon.cpp \
    myrectangle.cpp

HEADERS += \
    dialogchecktosave.h \
    dialognoselected.h \
    drawingboard.h \
    graph.h \
    histwidget.h \
    mainwindow.h \
    myellipse.h \
    myimage.h \
    mypolygon.h \
    myrectangle.h

#CONFIG += console thread

FORMS += \
    dialogchecktosave.ui \
    dialognoselected.ui \
    histwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/resources.qrc

RC_FILE += resource/icon.rc
DESTDIR = $$absolute_path($${_PRO_FILE_PWD_}/bin/)

