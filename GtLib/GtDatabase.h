#ifndef __DATABASE_H
#define __DATABASE_H
/* database.h  - database handling

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

#include <QDateTime>
#include <QVariant>
#include <QVector>
#include <QDataStream>
#include <GtCore.h>

#ifdef EXPORT 
# undef EXPORT
#endif
#ifdef BUILDING_GTLIB
# define EXPORT DLL_EXPORT
#else
# define EXPORT DLL_IMPORT
#endif

/*! Database entry 
*/
class EXPORT DbEntry {
public: 
	DbEntry():_start(QDateTime::currentDateTime()){_end = _start;};
	DbEntry(const QVariant &v, const QDateTime & tim = QDateTime::currentDateTime()):_start(tim),_end(tim),_data(v){};
	DbEntry(const DbEntry& o):_start(o._start),_end(o._end),_data(o._data){};

	bool operator == (const DbEntry& o){
		return _data == o._data;
	};

	DbEntry & operator = (const DbEntry& o){
		_start  = o._start;
		_end    = o._end;
		_data   = o._data;
		return *this;
	};

	QDateTime startDateTime () const {return _start;};
	QDateTime endDateTime () const {return _end;};
	QDate     startDate () const {return _start.date();};
	QDate     endDate () const {return _end.date();};

	QVariant & data () {return _data;};
	const QVariant & data () const {return _data;};

	void setEnd (const QDateTime & e) {_end = e;};
	void setStart (const QDateTime & e) {_start = e;};

private:
	QDateTime _start;
	QDateTime _end;
	QVariant  _data;
};

/*! Database class

Data is either a numeric interpolatable value or a unique identifier such as
an id or a name
*/
class EXPORT DataBase {
public:
	bool interpolatable() const {return _interpolatable;};
	DataBase (bool interpolatable = false): _interpolatable(interpolatable) {};
	int size () const {return _db.size();};
	DataBase (const DataBase & o) : _interpolatable(o._interpolatable),_db(o._db){};
	DataBase & operator = (const DataBase & o) {
		_interpolatable = o._interpolatable;
		_db = o._db;
		return *this;
	};
	const DbEntry& operator [] (int i) const {return _db[i];};
	DbEntry& operator [] (int i){return _db[i];};

	void addValue (const QVariant& v, const QDateTime & tim = QDateTime::currentDateTime());
	int lastChangeEntry () const {return _db.size() -1;};
	int lastIncreaseEntry () const;
	
	QDateTime lastChange () const {if (!_db.size()) return QDateTime(); return _db[lastChangeEntry()].startDateTime();};
	QDateTime lastObservation () const {if (!_db.size()) return QDateTime(); return _db[lastChangeEntry()].endDateTime();};
	QDateTime firstObservation () const {if (!_db.size()) return QDateTime(); return _db[0].startDateTime();};
	QDateTime lastIncrease () const {if (!_db.size()) return QDateTime(); return _db[lastIncreaseEntry()].startDateTime();};

	QVariant valueAt (const QDateTime & tim) const;
	QVariant currentValue () const {if (!_db.size()) return QVariant(); return _db[_db.size()-1].data();};
	QVariant previousValue (const QDateTime &t = QDateTime::currentDateTime(), const QVariant &def = QVariant()) const;
	QVariant previousValue (const QVariant &def) const;

	bool alive (const QDateTime & tim, const QDateTime & latest_obs) const;


	int firstOfDay(const QDate & d) const;
	int lastOfDay(const QDate & d) const;
	int lastOfMonth (const QDate & d) const;

	void condenseOldEntries ();

	static void test();
	void dump ();
	
	void store (QDataStream & s) const;
	void restore (QDataStream & s);

private:
	bool _interpolatable;
	QVector < DbEntry > _db;
};
QDataStream& operator << (QDataStream &st,const DataBase& s);
QDataStream& operator >> (QDataStream &st,DataBase& s);

#endif