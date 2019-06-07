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

#include <QFileInfo>
#include <QVariantMap>

#include "GtBookmarks.h"

Bookmark& Bookmark::operator =  (const Bookmark&o)
{
	type  = o.type;
	player = o.player;
	town =o.town; 
	ally = o.ally;
	return *this;
};


int Bookmark:: numColumns        ()
{
	return BmMax;
}
int Bookmark::defaultSortColumn ()
{
	return BmPoints;
}
Qt::SortOrder     Bookmark::defaultSortOrder  ()	
{
	return Qt::DescendingOrder;
}
bool Bookmark::canHideColumn     (int col)
{
	// if (col == BmColor) return false;
	if (col == BmName) return false;
	return true;
}
QVariant Bookmark::headerData ( int col, int role)
{
	QVariant r;

	if (role == Qt::DisplayRole) {
		if ( col == BmColor) {             return tr ("Color");
		} else if ( col == BmName) {       return tr ("Bookmark");
		} else if ( col == BmPoints) {     return tr ("Points");
		} else if ( col == BmPlayerName) { return tr ("Player");
		} else if ( col == BmAllyName)   { return tr ("Ally");
		} 
	} else if (role == Qt::DecorationRole) {
		if ( col == BmColor) {             return QIcon(":/icons/icons/color.ico") ;
		//} else if ( col == BmName) {       return QIcon(":/icons/icons/ally.ico") ;
		} else if ( col == BmPoints) {     return QIcon(":/icons/icons/points.ico") ;
		} else if ( col == BmPlayerName) {     return QIcon(":/icons/icons/player.ico") ;
		} else if ( col == BmAllyName) {     return QIcon(":/icons/icons/ally.ico") ;
		} 
	} else if (role == Qt::ToolTipRole) {
		if ( col == BmColor) {             return tr ("Color of allys and players");
		} else if ( col == BmName) {       return tr ("Bookmark name");
		} else if ( col == BmPoints) {     return tr ("Points");
		} else if ( col == BmPlayerName) { return tr ("Player");
		} else if ( col == BmAllyName)   { return tr ("Ally");
		} 
	}
	return QVariant();

}
QVariant Bookmark::itemData   ( int col, int role) const
{
	if(type == BmAlly) {

		if (role == Qt::DisplayRole) {
			if ( col == BmColor) {             return ally->color;
			} else if ( col == BmName) {       return ally->name;
			} else if ( col == BmPoints) {     return QString::number(ally->points);
			} else if ( col == BmPlayerName) { return QVariant();
			} else if ( col == BmAllyName)   { return QVariant();
			} 
		} else if (role == Qt::DecorationRole) {
			if ( col == BmName)     return QPixmap(":/icons/icons/ally.ico").scaled(QSize(16,16)) ;
		} else if (role == Qt::CheckStateRole) {
			if ( col == BmColor)
				return (ally->show)? Qt::Checked : Qt::Unchecked;
		}
	} else if(type == BmPlayer) {

		if (role == Qt::DisplayRole) {
			if ( col == BmColor) {             return player->color;
			} else if ( col == BmName) {       return player->name;
			} else if ( col == BmPoints) {     return QString::number(player->points);
			} else if ( col == BmPlayerName) { 
			} else if ( col == BmAllyName)   { return player->ally_name;
			} 
		} else if (role == Qt::DecorationRole) {
			if ( col == BmName)     return QPixmap(":/icons/icons/player.ico").scaled(QSize(16,16));
		} else if (role == Qt::CheckStateRole) {
			if ( col == BmColor)
				return (player->show)? Qt::Checked : Qt::Unchecked;
		}
	} else if(type == BmTown) {

		if (role == Qt::DisplayRole) {
			if ( col == BmColor) {             return QVariant ();
			} else if ( col == BmName) {       return town->name;
			} else if ( col == BmPoints) {     return QString::number (town->points);
			} else if ( col == BmPlayerName) { return town->player_name;
			} else if ( col == BmAllyName)   { return town->ally_name;
			} 
		} else if (role == Qt::DecorationRole) {
			if ( col == BmName) {
				if(town->ghost) 
					return QPixmap(":/icons/icons/ghost.ico").scaled(QSize(16,16));
				else
					return QPixmap(":/icons/icons/town.ico").scaled(QSize(16,16)) ;
			}
		}
    } else if(type == BmHeat) {

        if (role == Qt::DisplayRole) {
            if ( col == BmColor) {             return QVariant ();
            } else if ( col == BmName) {       return town->name;
            } else if ( col == BmPoints) {     return QString::number (town->points);
            } else if ( col == BmPlayerName) { return town->player_name;
            } else if ( col == BmAllyName)   { return town->ally_name;
            }
        } else if (role == Qt::DecorationRole) {
            if ( col == BmName) {
                if(town->ghost)
                    return QPixmap(":/icons/icons/ghost.ico").scaled(QSize(16,16));
                else
                    return QPixmap(":/icons/icons/town.ico").scaled(QSize(16,16)) ;
            }
        }
    }
    return QVariant();
}

QStringList  Bookmark::headline   ( const QVector <int> &cols ) 
{

	QStringList r;
	for (int i=0;i< cols.size(); ++i) {
		r.push_back (headerData (cols[i], Qt::DisplayRole).toString());
	}
	return r;

}
QStringList Bookmark::texts      ( const QVector <int> &cols ) const  
{
	QStringList r;
	for (int i=0;i< cols.size(); ++i) {
		QString tx = itemData (cols[i], Qt::DisplayRole).toString();
		if (cols[i] == BmColor) {	
			if (type==BmAlly) tx = (ally->color.name());
			else if(type==BmPlayer) tx = (player->color.name());
			else tx= (" -- ");
		}
		r.push_back  (tx);
	}
	return r;

}
QStringList Bookmark::bbCodes    ( const QVector <int> &cols ) const 
{
	QStringList r = texts(cols);
	for(int i=0;i< cols.size(); ++i) {
		if (cols[i] == BmColor) {	
		} else if (cols[i] == BmName) {
			if (type == BmAlly)        r[i]= QString("[ally]%1[/ally]").arg(ally->name);
			else if (type == BmPlayer) r[i]= QString("[player]%1[/player]").arg(player->name);
			else if (type == BmTown)   r[i]= QString("[town]%1[/town]").arg(town->id);
		} else if (cols[i] == BmAllyName) {
			if (type == BmPlayer)      r[i]= (QString("[ally]%1[/ally]").arg(player->ally_name));
			else if (type == BmTown)   r[i]= (QString("[ally]%1[/ally]").arg(town->ally_name));
		} else if (cols[i] == BmPlayerName) {
			if (type == BmTown) 
				r[i]= QString("[player]%1[/player]").arg(town->player_name);
		}
	}
	return r;

}
QString Bookmark::labelText  ( int col, int icon_size  ) const
{

	return "";
}

void Bookmark::unBookmark()
{
	if (type == BmAlly) ally->bookmark = false;
	else if (type == BmPlayer) player->bookmark = false; 
	else if (type == BmTown) town->bookmark = false;	
}


int Bookmark::compare (const Bookmark&o, int col) const
{
	if (type == BmAlly) {
		if (o.type == BmAlly) {
			if ( col == BmColor) {             return ally->compare(*o.ally, Ally::AllyColor);
			} else if ( col == BmName) {       return ally->compare(*o.ally, Ally::AllyName);
			} else if ( col == BmPoints) {     return ally->compare(*o.ally, Ally::AllyPoints);
			} else if ( col == BmPlayerName) { return 0;
			} else if ( col == BmAllyName)   { return 0;
			} 
		} else if (o.type == BmPlayer) {
			return 1;
		} else if (o.type == BmTown) {
			return 1;
		}
	} else if (type == BmPlayer) {
		if (o.type == BmAlly) {
			return -1;
		} else if (o.type == BmPlayer) {
			if ( col == BmColor) {             return player->compare(*o.player, Player::PlayerColor);
			} else if ( col == BmName) {       return player->compare(*o.player, Player::PlayerName);
			} else if ( col == BmPoints) {     return player->compare(*o.player, Player::PlayerPoints);
			} else if ( col == BmPlayerName) { return 0;
			} else if ( col == BmAllyName)   { return player->compare(*o.player, Player::PlayerAllyName);
			} 
		} else if (o.type == BmTown) {
			return 1;
		}
	} else if (type == BmTown) {
		if (o.type == BmAlly) {
			return -1;
		} else if (o.type == BmPlayer) {
			return -1;
		} else if (o.type == BmTown) {
			if ( col == BmColor) {             return 0;
			} else if ( col == BmName) {       return town->compare(*o.town, Town::TownName);
			} else if ( col == BmPoints) {     return town->compare(*o.town, Town::TownPoints);
			} else if ( col == BmPlayerName) { return town->compare(*o.town, Town::TownPlayerName);
			} else if ( col == BmAllyName)   { return town->compare(*o.town, Town::TownAllyName);
			} 
		}
	}
	return 0;
}
