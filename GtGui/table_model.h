#ifndef ___TABLE_MODEL_H
#define ___TABLE_MODEL_H
/* table_model.h  - Table model view architecture

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

#include <toolwidget.h>
#include <QTableView>
#include <QAbstractTableModel>
#include <QAbstractItemDelegate>
#include <QFontMetrics>
#include <QModelIndex>
#include <QSize>
#include <QDialog>
#include <QActionGroup>

#include <GtWorlddata.h>
#include <GtAllys.h>
#include <GtPlayers.h>

#include "ui_table_export.h"

class QMenu;


#ifdef EXPORT 
# undef EXPORT
#endif
#ifdef BUILDING_GTGUI
# define EXPORT DLL_EXPORT
#else
# define EXPORT DLL_IMPORT
#endif

class EXPORT SortIndex {
public:
	SortIndex (){};
	SortIndex (const SortIndex& o):_index(o._index),_sort_index(o._sort_index),_sel(o._sel) {};
	inline SortIndex& operator = (const SortIndex& o) {_index =o._index; _sort_index=o._sort_index; _sel=o._sel; return *this;};
	inline bool operator < (const SortIndex& o) const {return _sort_index < o._sort_index;};
	int  _index;
	int  _sort_index;
	bool _sel;
};

class EXPORT TableModel : public QAbstractTableModel {
	Q_OBJECT
public:
	virtual ~TableModel ();

	int          rowCount ( const QModelIndex & ) const {return _idx.size();};
	int          rowCount ( ) const {return _idx.size();};
	void         resetIndex        (const QVector <int> & nidx);
	void         setItemCheckState (const QModelIndex & index, Qt::CheckState state);
	bool         customEditOfItems (const QModelIndexList & idx);
	void         fillContextMenu   (QMenu* m, const QModelIndexList & idx);

	void            storeSelection (const QModelIndexList & idx);
	QModelIndexList restoreSelection ()  const;

	QSize        iconSize    () const;
	void         setIconSize (const QSize & s);

	int          rowOfIndex  (int idx) const;
	int          indexOfRow  (int row) const;
	QModelIndexList rowsOfItems (const QVector<int>&idx)  const;

	QVector <int> getIndex() const {
		QVector <int> r;
		for(int i=0;i<_idx.size();++i) 
			r.push_back (_idx[i]._index);		
		return r;
	};

	virtual QStringList       itemTexts      ( int idx, const QVector <int> &cols ) const = 0;  
	virtual QStringList       itemBBCodes    ( int idx, const QVector <int> &cols ) const {return itemTexts(idx, cols);};  

	virtual int               defaultSortColumn () const = 0;
	virtual int               maxIndex          () const = 0;
	virtual QByteArray        headerState     () const = 0;
	virtual void              saveHeaderState (const QByteArray& b) = 0;
	virtual bool              canHideColumn     (int) const =0;
	virtual void              worldChanged  ()	= 0;
	virtual bool              itemCheckable   (int idx, int col) const;
	virtual bool              itemChecked     (int idx, int col) const;
	virtual void              setItemChecked  (int idx, int col, bool);
	
	virtual bool              itemCustomEdit  (const QVector<int>&idx, int col);
	virtual void              fillContextMenu (QMenu* m,const QVector<int>&idx);

	virtual int               itemSortIndex (int idx, int col) const = 0;
	virtual void              sort ( int column, Qt::SortOrder order = Qt::AscendingOrder );

	public slots:
		void         triggerRedraw     () {emit layoutChanged ();};
		
protected:
	TableModel(QObject *parent = 0);

protected:
	QVector <SortIndex> _idx;
	QSize         _icon_size;
};

class ItemDelegate : public QAbstractItemDelegate {
	Q_OBJECT
public:
	ItemDelegate(QObject *parent = 0);
	void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	QSize sizeHint(const QStyleOptionViewItem &option,
		const QModelIndex &index ) const;
	bool editorEvent ( QEvent * event, QAbstractItemModel * model, 
		const QStyleOptionViewItem & option, const QModelIndex & index );

	void doLayout(const QStyleOptionViewItem &option,
		QRect *checkRect, QRect *pixmapRect, QRect *textRect,
		bool hint) const;

};

class TableView : public ToolWidget {
	Q_OBJECT;
public:
	virtual ~TableView ();
	void     initTable ();

	QVector <int> selectedItems () ;

	virtual QTableView *   table () = 0;
	virtual TableModel *   model () = 0;

	virtual void fillContextMenu (QMenu *) {}; 

	virtual void delSel () {};
	virtual bool canDelSel () const {return false;};

signals:
	void contextMenuSignal     (QWidget* w, const QPoint &globalPos);
	void itemContextMenuSignal (QWidget* w, const QPoint &globalPos, int item_index);
	void itemClickSignal       (QWidget* w, int item_index);
	void itemDoubleClickSignal (QWidget* w, int item_index);
	void itemDataChangedSignal (QWidget* w, int item_index);
	void selectionChangedSignal (QWidget* w);

	void itemClickSignal       (int item_index);
	void itemDoubleClickSignal (int item_index);
	void itemDataChangedSignal (int item_index);
	void selectionChangedSignal ();

public slots:
		void contextMenuRequested(const QPoint&);
		void headerClicked(int);
		void sectionMoved(int,int,int);
		void sectionResized();
		void colVisibilityChanged(QAction* act);
		void updateTable ();
		void exportTable ();
		void selectIndex (const QVector <int> &);
		void selectIndex (int);

		void saveHeaderState();
		void restoreHeaderState();

		void itemActivated ( const QModelIndex & index );
		void itemClicked ( const QModelIndex & index );
		void itemDoubleClicked ( const QModelIndex & index );
		void itemSelectionChanged ( const QItemSelection & selected, const QItemSelection & deselected );

protected:
	TableView (const QString& id, const QString& title);
	bool event (QEvent *ev);
	void sortModel (int column=-1);
	QActionGroup *vis_ag;
};


class EXPORT DlgTableExport : public QDialog {
	Q_OBJECT;
public:
	DlgTableExport(TableView * par);

	QString result () const {return res;};

public slots:

	void up ();
	void down ();
	void add ();
	void remove ();

	void checkButtons ();
	void updatePreview ();
	void updateLists ();

protected:
	QStringList cols;
	QVector <int> selcols;

	QString res;
	Ui::TableExport ui;
	TableView * _par;
};


#endif