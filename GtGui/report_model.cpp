#include "report_model.h"
#include "GtStats.h"
#include "GtTowns.h"
#include "GtPlayers.h"
#include "GtAllys.h"

AttReportData::AttReportData (const Report& r, int idx) {	
	const AttReport * a = r.att ();
	if(!a) return;
	index = idx;
	time = a->att_time;
	att_player_id = a->att_player_id;
	att_town_id=a->att_town_id;
	att_ally_id=-1;
	def_player_id=a->def_player_id;
	def_town_id=a->def_town_id;
	def_ally_id=-1;
	const WorldData w = WorldData::currentWorld();
	const Stats & s = w.stats();
	Town at;
	s.initTown (att_town_id, at, time);
	if (!at.ghost) {
		if(att_player_id<0) att_player_id = at.player_id;
		att_ally_id = at.ally_id;
	}
	att_town = at.name;
	Town dt;
	s.initTown (def_town_id, dt, time);
	if (!dt.ghost) {
		if(def_player_id<0) def_player_id = dt.player_id;
		def_ally_id = dt.ally_id;
	}
	def_town = dt.name;
	att_player="";
	att_ally="";
	def_player="";
	def_ally="";
	int api = w.playerIndex (att_player_id);
	int aai = w.allyIndex (att_ally_id);
	int dpi = w.playerIndex (def_player_id);
	int dai = w.allyIndex (def_ally_id);
	if(api>=0) att_player = w.players()[api].name;
	if(dpi>=0) def_player = w.players()[dpi].name;
	if(aai>=0) att_ally = w.allys()[aai].name;
	if(dai>=0) def_ally = w.allys()[dai].name;

	Report wd = w.wallDiff (att_player_id, time);
	WallReport * wr = wd.wall();
	wall_diff = (wr && wr->lost_as_att == a->att_unit_loss);	
};

AttReportData::AttReportData (const AttReportData &o) {
	*this = o;
};
AttReportData & AttReportData::operator = (const AttReportData &o) {
	time = o.time;
	att_player=o.att_player;
	att_town=o.att_town;
	att_ally=o.att_ally;
	def_player=o.def_player;
	def_town=o.def_town;
	def_ally=o.def_ally;
	att_player_id=o.att_player_id;
	att_town_id=o.att_town_id;
	att_ally_id=o.att_ally_id;
	def_player_id=o.def_player_id;
	def_town_id=o.def_town_id;
	def_ally_id= o.def_ally_id;
	wall_diff= o.wall_diff;	
	index = o.index;
	return *this;
}

int AttReportData::compare (const AttReportData &o, int col) const 
{
	 
	if(col == 	AttReportTime)    return (int) time.toTime_t () - (int)o.time.toTime_t();
	if(col == 	AttReportAttTown) return att_town.compare (o.att_town,Qt::CaseInsensitive);
	if(col == 	AttReportAttPlayer)return att_player.compare (o.att_player,Qt::CaseInsensitive);
	if(col == 	AttReportAttAlly) return att_ally.compare (o.att_ally,Qt::CaseInsensitive);
	if(col == 	AttReportDefTown) return def_town.compare (o.def_town,Qt::CaseInsensitive);
	if(col == 	AttReportDeffPlayer)return def_player.compare (o.def_player,Qt::CaseInsensitive);
	if(col == 	AttReportDeffAlly) return def_ally.compare (o.def_ally,Qt::CaseInsensitive);
	return 0;
}


void ReportModel::worldChanged  ()	
{
	allReports ();
};

void ReportModel::allReports ()	
{
	WorldData w = WorldData::currentWorld ();
	QVector <int> r;
	reports.clear ();
	for(int i=0;i<w.reportCount(); ++i) {
		reports.push_back (AttReportData (w.report(i),i));
		r.push_back (i);
	}	
	resetIndex (r);
};

void ReportModel::setPlayer (int pl)	
{
	WorldData w = WorldData::currentWorld ();
	QVector <int> r;
	reports.clear ();
	int cnt = 0;
	for(int i=0;i<w.reportCount(); ++i) {
		AttReportData dd (w.report(i),i);
		if(dd.att_player_id == pl || dd.def_player_id == pl) {
			reports.push_back (dd);
			r.push_back (cnt);
			++cnt;
		}
	}	
	resetIndex (r);
};
void ReportModel::setAlly (int al)	
{
	WorldData w = WorldData::currentWorld ();
	QVector <int> r;
	reports.clear ();
	int cnt = 0;
	for(int i=0;i<w.reportCount(); ++i) {
		AttReportData dd (w.report(i),i);
		if(dd.att_ally_id == al || dd.def_ally_id == al) {
			reports.push_back (dd);
			r.push_back (cnt);
			++cnt;
		}
	}	
	resetIndex (r);
};
void ReportModel::setTown (int to)	
{
	WorldData w = WorldData::currentWorld ();
	QVector <int> r;
	reports.clear ();
	int cnt = 0;
	for(int i=0;i<w.reportCount(); ++i) {
		AttReportData dd (w.report(i),i);
		if(dd.att_town_id == to || dd.def_town_id == to) {
			reports.push_back (dd);
			r.push_back (cnt);
			++cnt;
		}
	}	
	resetIndex (r);
};
/*
	if(col == 	AttReportTime)
	if(col == 	AttReportAttTown) 
	if(col == 	AttReportAttPlayer)
	if(col == 	AttReportAttAlly) 
	if(col == 	AttReportDefTown) 
	if(col == 	AttReportDeffPlayer)
	if(col == 	AttReportDeffAlly) 
*/
int ReportModel::itemSortIndex (int , int ) const {
	return 0; // WorldData::currentWorld ().allys()[idx].itemSortIndex (col);
};
QStringList ReportModel::itemTexts      ( int idx, const QVector <int> &cols ) const {
	QStringList ret;
	const AttReportData & r = reports[idx];
	for (int i=0;i< cols.size(); ++i) {
		int col = cols[i];
		QString s;
		if(col == 	AttReportTime) s = r.time.toString("dd.MM.yyyy hh:mm:ss");
		if(col == 	AttReportAttTown) s=r.att_town;
		if(col == 	AttReportAttPlayer)s=r.att_player;
		if(col == 	AttReportAttAlly) s=r.att_ally;
		if(col == 	AttReportDefTown) s=r.def_town;
		if(col == 	AttReportDeffPlayer)s=r.def_player;
		if(col == 	AttReportDeffAlly) 	s=r.def_ally;
		ret.push_back (s);
	}
	return ret;
};  
QStringList ReportModel::itemBBCodes    ( int idx, const QVector <int> &cols ) const {
	QStringList ret;
	const AttReportData & r = reports[idx];
	for (int i=0;i< cols.size(); ++i) {
		int col = cols[i];
		QString s;
		if(col == 	AttReportTime) s = r.time.toString("dd.MM.yyyy hh.mm.ss");
		if(col == 	AttReportAttTown) s=QString("[town]%1[/town]").arg(r.att_town_id);
		if(col == 	AttReportAttPlayer)s=QString("[player]%1[/player]").arg(r.att_player);
		if(col == 	AttReportAttAlly) s= QString("[ally]%1[/ally]").arg(r.att_ally);
		if(col == 	AttReportDefTown) s=QString("[town]%1[/town]").arg(r.def_town_id);
		if(col == 	AttReportDeffPlayer)s=QString("[player]%1[/player]").arg(r.def_player);
		if(col == 	AttReportDeffAlly) 	s=QString("[ally]%1[/ally]").arg(r.def_ally);
		ret.push_back (s);
	}
	
	return ret;
};  

QVariant ReportModel::data ( const QModelIndex &index, int role ) const {
	if ( !index.isValid() ) return QVariant();
	int idx = indexOfRow (index.row());
	if (idx < 0 || idx >= reports.size()) return QVariant();
	const AttReportData & r = reports[idx];
	int col = index.column();
	if (role == Qt::DisplayRole || role == Qt::ToolTipRole) {
		QVariant s;
		if(col == 	AttReportTime) s = r.time.toString("dd.MM.yyyy hh.mm.ss");
		if(col == 	AttReportAttTown) s=r.att_town;
		if(col == 	AttReportAttPlayer)s=r.att_player;
		if(col == 	AttReportAttAlly) s=r.att_ally;
		if(col == 	AttReportDefTown) s=r.def_town;
		if(col == 	AttReportDeffPlayer)s=r.def_player;
		if(col == 	AttReportDeffAlly) 	s=r.def_ally;
		return s;		
	}
	return QVariant();
};
QVariant ReportModel::headerData ( int col, Qt::Orientation orientation, int role) const {
	if (orientation == Qt::Horizontal) {

		if (role == Qt::DisplayRole) {
			if(col == 	AttReportTime)    return tr("Time");
			if(col == 	AttReportAttTown)    return tr("Attacking town");
			if(col == 	AttReportAttPlayer)   return tr("Attacker");
			if(col == 	AttReportAttAlly)    return tr("Attacking ally");
			if(col == 	AttReportDefTown)    return tr("Target");
			if(col == 	AttReportDeffPlayer)   return tr("Defender");
			if(col == 	AttReportDeffAlly)    return tr("Defender ally");
		} else if (role == Qt::ToolTipRole) {
			if(col == 	AttReportTime)    return tr("Time");
			if(col == 	AttReportAttTown)    return tr("Attacking town");
			if(col == 	AttReportAttPlayer)   return tr("Attacker");
			if(col == 	AttReportAttAlly)    return tr("Attacking ally");
			if(col == 	AttReportDefTown)    return tr("Target");
			if(col == 	AttReportDeffPlayer)   return tr("Defender");
			if(col == 	AttReportDeffAlly)    return tr("Defender ally");
		}
		
	} else {
		if (role == Qt::DisplayRole) 
			return QString::number (col+1);
	}
	return QVariant ();
};

void ReportModel::deleteItems (const QVector <int> &idx) 
{
	QVector <int> ridx;
	for(int i=0;i<idx.size();++i) {
		ridx.push_back(reports[idx[i]].index);
	}

}





ReportView::ReportView () : TableView ("Reports", tr("Reports")) 
{
	QFrame * f= new QFrame ;
	ui.setupUi (f);
	ui._ghosts->setIcon(QIcon(":/icons/icons/world.ico"));
	ui._ghosts->setToolTip(tr("Show all reports"));
	ui._tb2->hide();

	connect (ui._ghosts, SIGNAL(clicked()), this, SLOT(allReports()));
	ui._tab->setSelectionMode (QAbstractItemView::SingleSelection);

	_model = new ReportModel (this);

	initTable();
	setCentralWidget (f);


	connect (this, SIGNAL(itemDoubleClickSignal (int)), this, SLOT(reportClicked (int)));

}


void ReportView::allReports ()
{
	_model->allReports ();
	restoreHeaderState ();
	sortModel (-1);
	ui._info->setText (QString("<b>%1</b>").arg(tr("%1 Reports").arg (_model->rowCount())));
}
void ReportView::setTown (int i)
{
	if(i<0) return;
	_model->setTown (WorldData::currentWorld ().towns()[i].id);
	restoreHeaderState ();
	sortModel (-1);
	QString tn = QString("<img src=':/icons/icons/town.ico' width=16 height=16><b>%1").arg(WorldData::currentWorld ().towns()[i].name);
	ui._info->setText (QString("<b>%1</b>").arg(tr("%1 Reports for %2").arg (_model->rowCount()).arg(tn)));
}
void ReportView::setAlly (int i)
{
	if(i<0) return;
	_model->setAlly (WorldData::currentWorld ().allys()[i].id);
	restoreHeaderState ();
	sortModel (-1);
	QString tn = QString("<img src=':/icons/icons/ally.ico' width=16 height=16><b>%1").arg(WorldData::currentWorld ().allys()[i].name);
	ui._info->setText (QString("<b>%1</b>").arg(tr("%1 Reports for %2").arg (_model->rowCount()).arg(tn)));
}
void ReportView::setPlayer (int i)
{
	if(i<0) return;
	_model->setPlayer (WorldData::currentWorld ().players()[i].id);
	restoreHeaderState ();
	sortModel (-1);
	QString tn = QString("<img src=':/icons/icons/player.ico' width=16 height=16><b>%1").arg(WorldData::currentWorld ().players()[i].name);
	ui._info->setText (QString("<b>%1</b>").arg(tr("%1 Reports for %2").arg (_model->rowCount()).arg(tn)));
}


void ReportView::delSel () 
{
	_model->deleteItems(selectedItems());
}

void ReportView::fillContextMenu (QMenu *m)
{	

}


void ReportView::worldChanged ()
{
	allReports ();
}

void ReportView::handleCmd (const QString& key)
{
	{
		ToolWidget::handleCmd(key);
	}
}

void ReportView::modelDataChanged ()
{
	// emit updateInfMapSignal ();
}














