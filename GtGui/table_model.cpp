/* table_model.cpp  - Table data model

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
#include <QtAlgorithms>
#include "table_model.h"

TableModel::TableModel(QObject *parent) :  QAbstractTableModel(parent), _icon_size (20,20)
{
}

TableModel::~TableModel ()
{
}

void  TableModel::resetIndex (const QVector <int> & nidx)
{
	beginResetModel ();
	int si = nidx.size();
	_idx.resize (si);
	for(int i =0; i< si;++i) {
		_idx[i]._index = nidx[i];
		_idx[i]._sel = false;
	}
	endResetModel ();
}

QSize TableModel::iconSize () const
{
	return _icon_size;
}

void  TableModel::setIconSize (const QSize & s) 
{
	_icon_size = s; 
	triggerRedraw ();
}

bool TableModel::canHideColumn (int) const
{
	return true;
}

bool  TableModel::itemCheckable   (int , int) const 
{
	return false;
}

bool TableModel::itemChecked  (int , int) const
{
	return false;
}

void TableModel::setItemChecked  (int,  int , bool)
{
}


int TableModel::rowOfIndex (int idx) const
{
	for(int i = 0 ; i < _idx.size(); ++i) 

		if (_idx[i]._index == idx)
		
			return i;

	return -1;
}

int TableModel::indexOfRow (int row) const
{
	if ( row < 0 || row >= _idx.size() ) 
	
		return -1;

	return _idx[row]._index;
}


QModelIndexList TableModel::rowsOfItems (const QVector<int>&idx)  const
{
	QModelIndexList r;
	for (int i=0;i< idx.size(); ++i) {
		int ro = rowOfIndex (idx[i]);
		if(ro < 0) continue;
		r.push_back (index (ro,0));
	}
	return r;
}



void  TableModel::storeSelection (const QModelIndexList & idx)
{
	for (int i=0;i<_idx.size();++i) {
		_idx[i]._sel = false;
	}

	for (int i=0;i<idx.size();++i) 
		_idx[idx[i].row()]._sel = true;
}

QModelIndexList TableModel::restoreSelection () const
{
	QModelIndexList r;
	for (int i=0;i< _idx.size(); ++i) 
		if (_idx[i]._sel) 
			r.push_back(index(i,0));
	return r;
}

void TableModel::setItemCheckState (const QModelIndex & index, Qt::CheckState state)
{
	if ( !index.isValid() ) 
		return;

	int idx = indexOfRow (index.row());
	setItemChecked (idx, index.column(), state == Qt::Checked);

	emit dataChanged(index,index);

}



bool TableModel::customEditOfItems (const QModelIndexList & idx)
{
	if(!idx.size()) return false;
	QVector<int> ix;
	for (int i=0;i< idx.size();++i) 
		ix.push_back (indexOfRow(idx[i].row()));
	if (!itemCustomEdit(ix,idx[0].column())) return false;

	emit dataChanged (idx[0],idx[idx.size()-1]);

	return true;
}

bool TableModel::itemCustomEdit  (const QVector<int>&, int )
{
	return false;
}

void TableModel::fillContextMenu (QMenu* , const QVector<int>&) 
{
};

void TableModel::fillContextMenu (QMenu* m, const QModelIndexList & idx)
{
	QVector<int> ix;
	for (int i=0;i< idx.size();++i) 
		ix.push_back (indexOfRow(idx[i].row()));
	fillContextMenu (m, ix);
}


static inline bool lessThan (const SortIndex& a, const SortIndex& b) {return a._sort_index< b._sort_index;};
static inline bool greaterThan (const SortIndex& a, const SortIndex& b) {return a._sort_index> b._sort_index;};

void TableModel::sort ( int column, Qt::SortOrder order) 
{
	emit layoutAboutToBeChanged ();
	for (int i=0;i< _idx.size();++i) 
		_idx[i]._sort_index = itemSortIndex (_idx[i]._index, column);
	if (order == Qt::AscendingOrder) {
		qSort (_idx.begin(),_idx.end(), lessThan) ;
	} else {
		qSort (_idx.begin(),_idx.end(), greaterThan) ;
	}
	emit layoutChanged ();
}