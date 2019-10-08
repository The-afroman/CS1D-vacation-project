#-------------------------------------------------
#
# Project created by QtCreator 2019-09-08T20:38:15
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project1_CS1D
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
        addfood.cpp \
        admin.cpp \
        database.cpp \
        login.cpp \
        main.cpp \
        mainwindow.cpp \
        removefood.cpp \
        shortesttripwindow.cpp \
        trippage.cpp \
        removecity.cpp

HEADERS += \
        addfood.h \
        admin.h \
        city.h \
        database.h \
        login.h \
        mainwindow.h \
        removefood.h \
        shortesttripwindow.h \
        trippage.h \
        removecity.h

FORMS += \
        addfood.ui \
        admin.ui \
        login.ui \
        mainwindow.ui \
        removecity.ui \
        removefood.ui \
        shortesttripwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../../../map of europe.jpg \
    cities.db \
    map of europe.jpg

RESOURCES += \
