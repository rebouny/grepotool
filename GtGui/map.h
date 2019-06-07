#ifndef ___MAP_H
#define ___MAP_H
/* map.h  - world map rendering

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

#include <QThread>
#include <QVector>
#include <QMutex>
#include <QWaitCondition>
#include <QPolygonF>
#include <QColor>


// ----------------------------------------------
// Settings associated with the Map viewer
// ----------------------------------------------


#define MAPVIEW_OCEAN_COLOR        "World/Mapview/OceanColor"
#define MAPVIEW_GRID_COLOR         "World/Mapview/GridColor"
#define MAPVIEW_OCEAN_LABEL_COLOR  "World/Mapview/OceanLabelColor"
#define MAPVIEW_SHOW_OCEAN_LABELS  "World/Mapview/ShowOceanLabels"
#define MAPVIEW_SHOW_GRID          "World/Mapview/ShowGrid"
#define MAPVIEW_SHOW_BOOKMARKED    "World/Mapview/ShowBookmarked"
#define MAPVIEW_SHOW_GHOSTS        "World/Mapview/ShowGhosts"
#define MAPVIEW_SHOW_CONQUERS      "World/Mapview/ShowConquers"
#define MAPVIEW_LEGEND_MODE        "World/Mapview/LegendMode"
#define MAPVIEW_GHOST_COLOR        "World/Mapview/GhostColor"
#define MAPVIEW_ROCK_ZOOM          "World/Mapview/RockZoom"
#define MAPVIEW_TACTICAL_TYPES     "World/Mapview/TacticalTownTypes"

#define MAPVIEW_UNSELECTED_MODE    "World/Mapview/UnselectedMode"
#define MAPVIEW_UNSELECTED_COLOR   "World/Mapview/UnselectedColor"

#define MAPVIEW_INFMAP_ZOOM        "World/Mapview/InfMapZoom"
#define MAPVIEW_INFMAP_LABEL_ZOOM  "World/Mapview/InfMapLabelZoom"
#define MAPVIEW_INFMAP_OPACITY     "World/Mapview/InfMapOpacity"
#define MAPVIEW_INFMAP_CITY_REACH  "World/Mapview/InfMapCityReach"

#define MAPVIEW_TOWN_LABEL_ZOOM    "World/Mapview/TownLabelZoom"
#define MAPVIEW_TOWN_LABEL_PLAYER  "World/Mapview/TownLabelPlayer"
#define MAPVIEW_TOWN_LABEL_ALLY    "World/Mapview/TownLabelAlly"
#define MAPVIEW_TOWN_LABEL_POINTS  "World/Mapview/TownLabelPoints"

#define MAPVIEW_TOWN_DBLCLICK      "World/Mapview/TownDblClick"
#define MAPVIEW_MOUSE_WHEEL_INVERT "World/Mapview/MouseWheelInvert"

#define MAPVIEW_INFMAP_LABEL_MODE  "World/Mapview/InfMapLabelMode"



#define NZOOM 35
static const double zoom_factors [NZOOM] = {
	1, 1.125, 1.25 , 1.5 , 1.75, 2   , 2.25, 2.5, 3.0, 3.5, 4,   5,
	6, 7    , 8    , 9 ,   10,   12.5,   15,  17.5,  20, 25,  30, 
	35,40   ,50,    60,    70 ,  80,     90, 100, 125, 150, 175, 200};



class MapThread  : public QThread {
	Q_OBJECT;
public:
	MapThread (QObject * p);
	~MapThread ();

	void aquireImage (int zoom_level, const QPoint &offset, const QSize &viewport);

	void run();

public slots:
	void meshCreated (const QVector<QPolygonF> &pol, const QVector<QPoint>& pts, const QVector<QColor>& col);
	void meshColorsChanged (const QVector<QColor>& col);
	void clearMesh();

signals:
	void imageRendered (const QImage& img, const QRectF& r);

protected:
	QMutex _m;
	QWaitCondition _condition;
	bool _restart;
	bool _abort;    

	QVector <QPolygonF> _pol;
	QVector <QColor>    _pol_col;
	QVector <QPoint>    _pol_pos;
	int                 _pol_reach;
	int                 _pol_opa;

	int                 _zoom_level;
	QPoint              _offset;
	QSize               _viewport;
};



class MeshThread : public QThread {
	Q_OBJECT;
public:
	MeshThread (QObject * p);
	~MeshThread ();
	void createMesh ();

signals:
	void meshCreated (const QVector<QPolygonF> &pol, const QVector<QPoint>& pts, const QVector<QColor>& col);
	void meshColorsChanged (const QVector<QColor>& col);
	void progress (int);

protected:
	void run();

private:
	QMutex _m;
	QWaitCondition _condition;
	bool _restart;
	bool _abort;    
	bool _update_all;
	QVector <QColor>  _cols;
	QVector <QPoint>  _pos;
};










#endif
