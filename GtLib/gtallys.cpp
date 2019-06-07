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

#include "GtAllys.h"


Ally& Ally::operator = (const Ally &o)
{
	id=o.id;
	name=o.name;
	points=o.points;
	off=o.off;
	def=o.def;
	bash=o.bash;

	players=o.players;
	towns=o.towns;
	first_obs=o.first_obs;
	last_obs=o.last_obs;
	alive=o.alive;


	name_rank= o.name_rank;

	color = o.color;
	show = o.show;
	flags = o.flags;
	naps = o.naps;
	bnds = o.bnds;
	bookmark = o.bookmark;

	oceans = o.oceans;

	return *this;
};

int           Ally::numColumns        (){return AllyMax;};
int           Ally::defaultSortColumn (){return AllyPoints;};
Qt::SortOrder Ally::defaultSortOrder  (){return Qt::DescendingOrder;};	
bool          Ally::canHideColumn     (int col){return col > 1;};

bool          Ally::itemCheckable   (int col) {return col == AllyColor;};
bool          Ally::itemChecked     (int col) const {if(col != AllyColor) return false; return show;};
void          Ally::setItemChecked  (int col, bool c) {if(col != AllyColor) return ; show = c;};


int Ally::compare (const Ally&o, int col) const
{
	if ( col == AllyColor) {            
	} else if ( col == AllyName) {       return name_rank - o.name_rank;
	} else if ( col == AllyPoints) {     return points - o.points;
	} else if ( col == AllyNumPlayers) { return players.size()-o.players.size();
	} else if ( col == AllyNumTowns) {   return towns.size()-o.towns.size();
	} else if ( col == AllyDef) {        return def-o.def; 
	} else if ( col == AllyOff) {        return off-o.off;
	} else if ( col == AllyBash) {       return bash-o.bash;
	} 
	return 0;
}

int Ally::itemSortIndex (int col) const
{
	if ( col == AllyColor) {             return 0;
	} else if ( col == AllyName) {       return name_rank ;
	} else if ( col == AllyPoints) {     return points;
	} else if ( col == AllyNumPlayers) { return players.size();
	} else if ( col == AllyNumTowns) {   return towns.size();
	} else if ( col == AllyDef) {        return def; 
	} else if ( col == AllyOff) {        return off;
	} else if ( col == AllyBash) {       return bash;
	} 
	return 0;
}



QVariant Ally::headerData ( int col, int role)
{
	QVariant r;

	if (role == Qt::DisplayRole) {
		if ( col == AllyColor) {             return tr ("Color");
		} else if ( col == AllyName) {       return tr ("Name");
		} else if ( col == AllyPoints) {     return tr ("Points");
		} else if ( col == AllyNumPlayers) { return tr ("Players");
		} else if ( col == AllyNumTowns) {   return tr ("Towns");
		} else if ( col == AllyDef) {        return tr ("Def");
		} else if ( col == AllyOff) {        return tr ("Off");
		} else if ( col == AllyBash) {       return tr ("Total");
		} 
	} else if (role == Qt::DecorationRole) {
		if ( col == AllyColor) {             return QIcon(":/icons/icons/color.ico") ;
		} else if ( col == AllyName) {       return QIcon(":/icons/icons/ally.ico") ;
		} else if ( col == AllyPoints) {     return QIcon(":/icons/icons/points.ico") ;
		} else if ( col == AllyNumPlayers) { return QIcon(":/icons/icons/player.ico") ;
		} else if ( col == AllyNumTowns) {   return QIcon(":/icons/icons/town.ico") ;
		} else if ( col == AllyDef) {        return QIcon(":/icons/icons/shield.ico") ;
		} else if ( col == AllyOff) {        return QIcon(":/icons/icons/sword.ico") ;
		} else if ( col == AllyBash) {       return QIcon(":/icons/icons/swords.ico") ;
		} 
	} else if (role == Qt::ToolTipRole) {
		if ( col == AllyColor) {             return tr ("Ally color");
		} else if ( col == AllyName) {       return tr ("Ally name");
		} else if ( col == AllyPoints) {     return tr ("Points");
		} else if ( col == AllyNumPlayers) { return tr ("Number of players");
		} else if ( col == AllyNumTowns) {   return tr ("Number of towns");
		} else if ( col == AllyDef) {        return tr ("Defense bashpoints");
		} else if ( col == AllyOff) {        return tr ("Attack bashpoints");
		} else if ( col == AllyBash) {       return tr ("Total bashpoints");
		} 
	}
	return QVariant();
}
QVariant Ally::itemData   ( int col, int role) const
{
	if (role == Qt::DisplayRole) {
		if ( col == AllyColor) {             return color;
		} else if ( col == AllyName) {       return name;
		} else if ( col == AllyPoints) {     return QString::number(points);
		} else if ( col == AllyNumPlayers) { return QString::number(players.size());
		} else if ( col == AllyNumTowns) {   return QString::number(towns.size());
		} else if ( col == AllyDef) {        return QString::number(def); 
		} else if ( col == AllyOff) {        return QString::number(off);
		} else if ( col == AllyBash) {       return QString::number(bash);
		} 
	} else if (role == Qt::DecorationRole) {

	} else if (role == Qt::ToolTipRole) {
		return headerData (col,role);

	} else if (role == Qt::TextAlignmentRole) {
		if ( col == AllyColor) {
		} else if ( col == AllyName) {      return Qt::AlignLeft;
		} else if ( col == AllyPoints) {    return Qt::AlignRight;
		} else if ( col == AllyNumPlayers) {return Qt::AlignRight;
		} else if ( col == AllyNumTowns) {  return Qt::AlignRight;
		} else if ( col == AllyDef) {       return Qt::AlignRight;
		} else if ( col == AllyOff) {       return Qt::AlignRight;
		} else if ( col == AllyBash) {      return Qt::AlignRight;
		} 
	} else if (role == Qt::CheckStateRole) {
		if ( col == AllyColor)
			return (show)? Qt::Checked : Qt::Unchecked;
	}
	return QVariant();
}


QString Ally::labelText  ( int col, int icon_size ) const 
{
	if ( col == AllyColor) {             
		return QString("<img src=':/icons/icons/color.ico' width=%1 height=%2>&nbsp;<b>#%3</b>")
			.arg(icon_size).arg(icon_size).arg(color.name());
	} else if ( col == AllyName) {       
		return QString("<img src=':/icons/icons/ally.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(name);
	} else if ( col == AllyPoints) {
		return QString("<img src=':/icons/icons/points.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(QString::number(points));
	} else if ( col == AllyNumPlayers) { 
		return QString("<img src=':/icons/icons/player.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(QString::number(players.size()));
	} else if ( col == AllyNumTowns) {   
		return QString("<img src=':/icons/icons/towns.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(QString::number(towns.size()));
	} else if ( col == AllyDef) {        
		return QString("<img src=':/icons/icons/shield.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(QString::number(def));
	} else if ( col == AllyOff) {        
		return QString("<img src=':/icons/icons/sword.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(QString::number(off));
	} else if ( col == AllyBash) {       
		return QString("<img src=':/icons/icons/swords.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(QString::number(bash));
	} 
	return QString ();
}


QStringList Ally::headline      ( const QVector <int> &cols ) 
{
	QStringList r;
	for (int i=0;i< cols.size(); ++i) {
		r.push_back (headerData (cols[i], Qt::DisplayRole).toString());
	}
	return r;
}

QStringList Ally::texts      ( const QVector <int> &cols ) const
{
	QStringList r;
	for (int i=0;i< cols.size(); ++i) {
		if (cols[i] == AllyColor) {	
			r.push_back (color.name());
		} else {		
			r.push_back (itemData (cols[i], Qt::DisplayRole).toString());
		}
	}
	return r;
}

QStringList  Ally::bbCodes    ( const QVector <int> &cols ) const 
{
	QStringList r;
	for(int i=0;i< cols.size(); ++i) 
		if (cols[i] == AllyColor) {	
			r.push_back (color.name());
		} else if (cols[i] == AllyName) {
			r.push_back (QString("[ally]%1[/ally]").arg(name));
		} else {
			r.push_back (itemData (cols[i], Qt::DisplayRole).toString());
		}
		return r;
}

