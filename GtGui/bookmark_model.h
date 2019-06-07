#ifndef ___BOOKMARK_MODEL_H
#define ___BOOKMARK_MODEL_H

#include "table_model.h"
#include "ui_table.h"

#include <GtBookmarks.h>

class BookmarkModel : public TableModel {
	Q_OBJECT
public:
	BookmarkModel (QObject * p= 0):TableModel (p){};
	int columnCount(const QModelIndex &) const {return Bookmark::numColumns();};
	int               defaultSortColumn () const {return Bookmark::defaultSortColumn();};
	int               maxIndex          () const {return _bm.size();};
	QByteArray        headerState     () const {return WorldData::setting("Bookmarktable/header").toByteArray();};
	void              saveHeaderState (const QByteArray& b) {WorldData::setSetting("Bookmarktable/header",b);};
	bool              canHideColumn     (int c) const {return Bookmark::canHideColumn(c);};
	void              worldChanged  ();

	Bookmark::BmType  itemType (int idx) const {return _bm[idx].type;};
	int itemIndex (int idx) const;
	int               itemSortIndex (int , int) const {	return 0; };
	QStringList       itemTexts      ( int idx, const QVector <int> &cols ) const {
		return _bm[idx].texts (cols);
	};  
	QStringList       itemBBCodes    ( int idx, const QVector <int> &cols ) const {
		return _bm[idx].bbCodes(cols);
	};  

	void sort ( int column, Qt::SortOrder order = Qt::AscendingOrder ) {
		emit layoutAboutToBeChanged ();
		WorldData w = WorldData::currentWorld ();
		for ( int i = 0 ; i <  ( _idx.size() - 1 ); ++i ) {
			for ( int j = i+1; j < _idx.size(); ++j ) {
				int cmp = _bm[_idx[i]._index].compare(_bm[_idx[j]._index], column);
				if(_bm[_idx[i]._index].type != _bm[_idx[j]._index].type && order == Qt::AscendingOrder) cmp=-cmp;
				if (((order == Qt::AscendingOrder) && cmp > 0 ) ||
					((order == Qt::DescendingOrder) && cmp < 0 )) {
						SortIndex dmy = _idx[i];
						_idx[i] = _idx[j];
						_idx[j] = dmy;						
				}
			}
		}
		emit layoutChanged ();
	};

	QVariant data ( const QModelIndex &index, int role = Qt::DisplayRole) const {
		if ( !index.isValid() ) return QVariant();
		int idx = indexOfRow (index.row());
		if (idx < 0 || idx >= _bm.size()) return QVariant();
		return _bm[idx].itemData(index.column(), role);
	};
	QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const {
		if (orientation == Qt::Horizontal) {
			return Bookmark::headerData (section, role);
		} else {
			if (role == Qt::DisplayRole) 
				return QString::number (section+1);
		}
		return QVariant ();
	};

	void deleteItems (const QVector <int> &idx);

	bool              itemCheckable   (int idx, int col) const;
	bool              itemChecked     (int idx, int col) const;
	void              setItemChecked  (int idx, int col, bool);
	bool              itemCustomEdit  (const QVector<int>&idx, int col);


	QVector <Bookmark> _bm;

};







class BookmarkView : public TableView {

	Q_OBJECT;

public:
	BookmarkView ();
	QTableView *   table () {return ui._tab;}
	TableModel *   model () {return _model;};
	void fillContextMenu (QMenu *); 
	void handleCmd (const QString& key);
	void worldChanged ();
	void delSel ();
	bool canDelSel () const {return true;};


public slots:
	void itemDblClicked (int);
	void modelDataChanged ();

private:
	BookmarkModel *_model;	
	Ui::Table ui;
};




















#endif