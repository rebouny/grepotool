#ifndef ___GT_UNITS_H
#define ___GT_UNITS_H
/*
GtUnits

*/

#include <GtIndexes.h>
#include <GtCore.h>

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




class EXPORT Unit {
	Q_DECLARE_TR_FUNCTIONS(Unit);
public:
	Unit (){};
	Unit (const Unit &o) {*this = o;};
	Unit & operator = (const Unit& o);

	static Unit      extractData (const QVariant & u, UnitIndex i);
	static UnitIndex unitIndex (const QString & name); 
	static QString   unitName  (UnitIndex i, bool plural); 
	static QString   unitIconFile (UnitIndex i); 

	bool isLandUnit () const {return ::isLandUnit (type);};
	bool isFlyingUnit () const {return ::isFlyingUnit (type);};

	UnitIndex       type; 
	double          build_time;
	double          seaspeed;
	double          landspeed;
	int             attack;
	AttackTypeIndex attack_type;
	int             defence[4];
	QString         name;
	QString         name_pl;
	QImage          image;
	QString         desc;
};

class BonusData;

class EXPORT UnitData {
public:
	UnitData () {
		for (int i=0;i<UnitMax;++i) 
			val[i]=0; 
	};
	UnitData (const UnitData& o){*this = o;};
	UnitData & operator = (const UnitData& o) {
		for (int i=0;i<UnitMax;++i) 
			val[i] = o.val[i]; 
		return *this;
	};

	bool operator == (const UnitData& o) const {
		for (int i=0;i<UnitMax;++i) 
			if(val[i] != o.val[i]) return false;
		return true;
	};
	bool operator != (const UnitData& o) const {return !(*this == o);};

	UnitData & operator -= (const UnitData& o) {
		for (int i=0;i<UnitMax;++i) 
			val[i] -= o.val[i]; 
		return *this;
	};

	UnitData operator - (const UnitData& o) const {
		UnitData r(*this);
		r-=o;
		return r;
	};

	UnitData & operator += (const UnitData& o) {
		for (int i=0;i<UnitMax;++i) 
			val[i] += o.val[i]; 
		return *this;
	};

	UnitData operator + (const UnitData& o) const {
		UnitData r(*this);
		r+=o;
		return r;
	};

	QVariantMap toVariant () const {
		QVariantMap r;
		for (int i=0;i<UnitMax;++i) 
			if (val[i])
				r[unitJsonNames[i]] = val[i];
		return r;
	};
	inline bool isValid() const  {
		for (int i=0;i<UnitMax;++i) 
			if(val[i]) 	return true;
		return false;
	};

	static UnitData fromVariant (const QVariantMap & m) {
		UnitData r;
		for (int i=0;i<UnitMax;++i) 
			if (m.contains(unitJsonNames[i])) 
				r.val[i] = m[unitJsonNames[i]].toInt();
		return r;
	};
	UnitData landUnits () const {
		UnitData r;
		for (int i=0;i<UnitMax;++i) if (isLandUnit ((UnitIndex) i)) r.val[i] = val[i];
		return r;
	};
	UnitData landFightUnits () const {
		UnitData r;
		for (int i=0;i<UnitMax;++i) if (isLandUnit ((UnitIndex) i)||isFlyingUnit ((UnitIndex) i)) r.val[i] = val[i];
		return r;
	};
	UnitData mythUnits () const {
		UnitData r;
		for (int i=0; i < UnitMax;++i) if (isMythUnit ((UnitIndex) i)) r.val[i] = val[i];
		return r;
	};
	UnitData seaUnits () const {
		UnitData r;
		for (int i=0;i<UnitMax;++i) if (isSeaUnit ((UnitIndex) i)) r.val[i] = val[i];
		return r;
	};
	UnitData seaAttUnits () const {
		UnitData r;
		for (int i=0;i<UnitMax;++i) if (isSeaAttUnit ((UnitIndex) i)) r.val[i] = val[i];
		return r;
	};
	UnitData seaDefUnits () const {
		UnitData r;
		for (int i=0;i<UnitMax;++i) if (isSeaDefUnit ((UnitIndex) i)) r.val[i] = val[i];
		return r;
	};
	UnitData flyingUnits () const {
		UnitData r;
		for (int i=0;i<UnitMax;++i) if (isFlyingUnit ((UnitIndex) i)) r.val[i] = val[i];
		return r;
	};
	int bhp () const {
		int r = 0;
		for (int i=0;i<UnitMax;++i) r += val[i] * unitBHP[i];
		return r;
	};

	double attValue (AttackTypeIndex t, const BonusData& b) const;
	double defValue (AttackTypeIndex t, const BonusData& b) const;

	TownTypeIndex attackType () const;
	TownTypeIndex tacticalType () const;

	int        val[UnitMax];
};

#endif