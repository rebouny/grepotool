#ifndef ___GT_ISLANDS_H
#define ___GT_ISLANDS_H
/* 
GtIslands
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


class EXPORT Island {
public:
	Island ():id(-1){};
	bool isValid() const {return id>=0;};
	Island(const Island& o){*this = o;};
	Island & operator = (const Island& o);

	int           id;
	int           x;
	int           y;
	QPoint        pos;
	int           type;
	QImage        image;

	QVector <int> towns; 
};



#endif