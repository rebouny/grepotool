#ifndef ___REPORT_MODEL_H
#define ___REPORT_MODEL_H



#include <GtWorlddata.h>
#include <GtReports.h>
#include "table_model.h"
#include "ui_table.h"

#include "popup.h"

#include <QToolButton>
#include <QSpinBox>
#include <QPainter>


enum AttReportCols {
	AttReportTime,
	AttReportAttTown,
	AttReportAttPlayer,
	AttReportAttAlly,
	AttReportDefTown,
	AttReportDeffPlayer,
	AttReportDeffAlly,
	AttReportMax
};

class AttReportData {
	Q_DECLARE_TR_FUNCTIONS (AttReportData); 
public:
	AttReportData (const Report& r, int idx = 0);
	AttReportData () {};
	AttReportData (const AttReportData &o) ;
	AttReportData & operator = (const AttReportData &o) ;
	int compare (const AttReportData &o, int col) const ;
	QDateTime time;
	QString   att_player;
	QString   att_town;
	QString   att_ally;
	QString   def_player;
	QString   def_town;
	QString   def_ally;
	int   att_player_id;
	int   att_town_id;
	int   att_ally_id;
	int   def_player_id;
	int   def_town_id;
	int   def_ally_id;
	bool  wall_diff;
	int   index;
};

class ReportModel : public TableModel {
	Q_OBJECT
public:
	ReportModel (QObject * p= 0):TableModel (p){};
	int columnCount(const QModelIndex &) const {return AttReportMax;};
	int               defaultSortColumn () const {return 0;};
	int               maxIndex          () const {return reports.size();};
	QByteArray        headerState     () const {return WorldData::setting("Reporttable/header").toByteArray();};
	void              saveHeaderState (const QByteArray& b) {WorldData::setSetting("Reporttable/header",b);};
	bool              canHideColumn     (int c) const {if (c) return true; return false;};
	void              worldChanged  ();
	int               itemSortIndex (int idx, int col) const;
	QStringList       itemTexts      ( int idx, const QVector <int> &cols ) const;  
	QStringList       itemBBCodes    ( int idx, const QVector <int> &cols ) const;  
	QVariant data ( const QModelIndex &index, int role = Qt::DisplayRole) const;
	QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const ;
	void deleteItems (const QVector <int> &idx);
	int reportIndex (int i) const {return reports[i].index;};
	void sort ( int column, Qt::SortOrder order = Qt::AscendingOrder ) {
		emit layoutAboutToBeChanged ();		
		for ( int i = 0 ; i <  ( _idx.size() - 1 ); ++i ) {
			for ( int j = i+1; j < _idx.size(); ++j ) {
				int cmp = reports[_idx[i]._index].compare(reports[_idx[j]._index], column);
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
public slots: 
	void allReports ();
	void setTown (int);
	void setAlly (int);
	void setPlayer (int);
protected:
	QVector <AttReportData> reports;
};







class ReportView : public TableView {

	Q_OBJECT;

public:
	ReportView ();
	QTableView *   table () {return ui._tab;}
	TableModel *   model () {return _model;};
	void fillContextMenu (QMenu *); 
	void handleCmd (const QString& key);
	void worldChanged ();
	void delSel ();
	bool canDelSel () const {return true;};
	int reportIndex (int i) const {return _model->reportIndex(i);};
signals:
	void reportSelectedSignal (int );
public slots: 
	void allReports ();
	void setTown (int i);
	void setAlly (int i);
	void setPlayer (int i);
	void reportClicked (int i) {emit reportSelectedSignal (reportIndex(i));};
	void modelDataChanged ();

private:
	ReportModel *_model;	
	Ui::Table ui;
};






#endif