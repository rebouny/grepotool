#ifndef ___PLAN_MODEL_H
#define ___PLAN_MODEL_H
/* plan_model.h  - Plan data model

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

#include <QComboBox>
#include <QCheckBox>

#include <GtPlans.h>

#ifdef EXPORT 
# undef EXPORT
#endif
#ifdef BUILDING_GTGUI
# define EXPORT DLL_EXPORT
#else
# define EXPORT DLL_IMPORT
#endif

class EXPORT  PlanModel : public TableModel {
	Q_OBJECT
public:
	PlanModel (const QString& key, QObject * p= 0):TableModel (p),_key (key){};
	virtual ~PlanModel () {};
	virtual PlanList & plans () const = 0;
	virtual QStringList planListNames () const = 0;  
	virtual int currentPlan () const = 0;
	virtual void setCurrentPlan (int i) = 0; 
	virtual void newList () = 0; 
	virtual void deleteList () = 0; 
	
	int     columnCount(const QModelIndex &) const {return PlanMax;};
	int     defaultSortColumn () const {return PlanTime;};

	int               maxIndex          () const {return plans().plans.size();};

	QByteArray        headerState     () const {return WorldData::setting(_key+"/header").toByteArray();};
	void              saveHeaderState (const QByteArray& b) {WorldData::setSetting(_key+"/header",b);};
	bool              canHideColumn     (int c) const;

	void              worldChanged  ();
	QStringList       itemTexts      ( int idx, const QVector <int> &cols ) const;  
	QStringList       itemBBCodes    ( int idx, const QVector <int> &cols ) const;  

	void sort ( int column, Qt::SortOrder order = Qt::AscendingOrder ) ;

	QVariant data ( const QModelIndex &index, int role = Qt::DisplayRole) const ;

	QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const ;

	bool              itemCustomEdit  (const QVector<int>&idx, int col);

	int               itemSortIndex (int , int ) const {return 0;};
protected:
	QString _key;
};







class EXPORT PlanView : public TableView {

	Q_OBJECT;

public:
	PlanView (const QString& id, const QString& title);
	QTableView *   table () {return ui._tab;}
	TableModel *   model () {return _model;};
	void worldChanged ();
	void delSel ();
	bool canDelSel () const {return true;};
	void addPlan (const Plan & pl);
	void fillContextMenu (QMenu *); 
	void handleCmd (const QString& key);

	const Plan & plan (int i) const {return _model->plans().plans[i];};

signals:
	void plansChangedSignal ();
	void addToPlansSignal ();

public slots:
	void modelDataChanged () {	emit plansChangedSignal (); };
  
	void setFixedArrivalTime (const QDateTime & tim);
	void setFixedStartTime (const QDateTime & tim);
	void setSlowestUnit (int u);
	void setSpecials (bool movement_boost, bool lhouse, bool meteo, bool carto, int atlanta);
	void setTarget (int tgt);
	void setSource (int src, bool movement_boost, int atlanta, UnitIndex u);
	
	// menu commands
	void setStartTime ();
	void setArrivalTime ();
	void setUnit ();
	void setSpecials ();
	void deleteSelected () {delSel ();};
	void newList ();
	void deleteList ();
	
	void setCurrentList (int);

	void selColor ();
	void symChg (int);
	void showToggled();

protected:
	PlanModel *_model;	
	Ui::Table ui;

	QComboBox * _list_cb;
	QComboBox * _sym_cb;
	QCheckBox * _show;

	QAction * _delsel;
	QAction * _start;
	QAction * _arrival;
	QAction * _specials;
	QAction * _unit;
	QAction * _newlist;
	QAction * _dellist;
	QAction * _add;
};

class EXPORT MyTownsModel : public PlanModel {
	Q_OBJECT;
public:
	MyTownsModel (QObject* p=0) : PlanModel ("MyTowns", p){};
	PlanList & plans () const {return WorldData::currentMyTownsList();};
	int currentPlan () const {return WorldData::currentMyTownsListIndex();};
	void setCurrentPlan (int i) { WorldData::setCurrentMyTownsListIndex(i);};
	QStringList planListNames () const {
		QStringList r;
		const QVector <PlanList> & pl =  WorldData::currentWorld().mytowns();
		for (int i=0;i< pl.size(); ++i ) {
			r.push_back (pl[i].name);
		}
		return r;
	};  
	void newList () {
		QVector <PlanList> & pl =  WorldData::currentWorld().mytowns();
		int pn = pl.size();
		PlanList npl;
		npl.name = tr("New List %1").arg (pn) ;
		pl.push_back (npl);
		setCurrentPlan (pn);
	}; 
	void deleteList () {
		int ci = currentPlan ();
		QVector <PlanList> & pl =  WorldData::currentWorld().mytowns();
		pl.erase(pl.begin()+ci);
		--ci;
		if(ci<0) ci=0;
		setCurrentPlan (ci);
	}; 

};

class EXPORT TargetsModel : public PlanModel {
	Q_OBJECT;
public:
	TargetsModel (QObject* p=0) : PlanModel ("Targets", p){};
	PlanList & plans () const {return WorldData::currentTargetList();};
	int currentPlan () const {return WorldData::currentTargetListIndex();};
	void setCurrentPlan (int i) { WorldData::setCurrentTargetListIndex(i);};
	QStringList planListNames () const {
		QStringList r;
		const QVector <PlanList> & pl =  WorldData::currentWorld().targets();
		for (int i=0;i< pl.size(); ++i ) {
			r.push_back (pl[i].name);
		}
		return r;
	};  
	void newList () {
		QVector <PlanList> & pl =  WorldData::currentWorld().targets();
		int pn = pl.size();
		PlanList npl;
		npl.name = tr("New List %1").arg (pn) ;
		pl.push_back (npl);
		setCurrentPlan (pn);
	}; 
	void deleteList () {
		int ci = currentPlan ();
		QVector <PlanList> & pl =  WorldData::currentWorld().targets();
		pl.erase(pl.begin()+ci);
		--ci;
		if(ci<0) ci=0;
		setCurrentPlan (ci);
	}; 
};


class EXPORT PlansModel : public PlanModel {
	Q_OBJECT;
public:
	PlansModel (QObject* p=0) : PlanModel ("Plans", p){};
	PlanList & plans () const {return WorldData::currentPlansList();};
	int currentPlan () const {return WorldData::currentPlansListIndex();};
	void setCurrentPlan (int i) { WorldData::setCurrentPlansListIndex(i);};
	QStringList planListNames () const {
		QStringList r;
		const QVector <PlanList> & pl =  WorldData::currentWorld().plans();
		for (int i=0;i< pl.size(); ++i ) {
			r.push_back (pl[i].name);
		}
		return r;
	};  
	void newList () {
		QVector <PlanList> & pl =  WorldData::currentWorld().plans();
		int pn = pl.size();
		PlanList npl;
		npl.name = tr("New List %1").arg (pn) ;
		pl.push_back (npl);
		setCurrentPlan (pn);
	}; 
	void deleteList () {
		int ci = currentPlan ();
		QVector <PlanList> & pl =  WorldData::currentWorld().plans();
		pl.erase(pl.begin()+ci);
		--ci;
		if(ci<0) ci=0;
		setCurrentPlan (ci);
	}; 
};


class EXPORT MyTownsView : public PlanView {
	Q_OBJECT;
public:

	MyTownsView ():PlanView("MyTowns",tr("My towns")) {
		_model = new MyTownsModel (this);
		initTable();
	};

};

class EXPORT TargetsView : public PlanView {
	Q_OBJECT;
public:
	TargetsView ():PlanView("Targets",tr("Targets")) {
		_model = new TargetsModel (this);
		initTable();
	};
};

class EXPORT PlansView : public PlanView {
	Q_OBJECT;
public:
	PlansView ():PlanView("Plans",tr("Plans")) {
		_model = new PlansModel (this);
		initTable();
		ui._ghosts->hide();
		_sym_cb->hide();
		_show->hide();
	};
};
















#endif