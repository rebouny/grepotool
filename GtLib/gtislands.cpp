
#include <QStringList>
#include <QFile>
#include <QByteArray>
#include <QVariantMap>
#include "GtIslands.h"

Island & Island::operator = (const Island& o) 
{
	id = o.id;
	x=o.x;
	y=o.y;
	pos = o.pos;
	type=o.type;
	image=o.image;
	towns = o.towns; 
	return *this;
}
