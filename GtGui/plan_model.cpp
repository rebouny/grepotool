/* plan_model.cpp  - Plans data model

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

#include <QDebug>
#include <GtTowns.h>
#include "command.h"
#include "mainwin.h"

#include "plan_model.h"

#include "popup.h"
#include <GtPlans.h>
#include <GtPlayers.h>
#include <GtTowns.h>



bool PlanModel::canHideColumn     (int c) const
{
	if (c == PlanSource ) return false;
	if (c == PlanTarget ) return false;
	return true;
}

bool PlanModel::itemCustomEdit  (const QVector<int>&idx, int col)
{

	if( idx.size() == 0) return false;

	if( col == PlanSpecials ) {
		bool lh = false;
		bool ca = false;
		bool me = false;
		bool mb = false;
		int  al = 0;
		if (idx.size() == 1) {
			al = plans().plans[idx[0]].atlanta_level;
			lh = plans().plans[idx[0]].lighthouse;
			mb = plans().plans[idx[0]].movement_boost;
			ca = plans().plans[idx[0]].cartography;
			me = plans().plans[idx[0]].meteorology;
		}
		if(!SpecialSelector::selectSpecials (QCursor::pos(), idx.size() > 1,
			lh, ca , me, mb , al) ) return true;
		qDebug() << "specials changed ";

		for(int i=0;i< idx.size(); ++i) {
			Plan & pl = plans().plans[idx[i]];
			if (pl.source_id >= 0) {
				WorldData w = WorldData::currentWorld();
				int ti= w.townIndex(pl.source_id);
				if(ti >= 0 && idx.size() ==  1) {
					Town & to = w.towns()[ti];
					ResearchData rd = to.research ();
					BuildingData bd = to.buildings ();
						bd.val[Lighthouse] = lh;
						rd.val[ResearchMeteorology] = me;
						rd.val[ResearchCartography] = ca;
						to.setResearch  (rd);
						to.setBuildings (bd);
				}
			}
			pl.atlanta_level = al;
			pl.movement_boost = mb;
			pl.setupDisplayVals();
		}

		return true;
	}
	if( col == PlanUnit) {

		UnitIndex u = Militia;
		if(idx.size() == 1) u = plans().plans[idx[0]].slowest_unit;
		u = UnitSelector::selectUnit (QCursor::pos(), u);
		if (u== Militia) return true;

		for(int i=0;i< idx.size(); ++i) {
			plans().plans[idx[i]].slowest_unit = u;
			plans().plans[idx[i]].setupDisplayVals();
		}
		
		return true;
	}
	return false;
}

QStringList PlanModel::itemTexts      ( int idx, const QVector <int> &cols ) const
{
	return plans().plans[idx].texts(cols);
}
QStringList PlanModel::itemBBCodes    ( int idx, const QVector <int> &cols ) const  
{
	return plans().plans[idx].bbCodes(cols);
}


void PlanModel::worldChanged  ()	
{
	plans().setupDisplayData();
	QVector <int>nidx (plans().plans.size());
	for ( int i = 0 ; i <  nidx.size(); ++i ) nidx[i] = i;
	resetIndex (nidx);
};


void PlanModel::sort ( int column, Qt::SortOrder order ) {
	emit layoutAboutToBeChanged ();
	plans().setupDisplayData();	
	PlanList & pl = plans();
	for ( int i = 0 ; i <  ( _idx.size() - 1 ); ++i ) {
		for ( int j = i+1; j < _idx.size(); ++j ) {			
			int cmp = pl.plans[_idx[i]._index].compare(pl.plans[_idx[j]._index], column);
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

QVariant PlanModel::data ( const QModelIndex &index, int role ) const 
{
	if ( !index.isValid() ) return QVariant();
	int idx = indexOfRow (index.row());
	return plans().plans[idx].itemData( index.column(), role );
};

QVariant PlanModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
	if (orientation == Qt::Horizontal) {
		return Plan::headerData (section, role);

	} else {
		if (role == Qt::DisplayRole) 
			return QString::number (section+1);
	}
	return QVariant ();
};








PlanView::PlanView (const QString& id, const QString& title) : TableView (id,title) 
{
	QFrame * f= new QFrame ;
	ui.setupUi (f);
	setCentralWidget (f);

	ui._info->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Fixed);
	// ui._ghosts->hide();
	ui._tb2->hide();
	_list_cb = new QComboBox ;
	_list_cb->setCompleter (0);
	_list_cb->setEditable (true);
	_list_cb->setDuplicatesEnabled (true);
	_list_cb->setInsertPolicy (QComboBox::InsertAtCurrent);
	connect (_list_cb, SIGNAL (activated (int)), this, SLOT(setCurrentList(int)));

	_sym_cb = new  QComboBox ;
	_show = new  QCheckBox (tr("Show on map"));
	connect (_sym_cb, SIGNAL (activated (int)), this, SLOT(symChg(int)));
	connect (_show, SIGNAL (toggled(bool)), this, SLOT(showToggled()));
	connect (ui._ghosts,SIGNAL(clicked()),this,SLOT(selColor ()));

	ui._head_l->insertWidget(0, _list_cb);
	ui._head_l->insertWidget(2, _show);
	ui._head_l->insertWidget(3, _sym_cb);
	

	_delsel = new QAction (tr("Delete selected"), this);
	_start = new QAction (tr("Set fixed start time"), this);;
	_arrival= new QAction (tr("Set fixed arrival time"), this);;
	_specials= new QAction (tr("Edit special conditions"), this);;
	_unit = new QAction (tr("Set slowest unit"), this);;
	_newlist= new QAction (tr("New list"), this);;
	_dellist= new QAction (tr("Delete list"), this);;
	_add= new QAction (tr("Add to plans"), this);;

	connect (_delsel,SIGNAL(triggered()), this, SLOT(deleteSelected()));
	connect (_start,SIGNAL(triggered()), this, SLOT(setStartTime()));
	connect (_arrival,SIGNAL(triggered()), this, SLOT(setArrivalTime()));
	connect (_specials,SIGNAL(triggered()), this, SLOT(setSpecials ()));
	connect (_unit,SIGNAL(triggered()), this, SLOT(setUnit()));
	connect (_newlist,SIGNAL(triggered()), this, SLOT(newList()));
	connect (_dellist,SIGNAL(triggered()), this, SLOT(deleteList()));
	connect (_add,SIGNAL(triggered()), this, SIGNAL(addToPlansSignal()));
}

void PlanView::fillContextMenu (QMenu *m)
{	
	QVector <int> s = selectedItems ();
	if(s.size()) {
		if(!dynamic_cast<PlansView*> (this)) {
			m->addAction (_add);
			m->addSeparator ();
		}
		m->addAction (_arrival);
		m->addAction (_start);
		//m->addAction (_specials);
		//m->addAction (_unit);
		m->addSeparator ();
		m->addAction (_delsel);
	}
	m->addSeparator ();
	m->addAction (_newlist);
	m->addAction (_dellist);

}


void PlanView::setStartTime ()
{
	QVector <int> s = selectedItems ();
	QDateTime t = QDateTime::currentDateTime();
	if(s.size() == 1) t = _model->plans().plans[s[0]].start_time;
	if (!TimePopup::selectTime (QCursor::pos(), t) )return;
	setFixedStartTime (t);
}
void PlanView::setArrivalTime ()
{
	QVector <int> s = selectedItems ();
	QDateTime t = QDateTime::currentDateTime();
	if(s.size() == 1) t = _model->plans().plans[s[0]].arrival_time;
	if (!TimePopup::selectTime (QCursor::pos(), t) ) return;
	setFixedArrivalTime (t);
}
void PlanView::setUnit ()
{
	QVector <int> s = selectedItems ();
	UnitIndex u = Militia;
	if(s.size() == 1) u = _model->plans().plans[s[0]].slowest_unit;
	u = UnitSelector::selectUnit (QCursor::pos(), u);
	if(u!= Militia) 
		setSlowestUnit(u);
}
void PlanView::setSpecials ()
{
	QVector <int> s = selectedItems ();
	QDateTime t = QDateTime::currentDateTime();
	bool lh = false;
	bool ca = false;
	bool me = false;
	bool mb = false;
	int  al = 0;
	if (s.size() == 1) {
		al = _model->plans().plans[s[0]].atlanta_level;
		lh = _model->plans().plans[s[0]].lighthouse;
		mb = _model->plans().plans[s[0]].movement_boost;
		ca = _model->plans().plans[s[0]].cartography;
		me = _model->plans().plans[s[0]].meteorology;
	}
	if(!SpecialSelector::selectSpecials (QCursor::pos(), s.size() > 1,
		lh, ca , me, mb , al) ) return ;
	qDebug() << "specials changed ";
	setSpecials (mb, lh, me, ca, al);
}
void PlanView::newList ()
{
	_model->newList ();
	worldChanged ();
	emit plansChangedSignal ();	
}
void PlanView::deleteList ()
{
	_model->deleteList ();
	worldChanged ();
	emit plansChangedSignal ();	
}
void PlanView::setCurrentList (int i)
{
	// qDebug() << "current index changed "<< i;

	int ci = _model->currentPlan();
	_model->plans().name = _list_cb->itemText(ci);	
	_model->setCurrentPlan (i);	
	worldChanged();
	_model->triggerRedraw ();
	emit plansChangedSignal ();	
}

void PlanView::selColor ()
{
	_model->plans().color = ColorPopup::selectColor (QCursor::pos(),_model->plans().color);
	worldChanged();
	emit plansChangedSignal ();	
}
void PlanView::symChg (int)
{
	_model->plans().symbol = _sym_cb->currentIndex();
	worldChanged ();
	emit plansChangedSignal ();	
}
void PlanView::showToggled()
{
	_model->plans().show_on_map = _show->isChecked();
	worldChanged ();
	emit plansChangedSignal ();	
}

void PlanView::handleCmd (const QString& key)
{
	WorldData w = WorldData::currentWorld();
	ToolWidget::handleCmd(key);
}





void PlanView::worldChanged () 
{
	_list_cb->blockSignals (true);
	_list_cb->clear ();
	_list_cb->addItems (_model->planListNames ());
	_list_cb->setCurrentIndex (_model->currentPlan());
	_list_cb->blockSignals (false);
	_model->worldChanged();
	restoreHeaderState ();
	sortModel (-1);

	QPixmap pm (20,20); 
	QColor co = _model->plans().color; 
	pm.fill (co);
	ui._ghosts->setIcon (pm);
	_show->blockSignals (true);
	_show->setChecked (_model->plans().show_on_map);
	_show->blockSignals (false);


	_sym_cb->blockSignals (true);
	_sym_cb->clear();
	_sym_cb->setSizeAdjustPolicy (QComboBox::AdjustToMinimumContentsLength);
	_sym_cb->setIconSize (QSize(20,20));
	for (int i =0;i< TownTypeMax; ++i) {
		QImage img (20,20,QImage::Format_ARGB32_Premultiplied);
		img.fill (QColor(0,0,0,0));
		QPainter p(&img);
		QColor penc = Qt::black;
		if (color2gray(co) < 50) penc = Qt::white;
		p.setPen(penc);
		p.setBrush (co);			
		Town::renderTypeSymbol (&p,(TownTypeIndex) i,QPoint(10,10),10);
		_sym_cb->addItem(QIcon(QPixmap::fromImage (img)),"");
	}
	int ci = _model->plans().symbol ;
	if (ci >=  TownTypeMax || ci<0) ci = 0;
	_sym_cb->setCurrentIndex (ci);
	_sym_cb->blockSignals (false);
}

void PlanView::delSel ()
{
	QVector <int> s = selectedItems ();
	QVector <Plan> np; 
	for(int i=0;i< _model->plans().plans.size(); ++i) {
		if(!s.contains(i)) np.push_back (_model->plans().plans[i]);
	}
	_model->plans().plans = np;
	worldChanged ();	
	_model->triggerRedraw ();
	emit plansChangedSignal ();	
}

void PlanView::addPlan (const Plan & pl) {
	_model->plans().plans.push_back(pl);
	worldChanged ();
	_model->triggerRedraw ();
	emit plansChangedSignal ();	
}

void PlanView::setFixedArrivalTime (const QDateTime & tim)
{
	QVector <int> s = selectedItems ();
	for(int i=0;i< s.size(); ++i) {
		_model->plans().plans[s[i]].setFixedArrivalTime (tim);
		_model->plans().plans[s[i]].setupDisplayVals();
	}
	worldChanged ();
	_model->triggerRedraw ();
	emit plansChangedSignal ();	
}

void PlanView::setSpecials (bool mb, bool lhouse, bool meteo, bool carto, int atlanta)
{
	QVector <int> s = selectedItems ();
	for(int i=0;i< s.size(); ++i) {
		Plan & pl = _model->plans().plans[s[i]];
		if (pl.source_id >= 0) {
			WorldData w = WorldData::currentWorld();
			int ti= w.townIndex(pl.source_id);
			if(ti >= 0) {
				Town & to = w.towns()[ti];
				ResearchData rd = to.research ();
				BuildingData bd = to.buildings ();
				bd.val[Lighthouse] = lhouse;
				rd.val[ResearchMeteorology] = meteo;
				rd.val[ResearchCartography] = carto;
				to.setResearch  (rd);
				to.setBuildings (bd);
			}
		}
		pl.atlanta_level = atlanta;
		pl.movement_boost = mb;
		pl.setupDisplayVals();
	}
	worldChanged ();
	_model->triggerRedraw ();
	emit plansChangedSignal ();	
}

void PlanView::setSlowestUnit (int u)
{
	QVector <int> s = selectedItems ();
	for(int i=0;i< s.size(); ++i) {
		_model->plans().plans[s[i]].slowest_unit = (UnitIndex) u;
		_model->plans().plans[s[i]].setupDisplayVals();
	}
	worldChanged ();
	_model->triggerRedraw ();
	emit plansChangedSignal ();	
}

void PlanView::setFixedStartTime (const QDateTime & tim)
{
	QVector <int> s = selectedItems ();
	for(int i=0;i< s.size(); ++i) {
		_model->plans().plans[s[i]].setFixedStartTime (tim);
		_model->plans().plans[s[i]].setupDisplayVals();
	}
	worldChanged ();
	_model->triggerRedraw ();
	emit plansChangedSignal ();	
}

void PlanView::setTarget (int tgt)
{
	for(int i=0;i< _model->plans().plans.size(); ++i) {
		_model->plans().plans[i].target_id = tgt;
		_model->plans().plans[i].setupDisplayVals();
	}
	worldChanged ();
	_model->triggerRedraw ();
	emit plansChangedSignal ();	
}

void PlanView::setSource (int src, bool movement_boost, int atlanta, UnitIndex u)
{

	for(int i=0;i< _model->plans().plans.size(); ++i) {
		_model->plans().plans[i].source_id = src;
		_model->plans().plans[i].movement_boost = movement_boost;
		_model->plans().plans[i].atlanta_level = atlanta;
		_model->plans().plans[i].slowest_unit = u;
		_model->plans().plans[i].setupDisplayVals();

	}
	worldChanged ();
	_model->triggerRedraw ();
	emit plansChangedSignal ();	
}





















