#ifndef ___TOWNS_MODEL_H
#define ___TOWNS_MODEL_H
/* towns_model.h  - Town data model

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
#include "table_model.h"
#include "ui_table.h"

#include <GtTowns.h>



class TownModel : public TableModel {
	Q_OBJECT
public:
	TownModel (QObject * p= 0):TableModel (p){};
	int columnCount(const QModelIndex &) const {return Town::numColumns();};
	int               defaultSortColumn () const {return Town::defaultSortColumn();};
	int               maxIndex          () const {return WorldData::currentWorld ().towns().size();};
	QByteArray        headerState     () const {return WorldData::setting("Towntable/header").toByteArray();};
	void              saveHeaderState (const QByteArray& b) {WorldData::setSetting("Towntable/header",b);};
	bool              canHideColumn     (int c) const {return Town::canHideColumn(c);};
	void              worldChanged  ()	{
		resetIndex (WorldData::filteredTowns());
	};
	int              itemSortIndex (int idx, int col) const {
		return WorldData::currentWorld ().towns()[idx].itemSortIndex (col);
	};
	QStringList       itemTexts      ( int idx, const QVector <int> &cols ) const {
		return WorldData::currentWorld ().towns()[idx].texts (cols);
	};  
	QStringList       itemBBCodes    ( int idx, const QVector <int> &cols ) const {
		return WorldData::currentWorld ().towns()[idx].bbCodes (cols);
	};  

	QVariant data ( const QModelIndex &index, int role = Qt::DisplayRole) const {
		if ( !index.isValid() ) return QVariant();
		int idx = indexOfRow (index.row());
		WorldData w = WorldData::currentWorld ();
		if (idx < 0 || idx >= w.towns().size()) return QVariant();
		return w.towns()[idx].itemData(index.column(), role);
	};
	QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const {
		if (orientation == Qt::Horizontal) {
			return Town::headerData (section, role);
		} else {
			if (role == Qt::DisplayRole) 
				return QString::number (section+1);
		}
		return QVariant ();
	};

	bool              itemCheckable   (int idx, int col) const;
	bool              itemChecked     (int idx, int col) const;
	void              setItemChecked  (int idx, int col, bool);
	bool              itemCustomEdit  (const QVector<int>&idx, int col);
};




class TownView : public TableView {

	Q_OBJECT;

public:
	TownView ();
	QTableView *   table () {return ui._tab;}
	TableModel *   model () {return _model;};
	void fillContextMenu (QMenu *); 
	void handleCmd (const QString& key);
	void worldChanged ();

public slots:
	void townTypeSelected (QAction* act);
	void mapChange ();

private:
	TownModel *_model;
	QActionGroup *_type_ag;
	Ui::Table ui;
};




















#endif