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

#include "bookmark_model.h"

#include "popup.h"
#include <GtAllys.h>
#include <GtPlayers.h>
#include <GtTowns.h>


#define CMD_BM_CHECK "BmCheckAll"
#define CMD_BM_UNCHECK "BmUnheckAll"
#define CMD_BM_COLOR "BmSetColor"
#define CMD_BM_ALLY_COLOR "BmSetAllyColor"
#define CMD_BM_RANDOM_COLOR "BmRandomColor"
#define CMD_BM_DELSEL "BmDelSel"


bool BookmarkModel::itemCheckable   (int idx, int col) const
{
	if (col != Bookmark::BmColor) return false;
	const Bookmark & bm = _bm[idx];
	if(bm.type == Bookmark::BmAlly) {
		return true;
	} else if(bm.type == Bookmark::BmPlayer) {
		return true;
	}
	return false;
}

bool BookmarkModel::itemChecked     (int idx, int col) const
{
	if (col != Bookmark::BmColor) return false;
	const Bookmark & bm = _bm[idx];
	if(bm.type == Bookmark::BmAlly) {
		return bm.ally->itemChecked(Ally::AllyColor);
	} else if(bm.type == Bookmark::BmPlayer) {
		return bm.player->itemChecked(Player::PlayerColor);
	}
	return false;
}
void BookmarkModel::setItemChecked  (int idx, int col, bool b)
{
	if (col != Bookmark::BmColor) return;
	Bookmark & bm = _bm[idx];
	if(bm.type == Bookmark::BmAlly) {
		bm.ally->setItemChecked(Ally::AllyColor,b);
	} else if(bm.type == Bookmark::BmPlayer) {
		bm.player->setItemChecked(Player::PlayerColor,b);
	}
}
bool BookmarkModel::itemCustomEdit  (const QVector<int>&idx, int col)
{

	if (col != Bookmark::BmColor) return false;
	if( idx.size() > 1) return false;
	if( idx.size() == 0) return false;
		
	Bookmark & bm = _bm[idx[0]];
	if(bm.type == Bookmark::BmAlly) {
		QString tx = tr("Select color of %1").arg(bm.labelText(Bookmark::BmName, 16));
		bm.ally->color = ColorPopup::selectColor (QCursor::pos(), bm.ally->color, tx);
		return true;
	} else if(bm.type == Bookmark::BmPlayer) {
		QString tx = tr("Select color of %1").arg(bm.labelText(Bookmark::BmName, 16));
		bm.player->color = ColorPopup::selectColor (QCursor::pos(), bm.player->color, tx);
		return true;
	} 
	return false;
}

void BookmarkModel::worldChanged  ()	
{
	WorldData w = WorldData::currentWorld ();
	beginResetModel ();
	_bm.clear();
	for (int i=0;i<w.allys().size();++i) if(w.allys()[i].bookmark) _bm.push_back (Bookmark(&w.allys()[i]));
	for (int i=0;i<w.players().size();++i) if(w.players()[i].bookmark) _bm.push_back (Bookmark(&w.players()[i]));
	for (int i=0;i<w.towns().size();++i) if(w.towns()[i].bookmark) _bm.push_back (Bookmark(&w.towns()[i]));
	_idx = QVector <SortIndex> (_bm.size());
	for (int i=0;i<_bm.size();++i) {
		_idx[i]._index = i;
		_idx[i]._sel = false;
	}
	endResetModel ();
};


void BookmarkModel::deleteItems (const QVector <int> &s)
{
	for (int i=0;i<s.size(); ++i) {
		_bm[s[i]].unBookmark();
	}
}

int BookmarkModel::itemIndex (int i) const
{
	WorldData w = WorldData::currentWorld ();

	Bookmark::BmType t = _bm[i].type;	
	if (t == Bookmark::BmAlly) return w.allyIndex (_bm[i].ally->id);
	else if (t == Bookmark::BmPlayer) return w.playerIndex(_bm[i].player->id);
	else if (t == Bookmark::BmTown) return w.townIndex(_bm[i].town->id);
	return -1;
}



BookmarkView::BookmarkView () : TableView ("Bookmarks", tr("Bookmarks")) 
{
	QFrame * f= new QFrame ;
	ui.setupUi (f);
	ui._ghosts->hide();
	ui._info->hide();
	ui._tb2->hide ();
	_model = new BookmarkModel (this);

	initTable();
	setCentralWidget (f);



	addCmd (new CmdAct (this , CMD_BM_CHECK, tr ("Check"), tr("Check tt"), tr("Check wt"),QIcon ()));
	addCmd (new CmdAct (this , CMD_BM_UNCHECK, tr ("Uncheck"), tr("Uncheck tt"), tr("Uncheck wt"),QIcon ()));
	addCmd (new CmdAct (this , CMD_BM_COLOR, tr ("Set color"), tr("Set color tt"), tr("Set color wt"),QIcon ()));
	addCmd (new CmdAct (this , CMD_BM_RANDOM_COLOR, tr ("Set random colors"), tr("Set random colors tt"), tr("Set random colors wt"),QIcon ()));
	addCmd (new CmdAct (this , CMD_BM_ALLY_COLOR, tr ("Set color to ally color"), tr("Set color to ally color tt"), tr("Set color to ally color wt"),QIcon ()));
	addCmd (new CmdAct (this , CMD_BM_DELSEL, tr ("Delete selected"), tr("Delete selected tt"), tr("Delete selected wt"),QIcon ()));


	connect (this, SIGNAL(itemDoubleClickSignal (int)), this, SLOT(itemDblClicked (int)));
	
}



void BookmarkView::fillContextMenu (QMenu *m)
{	
	Cmd::get(CMD_BM_DELSEL)->addToMenu(m);
	// Cmd::get(CMD_BM_CHECK)->addToMenu(m);
	//Cmd::get(CMD_BM_UNCHECK)->addToMenu(m);
	//Cmd::get(CMD_BM_COLOR)->addToMenu(m);
	//Cmd::get(CMD_BM_ALLY_COLOR)->addToMenu(m);
	//Cmd::get(CMD_BM_RANDOM_COLOR)->addToMenu(m);
}


void BookmarkView::worldChanged ()
{
	_model->worldChanged();
	restoreHeaderState ();
	sortModel (-1);
}

void BookmarkView::handleCmd (const QString& key)
{
	if (key == CMD_BM_CHECK) {

	} else if (key == CMD_BM_UNCHECK) {

	} else if (key == CMD_BM_COLOR) {

	} else if (key == CMD_BM_ALLY_COLOR) {

	} else if (key == CMD_BM_RANDOM_COLOR) {

	} else if (key == CMD_BM_DELSEL) {
		delSel ();
	} else {
		ToolWidget::handleCmd(key);
	}
}

void BookmarkView::delSel ()
{
	_model->deleteItems(selectedItems());
	worldChanged();
}

void BookmarkView::itemDblClicked (int i)
{
	Bookmark::BmType t = _model->itemType (i);
	int idx =  _model->itemIndex (i);
	if (t == Bookmark::BmAlly) emit gotoAllySignal (idx);
	else if (t == Bookmark::BmPlayer) emit gotoPlayerSignal (idx);
	else if (t == Bookmark::BmTown) emit gotoTownSignal (idx);
}



void BookmarkView::modelDataChanged ()
{
	emit updateInfMapSignal ();
}

















