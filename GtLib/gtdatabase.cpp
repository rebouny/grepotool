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
#include <iostream>
#include "GtDatabase.h"
#include "GtData.h"

static void coutDate (const QDateTime & v) {
	QString k = v.toString("[dd.MM.-HH:mm:ss]");	
	std::cout << k.toLatin1().constData();
}
void DataBase::dump() {
	std::cout << "------------- start DataBase:\n";
	for(int i=0;i< size(); ++i) {
		std::cout << i <<": ";
		coutDate(_db[i].startDateTime());
		std::cout << "-";			
		coutDate(_db[i].endDateTime());
		std::cout << " : ";			
		QString k = _db[i].data().toString();
		std::cout << k.toLatin1().constData();
		std::cout << "\n";
	}
	std::cout << "------------- end DataBase:\n";

	std::cout << "last increase: ";		
	if(_db.size()) 
		coutDate(lastIncrease());
	else
		std::cout << " unknown";
	std::cout << "\n";
	std::cout << "-----\n";
};


void DataBase::test() 
{

	coutDate (QDateTime::fromString("13.11.13 12:30","dd.MM.yy HH:mm"));
	std::cout << "\n";

	DataBase d1(true);	
	d1.addValue (1, QDateTime::fromString("03.09.2013 12:30","dd.MM.yyyy HH:mm"));
	d1.addValue (3, QDateTime::fromString("10.09.2013 12:30","dd.MM.yyyy HH:mm"));
	d1.addValue (5, QDateTime::fromString("11.09.2013 12:30","dd.MM.yyyy HH:mm"));
	d1.addValue (2, QDateTime::fromString("13.10.2013 12:30","dd.MM.yyyy HH:mm"));
	d1.addValue (6, QDateTime::fromString("13.11.2013 12:30","dd.MM.yyyy HH:mm"));
	d1.addValue (2, QDateTime::fromString("13.11.2013 15:30","dd.MM.yyyy HH:mm"));
	d1.addValue (3, QDateTime::fromString("13.11.2013 19:30","dd.MM.yyyy HH:mm"));
	d1.addValue (3, QDateTime::fromString("13.11.2013 19:50","dd.MM.yyyy HH:mm"));
	d1.addValue (4, QDateTime::fromString("13.11.2013 20:30","dd.MM.yyyy HH:mm"));
	d1.addValue (4, QDateTime::fromString("14.11.2013 00:30","dd.MM.yyyy HH:mm"));
	d1.addValue (5, QDateTime::fromString("14.11.2013 09:30","dd.MM.yyyy HH:mm"));
	d1.addValue (4, QDateTime::fromString("14.11.2013 13:30","dd.MM.yyyy HH:mm"));
	d1.addValue (8, QDateTime::fromString("14.11.2013 15:30","dd.MM.yyyy HH:mm"));
	d1.addValue (6, QDateTime::fromString("14.11.2013 16:30","dd.MM.yyyy HH:mm"));
	d1.addValue (7, QDateTime::fromString("17.11.2013 09:30","dd.MM.yyyy HH:mm"));
	d1.addValue (8, QDateTime::fromString("17.11.2013 10:30","dd.MM.yyyy HH:mm"));
	d1.addValue (9, QDateTime::fromString("17.11.2013 11:30","dd.MM.yyyy HH:mm"));
	d1.addValue (7, QDateTime::fromString("17.11.2013 12:30","dd.MM.yyyy HH:mm"));
	d1.addValue (12, QDateTime::fromString("18.11.2013 12:30","dd.MM.yyyy HH:mm"));
	d1.addValue (11, QDateTime::fromString("18.11.2013 13:30","dd.MM.yyyy HH:mm"));
	d1.addValue (12, QDateTime::fromString("18.11.2013 15:30","dd.MM.yyyy HH:mm"));
	d1.addValue (13, QDateTime::fromString("19.11.2013 08:30","dd.MM.yyyy HH:mm"));
	d1.addValue (12, QDateTime::fromString("19.11.2013 09:30","dd.MM.yyyy HH:mm"));
	d1.addValue (11, QDateTime::fromString("19.11.2013 10:00","dd.MM.yyyy HH:mm"));
	d1.dump();
	d1.addValue (18, QDateTime::fromString("19.11.2013 09:45","dd.MM.yyyy HH:mm"));
	d1.addValue (18, QDateTime::fromString("19.11.2013 09:50","dd.MM.yyyy HH:mm"));
	d1.addValue (34, QDateTime::fromString("13.11.2013 22:30","dd.MM.yyyy HH:mm"));
	d1.dump();
	d1.condenseOldEntries ();
	d1.dump();
}

void DataBase::store (QDataStream & s) const
{
	s << _db.size();
	for (int i=0; i < _db.size(); ++i) {
		s << _db[i].startDateTime();
		s << _db[i].endDateTime();
		s << _db[i].data();
	}
}

void DataBase::restore (QDataStream & s)
{
	int n = 0;
	_db.clear ();
	s >> n;
	_db.reserve(n);
	for(int i=0; i< n ; ++i) {
		QDateTime st; 
		QDateTime et; 
		QVariant v;
		s >> st;
		s >> et;
		s >> v;
		DbEntry k(v,st);
		k.setEnd (et);
		_db.push_back (k);
	}
	condenseOldEntries ();
}

void DataBase::addValue (const QVariant& v, const QDateTime & tim)
{
	if(! _db.size()) {
		_db.push_back (DbEntry(v,tim));
		return;
	}

	for (int i = 0; i< _db.size(); ++i) {
		if (_db[i].endDateTime () >= tim && _db[i].startDateTime () <= tim ) {

			if (_db[i].data() == v) return;

			bool endmatch = _db[i].endDateTime () == tim;
			bool startmatch = _db[i].startDateTime () == tim;

			if (endmatch && startmatch) {
				_db[i].data() = v;
				return;
			} 
			if (endmatch) {
				_db[i].setEnd (_db[i].startDateTime ());
				_db.insert(i+1, DbEntry (v, tim));
				return;
			}
			if (startmatch) {
				_db[i].setStart (_db[i].endDateTime());
				_db.insert(i, DbEntry (v, tim));
				return;
			}
			_db.insert(i+1, DbEntry (_db[i].data(), _db[i].endDateTime()));
			_db[i].setEnd (_db[i].startDateTime());			
			_db.insert(i+1, DbEntry (v, tim));
			return;
		}
	}

	for (int i = _db.size()-1; i>=0; --i) {
		if (_db[i].endDateTime () < tim ) {
			if (_db[i].data() == v) {
				_db[i].setEnd (tim);
				return;
			}
			_db.insert(i+1, DbEntry (v,tim));
			return;
		}
	}

	for (int i = 0; i< _db.size(); ++i) {
		if (_db[i].startDateTime () > tim ) {
			if (_db[i].data() == v) {
				_db[i].setStart (tim);
				return;
			}
			_db.insert(i, DbEntry(v,tim));
			return;
		}
	}
};

int DataBase::lastIncreaseEntry () const
{
	if (!_db.size()) return -1;
	if (_db.size() == 1) return 0;
	if (!_interpolatable) return lastChangeEntry ();
	int k = _db.size()-1;
	int val = _db[k].data().toInt();
	int nval = val;
	--k;
	while (k >= 0) {
		val = nval;
		nval = _db[k].data().toInt();
		if (nval < val) break;
		--k;
	}
	return k+1;
};

bool DataBase::alive (const QDateTime & tim, const QDateTime & latest_obs) const
{
	if (!_db.size() ) return false;
	if (tim >= latest_obs) return true;
	if (tim < _db[0].startDateTime()) return false;
	if (_db[_db.size()-1].endDateTime() < tim ) {
		if(_db[_db.size()-1].endDateTime().secsTo (tim) > 100) 
			return false;
	}
	return true;
}



QVariant DataBase::valueAt (const QDateTime & tim) const 
{
	QVariant r;
	if (!_db.size() ) return r;
	int ne = 0;
	for (int i = 0;i< _db.size(); ++i) {
		if (_db[i].startDateTime() > tim) break;
		ne = i;
	}		
	if (ne == 0 )  // before the very first entry
		r = _db[ne].data(); 
	else if (ne == (_db.size()-1)) // after the last entry
		r = _db[ne].data(); 
	else if ( tim <= _db[ne].endDateTime()) // somewhere inside an entry
		r = _db[ne].data(); 
	else { // try interpolate linear between two entries
		if (!_interpolatable) {
			return _db[ne].data();
		}
		double v0 = _db[ne].data().toInt(); 
		double v1 = _db[ne+1].data().toInt(); 
		double dv = v1-v0;     
		double dt = _db[ne].endDateTime().secsTo(_db[ne+1].startDateTime());
		double t = _db[ne].endDateTime().secsTo(tim);
		r = v0 + dv * t / dt;
	}
	return r;
};

QVariant DataBase::previousValue (const QDateTime &tim, const QVariant &def) const
{
	if (!_db.size() ) return def;
	int ne = 0;
	for (int i = 0;i< _db.size(); ++i) {
		if (_db[i].startDateTime() > tim) break;
		ne = i;
	}	
	if (ne == 0 )  // before the very first entry
		return def;
	return _db[ne-1].data(); 
}

QVariant DataBase::previousValue (const QVariant &def) const
{
	if (_db.size() < 2) return def;
	return _db[_db.size()-2].data();
}

/*! The first entry of a certain day has to end on that day
*/
int DataBase::firstOfDay(const QDate & d) const
{
	for (int i=0;i<_db.size();++i) 
		if (_db[i].endDate() == d) 
			return i;
	return -1;
};

/*! The last entry of a certain day has to start on that day
*/
int DataBase::lastOfMonth(const QDate & d) const 
{
	if (!_db.size()) return -1;
	for (int i = _db.size()-1;i>=0;--i) {
		QDate dd = _db[i].startDate();
		if (dd.year() == d.year() && dd.month() == d.month()) 
			return i;
	}
	return -1;
};

/*! The last entry of a certain day has to start on that day
*/
int DataBase::lastOfDay(const QDate & d) const 
{
	if (!_db.size()) return -1;
	for (int i = _db.size()-1;i>=0;--i) {
		if (_db[i].startDate() == d) 
			return i;
	}
	return -1;
};

/*! Keep at most 2 entries per day if the stamp is older than 2 days and
at most 2 per month if the entry is older than 2 months
*/
void DataBase::condenseOldEntries () 
{
	QVector < DbEntry > ndb;
	for (int i=0;i< _db.size(); ++i) {
		if (i == 0 || ndb[ndb.size()-1].data() != _db[i].data()) 
			ndb.push_back(_db[i]);
		else {
			ndb[ndb.size()-1].setEnd (_db[i].endDateTime());
		}		
	}
	_db = ndb;
	ndb.clear();
	if (!_interpolatable) return;
	if (_db.size() < 4) return;
	QDate today = QDate::currentDate ();


	
	int i = 0;
	while (i < _db.size()) {

		// store the entry if its value differs from the last stored value
		if (i == 0 || ndb[ndb.size()-1].data() != _db[i].data()) 
			ndb.push_back(_db[i]);
		else {
			ndb[ndb.size()-1].setEnd (_db[i].endDateTime());
		}

		QDate ed = _db[i].endDate();
		
		int age = ed.daysTo (today);
		if (age < 2) {
			// keep all younger entries
			++i;
			continue;
		}
		int ld = -1;
		if (age > 60) {
			ld = lastOfMonth (ed);
		} 
		if (ld < 0) {
			ld = lastOfDay (ed);
		}
		// find next entry starting on the day this entry ends on
		if (ld < 0 || ld == i) {
			// no end entry found ==> process next
			++i;
			continue;
		}

		i = ld;
	}
	_db = ndb;
};

QDataStream& operator << (QDataStream &st,const DataBase& s){s.store(st);return st;};
QDataStream& operator >> (QDataStream &st,DataBase& s){s.restore(st);return st;};



