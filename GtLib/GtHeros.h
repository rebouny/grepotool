#ifndef ___GT_HEROS_H
#define ___GT_HEROS_H
/* 
GtHeros
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



class EXPORT Hero {
	Q_DECLARE_TR_FUNCTIONS(Hero);
public:
	Hero (){};
};

class EXPORT HeroData {
public:
	HeroData () {
		for (int i=0;i<HeroMax;++i) 
			val[i]=0; 
	};
	HeroData (const HeroData& o){*this = o;};
	HeroData & operator = (const HeroData& o) {
		for (int i=0;i<HeroMax;++i) 
			val[i] = o.val[i]; 
		return *this;
	};
	QVariantMap toVariant () const {
		QVariantMap r;
		for (int i=0;i<HeroMax;++i) 
			if (val[i])
				r[heroJsonNames[i]] = val[i];
		return r;
	};
	static HeroData fromVariant (const QVariantMap & m) {
		HeroData r;
		for (int i=0;i<HeroMax;++i) 
			if (m.contains(heroJsonNames[i])) 
				r.val[i] = m[heroJsonNames[i]].toInt();
		return r;
	};
	inline bool isValid() const  {for (int i=0;i<HeroMax;++i) if(val[i]) return true; return false;};
	int        val[HeroMax];
};


#endif