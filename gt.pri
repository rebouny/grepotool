####################################################################
#
# Global Qmake project definition file for Grepotool
# 
# Copyright (c) 2014 Peter Vorpahl 
#
# See the file COPYING for further information
# 
####################################################################

# Destination for binaries

DESTDIR      = ../../bin

# Qt modules to be used

QT      += core gui network widgets

CONFIG	+= stl qt thread exceptions warn_on

# A build subdirectory to keep the main source directory clean

BUILD_PATH = ./build
UI_DIR	= $${BUILD_PATH}/.ui
MOC_DIR	= $${BUILD_PATH}/.moc

# setup additional include paths and libraries
LIBS        += -L../../bin
DEPENDPATH  += .
INCLUDEPATH += .

OTG = $$TARGET

# Operating system specific import and export macros

win32 {
  DEFINES += DLL_EXPORT=__declspec(dllexport)
  DEFINES += DLL_IMPORT=__declspec(dllimport)
  LIBS    += -lpsapi -lshell32 
}
!win32 {
  DEFINES += DLL_EXPORT
  DEFINES += DLL_IMPORT  
}

# Specific project template for Microsoft compilers 
# All others work fine with Makefiles

message (Makespec: $$QMAKESPEC) 

win32-msvc*{
    TEMPLATE = $$join(TEMPLATE,,"vc",)
} 

# Resource compilation directory 

RCC_DIR	= $${BUILD_PATH}/.rcc


# Add library directories to include path

for(ll, GT_LIBS) { 
  	INCLUDEPATH += $$join(ll,,"../",) 
}

# Some definitions for debug build

build_pass:CONFIG (debug, debug|release) {

	# Link against the debug version of all 
	# libraries that are specified in the GT_LIBS variable

	for(ll, GT_LIBS) { 
		LIBS += $$join(ll,,"-l",d) 
	}

	# for debug output, we need the system console	

	CONFIG	+= console
	
	# append a 'd' (for debug) to the target
	
	TARGET	= $$join(OTG,,,d)
	
	# set up object directories to keep the main directory clean
	
	unix:OBJECTS_DIR	= $${BUILD_PATH}/debug/.obj/unix
	win32:OBJECTS_DIR	= $${BUILD_PATH}/debug/.obj/win32
	mac:OBJECTS_DIR	    = $${BUILD_PATH}/debug/.obj/mac

	# turn memory logging on
	DEFINES += __LOG_MEMORY

	# set global debugging define
	DEFINES += __DEBUG_BUILD
}

# Release build 

build_pass:CONFIG (release, debug|release) {

	# Link against the release version of all libraries 
	# that are specified in the GT_LIBS variable

	for(ll, GT_LIBS) { 
		LIBS += $$join(ll,,"-l",) 
	}

	#QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
	#QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

	#CONFIG	+= console

	# set up release build directories for objects to keep
	# the main directory clean	

	unix:OBJECTS_DIR	= $${BUILD_PATH}/release/.obj/unix
	win32:OBJECTS_DIR	= $${BUILD_PATH}/release/.obj/win32
	mac:OBJECTS_DIR	    = $${BUILD_PATH}/release/.obj/mac
} 
