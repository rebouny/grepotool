/* player_model.cpp  - Players data model

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
#include "player_model.h"
#include "popup.h"
#include <GtAllys.h>
#include <GtPlayers.h>
#include <GtTowns.h>



#define CMD_SHOW_ALLYLESS "PlayersShowAllyless"
#define CMD_SHOW_ALL_PLAYERS "PlayersShowAllPlayers"
#define CMD_PLAYERS_CHECK_ALL "PlayerCheckAll"
#define CMD_PLAYERS_UNCHECK_ALL "PlayerUnheckAll"
#define CMD_PLAYERS_SET_COLOR "PlayerSetColor"
#define CMD_PLAYERS_RANDOM_COLOR "PlayerRandomColor"
#define CMD_PLAYERS_ALLY_COLOR "PlayerAllyColor"

#define CMD_PLAYERS_BOOKMARK "PlayerBookmark"







bool PlayerModel::itemCheckable   (int, int col) const
{
	return Player::itemCheckable (col);
}
bool PlayerModel::itemChecked     (int idx, int col) const
{
	return WorldData::currentWorld().players()[idx].itemChecked(col);
}
void PlayerModel::setItemChecked  (int idx, int col, bool b)
{
	WorldData::currentWorld().players()[idx].setItemChecked(col,b);
}
bool PlayerModel::itemCustomEdit  (const QVector<int>&idx, int col)
{

	if (col != Player::PlayerColor) return false;
	if( idx.size() > 1) return false;
	if( idx.size() == 0) return false;
	
	Player & pl = WorldData::currentWorld().players()[idx[0]];
	QString tx = tr("Select color of %1").arg( pl.labelText(Player::PlayerName,16));
	pl.color = ColorPopup::selectColor (QCursor::pos(), pl.color, tx);
	return true;
}
















PlayerView::PlayerView () : TableView ("Players", tr("Players")) 
{

	QFrame * f= new QFrame ;
	ui.setupUi (f);

	ui._tab->setSelectionMode (QAbstractItemView::SingleSelection);

	_model = new PlayerModel (this);

	initTable();
	setCentralWidget (f);

	addCmd (new CmdAct (ui._tb2, CMD_SHOW_ALL_PLAYERS, tr ("Show all players"), tr ("Show all players"), tr ("Show all players wt"), QIcon (":/icons/icons/player_points.ico")));
	addCmd (new CmdAct (ui._ghosts, CMD_SHOW_ALLYLESS, tr ("Show players without alliance"), tr ("Show players without alliance tt"),	tr ("Show players without alliance wt"),QIcon (":/icons/icons/ally_no.ico")));
	addCmd (new CmdAct  (this , CMD_PLAYERS_CHECK_ALL, tr ("Check all"), tr("Check all tt"), tr("Check all wt"),QIcon ()));
	addCmd (new CmdAct  (this , CMD_PLAYERS_UNCHECK_ALL, tr ("Uncheck all"), tr("Uncheck all tt"), tr("Uncheck all wt"),QIcon ()));
	addCmd (new CmdAct  (this , CMD_PLAYERS_SET_COLOR, tr ("Set color of all"), tr("Set color fo all tt"), tr("Set color fo all wt"),QIcon ()));
	addCmd (new CmdAct  (this , CMD_PLAYERS_RANDOM_COLOR, tr ("Set random colors"), tr("Set random colors tt"), tr("Set random colors wt"),QIcon ()));
	addCmd (new CmdAct  (this , CMD_PLAYERS_ALLY_COLOR, tr ("Reset to ally color"), tr("Reset to ally color tt"), tr("Reset to ally color wt"),QIcon ()));
	addCmd (new CmdAct (this , CMD_PLAYERS_BOOKMARK, tr ("Bookmark player"), tr("Bookmark player tt"), tr("Bookmark player wt"),QIcon ()));

	connect (this, SIGNAL (itemDataChangedSignal (int)), this, SIGNAL (updateMapSignal()));
	connect (_model, SIGNAL (dataChanged (const QModelIndex &,const QModelIndex &)), this, SIGNAL (updateMapSignal()));

}


void PlayerView::fillContextMenu (QMenu *m)
{	
	Cmd::get(CMD_SHOW_ALLYLESS)->addToMenu (m);
	Cmd::get(CMD_SHOW_ALL_PLAYERS)->addToMenu (m);
	m->addSeparator ();
	Cmd::get(CMD_PLAYERS_CHECK_ALL)->addToMenu (m);
	Cmd::get(CMD_PLAYERS_UNCHECK_ALL)->addToMenu (m);
	Cmd::get(CMD_PLAYERS_SET_COLOR)->addToMenu (m);
	Cmd::get(CMD_PLAYERS_RANDOM_COLOR)->addToMenu (m);
	Cmd::get(CMD_PLAYERS_ALLY_COLOR)->addToMenu (m);

	m->addSeparator ();
	Cmd::get(CMD_PLAYERS_BOOKMARK)->addToMenu (m);
}


void PlayerView::worldChanged ()
{
	_model->worldChanged();
	int a = -1;
	WorldData w= WorldData::currentWorld();
	WorldData::getPlayerFilter(a);
	int ai = w.allyIndex (a);
	if (ai < 0) {
		ui._info->setText(tr("<b>%1 players without alliance</b>").arg(_model->rowCount()));
		
	} else {
		QString an = w.allys()[ai].name;
		ui._info->setText(QString ("<b>") +
			tr("%1 members of").arg(_model->rowCount()) +
			"&nbsp;<img src=':/icons/icons/ally.ico' width=16 height=16>&nbsp;" 
			+ an + "</b>");
	}

	restoreHeaderState ();
	sortModel (-1);


	int lsel = -1;
	WorldData::getLastSelPlayer (lsel);
	lsel = w.playerIndex(lsel);
	if (lsel>=0) selectIndex (lsel);


}


void PlayerView::handleCmd (const QString& key)
{
	WorldData w = WorldData::currentWorld ();
	if (key == CMD_SHOW_ALLYLESS) {
		WorldData::setPlayerFilter(-1);
		worldChanged();

	} else if (key == CMD_SHOW_ALL_PLAYERS) {
		
		WorldData w = WorldData::currentWorld ();
		QVector <int> apl;
		for (int i=0; i < w.players().size(); ++i) {
			const Player & pl = w.players()[i];
			if (pl.alive) apl.push_back (i);
		}
		_model->resetIndex (apl);
		restoreHeaderState ();
		sortModel (-1);
		int lsel = -1;
		WorldData::getLastSelPlayer (lsel);
		lsel = w.playerIndex(lsel);
		if (lsel>=0) selectIndex (lsel);
		
		ui._info->setText(QString ("<b>") +
			tr("%1 players of %2").arg(apl.size()).arg (w.worldName()) + "</b>");


	} else if (key == CMD_PLAYERS_CHECK_ALL) {
		QVector <int> ai = model()->getIndex ();
		for (int i=0;i< ai.size();++i) {
			w.players()[ai[i]].show = true;
		}
		emit updateMapSignal();
	} else if (key == CMD_PLAYERS_UNCHECK_ALL) {
		QVector <int> ai = model()->getIndex ();
		for (int i=0;i< ai.size();++i) {
			w.players()[ai[i]].show = false;
		}
		emit updateMapSignal();
	} else if (key == CMD_PLAYERS_SET_COLOR) {
		QColor nc = ColorPopup::selectColor (QCursor::pos(), QColor(0,0,0,0), tr("Select a new color for all players"));
		if (nc == QColor(0,0,0,0)) return;
		QVector <int> ai = model()->getIndex ();
		for (int i=0;i< ai.size();++i) {
			w.players()[ai[i]].color = nc;
		}
		emit updateMapSignal();

	} else if (key == CMD_PLAYERS_RANDOM_COLOR) {

		QVector <int> ai = model()->getIndex ();
		for (int i=0;i< ai.size();++i) {
			w.players()[ai[i]].color = randomColor ();
		}
		emit updateMapSignal();
	} else if (key == CMD_PLAYERS_BOOKMARK) {

		QVector <int> s = selectedItems ();
		for (int i=0;i<s.size(); ++i) {
			w.players()[s[i]].bookmark = true;
		}
		emit bookmarkChangedSignal ();


	} else if (key == CMD_PLAYERS_ALLY_COLOR) {
		QVector <int> ai = model()->getIndex ();
		for (int i=0;i< ai.size();++i) {
			int all_idx = w.players()[ai[i]].ally_index;
			if(all_idx >= 0) 
				w.players()[ai[i]].color = w.allys()[all_idx].color;
		}
		emit updateMapSignal();

	} else {
		ToolWidget::handleCmd(key);
	}

}

void PlayerView::modelDataChanged ()
{
	emit updateMapSignal ();
}















