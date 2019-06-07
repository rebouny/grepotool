/* data.cpp -  data

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

#include <QStringList>
#include <QFile>
#include <QIcon>
#include <QImage>
#include <QPainter>
#include <QByteArray>
#include <QVariantMap>
#include "GtTowns.h"
#include "GtWorlddata.h"

Town& Town::operator =  (const Town &o)
{
	id =o.id;
	name = o.name;
	points = o.points;
	player_id= o.player_id;
	ally_id=o.ally_id;
	island=o.island;
	island_index=o.island_index;
	x=o.x;
	y=o.x;
	no=o.no;// on island;
	pos = o.pos;

	first_obs=o.first_obs;
	last_obs=o.last_obs;
	last_owner_chg = o.last_owner_chg;
	last_owner = o.last_owner;

	alive=o.alive;

	player_index = o.player_index;
	ally_index = o.ally_index;  
	player_name=o.player_name; 
	ally_name = o.ally_name;   

	bookmark=o.bookmark;
	name_rank=o.name_rank;
	player_name_rank=o.player_name_rank;
	ally_name_rank=o.ally_name_rank;

	ocean = o.ocean;
	special = o.special;
	type = o.type;
	ghost = o.ghost;
    conquer = o.conquer;
	reports=o.reports;
	if (data && data->decRef()) delete data;
	data = o.data;
	if (data) data->incRef();
	return *this;
};

int  Town::numColumns        ()
{
	return TownMax;
}
int Town::defaultSortColumn ()
{
	return TownPoints;
}
Qt::SortOrder Town::defaultSortOrder  ()	
{
	return Qt::DescendingOrder;
}
bool Town::canHideColumn     (int col)
{
	return col!= TownName;
}
QVariant Town::headerData ( int col, int role)
{
	if (role == Qt::DisplayRole) {
		if(col == TownName) {                return tr("Name");   
		} else if (col == TownPoints) {      return tr("Points");
		} else if (col == TownPlayerName) {return tr("Player");
		} else if (col == TownAllyName) {return tr("Ally");
		} else if (col == TownOcean) {return tr("Ocean");
		} else if (col == TownIsland) {return tr("Island");
		} else if (col == TownSpecial) {return tr("Specials");
		} else if (col == TownUnits) {return tr("Units");
		} else if (col == TownType) {return tr("Type");
		}

	} else if (role == Qt::DecorationRole) {
		if(col == TownName) { return QIcon(":/icons/icons/town.ico") ;
		} else if (col == TownPoints) { return QIcon(":/icons/icons/points.ico") ;
		} else if (col == TownPlayerName) { return QIcon(":/icons/icons/player.ico") ;
		} else if (col == TownAllyName) { return QIcon(":/icons/icons/ally.ico") ;
		} else if (col == TownOcean) {return QIcon(":/icons/icons/world.ico") ;
		} else if (col == TownIsland) { return QIcon(":/icons/icons/island.ico") ;
		} else if (col == TownSpecial) { return QIcon(":/icons/icons/town_question.ico") ;
		} else if (col == TownUnits) { return QIcon(":/icons/icons/helmet.ico") ;
		} else if (col == TownType) {return QIcon(":/icons/icons/helmet.ico") ;
		}

	} else if (role == Qt::ToolTipRole) {
		if(col == TownName) {                return tr("Name");   
		} else if (col == TownPoints) {      return tr("Points");
		} else if (col == TownPlayerName) {return tr("Player");
		} else if (col == TownAllyName) {return tr("Ally");
		} else if (col == TownOcean) {return tr("Ocean");
		} else if (col == TownIsland) {return tr("Island");
		} else if (col == TownSpecial) {return tr("Specials");
		} else if (col == TownUnits) {return tr("Units");
		} else if (col == TownType) {return tr("Type");
		}

	}
	return QVariant();
}
QVariant Town::itemData   ( int col, int role) const
{
	if (role == Qt::DisplayRole) {
		if(col == TownName) {    return name;
		} else if (col == TownPoints) { return QString::number(points);
		} else if (col == TownPlayerName) { return player_name;
		} else if (col == TownAllyName) { return ally_name;
		} else if (col == TownOcean) { return QString::number(ocean);
		} else if (col == TownIsland) {return QString::number(island);
		} else if (col == TownSpecial) {return specialPixmap();
		} else if (col == TownUnits) {return unitsPixmap ();
		} else if (col == TownType) {return WorldData::townTypeText(type,false);
		}
	} else if (role == Qt::ToolTipRole) {
		if(col == TownName) {                return tr("Name");   
		} else if (col == TownPoints) {      return tr("Points");
		} else if (col == TownPlayerName) {return ghost?tr("Former owner"):tr("Owner");
		} else if (col == TownAllyName) {return tr("Ally");
		} else if (col == TownOcean) {return tr("Ocean");
		} else if (col == TownIsland) {return tr("Island");
		} else if (col == TownSpecial) {return tr("Specials");
		} else if (col == TownUnits) {return tr("Units");
		} else if (col == TownType) {return tr("Type");
		}
		return headerData (col,role);
	} else if (role == Qt::DecorationRole) {
		
		if (col == TownName) {
			if (ghost)
				return QPixmap (QString(":/icons/icons/ghost.ico")).scaled (QSize(16,16));
            if (conquer)
                return QPixmap (QString(":/icons/icons/ghost.ico")).scaled (QSize(64,64));
            return QPixmap (QString(":/icons/icons/town.ico")).scaled (QSize(16,16));
		}
		if (col == TownType) return QPixmap (QString(":/icons/icons/town_type%1.png").arg(type)).scaled (QSize(16,16));
	}

	return QVariant();
}


QPixmap Town::unitsPixmap () const
{
	if(!data) return QPixmap();


	int w= 0;
	int s = 16;

	for (int i=1;i< UnitMax; ++i) {
		if (data->units.val[i]) {
			w += s;
		}
	}
	if(!w) return QPixmap();
	
	QImage r(QSize (w,s), QImage::Format_ARGB32_Premultiplied);
	r.fill (0);
	QPainter p(&r);
	w = 0;
	for (int i=1;i< UnitMax; ++i) {
		if (data->units.val[i]) {
			QPixmap p1 (Unit::unitIconFile((UnitIndex)i));
			p.drawPixmap(w,0,p1.scaled(QSize(s,s)));
			w += s;
		}
	}
	return QPixmap::fromImage(r);
}

QString Town::unitsText () const
{
	if(!data) return "";
	return "";
}

QString Town::unitsTooltip () const
{
	if(!data) return "";
	return "";
}

QPixmap    Town::specialPixmap () const
{
	if(!data) return QPixmap();
	QPixmap p1;
	QPixmap p2;
	QPixmap p3;
	QPixmap p4;
	int w= 0;
	int s = 16;
	if(data->research.val[ResearchMeteorology]) {p1 = QPixmap(":/icons/research/meteorology.png");++w;}
	if(data->research.val[ResearchCartography]) {p2 = QPixmap(":/icons/research/cartography.png");++w;}
	if(data->buildings.val[Lighthouse])         {p3 = QPixmap(":/icons/buildings/lighthouse.png");++w;}
	if(data->heros.val[Atlanta])         {p4 = QPixmap(":/icons/heros/atlanta.png");++w;}
	if(!w) return p4;

	QImage r(QSize (w*s,s), QImage::Format_ARGB32);
	QPainter p(&r);
	w = 0;
	if (p1.width()) { p.drawPixmap(w,0,p1.scaled(QSize(s,s))); w+=s;}
	if (p2.width()) { p.drawPixmap(w,0,p2.scaled(QSize(s,s))); w+=s;}
	if (p3.width()) { p.drawPixmap(w,0,p3.scaled(QSize(s,s))); w+=s;}
	if (p4.width()) { p.drawPixmap(w,0,p4.scaled(QSize(s,s))); w+=s;}
	return QPixmap::fromImage(r);
}

QString  Town::specialText () const
{
	if(!data) return "";
	return "";

}
QString  Town::specialTooltip () const
{
	if(!data) return "";
	return "";
}

QString  Town::tacticalText () const
{
	QString r; 
	if(type == TownTypeUndefined) {
		r = tr("Undefined");
	} else if (type == TownTypeAtt) {      // rect  
		r = tr("Off");
	} else if (type == TownTypeDeff) {      // Triangle
		r = tr("Def");
	} else if (type == TownTypeAttShip) {   // raute
		r = tr("Attships");
	} else if (type == TownTypeAttKolo) {   // rect+hat
		r = tr("Att + Kolo");
	} else if (type == TownTypeBireme) {   // Tri down
		r = tr("Biris");
	} else if (type == TownTypeManti) {     // star
		r = tr("Mantis");
	} else if (type == TownTypePega) {      // Rect with slash
		r = tr("Pegasoi");
	} else if (type == TownTypeHarpy) {    //  rect with backslash
		r = tr("Harpys");
	}
	return r;
}

QString  Town::tacticalTooltip () const
{
	return QString("<p align=vcenter><img src=':/icons/icons/town_type%1.png' width=20 height=20> %2</p>").arg((int)type).arg(tacticalText());
}




QStringList Town::headline   ( const QVector <int> &cols ) 
{
	QStringList r;
	for (int i=0;i< cols.size(); ++i) {
		r.push_back (headerData (cols[i], Qt::DisplayRole).toString());
	}
	return r;
}
QStringList  Town::texts      ( const QVector <int> &cols ) const  
{
	QStringList r;
	for (int i=0;i< cols.size(); ++i) {
		QString tx = itemData (cols[i], Qt::DisplayRole).toString();
		if (cols[i] == TownSpecial) {
		} else if (cols[i] == TownUnits) {
		}
		r.push_back (tx);
	}
	return r;
}
QStringList  Town::bbCodes    ( const QVector <int> &cols ) const 
{
	QStringList r;
	for (int i=0;i< cols.size(); ++i) {
		QString tx = itemData (cols[i], Qt::DisplayRole).toString();
		if (cols[i] == TownName) {
			tx = bbCode(QString::number(id),"town");
		} else if (cols[i] == TownPlayerName) {
			tx = bbCode(tx,"player");
		} else if (cols[i] == TownAllyName) {
			tx = bbCode(tx,"ally");
		} else if (cols[i] == TownIsland) {
			tx = bbCode(tx,"island");
		}
		r.push_back (tx);
	}
	return r;
}
QString Town::labelText  ( int col, int icon_size  ) const
{
	if (col == TownName) {

	} else if (col == TownPoints) {
	} else if (col == TownPlayerName) {
	} else if (col == TownAllyName) {
	} else if (col == TownOcean) {
	} else if (col == TownIsland) {
	} else if (col == TownSpecial) {
	} else if (col == TownUnits) {
	} else if (col == TownType) {

	}
	return QString();
}
bool  Town::itemCheckable   (int )
{
	return false;
}
bool  Town::itemChecked     (int ) const
{
	return false;
}
void   Town::setItemChecked  (int , bool )
{
}
int Town::compare (const Town&o, int col) const
{
	if(col == TownName) {
		return name_rank - o.name_rank;
	} else if (col == TownPoints) {
		return points - o.points;
	} else if (col == TownPlayerName) {
		return player_name_rank - o.player_name_rank;
	} else if (col == TownAllyName) {
		return ally_name_rank - o.ally_name_rank;
	} else if (col == TownOcean) {
		return ocean - o.ocean;
	} else if (col == TownIsland) {
		return island -o.island;
	} else if (col == TownSpecial) {

	} else if (col == TownUnits) {
	} else if (col == TownType) {
	}
	return 0;
}

int Town::itemSortIndex (int col) const
{
	if(col == TownName) {
		return name_rank;
	} else if (col == TownPoints) {
		return points;
	} else if (col == TownPlayerName) {
		return player_name_rank ;
	} else if (col == TownAllyName) {
		return ally_name_rank;
	} else if (col == TownOcean) {
		return ocean ;
	} else if (col == TownIsland) {
		return island;
	} else if (col == TownSpecial) {
	} else if (col == TownUnits) {
	} else if (col == TownType) {
		return (int) type;
	}
	return 0;
}


void Town::handleReport (const Report& r)
{
}


#define SIN45   0.7071068
#define SIN60   0.8660254
#define CIRCFAC 0.7978846

void Town::renderTypeSymbol(QPainter* paint, TownTypeIndex type, const QPoint& pos, const double &r)
{	
	double cx = pos.x();
	double cy = pos.y();
	if (type == TownTypeAtt) {       // rect  
		QPointF p0 (cx - r*SIN45,   cy-r*SIN45); 
		QPointF p1 (cx + r*SIN45,   cy-r*SIN45); 
		QPointF p2 (cx + r*SIN45,   cy+r*SIN45); 
		QPointF p3 (cx - r*SIN45,   cy+r*SIN45); 
		QPolygonF po;
		po << p0;
		po << p1;
		po << p2;
		po << p3;
		po << p0;
		paint->drawPolygon (po);
	} else if (type == TownTypeDeff) {      // Triangle
		QPointF p0 (cx,             cy-r); 
		QPointF p1 (cx - r * SIN60, cy + r * 0.5); 
		QPointF p2 (cx + r * SIN60, cy + r * 0.5); 
		QPolygonF po;
		po << p0;
		po << p1;
		po << p2;
		po << p0;
		paint->drawPolygon (po);
	} else if (type == TownTypeAttShip) {   // raute
		QPointF p0 (cx,             cy - r ); 
		QPointF p1 (cx + r,         cy); 
		QPointF p2 (cx ,            cy + r ); 
		QPointF p3 (cx -r ,         cy); 
		QPolygonF po;
		po << p0;
		po << p1;
		po << p2;
		po << p3;
		po << p0;
		paint->drawPolygon (po);
	} else if (type == TownTypeAttKolo) {   // rect+hat
		QPointF pp0 (cx - r*SIN45,   cy-r*SIN45); 
		QPointF p0  (cx,             cy - r ); 
		QPointF pp1 (cx + r*SIN45,   cy-r*SIN45); 
		QPointF pp2 (cx + r*SIN45,   cy+r*SIN45); 
		QPointF pp3 (cx - r*SIN45,   cy+r*SIN45); 
		QPolygonF ppo;
		ppo << pp0;
		ppo << p0;
		ppo << pp1;
		ppo << pp2;
		ppo << pp3;
		ppo << pp0;
		paint->drawPolygon (ppo);

	} else if (type == TownTypeBireme) {    // Tri down
		QPointF p0 (cx,             cy+r); 
		QPointF p1 (cx - r * SIN60, cy - r * 0.5); 
		QPointF p2 (cx + r * SIN60, cy - r * 0.5); 
		QPolygonF po;
		po << p0;
		po << p1;
		po << p2;
		po << p0;
		paint->drawPolygon (po);
	} else if (type == TownTypeManti) {     // star
		renderTypeSymbol(paint, TownTypeDeff, pos, r);
		renderTypeSymbol(paint, TownTypeBireme, pos, r);
	} else if (type == TownTypePega) {      // Rect with slash
		renderTypeSymbol(paint,TownTypeAtt, pos, r);
		QPointF p0 (cx - r*SIN45,   cy + r*SIN45); 
		QPointF p1 (cx + r*SIN45,   cy - r*SIN45); 
		paint->drawLine (p0,p1);		
	} else if (type == TownTypeHarpy) {    //  rect with backslash
		renderTypeSymbol(paint,TownTypeAtt, pos, r);
		QPointF p0 (cx + r*SIN45,   cy + r*SIN45); 
		QPointF p1 (cx - r*SIN45,   cy - r*SIN45); 
		paint->drawLine (p0,p1);		
	} else { //  if(typ == TownTypeUndefined) { // circle
		paint->drawEllipse (QPointF(cx,cy),r*CIRCFAC, r*CIRCFAC);
	}

}
