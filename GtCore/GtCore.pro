#
# QtUpdater.pro - QMake project definition file
#
# Copyright (c) 2014 P. Vorpahl
#
# This file is part of QtUpdater, a free utility for automating 
# and managing software updates via HTTP.
# 
# QtUpdater is free Software: you can redistribute it and/or modify 
# it under the terms of the GNU Lesser General Public License as 
# published by the Free Software Foundation, either version 3 of the 
# License, or any later version. Alternatively, you may use it under 
# the terms of the GNU General Public License as published by the Free 
# Software Foundation, either version 3 of the License, or any later 
# version.
# 
# QtUpdater is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License 
# along with QtUpdater; see the files 'GPL.txt' and 'LGPL.txt' in 
# the base directory of your installation. If not, see 
# 'http://www.gnu.org/licenses/'.

# Replace this with your local installation of Qt

TARGET   = GtCore

TEMPLATE = lib

RC_FILE = gtcore.rc

RESOURCES = gtcore.qrc

DEFINES += BUILDING_GTCORE
         
HEADERS  = GtDefines.h \
           GtCore.h \
           GtApp.h \
           GtDownload.h \
           GtSplash.h \
           GtArchive.h \
           GtProgress.h \
           json.h

SOURCES  = gtdownload.cpp \          
           gtcore.cpp \
           gtapp.cpp \
           gtsplash.cpp \
           gtarchive.cpp \
           gtrelease.cpp \
           gtprogress.cpp \
           json.cpp

include (../gt.pri)