#ifndef ___GT_BUILDINGS_H
#define ___GT_BUILDINGS_H
/* 
GtBuildings
*/

#include <GtIndexes.h>

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

class EXPORT Building {
	Q_DECLARE_TR_FUNCTIONS(Building);
public:
	Building (){};
};

class EXPORT BuildingData {
public:
	BuildingData () {
		for (int i=0;i<BuildingMax;++i) 
			val[i]=0; 
	};
	BuildingData (const BuildingData& o){*this = o;};
	BuildingData & operator = (const BuildingData& o) {
		for (int i=0;i<BuildingMax;++i) 
			val[i] = o.val[i]; 
		return *this;
	};
	QVariantMap toVariant () const {
		QVariantMap r;
		for (int i=0;i<BuildingMax;++i) 
			if (val[i])
				r[buildingJsonNames[i]] = val[i];
		return r;
	};
	static BuildingData fromVariant (const QVariantMap & m) {
		BuildingData r;
		for (int i=0;i<BuildingMax;++i) 
			if (m.contains(buildingJsonNames[i])) 
				r.val[i] = m[buildingJsonNames[i]].toInt();
		return r;
	};
	inline bool isValid() const  {for (int i=0;i<BuildingMax;++i) if(val[i]) return true; return false;};

	int        val[BuildingMax];
};


#endif