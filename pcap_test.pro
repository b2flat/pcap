TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lpcap
SOURCES += main.cpp \
    getpacket.cpp

HEADERS += \
    packetdata.h
