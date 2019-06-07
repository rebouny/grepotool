#ifndef ___GT_RESEARCH_H
#define ___GT_RESEARCH_H
/*
GtResearch

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

class EXPORT ResearchData {
public:
	ResearchData () {
		for (int i=0;i<ResearchMax;++i) 
			val[i]=false; 
	};
	ResearchData (const ResearchData& o){*this = o;};
	ResearchData & operator = (const ResearchData& o) {
		for (int i=0;i<ResearchMax;++i) 
			val[i] = o.val[i]; 
		return *this;
	};
	QVariantMap toVariant () const {
		QVariantMap r;		
		for (int i=0;i<ResearchMax;++i) 
			if (val[i])
				r[researchJsonNames[i]] = val[i];
		return r;
	};
	static ResearchData fromVariant (const QVariantMap & m) {
		ResearchData r;
		for (int i=0;i<ResearchMax;++i) 
			if (m.contains(researchJsonNames[i])) 
				r.val[i] = m[researchJsonNames[i]].toBool();
		return r;
	};
	inline bool isValid() const  {for (int i=0;i<ResearchMax;++i) if(val[i]) return true; return false;};

	bool        val[ResearchMax];
};

#endif