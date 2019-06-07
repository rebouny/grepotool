#ifndef __GT_WORLDLOADER_H
#define __GT_WORLDLOADER_H
/* gtworldloader.h  - world data handling

Copyright (c) 2013 P. Vorpahl

This file is part of Grepotool, a free utility for the browsergame 
Grepolis which is the intellectual property of InnoGames GmbH.

Grepotool is free Software: you can redistribute it and/or modify 
it under the terms of the GNU Lesser General Public License as 
published by the Free Software Foundation, either version 3 of the 
License, or any later version. Alternatively, you may use it under 
the terms of the GNU General Public License as published by the Free 
Software Foundation, either version 3 of the License, or any later 
version.

Grepotool is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License 
along with 'Grepotool; see the files 'GPL.txt' and 'LGPL.txt' in 
the base directory of your installation. If not, see 
'http://www.gnu.org/licenses/'.
*/

#include <QVector>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QMutexLocker>
#include <GtWorlddata.h>
#include <GtServer.h>

class GtDownload;
class GtProgress;


#ifdef EXPORT 
# undef EXPORT
#endif
#ifdef BUILDING_GTLIB
# define EXPORT DLL_EXPORT
#else
# define EXPORT DLL_IMPORT
#endif



class EXPORT LoaderThread : public QThread {
	Q_OBJECT;
public:
	LoaderThread (QObject * p, GtProgress* prog);
	~LoaderThread ();

public slots:
	void loadWorld (const QString& sn);

signals:
	void worldLoaded (WorldData w);

protected:
	void run();

private:
	QMutex _m;
	QWaitCondition _condition;
	bool _restart;
	bool _abort;    
	QString _world;
	GtProgress* _prog;
};




class Splash;
class EXPORT GtServerSelector : public QObject  {
	Q_OBJECT;

public:
	GtServerSelector (QObject * par=0);
	QString initialSelect();

public slots:
	
	void countryChanged (int);
	void srvChanged     (int);
	
protected:
	int country;
	int number;

	QStringList countries;
	Splash * splash;
};

#endif