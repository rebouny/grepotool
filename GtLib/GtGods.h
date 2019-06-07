#ifndef ___GT_GODS_H
#define ___GT_GODS_H
/*
GtGods
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


class EXPORT God {
	Q_DECLARE_TR_FUNCTIONS(God);
public:
	God(){};
};
#endif