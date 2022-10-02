#-------------------------------------------------
#
# Project created by QtCreator 2022-09-11T18:04:49
#
#-------------------------------------------------

QT       += core gui charts datavisualization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = missile_trajectory_qt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    setinitdata.cpp \
    setconstdata.cpp\
    dynamic.cpp\
    linearInterp.cpp\
    RK4.cpp\
    data.cpp


HEADERS += \
        mainwindow.h \
    setinitdata.h \
    setconstdata.h\
    data.h\
    dynamic.h\
    linearInterp.h\
    RK4.h



FORMS += \
        mainwindow.ui \
    setinitdata.ui \
    setconstdata.ui
