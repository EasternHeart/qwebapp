#-------------------------------------------------
#
# Project created by QtCreator 2013-08-28T20:47:40
#
#-------------------------------------------------

QT       += core gui network webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qwebapp
TEMPLATE = app


SOURCES += main.cpp\
        webappview.cpp

HEADERS  += webappview.h

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += QJson
