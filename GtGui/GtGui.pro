TARGET = GtGui

TEMPLATE = lib

DEFINES += BUILDING_GTGUI

GT_LIBS = GtCore GtLib

RESOURCES = gtgui.qrc

RC_FILE   = gtgui.rc

FORMS    = dlg_about.ui \
           datetime.ui \
           town_info.ui \
           units.ui \
           world_news.ui \
           polis_search.ui \
           table.ui \
           table_export.ui \
           simulator.ui \
           specials.ui

HEADERS += mainwin.h \
           table_model.h \
           world_news.h \
           polis_search.h \
           selector.h \
           mapview.h \
           simulator.h \
           command.h \
           map.h \
           popup.h \
           ally_model.h \
           report_model.h \
           player_model.h \
           town_model.h \
           plan_model.h \
           bookmark_model.h \
           town_info.h \
           toolwidget.h 


SOURCES += gtgui.cpp \
           mainwin.cpp \
           command.cpp \
           simulator.cpp \
           world_news.cpp \
           polis_search.cpp \
           town_info.cpp \
           table_model.cpp \
           table_view.cpp \
           plan_model.cpp \
           bookmark_model.cpp \
           item_delegate.cpp \
           selector.cpp\
           popup.cpp \
           report_model.cpp \
           table_export.cpp \
           map.cpp \
           mapview.cpp \
           mesh_thread.cpp \
           ally_model.cpp \
           player_model.cpp \
           town_model.cpp \
           toolwidget.cpp 


include (../gt.pri)

