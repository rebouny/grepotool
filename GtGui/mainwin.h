#ifndef ___MAINWIN_H
#define ___MAINWIN_H
/* mainwin.h  - main window

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

#include <QMainWindow>
#include <QAction>
#include <QSpinBox>
#include <QLabel>
#include <QClipboard>
#include <QProgressBar>

#include <GtWorlddata.h>


class GtProgress;
class ToolWidget;

class PlayerView;
class TownView;
class AllyView;
class BookmarkView;
class MyTownsView;
class TargetsView;
class PlansView;
class ReportView;
class NewsViewer;

class TownInfo;

class MapView;
class MapWindow;
class WorldData;
class Selector;

class Simulator;

class ActIndex : public QObject {
	Q_OBJECT;
public:
	ActIndex ( QAction* a, int idx, QObject *par, const char * slot):QObject (a),index(idx){
		connect (a, SIGNAL(triggered()), this, SLOT(actTriggered()));
		connect (this, SIGNAL(triggered(int)), par, slot);
	}; 

public slots:
	void actTriggered() {emit triggered(index);};

signals:
	void triggered (int);

private:
	int index;
};


class IdAct  : public QAction {
	Q_OBJECT;
public:
	IdAct (const QString& id,const QString& txt,const QString& icon, QObject * o, const char* slot);
signals:
	void triggered (const QString & id);
public slots:
	void onTrigger() {emit triggered (_id);};
private:
	QString _id;
};


class MainWin : public QMainWindow {
	Q_OBJECT;
public:
	MainWin () ;
	~MainWin () ;

	void registerToolBar (QToolBar * b, const QString& s);

	void createMenus ();
	

signals:
	void townInfoChangedSignal (int); // after a report was received successfully
	void aquireNewWorld (const QString& l);

public slots:

	void setLanguage (const QString& l);
	void loadWorld (const QString& l);

	void searchNewWorlds();
	void mergeWithTonda ();

	void editWorldName();

	void progress (const QString& head, const QString& desc, int permill);
	void completed (bool success, const QString& error);
	void cancelled ();

	void worldLoaded (WorldData w);

	void restoreMainState ();
	void storeMainState ();

	void about ();

	void help (); 
	void projectHome (); 
	void checkUpdate (); 
	void ffPlugin (); 
	void ffScript (); 

	void clipboardChanged (QClipboard::Mode mode);

	void offsetChanged ();

	void allySelected (int);
	void playerSelected (int);
	void townSelected (int);
	void mytownSelected (int);
	void targetSelected (int idx);
	void gotoCoords ();
	void zoomToTown (int);
	void scrollToTown (int);
	void selectAlly (int);
	void selectTown (int);
	void selectPlayer (int);

	void bookmarkTown (int);
	void bookmarkAlly (int);
	void bookmarkPlayer (int);
	void bookmarksChanged ();
	
	void addTownToMyTowns (int);
	void addTownToTargets (int);
	void addTargetToPlans ();
	void addMyTownToPlans ();

	void meshProgress (int);

	void updateMenu ();
	
protected:

	void closeEvent(QCloseEvent*);

	void	moveEvent ( QMoveEvent * ev );

	void	resizeEvent ( QResizeEvent * ev );

	void registerToolWidget (ToolWidget * w, Qt::DockWidgetArea dw);

public:
	static MainWin * instance;
	static QPoint currentMapOffset ();
	static int currentMapZoomLevel ();

	MapWindow  * mapview;

	AllyView   * allys;
	TownView   * towns;
	PlayerView * players;
	BookmarkView * bookmarks;

	Simulator * sim;

	MyTownsView * mytowns;
	TargetsView * targets;
	PlansView * plans;
	ReportView * reports;

	NewsViewer * news;

	TownInfo * town_info;

	QProgressBar *prog;

	GtProgress* gtprog;

	QVector <QDockWidget *> dw_list;
	QVector <ToolWidget *> tw_list;
	QVector <QToolBar *> tb_list;

	Selector * townsel;
	Selector * playersel;

	QSpinBox *xpos;
	QSpinBox *ypos;
	QLabel*  meshlab;

	QMenu *  srv;
	QVector <IdAct*> srv_list;
};


#endif
