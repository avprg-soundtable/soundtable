#-------------------------------------------------
#
# Project created by QtCreator 2015-01-14T13:01:54
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    a/projectafactory.cpp \
    a/controlProcessor.cpp \
    a/filterProcessor.cpp \
    a/detectProcessor.cpp \
    a/soundProcessor.cpp \
    b/projectbfactory.cpp \
    abstractprojectinfo.cpp \
    abstractprojectwidget.cpp \
    abstractprojectfactory.cpp \
    a/projectawidget.cpp \
    b/projectbwidget.cpp \
    a/ip/posix/NetworkingUtils.cpp \
    a/ip/posix/UdpSocket.cpp \
    a/ip/IpEndpointName.cpp \
    a/osc/OscOutboundPacketStream.cpp \
    a/osc/OscPrintReceivedElements.cpp \
    a/osc/OscReceivedElements.cpp \
    a/osc/OscTypes.cpp \
    a/puredataosccontroller.cpp

HEADERS  += mainwindow.h \
    a/projectafactory.h \
    a/controlProcessor.h \
    a/filterProcessor.h \
    a/detectProcessor.h \
    a/soundProcessor.h \
    b/projectbfactory.h \
    abstractprojectinfo.h \
    abstractprojectwidget.h \
    abstractprojectfactory.h \
    a/projectawidget.h \
    b/projectbwidget.h \
    a/ip/IpEndpointName.h \
    a/ip/NetworkingUtils.h \
    a/ip/PacketListener.h \
    a/ip/TimerListener.h \
    a/ip/UdpSocket.h \
    a/osc/MessageMappingOscPacketListener.h \
    a/osc/OscException.h \
    a/osc/OscHostEndianness.h \
    a/osc/OscOutboundPacketStream.h \
    a/osc/OscPacketListener.h \
    a/osc/OscPrintReceivedElements.h \
    a/osc/OscReceivedElements.h \
    a/osc/OscTypes.h \
    a/puredataosccontroller.h

FORMS    += mainwindow.ui \
    a/projectawidget.ui \
    b/projectbwidget.ui

include(../libs/videoengine/videoengine.pri)
