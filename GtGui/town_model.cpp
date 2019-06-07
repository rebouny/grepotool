/* towns_model.cpp  - Town data model

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

#include "command.h"
#include "mainwin.h"

#include "town_model.h"
#include "polis_search.h"

#include <GtAllys.h>
#include <GtPlayers.h>
#include <GtTowns.h>

#define CMD_TOWNS_SHOW_GHOSTS  "TownShowGhosts"
#define CMD_TOWNS_SHOW_CONQUERS    "TownShowConquers"
#define CMD_TOWNS_SEL_ALL      "TownSelAll"
#define CMD_TOWNS_ADD_TO_MYTOWNS "TownAddMytowns"
#define CMD_TOWNS_ADD_TO_TARGETS "TownAddTargets"

#define CMD_TOWNS_GUESS_TYPE   "TownGuessType"

#define TOWN_TAB_CURRENT_INDEX  "World/Towns/TabCurrentIndex"

#define CMD_TOWNS_BOOKMARK "TownBookmark"
#define CMD_TOWNS_SEARCH "TownSearch"







bool TownModel::itemCheckable   (int , int col) const
{
	return Town::itemCheckable (col);
}
bool TownModel::itemChecked     (int idx, int col) const
{
	return WorldData::currentWorld().towns()[idx].itemChecked(col);
}
void TownModel::setItemChecked  (int idx, int col, bool b)
{
	WorldData::currentWorld().towns()[idx].setItemChecked(col,b);
}

bool TownModel::itemCustomEdit  (const QVector<int>&idx, int col)
{

	return false;
}








TownView::TownView () : TableView ("NewTowns", tr("Towns")) 
{
	// new Setting (this, TOWN_TAB_CURRENT_INDEX, QPoint (-1,-1));

	QFrame * f= new QFrame ;
	ui.setupUi (f);

	_model = new TownModel (this);

	initTable();
	setCentralWidget (f);
	//Setting::connectToChanged (TOWN_TAB_CURRENT_INDEX,this,SLOT(settingChange()));
	// Setting::connect (MAPVIEW_GLOBAL_OFFSET, this, SLOT(mapChange()));

	addCmd(new CmdAct (ui._ghosts, CMD_TOWNS_SHOW_GHOSTS,    tr ("Show ghost towns"), tr("Show ghost towns"), tr("Show ghost towns wt"),QIcon (":/icons/icons/ghost.ico")));
    //addCmd(new CmdAct (ui._conquers, CMD_TOWNS_SHOW_CONQUERS,    tr ("Show conquered towns"), tr("Show conquered towns"), tr("Show conquered towns wt"),QIcon (":/icons/icons/ghost.ico")));
    addCmd(new CmdAct  (this ,      CMD_TOWNS_SEL_ALL,        tr ("Select all"), tr("Select the entire list"), tr("Select all wt"),QIcon ()));
	addCmd(new CmdAct (this ,      CMD_TOWNS_ADD_TO_MYTOWNS, tr ("Add to My Towns"), tr("Add the current selection to the current My Towns list"), tr("Add to My Towns wt"),QIcon ()));
	addCmd(new CmdAct (this ,      CMD_TOWNS_ADD_TO_TARGETS, tr ("Add to Targets"), tr("Add the current selection to the current Targets list tt"), tr("Add to Targets wt"),QIcon ()));
	addCmd(new CmdAct  (this ,      CMD_TOWNS_GUESS_TYPE, tr ("Guess type"), tr("Guess the tactical type from units in the town."), tr("Guess type wt"),QIcon ()));
	addCmd (new CmdAct (this ,   CMD_TOWNS_BOOKMARK, tr ("Bookmark town"), tr("Bookmark town tt"), tr("Bookmark town wt"),QIcon ()));
	addCmd (new CmdAct (ui._tb2 , CMD_TOWNS_SEARCH, tr ("Polis search"), tr("Polis search"), tr("Polis search wt"),QIcon (":/icons/icons/zoom_lens.ico")));

	_type_ag = new QActionGroup (this);
	for (int i=0;i< TownTypeMax; ++i) {
		QAction * tta = new QAction (WorldData::currentWorld().townTypeText((TownTypeIndex) i, false), this);
		tta->setCheckable (true);
		tta->setData (i);
		_type_ag ->addAction (tta);
	}
	connect (_type_ag, SIGNAL(triggered(QAction*)), this, SLOT(townTypeSelected(QAction*)));

	connect (this, SIGNAL (itemDoubleClickSignal (int)), this, SIGNAL (gotoTownSignal(int)));
}

void TownView::townTypeSelected (QAction* act)
{
	WorldData w =WorldData::currentWorld();

	TownTypeIndex st = (TownTypeIndex) act->data().toInt();
	QVector <int> s = selectedItems ();
	for (int i=0;i<s.size(); ++i) {
		w.towns()[s[i]].type = st;
	}

	model()->triggerRedraw ();
}



void TownView::fillContextMenu (QMenu *m)
{	
	Cmd::get(CMD_TOWNS_SHOW_GHOSTS)->addToMenu (m);
    //Cmd::get(CMD_TOWNS_SHOW_CONQUERS)->addToMenu (m);
    Cmd::get(CMD_TOWNS_SEARCH)->addToMenu (m);
	Cmd::get(CMD_TOWNS_SEL_ALL)->addToMenu (m);
	Cmd::get(CMD_TOWNS_ADD_TO_MYTOWNS)->addToMenu (m);
	Cmd::get(CMD_TOWNS_ADD_TO_TARGETS)->addToMenu (m);
	m->addSeparator();
	QMenu *mm = m->addMenu (tr("Tactical town type"));
	Cmd::get(CMD_TOWNS_GUESS_TYPE)->addToMenu (mm);		
	mm->addSeparator();
	for (int i=0;i < _type_ag->actions().size(); ++i) {
		mm->addAction (_type_ag->actions()[i]);
	}
	m->addSeparator ();
	Cmd::get(CMD_TOWNS_BOOKMARK)->addToMenu (m);
}


void TownView::mapChange ()
{
	model()->triggerRedraw();
}


void TownView::worldChanged  ()
{
	_model->worldChanged();
	int player = -1;
	int ally = -1;

	WorldData::getTownFilter (player,ally);
	restoreHeaderState ();
	sortModel (-1);
	int n = model()->rowCount();

	WorldData w= WorldData::currentWorld();

	if(player<0 && ally<0) {
		ui._info->setText(QString ("<b><img src=':/icons/icons/ghost.ico' width=16 height=16>&nbsp;%1&nbsp;%2</b>").arg(n).arg (tr("Ghost towns")));
	} else if(player>=0) {
		int pi = w.playerIndex (player);
		ui._info->setText(QString ("<b>")+
			tr("%1 towns of %2").arg(n).arg("&nbsp;<img src=':/icons/icons/player.ico' width=16 height=16>&nbsp;") 
			+ w.players()[pi].name + "</b>");
	} else {
		int ai = w.allyIndex (ally);
		ui._info->setText(QString ("<b>")+
			tr("%1 towns of %2").arg(n).arg("&nbsp;<img src=':/icons/icons/ally.ico' width=16 height=16>&nbsp;") 
			+ w.allys()[ai].name + "</b>");
	}

	int lsel = -1;
	WorldData::getLastSelTown (lsel);
	lsel = w.townIndex(lsel);
	if (lsel>=0) selectIndex (lsel);

}

void TownView::handleCmd (const QString& key)
{
	WorldData w = WorldData::currentWorld();

	if (key == CMD_TOWNS_SHOW_GHOSTS) {
		WorldData::setTownFilter (-1,-1);
		worldChanged ();
    } else if (key == CMD_TOWNS_SHOW_CONQUERS) {
        WorldData::setTownFilter (-1,-1);
        worldChanged ();

	} else if (key == CMD_TOWNS_GUESS_TYPE) {

		QVector <int> s = selectedItems ();
		for (int i=0;i<s.size(); ++i) {
			TownTypeIndex st = w.towns()[s[i]].type;
			if(st == TownTypeUndefined) {
				w.towns()[s[i]].type = w.towns()[s[i]].units().tacticalType();
			}
		}
		model()->triggerRedraw ();

	} else if (key == CMD_TOWNS_BOOKMARK) {

		QVector <int> s = selectedItems ();
		for (int i=0;i<s.size(); ++i) {
			w.towns()[s[i]].bookmark = true;
		}
		emit bookmarkChangedSignal ();

	} else if (key == CMD_TOWNS_SEARCH) {
		DlgSearch dlg;

		if (QDialog::Accepted == dlg.exec () ) {
			_model -> resetIndex (dlg.result());
			ui._info->setText(QString ("<b>")+
				tr("Search result: %1 towns").arg(dlg.result().size()) + "</b>");

		}

	} else if (key == CMD_TOWNS_SEL_ALL) {

		ui._tab->selectAll();

	} else if (key == CMD_TOWNS_ADD_TO_MYTOWNS) {
				
		QVector <int> sel = selectedItems ();
		for(int i=0;i<sel.size(); ++i) {
			MainWin::instance->addTownToMyTowns (sel[i]);
		}
				
	} else if (key == CMD_TOWNS_ADD_TO_TARGETS) {
				
		QVector <int> sel = selectedItems ();
		for(int i=0;i<sel.size(); ++i) {
			MainWin::instance->addTownToTargets (sel[i]);
		}
				
	} else {
		ToolWidget::handleCmd(key);
	}

}














