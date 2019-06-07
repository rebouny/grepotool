TARGET = Grepotool

TEMPLATE = app

DEFINES += BUILDING_GTAPP

GT_LIBS = GtCore

RC_FILE = gtapp.rc

RESOURCES = gtapp.qrc

HEADERS += 
           
SOURCES += gtmain.cpp 

include (../gt.pri)

