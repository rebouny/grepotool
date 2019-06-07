#ifndef ___GT_SPELLS_H
#define ___GT_SPELLS_H
/* 
GtSpells

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

class EXPORT Spell {
	Q_DECLARE_TR_FUNCTIONS(Spell);
public:
	Spell (){};
};


#endif