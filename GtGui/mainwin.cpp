/* mainwin.cpp - main window

Copyright (c) 2013 P. Vorpahl

This file is part of Grepotool, a free utility for the browsergame 
Grepolis which is the intellectual property of InnoGames GmbH.

Grepotool is free Software: you can redistribute it and/or modify 
it under the terms of the GNU General Public License as published by the Free 
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
#include <GtProgress.h>
#include <GtReports.h>
#include <GtWorldLoader.h>
#include "mainwin.h"
#include "ally_model.h"
#include "command.h"
#include "player_model.h"
#include "town_model.h"
#include "plan_model.h"
#include "report_model.h"
#include "bookmark_model.h"
#include "town_info.h"
#include "world_news.h"


#include "ui_dlg_about.h"
#include "mapview.h"
#include "simulator.h"

#include "selector.h"
#include <GtApp.h>
#include <GtServer.h>

#include <QToolBar>
#include <QMenuBar>
#include <QScrollBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QDockWidget>
#include <QSettings>
#include <QDesktopServices>


#define USERSCRIPT_LINK "http://userscripts.org/scripts/show/183441"
#define PLUGIN_LINK     "https://addons.mozilla.org/de/firefox/addon/grepo-tool-support/" 
#define PROJECT_LINK    "https://sourceforge.net/projects/grepo-tool"


IdAct::IdAct(const QString& id,const QString& txt,const QString& icon, QObject * o, const char* slot):QAction(QIcon(icon),txt, o),_id(id)
{
	connect (this, SIGNAL (triggered()) , this, SLOT(onTrigger()));
	connect (this, SIGNAL (triggered(const QString&)) , o, slot);
}





MainWin * MainWin::instance = 0;


MainWin::MainWin ()
{
	instance = this;
	setMinimumSize(800,600);

	mapview = new MapWindow;
	setCentralWidget (mapview);
	registerToolWidget (mapview, Qt::NoDockWidgetArea);
	connect (mapview->_view, SIGNAL(townDblClickSignal (int)), this, SLOT(selectTown (int)));

	allys = new AllyView;
	registerToolWidget (allys, Qt::LeftDockWidgetArea);
	connect (allys, SIGNAL(updateInfMapSignal ()), mapview->_view, SLOT(updateInfMap()));
	connect (allys,   SIGNAL(itemClickSignal (int)), this, SLOT(allySelected (int)));
	connect (allys,   SIGNAL(bookmarkChangedSignal ()), this, SLOT(bookmarksChanged ()));
	

	players = new PlayerView;
	registerToolWidget (players, Qt::LeftDockWidgetArea);
	connect (players, SIGNAL(updateMapSignal ()), mapview->_view, SLOT(updateMap()));
	connect (players, SIGNAL(itemClickSignal (int)), this, SLOT(playerSelected (int)));
	connect (players,   SIGNAL(bookmarkChangedSignal ()), this, SLOT(bookmarksChanged ()));

	towns = new TownView;
	registerToolWidget (towns, Qt::RightDockWidgetArea);
	connect (towns,   SIGNAL(itemClickSignal (int)), this, SLOT(townSelected (int)));
	connect (towns, SIGNAL(itemDoubleClickSignal (int)), this, SLOT(zoomToTown (int)));
	connect (towns,   SIGNAL(bookmarkChangedSignal ()), this, SLOT(bookmarksChanged ()));

	town_info = new TownInfo;
	registerToolWidget (town_info, Qt::RightDockWidgetArea);
	connect (town_info, SIGNAL(townChangedSignal(int)), towns->model(), SLOT(triggerRedraw()));
	connect (town_info, SIGNAL(gotoTownSignal (int)), this, SLOT(zoomToTown (int)));
	connect (town_info, SIGNAL(townChangedSignal(int)), mapview->_view, SLOT(updateMap()));

	bookmarks = new BookmarkView;
	registerToolWidget (bookmarks, Qt::RightDockWidgetArea);
	connect (bookmarks, SIGNAL(updateInfMapSignal()), towns->model(), SLOT(triggerRedraw()));
	connect (bookmarks, SIGNAL(updateInfMapSignal()), players->model(), SLOT(triggerRedraw()));
	connect (bookmarks, SIGNAL(updateInfMapSignal()), allys->model(), SLOT(triggerRedraw()));
	connect (bookmarks, SIGNAL(updateInfMapSignal ()), mapview->_view, SLOT(updateInfMap()));
	connect (allys, SIGNAL(updateInfMapSignal ()), bookmarks->model(), SLOT(triggerRedraw()));
	connect (allys, SIGNAL(updateMapSignal ()), bookmarks->model(), SLOT(triggerRedraw()));
	connect (players, SIGNAL(updateInfMapSignal ()), bookmarks->model(), SLOT(triggerRedraw()));
	connect (players, SIGNAL(updateMapSignal ()), bookmarks->model(), SLOT(triggerRedraw()));

	connect (bookmarks, SIGNAL(gotoTownSignal (int)), this, SLOT(selectTown (int)));
	connect (bookmarks, SIGNAL(gotoPlayerSignal (int)), this, SLOT(selectPlayer (int)));
	connect (bookmarks, SIGNAL(gotoAllySignal (int)), this, SLOT(selectAlly(int)));


	mytowns = new MyTownsView;
	registerToolWidget (mytowns, Qt::BottomDockWidgetArea);
	connect (mytowns, SIGNAL(plansChangedSignal()), mapview->_view, SLOT(updateMap()));
	
	targets = new TargetsView;
	registerToolWidget (targets, Qt::BottomDockWidgetArea);
	connect (targets, SIGNAL(plansChangedSignal()), mapview->_view, SLOT(updateMap()));
	
	plans = new PlansView;
	registerToolWidget (plans, Qt::BottomDockWidgetArea);
	
	sim = new Simulator;

	reports = new ReportView;
	registerToolWidget (reports, Qt::LeftDockWidgetArea);

	connect (reports, SIGNAL(reportSelectedSignal (int)), sim, SLOT(setReport (int)));
	connect (players, SIGNAL(itemClickSignal (int)), reports, SLOT(setPlayer(int)));
	connect (allys, SIGNAL(itemClickSignal (int)), reports, SLOT(setAlly(int)));
	connect (towns, SIGNAL(itemClickSignal (int)), reports, SLOT(setTown(int)));

	connect (mytowns, SIGNAL (itemClickSignal (int)), this, SLOT(mytownSelected (int)));
	connect (mytowns, SIGNAL (addToPlansSignal ()), this, SLOT(addMyTownToPlans()));
	connect (targets, SIGNAL (addToPlansSignal ()), this, SLOT(addTargetToPlans()));
	connect (targets, SIGNAL (itemClickSignal (int)), this, SLOT(targetSelected (int)));

	connect (sim , SIGNAL(reportSignal(int)), towns->model(), SLOT(triggerRedraw()));
	connect (sim , SIGNAL(reportSignal(int)), town_info, SLOT(selectTown(int)));
	connect (sim , SIGNAL(reportSignal(int)), mapview->_view, SLOT(updateMap()));


	news = new NewsViewer;
	registerToolWidget (news, Qt::TopDockWidgetArea);
	connect (news, SIGNAL(townClickSignal (int)), this, SLOT(selectTown (int)));
	connect (news, SIGNAL(playerClickSignal (int)), this, SLOT(selectPlayer (int)));
	connect (news, SIGNAL(allyClickSignal(int)), this, SLOT(selectAlly(int)));
	connect (players, SIGNAL(itemClickSignal (int)), news, SLOT(setPlayer(int)));
	connect (allys, SIGNAL(itemClickSignal (int)), news, SLOT(setAlly(int)));

	connect (bookmarks, SIGNAL(gotoTownSignal (int)), news, SLOT(setTown (int)));
	connect (bookmarks, SIGNAL(gotoPlayerSignal (int)), news, SLOT(setPlayer (int)));
	connect (bookmarks, SIGNAL(gotoAllySignal (int)), news, SLOT(setAlly(int)));

	connect (mapview->_view, SIGNAL(townDblClickSignal (int)), news, SLOT(setTown (int)));





	connect(GtApp::clipboard(), SIGNAL(changed (QClipboard::Mode)), this, SLOT(clipboardChanged (QClipboard::Mode)));

	// Just a hack to initialize the connection.
	GtApp::clipboard()->setText("");

	prog = new QProgressBar;
	prog->setRange  (0,1000);

	meshlab = new QLabel;
	QStatusBar *sp = new QStatusBar(this);
	// sp->addPermanentWidget (meshlab);
	sp->addPermanentWidget (prog);

	gtprog = new GtProgress (this);
	connect (gtprog, SIGNAL(progress (const QString&, const QString&, int )), this,SLOT(progress (const QString&, const QString&, int )));
	connect (gtprog, SIGNAL(completed (bool , const QString& )), this,SLOT(completed (bool , const QString& )));
	connect (gtprog, SIGNAL(cancelled ()), this,SLOT(cancelled ()));
	
	LoaderThread * lt = new LoaderThread (this, gtprog);
	connect (lt,SIGNAL (worldLoaded(WorldData)), this, SLOT(worldLoaded(WorldData)));
	connect (this, SIGNAL(aquireNewWorld(const QString&)), lt,SLOT(loadWorld(const QString&)));

	townsel = new Selector(this,Selector::SelectTowns);
	playersel = new Selector(this,Selector::SelectPlayers);

	connect (playersel,SIGNAL(itemSelectedSignal(int)), this, SLOT(selectPlayer(int)));
	connect (townsel,SIGNAL(itemSelectedSignal(int)), this, SLOT(selectTown(int)));
	connect (townsel,SIGNAL(gotoClickedSignal (int)), this, SLOT(zoomToTown(int)));

	setStatusBar (sp);
	QList<int>sl;
	sl.push_back(200);
	sl.push_back(400);

 }

void MainWin::progress (const QString& head, const QString& desc, int permill)
{
	statusBar()->showMessage(QString ("%1 - %2").arg(head).arg(desc));
	prog->setValue(permill);
}

void MainWin::completed (bool success, const QString& error)
{
	prog->setValue(0);
	if (success) {
		statusBar()->clearMessage();
	} else {
		statusBar()->showMessage(error);
	}
}

void MainWin::cancelled ()
{
	prog->setValue(0);
	statusBar()->showMessage(tr("Aborted"));
}

void MainWin::setLanguage (const QString& l)
{
	GtApp::instance()->setLanguage (l);
}
void MainWin::loadWorld (const QString& l)
{
	qDebug () << l;
	emit aquireNewWorld (l);
}


void MainWin::meshProgress (int v)
{
	if (v == 1000) {
		meshlab->setText("ok");
	} else {
		int dec = v%10;
		int nv =  v/10;
		meshlab->setText(tr("Meshing %1.%2%").arg(nv).arg(dec));
	}
}

QPoint MainWin::currentMapOffset () {
	return instance->mapview->_view->currentOffset();
};

int MainWin::currentMapZoomLevel () {
	return instance->mapview->_view->currentZoomLevel();
};

void MainWin::clipboardChanged (QClipboard::Mode mode)
{
	if (mode != QClipboard::Clipboard) return ;

	if (sim->handleIncomingData (GtApp::clipboard()->text())) {
		GtApp::clipboard ()->clear ();		
	}
	
}

void MainWin::worldLoaded (WorldData w)
{
	storeMainState();
	WorldData::setCurrentWorld (w);
	restoreMainState();
}



void MainWin::restoreMainState ()
{
	updateMenu ();
	townsel->updateList ();
	playersel->updateList ();

	for (int i=0;i<tw_list.size();++i) 
		tw_list[i]->worldChanged();

	QSettings s ("Grepotool", GT_VERSION_SHORT);
	QString glob ("Global/MainWindow/") ;
	QString srv = WorldData::currentWorld().serverName();
	QString wrld = srv+"/MainWindow/";

	QString basekey = glob;
	/*
	if(!srv.isEmpty() && Setting::value(STORE_SETTINGS_PER_WORLD).toBool()) {
		basekey = wrld;
	}
	*/
	bool mx = s.value(basekey+"WindowMaximized").toBool();
	if (mx) {
		setWindowState(windowState() | Qt::WindowMaximized);
	} else {
		restoreGeometry(s.value(basekey+"WindowGeometry").toByteArray());
	}
	restoreState(s.value(basekey+"WindowState").toByteArray());
	
	prog->reset();
	WorldData wd = WorldData::currentWorld();
	if(wd.isValid()) {
		statusBar()->showMessage (tr("World %1 (%2) successfully loaded").arg(wd.worldName()).arg(wd.serverName()),6000);
		setWindowTitle (QString ("Grepotool - (%1) %2").arg(wd.serverName()).arg(wd.worldName())); 
	} else {
		statusBar()->showMessage (tr("No world loaded").arg(wd.worldName()).arg(wd.serverName()),6000);
		setWindowTitle (QString ("Grepotool")); 
	}
}

void MainWin::storeMainState ()
{
	QString srv = WorldData::currentWorld().serverName();
	
	for (int i=0;i<tw_list.size();++i) 
		tw_list[i]->worldAboutToChange();

	QSettings s("Grepotool", GT_VERSION_SHORT);
	QString glob ("Global/MainWindow/") ;
	s.setValue(glob+"WindowGeometry", saveGeometry());
	s.setValue(glob+"WindowState", saveState());
	s.setValue(glob+"WindowMaximized", isMaximized());
	
	if (srv.isEmpty()) return;
	QString wrld = srv+"/MainWindow/";
	s.setValue(wrld+"WindowGeometry", saveGeometry());
	s.setValue(wrld+"WindowState", saveState());
	s.setValue(wrld+"WindowMaximized", isMaximized());
}

void MainWin::playerSelected (int idx)
{
	if(idx<0) return;
	WorldData w = WorldData::currentWorld();
	const Player & pl = w.players()[idx];
	WorldData::setLastSelPlayer(pl.id);	
	WorldData::setTownFilter (pl.id, pl.ally_id);
	towns->worldChanged();
}

void MainWin::allySelected (int idx)
{
	if(idx<0) return;
	WorldData w = WorldData::currentWorld();
	int ai = -1 ;
	ai = w.allys()[idx].id;
	WorldData::setPlayerFilter(ai);
	WorldData::setLastSelAlly(ai);
	WorldData::setTownFilter (-1,ai);
	players->worldChanged();
	towns->worldChanged();
	reports->setAlly (idx);
}

/*! Town in townlist selected
*/
void MainWin::townSelected (int idx)
{
	if (idx < 0) return;
	WorldData w = WorldData::currentWorld();
	WorldData::setLastSelTown(w.towns()[idx].id);
	town_info->selectTown (idx);
	mytowns->setTarget (w.towns()[idx].id);
	news->setTown (idx);
	reports->setTown (idx);
	
}

void MainWin::mytownSelected (int idx)
{
	if (idx<0) return;
	const Plan& pl = mytowns->plan(idx);
	targets->setSource (pl.source_id, pl.movement_boost,pl.atlanta_level, pl.slowest_unit);
}

void MainWin::targetSelected (int idx)
{
	if (idx<0) return;
	const Plan& pl = targets->plan(idx);
	mytowns->setTarget (pl.target_id);
}


void MainWin::selectTown (int i)
{
	if(i<0) return;
	WorldData w = WorldData::currentWorld();
	const Town &to = w.towns()[i];
	WorldData::setLastSelTown(to.id);
	if (to.ghost) {
		WorldData::setTownFilter (-1,-1);
	} else {
		WorldData::setTownFilter (to.player_id, to.ally_id);
		WorldData::setPlayerFilter(to.ally_id);
		WorldData::setLastSelPlayer(to.player_id);	
		players->worldChanged();
		players->selectIndex(to.player_index);
		if (to.ally_id>=0) {
			WorldData::setLastSelAlly(to.ally_id);
			allys->worldChanged();
			allys->selectIndex(to.ally_index);
		}
	}
	towns->worldChanged();
	towns->selectIndex (i);
	town_info->selectTown (i);	
	mytowns->setTarget (to.id);
	reports->setTown (i);

}


void MainWin::selectAlly (int i)
{
	if(i<0) return;
	WorldData w = WorldData::currentWorld();	
	const Ally & al = w.allys()[i];
	WorldData::setTownFilter (-1, al.id);
	WorldData::setPlayerFilter(al.id);
	players->worldChanged();
	WorldData::setLastSelAlly(al.id);
	allys->worldChanged();
	allys->selectIndex(i);
	towns->worldChanged();
	reports->setAlly (i);

}
void MainWin::selectPlayer (int i)
{
	if(i<0) return;
	WorldData w = WorldData::currentWorld();	
	const Player & pl = w.players()[i];
	WorldData::setTownFilter (pl.id, pl.ally_id);
	WorldData::setPlayerFilter(pl.ally_id);
	WorldData::setLastSelPlayer(pl.id);	
	players->worldChanged();
	players->selectIndex(i);
	if (pl.ally_id>=0) {
		WorldData::setLastSelAlly(pl.ally_id);
		allys->worldChanged();
		allys->selectIndex(pl.ally_index);
	}
	towns->worldChanged();
	reports->setPlayer (i);

}

void MainWin::zoomToTown (int i)
{
	if(i<0) return;
	WorldData w = WorldData::currentWorld();
	QPoint p = w.towns()[i].pos;
	int dzl = Cmd::value(MAPVIEW_GOTO_ZOOM).toInt();
	mapview->_view->zoomTo(p,dzl);
}

void MainWin::scrollToTown (int i)
{
	if(i<0) return;
	mapview->_view->scrollTo( WorldData::currentWorld().towns()[i].pos );
}

void MainWin::bookmarkTown (int i)
{
	if(i<0) return;
	WorldData & w= WorldData::currentWorld();
	w.towns()[i].bookmark = true;
	bookmarks->worldChanged ();
}

void MainWin::bookmarkAlly (int i)
{
	if(i<0) return;
	WorldData & w= WorldData::currentWorld();
	w.allys()[i].bookmark = true;
	bookmarks->worldChanged ();
}

void MainWin::bookmarkPlayer (int i)
{
	if(i<0) return;
	WorldData & w= WorldData::currentWorld();
	w.players()[i].bookmark = true;
	bookmarks->worldChanged ();
}

void MainWin::bookmarksChanged ()
{
	bookmarks->worldChanged ();
}

void MainWin::help () 
{
}
/*
#define USERSCRIPT_LINK "http://userscripts.org/scripts/show/183441"
#define PLUGIN_LINK     "https://addons.mozilla.org/de/firefox/addon/grepo-tool-support/" 
#define PROJECT_LINK    "https://sourceforge.net/projects/grepo-tool"
*/

void MainWin::ffPlugin () 
{
	QDesktopServices::openUrl(QUrl(PLUGIN_LINK, QUrl::TolerantMode));
}

void MainWin::ffScript () 
{
	QDesktopServices::openUrl(QUrl(USERSCRIPT_LINK, QUrl::TolerantMode));
}

void MainWin::projectHome ()
{
	QDesktopServices::openUrl(QUrl(PROJECT_LINK, QUrl::TolerantMode));
}

void MainWin::checkUpdate ()
{

}



















void MainWin::addTownToMyTowns (int i)
{
	WorldData w = WorldData::currentWorld ();
	if(i<0) return;
	mytowns->addPlan (Plan (w.towns()[i].id,-1)) ;
}

void MainWin::addTownToTargets (int i)
{
	WorldData w = WorldData::currentWorld ();
	if(i<0) return;
	targets->addPlan (Plan (-1,w.towns()[i].id));
}

void MainWin::addMyTownToPlans ()
{
	QVector <int> sel = mytowns->selectedItems ();
	for (int i=0;i< sel.size (); ++i) {
		plans->addPlan (mytowns->plan (sel[i]));
	}
}

void MainWin::addTargetToPlans ()
{
	QVector <int> sel = targets->selectedItems ();
	for (int i=0;i< sel.size (); ++i) {
		plans->addPlan (targets->plan (sel[i]));
	}
}



void MainWin::registerToolBar (QToolBar * b, const QString& s)
{
	b->setObjectName (s);
	tb_list.push_back (b);
}


void MainWin::registerToolWidget (ToolWidget * w, Qt::DockWidgetArea dw)
{
	tw_list.push_back (w);
	if (dw == Qt::NoDockWidgetArea) return;
	QDockWidget * d = new QDockWidget (w->title(), this);
	d->setObjectName(w->title());
	addDockWidget(dw, d);
	d->setWidget (w);
	dw_list.push_back (d);
	d->setObjectName (w->globalWidgetKey());
}



void MainWin::createMenus ()
{
	QMenuBar * mb = menuBar();

	QMenu * f = mb->addMenu (tr("File"));
	f->addAction(tr("Exit"), this, SLOT(close()));

	QToolBar * mtb = new QToolBar (tr("Mapview toolbar"));	
	Cmd::get(MAPVIEW_GLOBAL_ZOOM)->addToToolBar(mtb);
	mtb->addSeparator();
	xpos = new QSpinBox;
	ypos = new QSpinBox;
	xpos->setRange(0,1000);
	ypos->setRange(0,1000);
	mtb->addWidget(new QLabel("<b>X:</b>"));
	mtb->addWidget (xpos);
	mtb->addWidget(new QLabel("<b>Y:</b>"));
	mtb->addWidget (ypos);
	mtb->addAction (QIcon(":/icons/icons/coord_goto.ico"), tr("Go to coords"), this, SLOT(gotoCoords()));	
	registerToolBar (mtb, "NavToolbar");
	connect(mapview->_view,SIGNAL(zoomChangedSignal(int)), this, SLOT(offsetChanged()));
	srv = mb->addMenu (tr("Server"));

	QMenu * vm = mb->addMenu (tr("View"));


	QMenu * sett = mb->addMenu (tr("Settings"));
	for(int i=0;i< tw_list.size();++i) {
		tw_list[i]->createSettingsSubMenu (sett,true);
	}

	QMenu * mapp = sett->addMenu (tr("Application"));

	QStringList ll = GtApp::instance()->installedLanguages();
	if (ll.size()) {
		QMenu * lng = mapp->addMenu (tr("Language"));
		for (int i=0;i< ll.size(); ++i) {
			lng->addAction (new IdAct (ll[i], GtServer::countryLanguage (ll[i]), GtServer::countryFlagFile(ll[i]),this,SLOT(setLanguage(const QString&))));
		}
	}
	
	sett->addAction (tr("Update servers by Tondas list"), this, SLOT(mergeWithTonda()));

	// Cmd::get(STORE_SETTINGS_PER_WORLD)->addToMenu(mapp);

	QMenu * h = mb->addMenu (tr("Help"));

	h->addAction (tr ("Project hompage"), this , SLOT(projectHome()));
	h->addAction (tr ("Firefox plugin"), this , SLOT(ffPlugin()));
	h->addAction (tr ("Userscript"), this , SLOT(ffScript()));
	h->addSeparator ();
	h->addAction(tr("About"), this, SLOT(about()));
	

	QToolBar * srtb = new QToolBar (tr("Search toolbar"));	
	townsel->addToToolbar (srtb);
	mtb->addSeparator();
	playersel->addToToolbar (srtb);
	registerToolBar (srtb, "SearchToolbar");

	// finally populate view menu and add registered toolbars

	for (int i=0; i < dw_list.size(); ++i) vm->addAction (dw_list[i]->toggleViewAction());
	vm->addAction (sim->hideAct ());
	vm->addSeparator();
	for (int i=0; i < tb_list.size(); ++i) {
		addToolBar(tb_list[i]);
		vm->addAction (tb_list[i]->toggleViewAction());
	}
	
	updateMenu ();
}

void MainWin::updateMenu ()
{
	for(int i=0;i <srv_list.size(); ++i) srv_list[i]->deleteLater();
	srv->clear();
	srv_list.clear();
	QStringList cl = GtServer::countries(); 
	QMenu *mct = srv->addMenu(tr("Countries"));
	for (int i=0;i< cl.size();++i) {
		QMenu *cm = mct->addMenu (QIcon(GtServer::countryFlagFile(cl[i])),
			GtServer::countryName(cl[i]));
		QList <GtServer> sl = GtServer::serversOfCountry(cl[i]);
		for (int j=0;j<sl.size();++j) {
			IdAct * dmy = new IdAct (sl[j].serverName(),
				QString("(%1) %2").arg(sl[j].serverName()).arg(sl[j].worldName ()),
				GtServer::countryFlagFile(cl[i]),this,SLOT(loadWorld(const QString&)));
			cm->addAction (dmy);
			srv_list.push_back (dmy);
		}
	}
	QList <GtServer> lv = GtServer::lastVisited ();
	if (lv.size()) {
		srv->addSeparator();
		for(int i=0;i<10 && i< lv.size();++i) {
			IdAct * dmy = new IdAct (lv[i].serverName(), 
				QString("(%1) %2").arg(lv[i].serverName()).arg(lv[i].worldName ()),
				GtServer::countryFlagFile(lv[i].country()),
				this,SLOT(loadWorld(const QString&)));
			srv->addAction (dmy);
			srv_list.push_back (dmy);
		}
	}
}

void MainWin::searchNewWorlds()
{
	GtServer::scanForNewWorlds (gtprog);
	updateMenu();
}

void MainWin::mergeWithTonda()
{
	QMessageBox msgBox;
	QString tx = tr("Updating Server list<br>Please visit <a href='http://polissearch.marco93.de'>Tondas polis search</a>.");
	msgBox.setText(tx);
	msgBox.show();
	QString msg = GtServer::mergeWithTonda (gtprog);
	msgBox.setText(tx+"<br>"+msg);	
	msgBox.exec();
	updateMenu();
}

void MainWin::editWorldName()
{
}

void MainWin::offsetChanged ()
{	
	QPoint p = mapview->_view->currentOffset();
	int x = p.x() / 128;
	int y = p.y() / 128;
	if(x<0) x = 0;
	if(y<0) y = 0;
	if(x>999) x = 999;
	if(y>999) y = 999;
	xpos->setValue(x);
	ypos->setValue(y);
}


void MainWin::gotoCoords ()
{
	QPoint p(xpos->value()*128,ypos->value()*128);
	mapview->_view->scrollTo (p);
}




void MainWin::moveEvent ( QMoveEvent * ev )
{
	//if(_is_init) storeMainState();
	QMainWindow::moveEvent ( ev );
}
void MainWin::resizeEvent ( QResizeEvent * ev )
{
	// if(_is_init) storeMainState();
	QMainWindow::resizeEvent ( ev );
}



void MainWin::closeEvent(QCloseEvent* ev)
{
	// App::instance->cancelLoading ();

	sim->close ();
	delete sim;

	storeMainState ();

	WorldData::currentWorld().storeSettings (0);

	QMainWindow::closeEvent(ev);
}


MainWin::~MainWin () 
{
}

void MainWin::about ()
{
	Ui::DlgAbout ui;
	QDialog dlg;
	ui.setupUi (&dlg);	
	dlg.setWindowTitle (QString("Grepotool %1").arg (GtApp::instance()->currentVersion()));
	ui._text_2->verticalScrollBar()->setSingleStep(8);	
	dlg.exec ();
}



