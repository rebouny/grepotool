/* database.cpp - databases

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
/* CHANGES:

24.07.14 Pete     Adapted to changes in file structure of islands.txt

*/

#include <QFile>
#include <GtProgress.h>
#include <GtApp.h>
#include "GtDatabase.h"
#include "GtStats.h"
#include "GtPlayers.h"
#include "GtTowns.h"
#include "GtAllys.h"
#include "GtIslands.h"

QDataStream& operator << (QDataStream &st,const PlayerStats& s){s.store(st);return st;};
QDataStream& operator >> (QDataStream &st,PlayerStats& s){s.restore(st);return st;};
QDataStream& operator << (QDataStream &st,const TownStats& s){s.store(st);return st;};
QDataStream& operator >> (QDataStream &st,TownStats& s){s.restore(st);return st;};
QDataStream& operator << (QDataStream &st,const TownInfo& s){s.store(st);return st;};
QDataStream& operator >> (QDataStream &st,TownInfo& s){s.restore(st);return st;};
QDataStream& operator << (QDataStream &st,const IslandInfo& s){s.store(st);return st;};
QDataStream& operator >> (QDataStream &st,IslandInfo& s){s.restore(st);return st;};
QDataStream& operator << (QDataStream &st,const AllyStats& s){s.store(st);return st;};
QDataStream& operator >> (QDataStream &st,AllyStats& s){s.restore(st);return st;};


bool Stats::playerStats (PlayerStatsDat& pl) const
{
	if(!_player_hash.contains(pl.id)) return false;
	const PlayerStats &p  = _players[_player_hash[pl.id]];
	pl.alive = p._alive;
	pl.last_obs = p._name.lastObservation().toTime_t(); 
	pl.first_obs = p._name.firstObservation().toTime_t();

	int ct = QDateTime::currentDateTime ().toTime_t();
	int d1 = 24*60*60;
	int coff = p._off.currentValue().toInt();
	int cdef = p._deff.currentValue().toInt();
	
	pl.off_bash_1 = coff-p._off.valueAt(QDateTime::fromTime_t (ct-d1)).toInt();
	pl.off_bash_3 = coff-p._off.valueAt(QDateTime::fromTime_t (ct-3*d1)).toInt();
	pl.off_bash_7 = coff-p._off.valueAt(QDateTime::fromTime_t (ct-7*d1)).toInt();
	pl.def_bash_1 = cdef-p._deff.valueAt(QDateTime::fromTime_t (ct-d1)).toInt();
	pl.def_bash_3 = cdef-p._deff.valueAt(QDateTime::fromTime_t (ct-3*d1)).toInt();
	pl.def_bash_7 = cdef-p._deff.valueAt(QDateTime::fromTime_t (ct-7*d1)).toInt();
	
	pl.cur_ally = p._ally_id.currentValue().toInt();
	pl.last_ally = p._ally_id.previousValue(pl.cur_ally).toInt();
	pl.chg_time = p._ally_id.lastChange().toTime_t();
	return true;
}

bool Stats::allyStats (AllyStatsDat& al) const
{
	if(!_ally_hash.contains(al.id)) return false;
	return true;
}

bool Stats::townStats (TownStatsDat& to) const
{
	if(!_town_hash.contains(to.id)) return false;
	const TownStats &t  = _towns[_town_hash[to.id]];
	to.alive = t._alive;
	to.last_obs = t._name.lastObservation ().toTime_t ();
	to.first_obs = t._name.firstObservation ().toTime_t ();
	to.current_owner = t._player_id.currentValue().toInt();
	to.ghost = to.current_owner < 0;
	to.last_owner = t._player_id.previousValue(to.current_owner).toInt();
	to.chg_time = t._player_id.lastChange ().toTime_t();
	return true;
}

bool Stats::townHistory (int id, QVector<QDateTime> &st, QVector<QDateTime> &en,  QVector<int> &own  ) const
{
	if(!_town_hash.contains(id)) return false;
	const TownStats &t  = _towns[_town_hash[id]];

	for(int i=0;i< t._player_id.size(); ++i) {
		const DbEntry &e = t._player_id[i];
		st.push_back (e.startDateTime ());
		en.push_back (e.endDateTime ());
		own.push_back(e.data().toInt());
	}

	return true;
}

bool Stats::playerHistory (int id,  QVector<QDateTime> &st, QVector<int> &ally  ) const
{
	if(!_player_hash.contains(id)) return false;
	const PlayerStats &pl  = _players[_player_hash[id]];

	for(int i=0;i< pl._ally_id.size(); ++i) {
		const DbEntry &e = pl._ally_id[i];
		st.push_back (e.startDateTime ());		
		ally.push_back(e.data().toInt());
	}

	return true;
}

void Stats::handlePlayer (int id, const QString &name, int points, int ally_id, int ntowns)
{
	_db_end = QDateTime::currentDateTime();
	if(!_db_start.isValid()) _db_start = _db_end;
	PlayerStats &p = player(id);
	p._alive=true;
	p._name.addValue(name);
	p._points.addValue(points);
	p._ally_id.addValue(ally_id);
	p._ntowns.addValue(ntowns);
}

void Stats::handlePlayerOffBash  (int id, int def)
{
	PlayerStats &p = player(id);
	p._off.addValue (def);
}

void Stats::handlePlayerDefBash  (int id, int def)
{
	PlayerStats &p = player(id);
	p._deff.addValue (def);
}

void Stats::initPlayer (int id, Player & pl, const QDateTime &t) const
{
	const PlayerStats &p = _players[_player_hash[id]];
	pl.id          = id;
	pl.alive       = p._alive;
	pl.first_obs   = p._name.firstObservation();
	pl.last_obs    = p._name.lastObservation ();
	pl.name        = p._name.valueAt (t).toString();
	pl.ally_id     = p._ally_id.valueAt (t).toInt();
	pl.points      = p._points.valueAt (t).toInt();
	pl.off         = p._off.valueAt (t).toInt();;
	pl.def         = p._deff.valueAt (t).toInt();;
	pl.bash        = pl.off+pl.def;
	pl.ally_index  = -1;
	pl.points_act  = p._points.lastIncrease();
	pl.off_act     = p._off.lastIncrease();
	pl.def_act     = p._deff.lastIncrease();
	pl.act         = (pl.off_act>pl.points_act)? pl.off_act : pl.points_act;
	pl.towns.clear();


	int ct = QDateTime::currentDateTime ().toTime_t();
	int d1 = 24*60*60;
	int coff = p._off.currentValue().toInt();
	int cdef = p._deff.currentValue().toInt();
	
	pl.off1 = coff-p._off.valueAt(QDateTime::fromTime_t (ct-d1)).toInt();
	pl.off3 = coff-p._off.valueAt(QDateTime::fromTime_t (ct-3*d1)).toInt();
	pl.off7 = coff-p._off.valueAt(QDateTime::fromTime_t (ct-7*d1)).toInt();
	pl.def1 = cdef-p._deff.valueAt(QDateTime::fromTime_t (ct-d1)).toInt();
	pl.def3 = cdef-p._deff.valueAt(QDateTime::fromTime_t (ct-3*d1)).toInt();
	pl.def7 = cdef-p._deff.valueAt(QDateTime::fromTime_t (ct-7*d1)).toInt();
	


}


void Stats::handleAlly   (int id, const QString &name, int points, int nplayers, int ntowns)
{
	AllyStats & p = ally (id);
	p._alive = true;
	p._name.addValue(name);
	p._points.addValue(points);
	p._nplayers.addValue(nplayers);
	p._ntowns.addValue(ntowns);	
}

void Stats::initAlly   (int id, Ally & al, const QDateTime &t)  const
{
	const AllyStats &a = _allys[_ally_hash[id]];
	al.id          = id;
	al.alive       = a._alive;
	al.first_obs   = a._name.firstObservation();
	al.last_obs    = a._name.lastObservation ();
	al.name        = a._name.valueAt (t).toString();
	al.points      = a._points.valueAt(t).toInt();
	al.off = 0;
	al.def = 0;
	al.bash = 0;
	al.players.clear();
	al.towns.clear();
}

void Stats::handleIsland (int id, int x, int y, int type)
{
	IslandInfo ii ;
	ii._id=id;
	ii._x=x;
	ii._y=y;
	ii._type=type;
	_island_info.push_back (ii);
}


void Stats::handleTown   (int id, const QString &name, int points, int player_id, int x, int y, int n)
{
	if (!_town_info_hash.contains(id)) {
		_town_info_hash[id] = _town_info.size();
		_town_info.push_back (TownInfo (id,x,y,n));
	}

	TownStats &t = town(id);
	t._name.addValue(name);
	t._points.addValue(points);
	t._player_id.addValue(player_id);
	t._alive = true;
	if (player_id<0) return;
	PlayerStats &p = player(player_id);
	int ally = p._ally_id.currentValue().toInt();
	t._ally_id.addValue(ally);
}

void Stats::initTown   (int id, Town & to, const QDateTime &tim) const
{
	const TownStats &t  = _towns[_town_hash[id]];
	QString td = tim.toString();
	QString ttd = t._name.lastObservation ().toString();


	to.id          = id;
	to.ghost       = false;
	to.alive       = t._alive;
	to.first_obs   = t._name.firstObservation();
	to.last_obs    = t._name.lastObservation ();
	to.name        = t._name.valueAt (tim).toString();
	to.points      = t._points.valueAt(tim).toInt();
	to.ally_id     = t._ally_id.valueAt(tim).toInt();
	to.player_id   = t._player_id.valueAt(tim).toInt();
	to.player_index = -1;
	to.ally_index = -1;
	to.no = -1;
	to.last_owner_chg = t._player_id.lastChange();
	to.last_owner = t._player_id.previousValue (to.player_id).toInt();


	if (to.player_id <0) {
		to.ghost = true;
		to.ally_id     = t._ally_id.previousValue(tim,-1).toInt();
		to.player_id   = t._player_id.previousValue(tim,-1).toInt();
	} 

	if (!_town_info_hash.contains(id)) 
		return;
	const TownInfo & ti = _town_info[_town_info_hash[id]];
	to.x = ti._island_x;
	to.y = ti._island_y;
	to.no = ti._pos_on_island;
}

void Stats::initIsland (int n, Island & il) const
{
	const IslandInfo & ili = _island_info[n];
	il.id = ili._id;
	il.type = ili._type;
	il.x = ili._x;
	il.y = ili._y;
	
	if (il.x & 1) {
		il.pos = QPoint (il.x * 128, il.y*128+64 );
	} else {
		il.pos = QPoint (il.x * 128, il.y*128);
	}
}


void Stats::handleConquest  (int timestamp, int town_id, int points, int old_player_id, int old_ally_id, int new_player_id, int new_ally_id)
{
	QDateTime ti = QDateTime::fromTime_t(timestamp);
	QDateTime lti = QDateTime::fromTime_t(timestamp-1);
	TownStats & p = town(town_id);
	p._points.addValue (points,ti);
	p._player_id.addValue (old_player_id,lti);
	p._player_id.addValue (new_player_id,ti);
	p._ally_id.addValue (old_ally_id,lti);
	p._ally_id.addValue (new_ally_id,ti);
}

Stats::Stats ()
{
}


bool Stats::loadV1 (const QString& fn, GtProgress * prog)
{
	QByteArray ba =  readZipFile  (fn);
	if(!ba.size()) return false;
	QDataStream s(&ba,QIODevice::ReadOnly);
	s.setVersion (QDataStream::Qt_4_7);
	_version = 0;
	s >> _version;
	QList<int> aid;
	QList<int> pid;
	QList<int> tid;
	s>>aid;
	s>>pid;
	s>>tid;

	int nti = 0;
	int nii = 0;

	qint64 n = 0;
	qint64 ntot = aid.size() + pid.size() + tid.size();
	if (_version > 1) {
		s >> nti;
		s >> nii;
		ntot += nti;
		ntot += nii;		
	}

	_db_start =QDateTime::currentDateTime();
	for (int i=0;i< aid.size();++ i) {
		prog->setProgress(n++, ntot);
		GtApp::processEvents();
		AllyStats a; 
		s>>a; 
		_allys.push_back(a);
		_ally_hash[aid[i]] = i;
	}
	for (int i=0;i< pid.size();++ i) {
		prog->setProgress(n++, ntot);
		GtApp::processEvents();
		PlayerStats a; 
		s>>a; 
		_players.push_back(a);
		_player_hash[pid[i]] = i;
		if (a._name.firstObservation() < _db_start) 
			_db_start = a._name.firstObservation();
		if (!_db_end.isValid() || a._name.lastObservation() > _db_end) 
			_db_end = a._name.lastObservation();		
	}
	for (int i=0;i< tid.size();++ i) {
		prog->setProgress(n++, ntot);
		GtApp::processEvents();
		TownStats a; 
		s>>a;
		_towns.push_back( a) ;
		_town_hash[tid[i]] = i;
	}

	s >> _num_players;
	s >> _num_allyless;
	s >> _num_towns;
	s >> _num_ghosts;
	s >> _num_allys;

	if ( _version < 2 ) return true;
	for (int i=0;i<nti;++i) {
		prog->setProgress(n++, ntot);
		GtApp::processEvents();
		TownInfo ti;
		s >> ti;
		_town_info_hash[ti._id] = i;
		_town_info.push_back (ti);
	}
	for (int i=0;i<nii;++i) {
		prog->setProgress(n++, ntot);
		GtApp::processEvents();
		IslandInfo ii;
		s >> ii;
		_island_info.push_back (ii);
	}

	if ( _version < 3 ) return true;
	QVector <bool> tall;
	QVector <bool> pall;
	QVector <bool> aall;
	s >> tall;
	s >> pall;
	s >> aall;
	for (int i=0;i< aid.size();++ i) {
		_allys[i]._alive = aall[i];
	}
	for (int i=0;i< pid.size();++ i) {
		_players[i]._alive = pall[i];
	}
	for (int i=0;i< tid.size();++ i) {
		_towns[i]._alive = tall[i];
	}
	condense ();
	return true;
}

bool Stats::save (const QString& fn,GtProgress * prog)
{
	QByteArray ba;
	QDataStream s(&ba,QIODevice::WriteOnly);
	s.setVersion (QDataStream::Qt_4_7);

	_version = 3;
	s << _version;
	QList<int> aid = _ally_hash.keys();
	QList<int> pid = _player_hash.keys();
	QList<int> tid = _town_hash.keys();
	s<<aid;
	s<<pid;
	s<<tid;
	int nti = _town_info.size();
	s << nti;
	int nii = _island_info.size();
	s << nii;

	qint64 n = 0;
	qint64 ntot = aid.size() + pid.size() + tid.size() + nti + nii;

	for (int i=0;i< aid.size();++ i){
		prog->setProgress(n++, ntot);
		GtApp::processEvents();
		
		s << _allys[_ally_hash[aid[i]]];
	}
	for (int i=0;i< pid.size();++ i){
		prog->setProgress(n++, ntot);
		GtApp::processEvents();
		s << _players[_player_hash[pid[i]]];
	}
	for (int i=0;i< tid.size();++ i){
		prog->setProgress(n++, ntot);
		GtApp::processEvents();
		s << _towns[_town_hash[tid[i]]];
	}
	s << _num_players;
	s << _num_allyless;
	s << _num_towns;
	s << _num_ghosts;
	s << _num_allys;

	for (int i= 0;i<nti; ++i) {
		prog->setProgress(n++, ntot);
		GtApp::processEvents();
		s << _town_info[i];
	}
	for (int i= 0;i<nii; ++i) {
		prog->setProgress(n++, ntot);
		GtApp::processEvents();
		s << _island_info[i];
	}
	QVector <bool> tall;
	QVector <bool> pall;
	QVector <bool> aall;
	for (int i=0;i< aid.size();++ i) {
		aall.push_back(_allys[_ally_hash[aid[i]]]._alive);
	}
	for (int i=0;i< pid.size();++ i) {
		 pall.push_back(_players[_player_hash[pid[i]]]._alive);
	}
	for (int i=0;i< tid.size();++ i) {
		tall.push_back(_towns[_town_hash[tid[i]]]._alive);
	}
	s << tall;
	s << pall;
	s << aall;

	return writeZipFile (fn,ba);
}


PlayerStats & Stats::player (int id) {
	if(!_player_hash.contains(id)) {
		_player_hash[id] = _players.size();
		PlayerStats pl;
		_players.push_back (pl);
		//_players[_player_hash[id]]._alive = true;
	}
	return _players[_player_hash[id]];
};

AllyStats & Stats::ally (int id) {
	if(!_ally_hash.contains(id)) {
		_ally_hash[id] = _allys.size();
		AllyStats al;	
		_allys.push_back (al);
		// _allys[_ally_hash[id]]._alive = true;
	}
	return _allys[_ally_hash[id]];
};
TownStats & Stats::town (int id) {
	if(!_town_hash.contains(id)) {
		_town_hash[id] = _towns.size();
		TownStats to;
		_towns.push_back (to);
		// _towns[_town_hash[id]]._alive=true;
	}
	return _towns[_town_hash[id]];
};

const PlayerStats & Stats::player (int id) const {
	return _players[_player_hash[id]];
};

const AllyStats & Stats::ally (int id) const {
	return _allys[_ally_hash[id]];
};

const TownStats & Stats::town (int id)const  {
	return _towns[_town_hash[id]];
};

bool Stats::update (const QString& dir, GtProgress* prog)
{
	for(int i=0;i< _allys.size();++i) _allys[i]._alive = false;
	for(int i=0;i< _players.size();++i) _players[i]._alive = false;
	for(int i=0;i< _towns.size();++i) _towns[i]._alive = false;

	prog->setProgress(0,0);
	prog->setDescription(tr("updating world database"));	
	qApp->processEvents();
	QByteArray  island_array;	
	QByteArray  town_array    = readGZipFile (dir+ "/towns.txt.gz");
	QByteArray  ally_array    = readGZipFile (dir+ "/alliances.txt.gz");
	QByteArray  player_array  = readGZipFile (dir+ "/players.txt.gz");	
	QByteArray  off_array     = readGZipFile (dir+ "/player_kills_att.txt.gz");		
	QByteArray  def_array     = readGZipFile (dir+ "/player_kills_def.txt.gz");		
	QByteArray  conquer_array = readGZipFile (dir+ "/conquers.txt.gz");	
	int num_islands = 0;
	int num_towns = countLines(town_array);
	int num_allys = countLines(ally_array);
	int num_players = countLines(player_array);
	int num_off = countLines(off_array);
	int num_def = countLines(def_array);
	int num_conquer = countLines(conquer_array);
	if (0 == _island_info.size()) {
		island_array = readGZipFile (dir+ "/islands.txt.gz");	
		num_islands = countLines (island_array);
	}
	qint64 tot = num_islands;
	tot += num_towns;
	tot += num_allys;
	tot += num_players ;
	tot += num_off;
	tot += num_def;
	tot += num_conquer;
	qint64 cnt = 0;

	if (num_islands) {
		prog->setDescription(tr("updating islands"));	
		QTextStream ts (island_array);
		QString l = ts.readLine ();
		while (!l.isEmpty ()) {
			prog->setProgress (++cnt, tot);
			qApp->processEvents();

			// $id, $island_x, $island_y, $island_type_number, $available_towns 
			// 24.07.14 new file structure: $id, $island_x, $island_y, $island_type_number, $available_towns, $resources_advantage, $resources_disadvantage
			QStringList k = l.split(",");
			if(k.size() < 5) {
				prog->setError (tr("Failed to read island descriptions"));
				return false;
			}		
			int id= k[0].toInt();
			int x = k[1].toInt();
			int y = k[2].toInt();
			int type = k[3].toInt();
			handleIsland (id,x,y,type);
			l = ts.readLine ();
		}
	}

	if (num_towns) {
		prog->setDescription(tr("updating towns"));	
		QTextStream ts (town_array);
		QString l = ts.readLine ();
		while (!l.isEmpty ()) {
			prog->setProgress (++cnt, tot);
			qApp->processEvents();

			// $id, $player_id, $name, $island_x, $island_y, $slot_number_on_island, $points
			QStringList k = l.split(",");
			if(k.size()!= 7) {
				prog->setError (tr("Failed to read town descriptions"));
				qApp->processEvents();
				return false;
			}		
			int id = k[0].toInt();
			int player_id = -1;
			if(!k[1].isEmpty()) player_id = k[1].toInt();
			QString name = replaceStrangeChars(k[2]);
			int x = k[3].toInt();
			int y = k[4].toInt();
			int no = k[5].toInt();
			int points = k[6].toInt();
			handleTown (id,name,points,player_id, x, y, no);
			l = ts.readLine ();
		}
	}

	if (num_allys) {
		prog->setDescription(tr("updating allys"));	
		QTextStream ts (ally_array);
		QString l = ts.readLine ();
		while (!l.isEmpty ()) {
			prog->setProgress (++cnt, tot);
			qApp->processEvents();

			// $id, $name, $points, $towns, $members, $rank
			QStringList k = l.split(",");
			if(k.size()!= 6) {
				prog->setError (tr("Failed to read ally descriptions"));
				return false;
			}		
			int id = k[0].toInt();
			QString name = replaceStrangeChars(k[1]);
			int points = k[2].toInt();
			int towns = k[3].toInt();
			int players = k[4].toInt();
			handleAlly (id, name, points, players, towns);
			l = ts.readLine ();
		}
	}

	if (num_players) {
		prog->setDescription(tr("updating players"));	
		QTextStream ts (player_array);
		QString l = ts.readLine ();
		while (!l.isEmpty ()) {
			prog->setProgress (++cnt, tot);
			qApp->processEvents();

			// $id, $name, $alliance_id, $points, $rank, $towns
			QStringList k = l.split(",");
			if(k.size()!= 6) {
				prog->setError (tr("Failed to read player descriptions"));
				qApp->processEvents();
				return false;
			}		
			int id       = k[0].toInt();
			int ally    = -1;
			if (!k[2].isEmpty()) ally = k[2].toInt();
			QString name = replaceStrangeChars(k[1]);
			int points = k[3].toInt();
			int towns = k[5].toInt();
			handlePlayer (id, name, points, ally, towns);			
			l = ts.readLine ();
		}
	}

	if (num_off) {
		prog->setDescription(tr("updating bashpoints"));	
		QTextStream ts (off_array);
		QString l = ts.readLine ();
		while (!l.isEmpty ()) {
			prog->setProgress (++cnt, tot);
			qApp->processEvents();

			// $rank, $player_id, $points
			QStringList k = l.split(",");
			if(k.size()!= 3) {
				prog->setError (tr("Failed to read att bashpoints"));
				qApp->processEvents();
				return false;
			}		
			int id = k[1].toInt();
			int points = k[2].toInt();
			handlePlayerOffBash (id, points);
			l = ts.readLine ();
		}
	}
	if (num_def) {
		prog->setDescription(tr("updating bashpoints"));	
		QTextStream ts (def_array);
		QString l = ts.readLine ();
		while (!l.isEmpty ()) {
			prog->setProgress (++cnt, tot);
			qApp->processEvents();

			// $rank, $player_id, $points
			QStringList k = l.split(",");
			if(k.size()!= 3) {
				prog->setError (tr("Failed to read def bashpoints"));
				qApp->processEvents();
				return false;
			}		
			int id = k[1].toInt();
			int points = k[2].toInt();
			handlePlayerDefBash (id, points);
			l = ts.readLine ();
		}
	}

	if (num_conquer) {
		prog->setDescription(tr("updating conquers"));	
		QTextStream ts (conquer_array);
		QString l = ts.readLine ();
		while (!l.isEmpty ()) {
			prog->setProgress (++cnt, tot);
			qApp->processEvents();

			// $town_id, $time, $new_player_id, $old_player_id, $new_ally_id, $old_ally_id, $town_points 
			QStringList k = l.split(",");
			if(k.size()!= 7) {
				prog->setError (tr("Failed to read conquers"));
				return false;
			}		
			int town_id = k[0].toInt();
			int tim  = k[1].toInt();
			int new_player_id = k[2].isEmpty ()?-1:k[2].toInt();
			int old_player_id = k[3].isEmpty ()?-1:k[3].toInt();
			int new_ally_id = k[4].isEmpty ()?-1:k[4].toInt();
			int old_ally_id = k[5].isEmpty ()?-1:k[5].toInt();
			int points = k[6].toInt();
			handleConquest (tim, town_id, points,old_player_id,old_ally_id,new_player_id,new_ally_id);
			l = ts.readLine ();
		}
	}

	condense ();

	return true;
}

