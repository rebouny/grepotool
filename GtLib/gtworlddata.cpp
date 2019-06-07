#include <QDebug>
#include "GtWorlddata.h"
#include "GtWorlddataPrivate.h"

WorldData WorldData::_global;
QVariantMap WorldData::_settings;


int WorldData::handleReport (const Report & r)
{
	int re = -1;
	if (r.server ().isEmpty ()) return re;
	if (r.server() != serverName ()) return re;  
	if (r.type() == ReportInvalid) {
		return re;
	} else if (r.type() == ReportAttack) {
		re= _d->reports.size();
		const AttReport * a = r.att();
		if(_d->reports.contains(r)) {
			re = _d->reports.indexOf(r);
			a = _d->reports[re].att();
		} else {
			_d->reports.push_back(r);
		}
	
		// now set town data if attack was big enough
		
		int bhp = a->att_units.bhp();
		if (bhp<300) return re;
		int ti = townIndex (a->att_town_id);
		if (ti < 0) return re;
		Town& to = _d->towns[ti];
		Report lr = lastAttack(a->att_town_id);
		if (lr.isValid() && lr.att()->att_time > a->att_time) return re;
		to.setUnits (a->att_units);
		to.type = a->att_units.attackType ();

	} else if (r.type() == ReportSpy) {
		if(_d->spys.contains(r)) return _d->spys.indexOf(r);
		re= _d->spys.size();
		_d->spys.push_back(r);
	} else if (r.type() == ReportWallState) {
		if(_d->wallstates.contains(r)) return _d->wallstates.indexOf(r);
		re= _d->wallstates.size();
		_d->wallstates.push_back(r);
	} 
	return re;
}
int WorldData::reportCount () const
{
	return _d->reports.size ();
}

int WorldData::spyCount () const
{
	return _d->spys.size ();
}

Report WorldData::report (int n) const
{
	return _d->reports[n];
}

Report WorldData::spy (int n) const
{
	return _d->spys[n];
}

Report WorldData::lastSpy (int town_id) const
{
	int lr= -1; 
	QDateTime ct = _d->world_time;
	for (int i=0;i< _d->spys.size(); ++i) {
		SpyReport * s = _d->spys[i].spy ();
		if (!s) continue;
		if (s->town_id != town_id) continue;
		if (lr == -1 || s->time > ct) {
			lr = i;
			ct = s->time;
		}
	}
	if (lr<0) 
		return Report ();
	return _d->spys[lr];
}

Report WorldData::wallDiff (int player_id, const QDateTime tim) const
{
	WallReport *lb = 0;
	WallReport *fa = 0;
	int lbt = 0;
	int fat = 0;
	for (int i=0;i< _d->wallstates.size(); ++i) {
		WallReport *w = _d->wallstates[i].wall();
		if (!w) continue;
		if (w->player_id != player_id) continue;
		if (w->_recv_time < tim) {
			int m = w->_recv_time.secsTo (tim);
			if (!lb || m<lbt) {
				lb = w;
				lbt = m;
			}
			
		} else {
			int m = tim.secsTo (w->_recv_time);
			if (!fa || m<fat) {
				fa = w;
				fat = m;
			}
		}
	}
	WallReport * r = new WallReport;
	r->_recv_time = tim;
	r->player_id = player_id;
	if (lb && fa) {
		r->killed_as_att = fa->killed_as_att - lb->killed_as_att;
		r->killed_as_def = fa->killed_as_def - lb->killed_as_def;
		r->lost_as_att = fa->lost_as_att -lb->lost_as_att;
		r->lost_as_def = fa->lost_as_def -lb->lost_as_def;
	}
	return Report (r);
}

Report WorldData::lastAttack (int town_id) const
{
	int lr= -1; 
	QDateTime ct = _d->world_time;
	for (int i=0;i< _d->reports.size(); ++i) {
		AttReport * s = _d->reports[i].att ();
		if (!s) continue;
		if (s->att_town_id != town_id) continue;
		if (lr == -1 || s->att_time > ct) {
			lr = i;
			ct = s->att_time;
		}
	}
	if (lr<0) 
		return Report ();
	return _d->reports[lr];
}

QVariant WorldData::globalSetting (const QString& key, const QVariant& def)
{
	if (_settings.contains(key)) return _settings[key];		
	return def;
}

QVariant WorldData::setting (const QString& key, const QVariant& def)
{
	if (_global._d->settings.contains(key)) return _global._d->settings[key];
	if (_settings.contains(key)) return _settings[key];		
	return def;
}

void WorldData::setSetting (const QString& key, const QVariant& val)
{
	_global._d->setSetting(key,val);
	if (val.isValid()) {
		_settings[key] = val;
		return;
	}
	if(!_settings.contains(key)) return;
	_settings.erase(_settings.find(key));
}

WorldData::WorldData () : _d(new WorldDataPriv) 
{
	_d->incRef();
};

WorldData::WorldData (const WorldData & o):_d(const_cast <WorldDataPriv*> (o._d))
{
	_d->incRef();
};

WorldData & WorldData::operator = (const WorldData & o) 
{
	if (_d == o._d) return *this;
	if (_d->decRef()) 
		delete _d;
	_d = const_cast <WorldDataPriv*> (o._d);
	_d->incRef();
	return *this;
}

WorldData::~WorldData ()
{
	if (_d->decRef()) 
		delete _d;	
}

Stats & WorldData::stats() {return _d->stats;};
const Stats & WorldData::stats() const {return _d->stats;};

QDateTime WorldData::worldStart () const {return _d->world_start;};
QDateTime WorldData::worldEnd () const {return _d->world_end;};
QDateTime WorldData::worldTime () const {return _d->world_time;};
QDateTime &WorldData::worldStart () {return _d->world_start;};
QDateTime &WorldData::worldEnd () {return _d->world_end;};
QDateTime &WorldData::worldTime () {return _d->world_time;};

inline bool WorldData::operator == (const WorldData & o) const {return _d == o._d;};
/*inline*/ bool WorldData::isValid () const {return _d->world_time.isValid();};
inline void WorldData::invalidate () {_d->world_time = QDateTime();};
WorldData& WorldData::currentWorld () {
	return _global;
};
void WorldData::setCurrentWorld (const WorldData& w) {
	_global.storeSettings (0);
	_global = w;
	GtServer::markVisited (w.serverName ());
};

Unit & WorldData::unit (UnitIndex u) {
	return _d->units[(int) u];
};
const Unit & WorldData::unit (UnitIndex u) const {return _d->units[(int) u];};

/*inline*/ QString WorldData::serverName () const {return _d->srv.serverName();};
/*inline*/ QString WorldData::worldName () const {return _d->srv.worldName();};

/*inline*/ QVector <Island>     &WorldData::islands ()  {return _d->islands;};
/*inline*/ QVector <Ally>       &WorldData::allys ()    {return _d->allys;};
/*inline*/ QVector <Town>       &WorldData::towns ()    {return _d->towns;};
/*inline*/ QVector <Player>     &WorldData::players ()  {return _d->players;};

/*inline*/ QVector <PlanList>   &WorldData::mytowns()   {return _d->mytowns;};
/*inline*/ QVector <PlanList>   &WorldData::targets()   {return _d->targets;};
/*inline*/ QVector <PlanList>   &WorldData::plans()     {return _d->plans;};

/*inline*/ const QVector <Island>   &WorldData::islands () const  {return _d->islands;};
/*inline*/ const QVector <Ally>     &WorldData::allys () const    {return _d->allys;};
/*inline*/ const QVector <Town>     &WorldData::towns () const    {return _d->towns;};
/*inline*/ const QVector <Player>   &WorldData::players () const  {return _d->players;};

/*inline*/ const QVector <PlanList> &WorldData::mytowns() const   {return _d->mytowns;};
/*inline*/ const QVector <PlanList> &WorldData::targets() const   {return _d->targets;};
/*inline*/ const QVector <PlanList> &WorldData::plans() const     {return _d->plans;};

/*inline*/ int WorldData::playerIndex (int id) const {if(_d->player_hash.contains(id)) return _d->player_hash[id]; return -1;};
/*inline*/ int WorldData::allyIndex (int id) const {if(_d->ally_hash.contains(id)) return _d->ally_hash[id]; return -1;};
/*inline*/ int WorldData::townIndex (int id) const {if(_d->town_hash.contains(id)) return _d->town_hash[id]; return -1;};
/*inline*/ int WorldData::islandIndex (int id) const {if(_d->island_id_hash.contains(id)) return _d->island_id_hash[id]; return -1;};
/*inline*/ int WorldData::islandIndex (int x, int y) const {if(_d->island_hash.contains(x*1000 + y)) return _d->island_hash[x*1000 + y]; return -1;};

QHash<int, int> & WorldData::islandHash () {return _d->island_hash ;};
QHash<int, int> & WorldData::islandIdHash () {return _d->island_id_hash;};
QHash<int, int> & WorldData::allyHash () {return _d->ally_hash;};
QHash<int, int> & WorldData::playerHash () {return _d->player_hash;};
QHash<int, int> & WorldData::townHash () {return _d->town_hash;};

bool WorldData::init(const QString & server, GtProgress* prog) {return _d->init(server,prog,QDateTime());};
void WorldData::storeSettings (GtProgress* prog) {
	_d->storeSettings (prog);
	_d->storePlans ();
};

QPoint WorldData::townCoordinates (int idx)  const
{
	QPoint p = towns()[idx].pos;
	return QPoint (p.x()/12800, p.y()/12800);
}
QPoint WorldData::islandCoordinates (int idx) const 
{
	return QPoint (islands()[idx].pos.x(), islands()[idx].pos.y());// + islandCenterOffset (idx);
}
int WorldData::oceanNumberOfTown (int idx)  const
{
	return oceanNumberFromMapCoords (towns()[idx].pos);
}
int WorldData::oceanNumberOfIsland (int idx)  const
{
	return oceanNumberFromMapCoords (islandCoordinates (idx));
}

int WorldData::oceanNumberFromTownCoords  (const QPoint& p)
{
	return p.x() * 10 + p.y(); 
}

int WorldData::oceanNumberFromMapCoords  (const QPoint& p)
{
	return oceanNumberFromTownCoords (QPoint (p.x()/12800,p.y()/12800)); 
}

QString WorldData::playerLabelText (int p) const
{
	if (p<0) return QString("<img src=':/icons/icons/ghost.ico' width=16 height=16> %1 ").arg(tr("Ghost town"));
	return QString("<img src=':/icons/icons/player.ico' width=16 height=16> %1 ").arg(players()[p].name);
}

QString WorldData::allyLabelText (int a) const
{
	if(a<0) return "";
	return QString("<img src=':/icons/icons/ally.ico' width=16 height=16> %1 ").arg(allys()[a].name);
}

QString WorldData::TownLabelText (int t, bool tooltipp) const
{
	if (t<0) return "";
	QString tn = QString("<img src=':/icons/icons/town.ico' width=16 height=16> %1 ").arg(towns()[t].name);
	QString tpn = QString("<img src=':/icons/icons/points.ico' width=16 height=16> %1 ").arg(towns()[t].points);
	int pi = towns()[t].player_index;
	QString pn = playerLabelText (pi);
	QString an = "";
	if(towns()[t].ghost) {
		if(pi<0) {
			pn = QString("<img src=':/icons/icons/ghost.ico' width=16 height=16> %1 ").arg(tr("Ghost town"));
		} else {
			pn = QString("<img src=':/icons/icons/player.ico' width=16 height=16> %1 ").arg(players()[pi].name);
			an = QString("<img src=':/icons/icons/ghost.ico' width=16 height=16> %1 ").arg(tr("Ghost town"));
		}
	} else {
		an = allyLabelText (players()[pi].ally_index);		
	}




	if (tooltipp) {
		QString r ("<b>");
		r += tn; 
		r += "<br>";
		r += tpn;
		r += "<br>";
		r += pn;
		if (an.length()) {
			r += "<br>";
			r += an;
		}
		r+= "</b>";
		return r;
	}
	QString r ("<b>");
	r += tn; 
	r += "<br>";
	r += pn;
	if (an.length() ){
		r += an;
	}
	r+= "</b>";
	return r;
}


QString WorldData::TownLabelText (const QString& to, int pl, int al, bool tooltipp) const
{
	if (to<0) return "";
	QString tn = QString("<img src=':/icons/icons/town.ico' width=16 height=16> %1 ").arg(to);
	
	QString pn = "";
	if (pl>=0) pn = playerLabelText (pl);
	QString an = "";
	if(al>=0) an = allyLabelText (al);
	if(pl<0) {
		pn = QString("<img src=':/icons/icons/ghost.ico' width=16 height=16> %1 ").arg(tr("Ghost town"));
	}

	if (tooltipp) {
		QString r ("<b>");
		r += tn; 
		r += "<br>";
		r += pn;
		if (an.length()) {
			r += "<br>";
			r += an;
		}
		r+= "</b>";
		return r;
	}
	QString r ("<b>");
	r += tn; 
	r += "<br>";
	r += pn;
	if (an.length() ){
		r += an;
	}
	r+= "</b>";
	return r;
}



QVector <int> WorldData::filteredAllys ()
{
	QVector<int> r;
	for (int i=0;i < _global._d->allys.size();++i) {
		const Ally& al = _global._d->allys[i];
		if(!al.alive) continue;
		// else if(!al.points) continue;
		r.push_back(i);
	}
	return r;
}

QVector <int> WorldData::filteredTowns () 
{
	int player= -1;
	int ally = -1;
	getTownFilter (player,ally);
	QVector <int> r;
	for(int i=0;i< _global._d->towns.size();++i) {
		const Town& to = _global._d->towns[i];
		if(!to.alive) continue;
		if(!to.points) continue;
		
		if (player >= 0) {
			if (to.ghost)  continue;
			if(to.player_id != player) continue;
		} else if (ally >= 0) {
			if (to.ghost)  continue;
			if (to.ally_id != ally) continue;
		} else {
			if (!to.ghost)  continue;
		}
		r.push_back(i);
	}
	return r;
}

QVector <int> WorldData::filteredPlayers () 
{
	int ally = -1;
	getPlayerFilter (ally);
	QVector <int> r;
	for(int i=0;i< _global._d->players.size();++i) {
		const Player& pl = _global._d->players[i];
		if(!pl.alive) continue;
		if(pl.ally_id != ally) continue;
		r.push_back(i);
	}
	return r;
}



QVector <int> WorldData::search (const SearchData & s)
{
	QVector <int> r;
	QVector <QPoint> pos;
	QVector <double> mxd2;
	
	PlanList &l = currentMyTownsList ();
	for (int i=0; i<l.plans.size(); ++i) {
		int ti = l.plans[i].source_id;
		if (ti<0) continue;
		ti = _global.townIndex(ti);
		if (ti<0) continue;
		const Town & to = _global._d->towns[ti];
		if (!to.alive) continue;
		int m = l.plans[i].maxDistanceForTravelTime (s.time);
		if (m == 0) continue;
		pos.push_back(to.pos);
		
		mxd2.push_back((double)m * (double)m);
	}
	double maxd2 = s.dist;
	maxd2 *= maxd2;
	QDateTime ct = QDateTime::currentDateTime ();
	for (int i=0;i<_global._d->towns.size();++i) {
		const Town & to = _global._d->towns[i];
		if (!to.alive) continue;
		if (to.ghost && !s.ghosts) continue;
		if (s.useocean && to.ocean != s.ocean) continue;
		if ( s.usedist ) {
			QPoint di = to.pos - s.mapcenter;
			double dx = di.x() ; double dy = di.y();
			double d2 = dx*dx+dy*dy;
			if (d2 > maxd2) continue;
		}
		if (s.useallys) {
			if (!to.ghost) {
				if (!s.allys.contains (to.ally_id)) continue;
			}
		}
		if ( s.useinact ) {
			if (!to.ghost) {
				const Player & pl = _global._d->players[to.player_index];
				int secs = pl.act.secsTo (ct);
				if (secs < s.useinact) continue;
			}
		}
		if (s.usetime) {
			bool ok= false;
			for (int j = 0 ; j < mxd2.size(); ++j) {
				QPoint di = to.pos - pos[j];
				double dx = di.x() ; double dy = di.y();
				double d2 = dx*dx+dy*dy;
				if (d2 < mxd2[j]){
					ok=true;
					break;
				}				
			}
			if (!ok) continue;
		}

		r.push_back (i);
	}
	return r;
}


QString  WorldData::townSpecialText (int town, bool text) const
{
	QString r ;
	if(towns()[town].data) {
	if (text) {
		if(towns()[town].data->research.val[ResearchMeteorology]) r += tr("Meteorology");
		if(towns()[town].data->research.val[ResearchCartography]) {
			if (!r.isEmpty()) r+=";";
			r += tr("Cartography");
		}
		if(towns()[town].data->buildings.val[Lighthouse])  {
			if (!r.isEmpty()) r+=";";
			r += tr("Lighthouse");
		}
		return r;
	} else {
		if(towns()[town].data->research.val[ResearchMeteorology]){
			r+= QString("<img src=':/icons/research/meteorology.png' width=20 height=20>:%1").arg(tr("Meteorology"));
		}
		if(towns()[town].data->research.val[ResearchCartography]){
			if (!r.isEmpty()) r+="<br>"; 
			r+= QString("<img src=':/icons/research/cartography.png' width=20 height=20>:%1").arg(tr("Cartography"));
		}
		if(towns()[town].data->buildings.val[Lighthouse]){
			if (!r.isEmpty()) r+="<br>"; 
			r+= QString("<img src=':/icons/buildings/lighthouse.png' width=20 height=20>:%1").arg(tr("Lighthouse"));
		}
	}
	}
	return QString("<p align=vcenter>")+r+"</p>";
}

QString WorldData::townTypeText(TownTypeIndex t, bool tooltipp)
{
	QString r; 
	if(t == TownTypeUndefined) {
		r = tr("Undefined");
	} else if (t == TownTypeAtt) {      // rect  
		r = tr("Off");
	} else if (t == TownTypeDeff) {      // Triangle
		r = tr("Def");
	} else if (t == TownTypeAttShip) {   // raute
		r = tr("Attships");
	} else if (t == TownTypeAttKolo) {   // rect+hat
		r = tr("Att + Kolo");
	} else if (t == TownTypeBireme) {   // Tri down
		r = tr("Biris");
	} else if (t == TownTypeManti) {     // star
		r = tr("Mantis");
	} else if (t == TownTypePega) {      // Rect with slash
		r = tr("Pegasoi");
	} else if (t == TownTypeHarpy) {    //  rect with backslash
		r = tr("Harpys");
	}
	if (!tooltipp) return r;
	return bbCodeLabel (r, QString (":/icons/icons/town_type%1.png").arg((int)t),20);
}








void WorldData::setTownFilter (int player, int ally)
{
	setSetting ("TownFilterPlayer", player);
	setSetting ("TownFilterAlly", ally);
}
void WorldData::getTownFilter (int &player, int &ally)
{
	ally = setting("TownFilterAlly", -1).toInt();
	player = setting("TownFilterPlayer", -1).toInt();
}
void WorldData::setPlayerFilter (int ally)
{
	setSetting ("PlayerFilterAlly", ally);
}
void WorldData::getPlayerFilter (int &ally)
{
	ally = setting("PlayerFilterAlly", -1).toInt();
}
void WorldData::setLastSelAlly (int ally)
{
	setSetting ("SelectedAlly", ally);
}
void WorldData::getLastSelAlly (int &ally)
{
	ally = setting("SelectedAlly", -1).toInt();
}
void WorldData::setLastSelPlayer (int ally)
{
	setSetting ("SelectedPlayer", ally);
}
void WorldData::getLastSelPlayer (int &ally)
{
	ally = setting("SelectedPlayer", -1).toInt();
}
void WorldData::setLastSelTown(int ally)
{
	setSetting ("SelectedTown", ally);
}
void WorldData::getLastSelTown (int &ally)
{
	ally = setting("SelectedTown", -1).toInt();
}

int WorldData::currentMyTownsListIndex ()
{
	return setting("CurrentMyTownsList", 0).toInt();
}
void WorldData::setCurrentMyTownsListIndex (int i)
{
	setSetting("CurrentMyTownsList", i);
}

int WorldData::currentTargetListIndex ()
{
	return setting("CurrentTargetList", 0).toInt();
}
void WorldData::setCurrentTargetListIndex (int i)
{
	setSetting("CurrentTargetList", i);
}

int WorldData::currentPlansListIndex ()
{
	return setting("CurrentPlansList", 0).toInt();
}
void WorldData::setCurrentPlansListIndex (int i)
{
	setSetting("CurrentPlansList", i);
}

PlanList& WorldData::currentMyTownsList ()
{
	int ci = currentMyTownsListIndex();
	while (ci >= _global._d->mytowns.size()) {
		_global._d->mytowns.push_back (PlanList ());
	}
	return _global._d->mytowns [ci];
}

PlanList& WorldData::currentTargetList ()
{
	int ci = currentTargetListIndex();
	while (ci >= _global._d->targets.size()) {
		_global._d->targets.push_back (PlanList ());
	}
	return _global._d->targets [ci];
}

PlanList& WorldData::currentPlansList ()
{
	int ci = currentPlansListIndex();
	while (ci >= _global._d->plans.size()) {
		_global._d->plans.push_back (PlanList ());
	}
	return _global._d->plans [ci];
}
