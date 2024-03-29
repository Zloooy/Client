######################################################################
# Automatically generated by qmake (3.1) Wed Sep 4 18:54:01 2019
######################################################################
#CONFIG -= qt
QT += core network
QMAKE_CXXFLAGS += -std=c++0x -pthread 
LIBS += -pthread
TEMPLATE = app
TARGET = Client
INCLUDEPATH += .

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += base_classes/background_service.h \
           base_classes/listener.h \
           base_classes/queue_listener.h \
           base_classes/queue_listener_background_service.h \
           base_classes/sender.h \
           base_classes/sender_background_service.h \
           child_classes/filesystem_watcher.h\
           child_classes/network_client.h
SOURCES += main.cpp \
           base_classes/background_service.cpp \
           child_classes/filesystem_watcher.cpp \
           child_classes/network_client.cpp
