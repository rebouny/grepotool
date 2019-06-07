#ifndef ___DATA_H
#define ___DATA_H
/* data.h  - data handling

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

/*
enum LocFilterType {
	LocWorld,
	LocOcean,
	LocRegion,
	LocMaxDistance
};

enum PlayerFilter {
	AllPlayers,
	Allyless,
	ByAlly
};
*/
// filter allys    by  loctation playerfilter+id player-activity 
//        players  by  loctation playerfilter+id player-activity 
//        towns    by  loctation playerfilter+id player-activity/ghosts

/*! Types of data displaied in table cells
enum TableItemType {  // meaning               internal      sort indexing   used
	ItemColorSel,     // color + checkbox      QColor&bool   bool            
	ItemText,         // names                 QString       rank_index      names  
	ItemNumber,       // formatted number      number        int             number ocean / points 
	ItemIconText,     // single icon+text      int / enum    int             town type / slowest unit / allive / dead
	ItemTime,         // seconds               time_t(int)   time_t(int)     travel time / activity entries  
	ItemDateTime,     // Date time             time_t(int)   time_t(int)     arrival / departure / first obs / last obs
	ItemIconList      // units, town spec.     Struct        ---             units / specials / buildings etc.
};
*/

// towns    col points town_name player_name ally_name                                     first_obs last_obs allive ocean island units buildings research heros god tactical_type reports
// allys    col points                       ally_name num_players num_towns def off total first_obs last_obs allive  
// players  col points           player_name ally_name             num_towns def off total first_obs last_obs allive points_act def_act off_act act 
/*



enum TownFilter {
	AllTowns,
	GhostTowns, 
	AllylessTowns,
	TownsOfAlly,
	TownsOfPlayer,
	TownsOfInactivePlayers, 
	TownsOfInactivePlayersOfAlly 
};

enum LocationFilter {
	LocWorld,
	LocOcean,
	LocMaxDistance
};

*/
#endif