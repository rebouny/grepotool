#ifndef ___TOWN_INFO_H
#define ___TOWN_INFO_H
/* town_info.h  - Town database widget

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
#include<GtTowns.h>
#include "toolwidget.h"
#include "popup.h"
#include "ui_town_info.h"


#include <QToolButton>
#include <QSpinBox>
#include <QPainter>



class NumEdit;

class TownInfo : public ToolWidget {
	Q_OBJECT;
public:

	TownInfo ();
	~TownInfo ();

	void fillContextMenu (QMenu*);

	void worldChanged ();
	void initWidget ();

public slots:

	void selectTown (int idx);
	void updateTown ();

	void godChanged (int);
	void gotoClicked () {
		if(town>=0) 
			emit gotoTownSignal (town);
	};

signals:
	void townChangedSignal(int);
    
private:
	Ui::TownInfo ui;
	int town;
	UnitData     ud;
	BuildingData bd;
	ResearchData rd;
	HeroData     hd;
	GodIndex     god;

	QVector <QToolButton*> units;
	QVector <NumEdit*>     edits;
	NumEdit* atlanta;
	QVector <QToolButton*> gods;
	QVector <QToolButton*> special;
	QButtonGroup * bg;
};


#endif