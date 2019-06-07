#ifndef __GT_STATS_H
#define __GT_STATS_H
/* 
GtStats
*/

#include <QDateTime>
#include <QVariant>
#include <QVector>
#include <QObject>
#include <QDataStream>

#include <GtDatabase.h>

#ifdef EXPORT 
# undef EXPORT
#endif
#ifdef BUILDING_GTLIB
# define EXPORT DLL_EXPORT
#else
# define EXPORT DLL_IMPORT
#endif


class EXPORT PlayerStats {
public:
	PlayerStats ():_alive(false),_points(true),_off(true),_deff(true){};
	void restore (QDataStream & s) {
		s >> _name;
		s >> _ally_id;
		s >> _ntowns;
		s >> _points;
		s >> _off;
		s >> _deff;
	};
	void store (QDataStream & s) const {
		s << _name;
		s << _ally_id;
		s << _ntowns;
		s << _points;
		s << _off;
		s << _deff;
	};
	void condense () {
		_name.condenseOldEntries ();
		_ally_id.condenseOldEntries ();
		_ntowns.condenseOldEntries ();
		_points.condenseOldEntries ();
		_off.condenseOldEntries ();
		_deff.condenseOldEntries ();
	};
	bool     _alive;
	DataBase _name;
    DataBase _ally_id;
    DataBase _ntowns;
    DataBase _points;
    DataBase _off;
    DataBase _deff;
};
QDataStream& operator << (QDataStream &st,const PlayerStats& s);
QDataStream& operator >> (QDataStream &st,PlayerStats& s);

class EXPORT AllyStats {
public:
	AllyStats ():_alive(false),_points(true),_off(true),_deff(true){};
	void restore (QDataStream & s) {
		s >> _name;
		s >> _nplayers;
		s >> _ntowns;
		s >> _points;
		s >> _off;
		s >> _deff;
	};
	void store (QDataStream & s) const {
		s << _name;
		s << _nplayers;
		s << _ntowns;
		s << _points;
		s << _off;
		s << _deff;
	};
	bool     _alive;
	void condense () {
		_name.condenseOldEntries ();
		_nplayers.condenseOldEntries ();
		_ntowns.condenseOldEntries ();
		_points.condenseOldEntries ();
		_off.condenseOldEntries ();
		_deff.condenseOldEntries ();
	};
	DataBase _name;
    DataBase _nplayers;
    DataBase _ntowns;
    DataBase _points;
    DataBase _off;
    DataBase _deff;
};
QDataStream& operator << (QDataStream &st,const AllyStats& s);
QDataStream& operator >> (QDataStream &st,AllyStats& s);

class EXPORT TownStats {
public:
	TownStats ():_alive(false),_points(true){};
	void restore (QDataStream & s) {
		s >> _name;
		s >> _player_id;
		s >> _ally_id;
		s >> _points;
		for(int i=0;i< _player_id.size(); ++i) {
			if(!_player_id[i].data().toInt()) {
				_player_id[i].data() = -1;
			}
		}
		for(int i=0;i< _ally_id.size(); ++i) {
			if(!_ally_id[i].data().toInt()) {
				_ally_id[i].data() = -1;
			}
		}
	};
	void store (QDataStream & s) const {
		s << _name;
		s << _player_id;
		s << _ally_id;
		s << _points;
	};
	void condense () {
		_name.condenseOldEntries ();
		_player_id .condenseOldEntries ();
		_ally_id.condenseOldEntries ();
		_points.condenseOldEntries ();
	};
	bool     _alive;
	DataBase _name;
    DataBase _player_id;
    DataBase _ally_id;
    DataBase _points;
};
QDataStream& operator << (QDataStream &st,const TownStats& s);
QDataStream& operator >> (QDataStream &st,TownStats& s);


class EXPORT TownInfo {
public:
	TownInfo (){};
	TownInfo (int id,int x,int y, int n):_id(id),_island_x(x),_island_y(y),_pos_on_island(n){};
	TownInfo (const TownInfo& o) {*this= o;}; 
	TownInfo & operator = (const TownInfo& o) {
	  _id = o._id;
	  _island_x = o._island_x;
	  _island_y = o._island_y;
	  _pos_on_island= o._pos_on_island;
	  return *this;
	}; 
	void restore (QDataStream & s) {
		s >> _id;
		s >> _island_x;
		s >> _island_y;
		s >> _pos_on_island;
	};
	void store (QDataStream & s) const {
		s << _id;
		s << _island_x;
		s << _island_y;
		s << _pos_on_island;
	};

	int  _id;
	int  _island_x;
	int  _island_y;
	int  _pos_on_island;
};
QDataStream& operator << (QDataStream &st,const TownInfo& s);
QDataStream& operator >> (QDataStream &st,TownInfo& s);


class EXPORT IslandInfo {
public:
	IslandInfo (){};
	IslandInfo (int id,int x,int y, int type):_id(id),_x(x),_y(y),_type(type){};
	IslandInfo (const IslandInfo& o) {*this= o;}; 
	IslandInfo & operator = (const IslandInfo& o) {
	  _id = o._id;
	  _x = o._x;
	  _y = o._y;
	  _type = o._type;
	  return *this;
	}; 
	void restore (QDataStream & s) {
		s >> _id;
		s >> _x;
		s >> _y;
		s >> _type;
	};
	void store (QDataStream & s) const {
		s << _id;
		s << _x;
		s << _y;
		s << _type;
	};

	int  _id;
	int  _x;
	int  _y;
	int  _type;
};

QDataStream& operator << (QDataStream &st,const IslandInfo& s);
QDataStream& operator >> (QDataStream &st,IslandInfo& s);


class Player;
class Ally;
class Town;
class Island;
class GtProgress;


struct PlayerStatsDat {
	int  id; 
	uint last_obs; 
	uint first_obs;
	bool alive;
	int  off_bash_1;
	int  off_bash_3;
	int  off_bash_7;
	int  def_bash_1;
	int  def_bash_3;
	int  def_bash_7;
	int  cur_ally;
	int  last_ally;
	int  chg_time;
};

struct TownStatsDat {
	int   id; 
	bool alive;
	bool ghost;
	uint  last_obs; 
	uint  first_obs; 
	int   current_owner;
	int   last_owner;
	uint  chg_time;
};

struct AllyStatsDat {
	int  id; 
	int  last_obs; // 0 = allive
	int  new_members_7;
	int  last_owner;
	int  chg_time;
};



class EXPORT Stats {
	Q_DECLARE_TR_FUNCTIONS (WorldData);

public:
	Stats ();

	bool loadV1 (const QString& fn, GtProgress* prog); 
	bool save   (const QString& fn, GtProgress* prog); 
	bool update (const QString& dir, GtProgress* prog); 

	void handlePlayer         (int id, const QString &name, int points, int ally_id, int ntowns);
	void handlePlayerOffBash  (int player_id, int bash);
	void handlePlayerDefBash  (int player_id, int bash);
	void handleAlly           (int id, const QString &name, int points, int nplayers, int ntowns);
	void handleTown           (int id, const QString &name, int points, int player_id, int x, int y, int n);
	void handleIsland         (int id, int x, int y, int type);
	void handleConquest       (int timestamp, int town_id, int points, int old_player_id, int old_ally_id, int new_player_id, int new_ally_id);

	bool townHistory (int id,  QVector<QDateTime> &start, QVector<QDateTime> &end,  QVector<int> &own  ) const;
	bool playerHistory (int id,  QVector<QDateTime> &st, QVector<int> &ally  ) const;

	QList<int> allyIds ()const {return _ally_hash.keys();};
	QList<int> playerIds()const {return _player_hash.keys();};
	QList<int> townIds () const {return _town_hash.keys();};
	int        numIslands () const {return _island_info.size();};

	void initPlayer (int id, Player & pl, const QDateTime &t) const; 
	void initAlly   (int id, Ally & al, const QDateTime &t) const; 
	void initTown   (int id, Town & to, const QDateTime &t) const; 
	void initIsland (int n, Island & to) const; 

	QDateTime worldStart () const {return _db_start;};
	QDateTime worldEnd () const {return _db_end;};

	int version() const {return _version;};

	bool playerStats (PlayerStatsDat& pl) const;
	bool allyStats (AllyStatsDat& al) const;
	bool townStats (TownStatsDat& to) const;

	void condense () {
		for(int i=0;i<_players.size(); ++i) {
			_players[i].condense();
		}
		for(int i=0;i<_allys.size(); ++i) {
			_allys[i].condense();
		}
		for(int i=0;i<_towns.size(); ++i) {
			_towns[i].condense();
		}
	};
private:
	QDateTime _db_start;
	QDateTime _db_end;

	int _version;

	QHash <int,int>   _player_hash;
	QHash <int,int>   _ally_hash;
	QHash <int,int>   _town_hash;
	QHash <int,int>   _town_info_hash;

	PlayerStats & player (int id);
	AllyStats & ally (int id);
	TownStats & town (int id);
	const PlayerStats & player (int id)const ;
	const AllyStats & ally (int id)const ;
	const TownStats & town (int id)const ;

	QVector <PlayerStats> _players;
	QVector <AllyStats>   _allys;
	QVector <TownStats>   _towns;
	QVector <TownInfo>    _town_info;
	QVector <IslandInfo>    _island_info;
	DataBase                _num_players;
	DataBase                _num_allyless;
	DataBase                _num_towns;
	DataBase                _num_ghosts;
	DataBase                _num_allys;
};

#endif