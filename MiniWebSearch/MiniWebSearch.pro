QT += core
QT -= gui

TARGET = MiniWebSearch
CONFIG += console
CONFIG -= app_bundle
CONFIC += c++11

TEMPLATE = app

SOURCES += main.cpp \
	porter2_stemmer.cpp \    

HEADERS += \
    parser.h \
    file.h \
    AVLTree.h \
    DSVector.hpp \
    porter2_stemmer.hpp \

