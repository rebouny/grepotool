#ifndef ___GT_REPORTS_H
#define ___GT_REPORTS_H
/* 
GtReports
*/

#include <GtUnits.h>
#include <GtBuildings.h>
#include <GtResearch.h>
#include <GtHeros.h>
#include <GtBoni.h>

#include <QApplication>
#include <QImage>
#include <QColor>
#include <QDateTime>

#ifdef EXPORT 
# undef EXPORT
#endif
#ifdef BUILDING_GTLIB
# define EXPORT DLL_EXPORT
#else
# define EXPORT DLL_IMPORT
#endif


enum ReportType {
	ReportInvalid,
	ReportAttack,
	ReportSpy,
	ReportWallState
};

class EXPORT ReportData {
public:

	ReportData (ReportType t=ReportInvalid):_ref(0),_type(t){};
	void incRef () {++_ref;};
	bool decRef () {--_ref; return (_ref==0);};
	ReportType type() const {return _type;};
	virtual bool parseMap (const QVariantMap & m) = 0;
	
	mutable int _ref;
	ReportType  _type;
	QString     _server;
	QString     _source;
	QString     _lang;
	QDateTime   _recv_time;
	QVariantMap _content;
};

class EXPORT AttReport : public ReportData {
public:
	AttReport () : ReportData (ReportAttack), wall_loss(0){};

	bool parseMap (const QVariantMap & m);

	QDateTime    att_time;
	int          att_town_id;
	int          att_player_id;
	int          def_town_id;
	int          def_player_id;
	int          wall_loss;
	BonusData    boni;
	UnitData     att_units;
	UnitData     att_unit_loss;
	UnitData     def_units;
	UnitData     def_unit_loss;
};

class EXPORT WallReport : public ReportData {
public:
	WallReport () : ReportData (ReportWallState) {};
	bool parseMap (const QVariantMap & m);

	int          player_id;
	UnitData     killed_as_att;
	UnitData     killed_as_def;
	UnitData     lost_as_att;
	UnitData     lost_as_def;
};

class EXPORT SpyReport : public ReportData {
public:
	SpyReport () : ReportData (ReportSpy) {};
	bool parseMap (const QVariantMap & m);

	QDateTime    time;
	int          town_id;
	UnitData     units;
	BuildingData buildings;
};



class EXPORT Report {
	Q_DECLARE_TR_FUNCTIONS(Report);
public:
	Report ():_d(0){};
	Report (const ReportData* d):_d(const_cast<ReportData*>(d)){if (_d)_d->incRef();};
	Report (const QString & v);
	~Report (){if (_d && _d->decRef()) delete _d;};
	Report (const Report& o):_d(0) {*this = o;};
	Report& operator = (const Report&o);
	bool operator == (const Report&o) const;

	ReportType type () const {
		if(!_d) return ReportInvalid;
		return _d->type();
	};

	QString server () const {
		if(!_d) return "";
		return _d->_server;
	};

	AttReport * att () {return dynamic_cast<AttReport *> (_d);};
	SpyReport * spy ()  {return dynamic_cast<SpyReport *> (_d);};
	WallReport * wall () {return dynamic_cast<WallReport *> (_d);};
	const AttReport * att () const {return dynamic_cast<const AttReport *> (_d);};
	const SpyReport * spy () const {return dynamic_cast<const SpyReport *> (_d);};
	const WallReport * wall () const {return dynamic_cast<const WallReport *> (_d);};

	QVariantMap toVariant () const;
	static Report fromVariant (const QVariantMap & m);	

	static QVariantMap parseReport (const QString & s);
	static QDateTime guessDate (const QString &s);
	static QVariant parseReportValue (const QString & nam, const QString & s);

	bool isValid () const {return _d != 0;};
	bool isInvalid () const {return _d == 0;};

	ReportData * _d;
};




#endif