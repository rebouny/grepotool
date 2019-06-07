/* town_info.cpp - Town database entry widget

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

#include "town_info.h"
#include <GtDatabase.h>
#include <GtWorldData.h>
#include <GtUnits.h>
#include <GtGods.h>
#include <GtHeros.h>
#include <GtTowns.h>
#include "command.h"

TownInfo::TownInfo ():ToolWidget ("TownInfo", tr("Town data")), town(-1)
{
	QFrame * f = new QFrame (this);
	ui.setupUi(f);
	setCentralWidget (f);
	connect (ui._goto,SIGNAL(clicked()), this,SLOT(gotoClicked()));

	bg = new QButtonGroup  (this);
	gods.push_back (ui._any);
	gods.push_back (ui._zeus);
	gods.push_back (ui._poseidon);
	gods.push_back (ui._hera);
	gods.push_back (ui._athene);
	gods.push_back (ui._hades);
	gods.push_back (ui._artemis);
	ui._any->setChecked (true);
	for (int i=0;i< gods.size(); ++i) {
		bg->addButton (gods[i],i);
	}
	ui._any->setIcon (QPixmap (":/icons/gods/anygod.png"));
	ui._zeus->setIcon (QPixmap (":/icons/gods/zeus.png"));
	ui._poseidon->setIcon (QPixmap (":/icons/gods/poseidon.png"));
	ui._hera->setIcon (QPixmap (":/icons/gods/hera.png"));
	ui._athene->setIcon (QPixmap (":/icons/gods/athena.png"));
	ui._hades->setIcon (QPixmap (":/icons/gods/hades.png"));
	ui._artemis->setIcon (QPixmap (":/icons/gods/artemis.png"));
	ui._atlanta->setIcon (QPixmap (":/icons/heroes/atlanta.png"));

	ui._meteorology->setIcon(QPixmap (":/icons/research/meteorology.png"));
	ui._cartography->setIcon(QPixmap (":/icons/research/cartography.png"));
	ui._lighthouse->setIcon(QPixmap (":/icons/buildings/lighthouse.png"));
	bg->setExclusive(true);
	connect (bg, SIGNAL (buttonClicked(int)), this, SLOT(godChanged (int)));


	units.push_back (0 ); // Militia  - just a dummy      
	units.push_back (ui._sword);
	units.push_back (ui._slinger);
	units.push_back (ui._archer);
	units.push_back (ui._hoplite);
	units.push_back (ui._rider);
	units.push_back (ui._chariot);
	units.push_back (ui._catapult);
	units.push_back (ui._slow);
	units.push_back (ui._biri);
	units.push_back (ui._fire);
	units.push_back (ui._brander);
	units.push_back (ui._fast);
	units.push_back (ui._trireme);
	units.push_back (ui._kolo);
	units.push_back (ui._minotaur);
	units.push_back (ui._manti);
	units.push_back (ui._zyklop);
	units.push_back (ui._hydra);
	units.push_back (ui._harpy);
	units.push_back (ui._medusa);
	units.push_back (ui._centaur);
	units.push_back (ui._pega);
	units.push_back (ui._cerberus);     // 
	units.push_back (ui._fury);
	units.push_back (ui._griffin);
	units.push_back (ui._boar);
	units.push_back (ui._godsent);

	special.push_back (ui._meteorology);
	special.push_back (ui._cartography);
	special.push_back (ui._lighthouse);

	for(int i=0;i< special.size(); ++i) {
		connect (special[i],SIGNAL(clicked()),this,SLOT(updateTown()));
	}


	for(int i=1;i< units.size(); ++i) {
		NumEdit * ne = new NumEdit (units[i],0,Unit::unitIconFile ((UnitIndex) i)); 
		edits.push_back(ne);
		ne->setValuePtr(& (ud.val[i]) );
		connect (ne,SIGNAL(valueChanged(int)), this, SLOT(updateTown()));
	}
	
	atlanta = new NumEdit (ui._atlanta, 0 , ":/icons/heroes/atlanta.png"); 
	atlanta->setRange(0,20);
	connect (atlanta,SIGNAL(valueChanged(int)), this, SLOT(updateTown()));
	atlanta->setValuePtr (&(hd.val[Atlanta]));
	godChanged(0);
	selectTown(-1);
}

void TownInfo::worldChanged ()
{
	selectTown(-1);
}

void TownInfo::fillContextMenu (QMenu*)
{
}

void TownInfo::initWidget ()
{
}


void TownInfo::godChanged (int g)
{
	god = (GodIndex) g;
	if (god == AnyGod) {
		ui._minotaur->setEnabled(false);
		ui._manti->setEnabled(false);
		ui._zyklop->setEnabled(false);
		ui._hydra->setEnabled(false);
		ui._harpy->setEnabled(false);
		ui._medusa->setEnabled(false);
		ui._centaur->setEnabled(false);
		ui._pega->setEnabled(false);
		ui._cerberus->setEnabled(false);     // 
		ui._fury->setEnabled(false);
		ui._griffin->setEnabled(false);
		ui._boar->setEnabled(false);
	} else if (god == Zeus) { // zeus
		ui._minotaur->setEnabled(true);
		ui._manti->setEnabled(true);
		ui._zyklop->setEnabled(false);
		ui._hydra->setEnabled(false);
		ui._harpy->setEnabled(false);
		ui._medusa->setEnabled(false);
		ui._centaur->setEnabled(false);
		ui._pega->setEnabled(false);
		ui._cerberus->setEnabled(false);     // 
		ui._fury->setEnabled(false);
		ui._griffin->setEnabled(false);
		ui._boar->setEnabled(false);
	} else if (god == Poseidon) { // 
		ui._minotaur->setEnabled(false);
		ui._manti->setEnabled(false);
		ui._zyklop->setEnabled(true);
		ui._hydra->setEnabled(true);
		ui._harpy->setEnabled(false);
		ui._medusa->setEnabled(false);
		ui._centaur->setEnabled(false);
		ui._pega->setEnabled(false);
		ui._cerberus->setEnabled(false);     // 
		ui._fury->setEnabled(false);
		ui._griffin->setEnabled(false);
		ui._boar->setEnabled(false);
	} else if (god == Athene) { // 
		ui._minotaur->setEnabled(false);
		ui._manti->setEnabled(false);
		ui._zyklop->setEnabled(false);
		ui._hydra->setEnabled(false);
		ui._harpy->setEnabled(false);
		ui._medusa->setEnabled(false);
		ui._centaur->setEnabled(true);
		ui._pega->setEnabled(true);
		ui._cerberus->setEnabled(false);     // 
		ui._fury->setEnabled(false);
		ui._griffin->setEnabled(false);
		ui._boar->setEnabled(false);
	} else if (god == Hera) { // 
		ui._minotaur->setEnabled(false);
		ui._manti->setEnabled(false);
		ui._zyklop->setEnabled(false);
		ui._hydra->setEnabled(false);
		ui._harpy->setEnabled(true);
		ui._medusa->setEnabled(true);
		ui._centaur->setEnabled(false);
		ui._pega->setEnabled(false);
		ui._cerberus->setEnabled(false);     // 
		ui._fury->setEnabled(false);
		ui._griffin->setEnabled(false);
		ui._boar->setEnabled(false);
	} else if (god == Hades) { // 
		ui._minotaur->setEnabled(false);
		ui._manti->setEnabled(false);
		ui._zyklop->setEnabled(false);
		ui._hydra->setEnabled(false);
		ui._harpy->setEnabled(false);
		ui._medusa->setEnabled(false);
		ui._centaur->setEnabled(false);
		ui._pega->setEnabled(false);
		ui._cerberus->setEnabled(true);     // 
		ui._fury->setEnabled(true);
		ui._griffin->setEnabled(false);
		ui._boar->setEnabled(false);
	} else if (god == Artemis) { //
		ui._minotaur->setEnabled(false);
		ui._manti->setEnabled(false);
		ui._zyklop->setEnabled(false);
		ui._hydra->setEnabled(false);
		ui._harpy->setEnabled(false);
		ui._medusa->setEnabled(false);
		ui._centaur->setEnabled(false);
		ui._pega->setEnabled(false);
		ui._cerberus->setEnabled(false);     // 
		ui._fury->setEnabled(false);
		ui._griffin->setEnabled(true);
		ui._boar->setEnabled(true);
	}
	updateTown ();
}

TownInfo::~TownInfo ()
{
}

void TownInfo::selectTown (int idx)
{

	// if (town == idx) return;
	static bool sem = false;
	if (sem) return;
	sem = true;
	town = idx;

	ui._town->setText (WorldData::currentWorld().TownLabelText (town,false));

	if(town<0) {
		ud = UnitData ();
		rd = ResearchData ();
		bd = BuildingData ();
		hd = HeroData ();
		god = AnyGod;
		for (int i=0;i< special.size(); ++i) special[i]->setEnabled(false);
		for (int i=1;i< units.size(); ++i) units[i]->setEnabled(false);
		for (int i=1;i < gods.size(); ++i) gods[i]->setEnabled(false);
		ui._any->setChecked(true);
		sem=false;		
		return;
	} else {
		for (int i=0;i < special.size(); ++i) special[i]->setEnabled(true);
		for (int i=1;i < units.size(); ++i) units[i]->setEnabled(true);
		Town& to = WorldData::currentWorld().towns()[idx];
		int pi = to.player_id;
		god = AnyGod;
		ud = to.units();
		hd = to.heros();
		rd = to.research();
		bd = to.buildings();
		if (to.data){
			int go = to.data->god;
			if (go>=0 && go < 7) 
				god = (GodIndex) go;
			to.setGod (god);
		}

		atlanta->setValuePtr (&(hd.val[Atlanta]));

		for(int i=1;i< units.size(); ++i) {
			edits[i-1]->setValuePtr(& (ud.val[i]) );
		}
		

		if (pi<0) {
			ui._any->setChecked(true);
			for (int i=1;i < gods.size(); ++i) gods[i]->setEnabled(false);
			for (int i=15;i<=26; ++i) units[i]->setEnabled(false);

		} else {
			for (int i=0;i < gods.size(); ++i) gods[i]->setEnabled(true);
			gods[god]->setChecked (true);
			
			ui._lighthouse->setChecked (bd.val[Lighthouse]>0);
			ui._cartography->setChecked (rd.val[ResearchCartography]);
			ui._meteorology->setChecked (rd.val[ResearchMeteorology]);
		}		
	}
	sem=false;
}

void TownInfo::updateTown ()
{
	if (town == -1) return;

	Town& to = WorldData::currentWorld().towns()[town];

	// to.movement_boost = ui._movement_boost->isChecked ();

	bd.val[Lighthouse] = ui._lighthouse->isChecked ()? 1: 0;
	rd.val[ResearchCartography] = ui._cartography->isChecked ();
	rd.val[ResearchMeteorology] = ui._meteorology->isChecked ();

	to.setGod(god);
	to.setBuildings(bd);
	to.setHeros(hd);
	to.setUnits(ud);
	to.setResearch(rd);
	
	emit townChangedSignal (town);
}
