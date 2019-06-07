TARGET = GtLib

TEMPLATE = lib

DEFINES += BUILDING_GTLIB

GT_LIBS = GtCore

RESOURCES = gtlib.qrc

RC_FILE   = gtlib.rc

HEADERS += GtIndexes.h \
           GtData.h \
           GtAllys.h \
           GtHeros.h \
           GtTowns.h \
           GtBoni.h \
           GtMesh.h \
           GtPlayers.h \
           GtIslands.h \
           GtPlans.h \
           GtReports.h \
           GtBookmarks.h \
           GtGods.h \
           GtUnits.h \
           GtBuildings.h \
           GtSpells.h \
           GtResearch.h \
           GtServer.h \
           GtStats.h \
           GtDatabase.h \
           GtWorldLoader.h \
           GtWorlddata.h \
           GtWorlddataPrivate.h 
                      
SOURCES += gtlib.cpp \
           gtallys.cpp \
           gtbookmarks.cpp \ 
           gtdata.cpp \
           gtdatabase.cpp \
           gtislands.cpp \
           gtplans.cpp \
           gtplayers.cpp \
           gtreports.cpp \
           gtserver.cpp \
           gtserverlist.cpp \
           gttowns.cpp \
           gtunits.cpp \
           gtbuildings.cpp \
           gtspells.cpp \
           gtheros.cpp \
           gtgods.cpp \
           gtstats.cpp \
           gtresearch.cpp \
           gtworldloader.cpp \ 
           gtworlddata.cpp \ 
           gtworlddataprivate.cpp \
           edge.cpp \
           tri_mesh.cpp \
           line_seg.cpp \
           triangle.cpp \
           vertex.cpp
           
           

include (../gt.pri)

