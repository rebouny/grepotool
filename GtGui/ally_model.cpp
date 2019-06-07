/* ally_model.cpp  - Alliances data model

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

#include "ally_model.h"

#include "popup.h"
#include <GtAllys.h>
#include <GtPlayers.h>
#include <GtTowns.h>


#define CMD_ALLYS_CHECK_ALL "AllysCheckAll"
#define CMD_ALLYS_UNCHECK_ALL "AllysUnheckAll"
#define CMD_ALLYS_SET_COLOR "AllysSetColor"
#define CMD_ALLYS_RANDOM_COLOR "AllysRandomColor"
#define CMD_ALLYS_BOOKMARK "AllysBookmark"


bool AllyModel::itemCheckable   (int, int col) const
{
	return Ally::itemCheckable (col);
}
bool AllyModel::itemChecked     (int idx, int col) const
{
	return WorldData::currentWorld().allys()[idx].itemChecked(col);
}
void AllyModel::setItemChecked  (int idx, int col, bool b)
{
	WorldData::currentWorld().allys()[idx].setItemChecked(col,b);
}
bool AllyModel::itemCustomEdit  (const QVector<int>&idx, int col)
{

	if (col != Ally::AllyColor) return false;
	if( idx.size() > 1) return false;
	if( idx.size() == 0) return false;
	
	Ally & al = WorldData::currentWorld().allys()[idx[0]];
	QString tx = tr("Select color of %1").arg( al.labelText(Ally::AllyName,16));
	al.color = ColorPopup::selectColor (QCursor::pos(), al.color, tx);
	return true;
}

void AllyModel::worldChanged  ()	
{
	resetIndex (WorldData::filteredAllys());
};


AllyView::AllyView () : TableView ("Alliances", tr("Alliances")) 
{
	QFrame * f= new QFrame ;
	ui.setupUi (f);
	ui._ghosts->hide();
	ui._tb2->hide();

	ui._tab->setSelectionMode (QAbstractItemView::SingleSelection);

	_model = new AllyModel (this);

	initTable();
	setCentralWidget (f);

	addCmd (new CmdAct (this , CMD_ALLYS_CHECK_ALL, tr ("Check all"), tr("Check all tt"), tr("Check all wt"),QIcon ()));
	addCmd (new CmdAct (this , CMD_ALLYS_UNCHECK_ALL, tr ("Uncheck all"), tr("Uncheck all tt"), tr("Uncheck all wt"),QIcon ()));
	addCmd (new CmdAct (this , CMD_ALLYS_SET_COLOR, tr ("Set color of all"), tr("Set color fo all tt"), tr("Set color fo all wt"),QIcon ()));
	addCmd (new CmdAct (this , CMD_ALLYS_RANDOM_COLOR, tr ("Set random colors"), tr("Set random colors tt"), tr("Set random colors wt"),QIcon ()));
	addCmd (new CmdAct (this , CMD_ALLYS_BOOKMARK, tr ("Bookmark ally"), tr("Bookmark ally tt"), tr("Bookmark wt"),QIcon ()));
}



void AllyView::fillContextMenu (QMenu *m)
{	
	Cmd::get(CMD_ALLYS_CHECK_ALL)->addToMenu(m);
	Cmd::get(CMD_ALLYS_UNCHECK_ALL)->addToMenu(m);
	Cmd::get(CMD_ALLYS_SET_COLOR)->addToMenu(m);
	Cmd::get(CMD_ALLYS_RANDOM_COLOR)->addToMenu(m);
	m->addSeparator ();
	Cmd::get(CMD_ALLYS_BOOKMARK)->addToMenu (m);

}


void AllyView::worldChanged ()
{
	_model->worldChanged();

	restoreHeaderState ();
	sortModel (-1);

	int lsel = -1;
	WorldData::getLastSelAlly (lsel);
	WorldData w = WorldData::currentWorld();
	lsel = w.allyIndex(lsel);

	if (lsel>=0) selectIndex (lsel);

	ui._info->setText (QString("<b>%1</b>").arg(tr("%1 allys of %2").arg (_model->rowCount()).arg(WorldData::currentWorld().worldName())));


}

void AllyView::handleCmd (const QString& key)
{
	WorldData w = WorldData::currentWorld();
	if (key ==  CMD_ALLYS_SET_COLOR) {
		QColor nc = ColorPopup::selectColor (QCursor::pos(), QColor(0,0,0,0), tr("Select a new color for all allys"));
		if (nc == QColor(0,0,0,0)) return;
		QVector <int> ai = model()->getIndex ();
		for (int i=0;i< ai.size();++i) {
			w.allys()[ai[i]].color = nc;
		}
		// itemDataChanged();
		emit updateInfMapSignal();
	} else if(key ==  CMD_ALLYS_RANDOM_COLOR) {
		QVector <int> ai = model()->getIndex ();
		for (int i=0;i< ai.size();++i) {
			w.allys()[ai[i]].color = randomColor();
		}
		// itemDataChanged();
		emit updateInfMapSignal();
	} else if(key ==  CMD_ALLYS_CHECK_ALL) {
		QVector <int> ai = model()->getIndex ();
		for (int i=0;i< ai.size();++i) {
			w.allys()[ai[i]].show= true;
		}
		// itemDataChanged();
		emit updateInfMapSignal();

	} else if(key ==  CMD_ALLYS_UNCHECK_ALL) {
		QVector <int> ai = model()->getIndex ();
		for (int i=0;i< w.allys().size();++i) {
			w.allys()[ai[i]].show= false;
		}
		// itemDataChanged();
		emit updateInfMapSignal();

	} else if(key ==  CMD_ALLYS_BOOKMARK) {
		QVector <int> s = selectedItems ();
		for (int i=0;i<s.size(); ++i) {
			w.allys()[s[i]].bookmark = true;
		}
		emit bookmarkChangedSignal ();

	} else {
		ToolWidget::handleCmd(key);
	}
}

void AllyView::modelDataChanged ()
{
	emit updateInfMapSignal ();
}


















