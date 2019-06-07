/* simulator.cpp - fight sim

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
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QWheelEvent>
#include <QGridLayout>
#include <QtCore/QtMath>
#include "report_model.h"
#include "simulator.h"
#include "GtWorlddata.h"
#include "GtTowns.h"
#include "GtPlayers.h"
#include "GtAllys.h"

void Simulator::simulate (const BonusData &att_boni,
		const BonusData &def_boni,
		const UnitData &at,
		const UnitData &de,
		int &wall_loss,
		UnitData &att_l,
		UnitData &def_l)
{
	UnitData att = at;
	UnitData def = de;
	double sea_att = att.attValue (Naval,att_boni);
	double sea_def = def.defValue (Naval,def_boni);
	double att_loss = 0.0;
	double def_loss = 0.0;

	bool seafight = (att.seaUnits().bhp() > 0); 
	bool seafight_lost = false;
	bool landfight = (att.landFightUnits().bhp() > 0); 
	bool landfight_lost = false;

	if (seafight) {

		if (sea_att > sea_def) {

			// total loss of defender ships
			def.val [Bireme]     = 0;
			def.val [Attackship] = 0;
			def.val [Trireme]    = 0;
			def.val [Hydra]      = 0;

            att_loss = qPow (sea_def / sea_att, 1.2);
			att.val [Bireme]     *= 1.0 - att_loss;
			att.val [Attackship] *= 1.0 - att_loss;
			att.val [Trireme]    *= 1.0 - att_loss;
			att.val [Hydra]      *= 1.0 - att_loss;

			// handle demolition ships
			int nb = att.val [Bireme] +att.val [Attackship] + att.val [Trireme];
			int br = def.val[Brander] ;

			while (nb && br) {
				if 	(br && att.val [Bireme]) {--br;--nb; --att.val [Bireme];}
				if 	(br && att.val [Trireme]) {--br;--nb; --att.val [Trireme];}
				if 	(br && att.val [Attackship]) {--br;--nb; --att.val [Attackship];}				
			}

		} else {

			seafight_lost = true;

			// total loss of attacker ships
			att.val [Bireme]     = 0;
			att.val [Attackship] = 0;
			att.val [Trireme]    = 0;
			att.val [Hydra]      = 0;

			// a potential colonize ship will be gone
			att.val [Kolo]       = 0;

            def_loss = qPow (sea_att / sea_def, 1.2);
			def.val [Bireme]     *= 1.0 - def_loss;
			def.val [Attackship] *= 1.0 - def_loss;
			def.val [Trireme]    *= 1.0 - def_loss;
			def.val [Hydra]      *= 1.0 - def_loss;

			// + loss of attacker land units and transporters:
			att_loss = (sea_def-sea_att)/(sea_att+sea_def);

			for (int i=0;i<UnitMax;++i) {
				if (isFlyingUnit((UnitIndex)i)) continue;
				att.val [i]   *= 1.0 - att_loss;
			}			
		}
	}

	// Landfight


	// Wall effect is at least 1.037^(wall/2) 
	//                at most  1.037^(wall) 
	// depending on number of katas: 

	int wall = def_boni.val[BonusWall];
	double wall_eff = wall;
	if (att.val[Kata]) {
		wall_eff = 2 * wall - att.val[Kata];
		if (wall_eff < wall) wall_eff = wall;
		wall_eff /= 2;
	}
    wall_eff = qPow (1.037,wall_eff);

	double wall_base = 10.0 * (def_boni.val[BonusWall] +1) ;

	double hack_att = att.attValue (Hack,att_boni);
	double hack_def = def.defValue (Hack,def_boni)*wall_eff+wall_base;
	double pierce_att = att.attValue (Pierce,att_boni);
	double pierce_def = def.defValue (Pierce,def_boni)*wall_eff+wall_base;
	double dist_att = att.attValue (Distance,att_boni);
	double dist_def = def.defValue (Distance,def_boni)*wall_eff+wall_base;
	
	double bv = 0;
	if (hack_att)   bv += hack_att/hack_def;
	if (pierce_att) bv += pierce_att/pierce_def;
	if (dist_att)   bv += dist_att/dist_def;
	
	def_loss = pow(bv,1.2);
	if (def_loss > 1.0) def_loss = 1.0;

	for (int i=0;i<UnitMax;++i) {
		if (isSeaUnit((UnitIndex)i)) continue;
		def.val[i] *= 1.0 - def_loss;
	}
		
	double tot_att = hack_att + pierce_att + dist_att;

	double hack_loss   = 0.0;
	double pierce_loss = 0.0;
	double dist_loss   = 0.0;
	if (hack_att)          hack_loss   = pow (hack_def / tot_att , 1.2 );
	if (pierce_att)        pierce_loss = pow (pierce_def / tot_att , 1.2 );
	if (dist_att)          dist_loss   = pow (dist_def / tot_att , 1.2 );
	if (hack_loss > 1.0)   hack_loss   = 1.0;
	if (pierce_loss > 1.0) pierce_loss = 1.0;
	if (dist_loss > 1.0)   dist_loss   = 1.0;

	for (int i=0;i<UnitMax;++i) {
		if (isSeaUnit((UnitIndex)i)) continue;
		
		AttackTypeIndex attack_type = WorldData::currentWorld ().unit((UnitIndex)i).attack_type;

		if (attack_type == Pierce) 
			att.val [i]   *= 1.0 - pierce_loss;
		if (attack_type == Hack) 
			att.val [i]   *= 1.0 - hack_loss;
		if (attack_type == Distance) 
			att.val [i]   *= 1.0 - dist_loss;
	}			

	// if some defender units remain, the landfight is lost
	landfight_lost = def.landFightUnits().bhp() > 0;

	// handle loss of kolo and transporters of defender if both fights are won
	if (seafight && !seafight_lost && !landfight_lost) {
		def.val[Transporter] = 0;
		def.val[FastTransporter] = 0;
		def.val[Kolo] = 0;
	}


	def_l = de - def;
	att_l = at - att;
}


NumberedLabel::NumberedLabel (const QString& iconfile, int min, int max, int & v, int & vd):ico(iconfile),minv(min),maxv(max),val(v),val_d(vd),dab(false)
{
	lab = new QLabel;
	QGridLayout * l = new QGridLayout ;
	l->setMargin(0);
	l->addWidget(lab,0,0);
	setLayout (l);
	setValue (minv);
}
	

CheckedLabel::CheckedLabel (const QString& iconfile, int & vd):ico(iconfile),val(vd)
{
	lab = new QLabel;
	QGridLayout * l = new QGridLayout ;
	l->setMargin(0);
	l->addWidget(lab,0,0);
	setLayout (l);
	setValue (vd);
}
void CheckedLabel::updatePixmap ()
{
	QPixmap ic = QPixmap(ico).scaled(40,40);
	QImage im (ic.toImage());
	QIcon icc (QPixmap::fromImage(im));
	if(!val) lab->setPixmap (icc.pixmap (40,40, QIcon::Disabled));
	else lab->setPixmap (icc.pixmap (40,40));
}
void CheckedLabel::setValue (int v)
{
	val = v;
	updatePixmap ();
	emit valueChanged (val);
}

void CheckedLabel::mousePressEvent (QMouseEvent* ) 
{
}

void CheckedLabel::mouseReleaseEvent (QMouseEvent* ) 
{
	if(val) setValue (0);
	else setValue (1);
}
	

void NumberedLabel::updatePixmap ()
{
	QPixmap ic = QPixmap(ico).scaled(40,40);
	QImage im (ic.toImage());
	QPainter p (&im);
	QFont f = p.font();
	f.setBold(true);
	f.setPixelSize(14);
	if(val > 9999) {
		f.setPixelSize(11);
	}
	p.setFont(f);
	if (val)
		renderText (&p, QPoint(2, im.height()/2-4), QString::number(val), Qt::black, Qt::white);

	f.setPixelSize(14);
	if(val_d > 9999) {
		f.setPixelSize(11);
	}
	p.setFont(f);
	if(val_d)
		renderText (&p, QPoint(2, im.height()-4), QString("-%1").arg(val_d), Qt::black, Qt::white);	

	QIcon icc (QPixmap::fromImage(im));

	if(!val_d && !val) lab->setPixmap (icc.pixmap (40,40, QIcon::Disabled));
	else lab->setPixmap (icc.pixmap (40,40));
}
void NumberedLabel::setValue (int v)
{
	val = v;
	updatePixmap ();
	emit valueChanged (val);
}


void NumberedLabel::setValueDead (int v)
{
	val_d = v;
	updatePixmap ();
	emit valueDeadChanged (val);
}


void NumberedLabel::wheelEvent (QWheelEvent* e) 
{
	if (!dab) {
		val += e->delta() / 120.0;
		if(val<minv) val = minv;
		if(val>maxv) val = maxv;
		setValue (val);
	} else {
		val_d += e->delta() / 120.0;
		if(val<minv) val_d = minv;
		if(val>maxv) val_d = maxv;
		setValueDead (val_d);
	}
}

void NumberedLabel::mousePressEvent (QMouseEvent* ) 
{

}

void NumberedLabel::mouseReleaseEvent (QMouseEvent* ) 
{

}



Simulator::Simulator () : ToolWidget ("Simulator", tr("Report simulator") )
{

	QFrame * f= new QFrame ;
	ui.setupUi (f);
	_wall_loss = 0;

	_hide_act = new QAction (tr("Report simulator"), this);
	connect (_hide_act,SIGNAL(triggered()), this,SLOT(popToFront()));

	ui.att_ico->setPixmap(QPixmap(":/icons/icons/swords.ico"));
	ui.def_ico->setPixmap(QPixmap(":/icons/icons/shield.ico"));

	for(int i=0;i< UnitMax; ++i) {
		UnitIndex ui = (UnitIndex) i;
		_att.push_back (new NumberedLabel (Unit::unitIconFile(ui),0,5000,att.val[i],att_loss.val[i]));
		_def.push_back (new NumberedLabel (Unit::unitIconFile(ui),0,5000,def.val[i],def_loss.val[i]));
	}

	QGridLayout *la = new QGridLayout;
	QGridLayout *lb = new QGridLayout;
	la->setMargin(0);
	lb->setMargin(0);

	UnitIndex l0[7] = {Transporter,Bireme,Attackship,Brander,FastTransporter,Trireme,Kolo};
	UnitIndex l1[7] = {Sword,Slinger,Archer,Hoplite,Rider,Chariot,	Kata};
	UnitIndex l3[7] = {Godsent,Minotaur,Zyklop,Harpy,Centaur,Zerberus,Griffin};
	UnitIndex l4[7] = {Militia,Manti,Hydra,Medusa,Pegasus,	Eriny,Kalydonian};
	for(int i= 0; i < 7; ++i) {
		la->addWidget (_att[l0[i]], 0, i);
		la->addWidget (_att[l1[i]], 1, i);
		la->addWidget (_att[l3[i]], 2, i);
		la->addWidget (_att[l4[i]], 3, i);
		lb->addWidget (_def[l0[i]], 0, i);
		lb->addWidget (_def[l1[i]], 1, i);
		lb->addWidget (_def[l3[i]], 2, i);
		lb->addWidget (_def[l4[i]], 3, i);
	}
	_att[Militia]->hide();
		
	ui.att_mid->setLayout (la);
	ui.def_mid->setLayout (lb);

	ld_zero = 0;
	_luck = new NumberedLabel (":/icons/icons/luck.png",-30, 30, att_boni.val[BonusLuck],ld_zero);
	_morale = new NumberedLabel (":/icons/icons/morale.png",0, 100, att_boni.val[BonusMorale], ld_zero);
	_att_priest = new CheckedLabel (":/icons/premium/priest.png", att_boni.val[BonusPriest]);
	_att_commander = new CheckedLabel (":/icons/premium/commander.png",att_boni.val[BonusCommander]);
	_att_captain = new CheckedLabel (":/icons/premium/captain.png", att_boni.val[BonusCaptain]);
	_att_phalanx = new CheckedLabel (":/icons/research/phalanx.png", att_boni.val[BonusPhalanx]);
	_att_ram = new CheckedLabel (":/icons/research/ram.png", att_boni.val[BonusRam]);

	_att_boost = new NumberedLabel (":/icons/spells/attack_boost.png",0, 30, att_boni.val[BonusAttBoost],ld_zero);
	_att_longterm_boost = new CheckedLabel (":/icons/spells/longterm_attack_boost.png", att_boni.val[BonusLongtermAttBoost]);
	_hero_strength = new CheckedLabel (":/icons/spells/hero_power.png", att_boni.val[BonusHeroStrength]);
	_fair_wind = new CheckedLabel (":/icons/spells/fair_wind.png", att_boni.val[BonusFairWind]);
	_desire = new CheckedLabel (":/icons/spells/desire.png", att_boni.val[BonusDesire]);
	_myrmidonian = new CheckedLabel (":/icons/spells/mirmidion_attack.png", att_boni.val[BonusMyrmidionAtt]);

	_wall  = new NumberedLabel (":/icons/buildings/wall.png",0, 30, def_boni.val[BonusWall], _wall_loss);
	_night = new CheckedLabel (":/icons/icons/night.png", def_boni.val[BonusNight]);
	_def_priest = new CheckedLabel (":/icons/premium/priest.png", def_boni.val[BonusPriest]);
	_def_commander = new CheckedLabel (":/icons/premium/commander.png",def_boni.val[BonusCommander]);
	_def_captain = new CheckedLabel (":/icons/premium/captain.png", def_boni.val[BonusCaptain]);
	_def_phalanx = new CheckedLabel (":/icons/research/phalanx.png", def_boni.val[BonusPhalanx]);
	_def_ram = new CheckedLabel (":/icons/research/ram.png", def_boni.val[BonusRam]);

	_tower = new CheckedLabel (":/icons/buildings/tower.png", def_boni.val[BonusTower]);
	_trojan= new CheckedLabel (":/icons/spells/trojan_defense.png", def_boni.val[BonusTrojanDef]);
	_def_boost = new NumberedLabel (":/icons/spells/defense_boost.png",0, 30, def_boni.val[BonusDefBoost],ld_zero);
	_def_longterm_boost = new CheckedLabel (":/icons/spells/longterm_defense_boost.png", def_boni.val[BonusLongtermDefBoost]);

	QGridLayout *la1 = new QGridLayout;
	QGridLayout *lb1 = new QGridLayout;
	la1->setMargin(0);
	lb1->setMargin(0);

	int col = 0;
	int row = 0;
	la1->addWidget (_luck, 0, col++);
	la1->addWidget (_morale, 0, col++);
	la1->addWidget (_att_priest, 0, col++);
	la1->addWidget (_att_commander, 0, col++);
	la1->addWidget (_att_captain, 0, col++);
	la1->addWidget (_att_phalanx, 0, col++);
	la1->addWidget (_att_ram, 0, col++);
	++row;col=0;
	la1->addWidget (_hero_strength, row, col++);
	la1->addWidget (_fair_wind, row, col++);
	la1->addWidget (_desire, row, col++);
	la1->addWidget (_att_boost, row, col++);
	la1->addWidget (_att_longterm_boost, row, col++);
	la1->addWidget (_myrmidonian, row, col++);
	
	col = 0;
	row = 0;
	lb1->addWidget (_wall, row, col++);
	lb1->addWidget (_night, row, col++);
	lb1->addWidget (_def_priest, row, col++);
	lb1->addWidget (_def_commander, row, col++);
	lb1->addWidget (_def_captain, row, col++);
	lb1->addWidget (_def_phalanx, row, col++);
	lb1->addWidget (_def_ram, row, col++);
	row++;col = 0;
	lb1->addWidget (_tower, row, col++);
	lb1->addWidget (_trojan, row, col++);
	lb1->addWidget (_def_boost, row, col++);
	lb1->addWidget (_def_longterm_boost, row, col++);

	ui.att_bottom->setLayout (la1);
	ui.def_bottom->setLayout (lb1);

	for (int i=0;i< BonusMax; ++i) {
		_att_boni[i] = 0;
		_def_boni[i] = 0;
	}

	_att_boni[BonusLuck] = _luck;
	_att_boni[BonusMorale] = _morale;
	_att_boni[BonusPriest] = _att_priest;
	_att_boni[BonusCommander] = _att_commander;
	_att_boni[BonusCaptain] = _att_captain;
	_att_boni[BonusPhalanx] = _att_phalanx;
	_att_boni[BonusRam] = _att_ram;
	_att_boni[BonusAttBoost] = _att_boost;
	_att_boni[BonusLongtermAttBoost] = _att_longterm_boost;
	_att_boni[BonusHeroStrength] = _hero_strength;
	_att_boni[BonusFairWind] = _fair_wind;
	_att_boni[BonusDesire] = _desire;
	_att_boni[BonusMyrmidionAtt] = _myrmidonian;

	_def_boni[BonusWall] = _wall;
	_def_boni[BonusNight] = _night;
	_def_boni[BonusPriest] = _def_priest;
	_def_boni[BonusCommander] = _def_commander;
	_def_boni[BonusCaptain] = _def_captain;
	_def_boni[BonusPhalanx] = _def_phalanx;
	_def_boni[BonusRam] = _def_ram;
	_def_boni[BonusTower] = _tower;
	_def_boni[BonusTrojanDef] = _trojan;
	_def_boni[BonusDefBoost] = _def_boost;
	_def_boni[BonusLongtermDefBoost] = _def_longterm_boost;
	for (int i=0;i< BonusMax; ++i) {
		if(_att_boni[i] ) _att_boni[i] ->setToolTip (BonusData::toolTip ((BonusIndex) i));
		if(_def_boni[i] ) _def_boni[i] ->setToolTip (BonusData::toolTip ((BonusIndex) i));
	}
	connect(ui.tb1,SIGNAL(clicked()), this, SLOT(simulate()));
	connect(ui.tb2,SIGNAL(clicked()), this, SLOT(reset()));
	connect(ui.tb3,SIGNAL(clicked()), this, SLOT(reverse()));
	ui.tb1->setToolTip (tr("Simulate"));
	ui.tb2->setToolTip (tr("Reset all values"));
	ui.tb3->setToolTip (tr("Reverse simulation"));
	ui.tb3->setEnabled(false);
	updateGeometry ();
	setCentralWidget (f);
	reset ();
}
void Simulator::reset ()
{
	att = UnitData();
	def = UnitData ();
	att_loss = UnitData();
	def_loss = UnitData ();
	att_boni= BonusData();
	att_boni.val[BonusMorale] = 100;
	att_boni.val[BonusLuck] = 0;
	def_boni= BonusData();
	_wall_loss = 0;
	updateDisplay ();
}

void Simulator::reverse ()
{
	if (!wall_diff.wall() || !rep.att()) return;
	UnitData att_units = rep.att()->att_units;
	UnitData att_loss_units = rep.att()->att_unit_loss;
	UnitData wd_att_loss_units = wall_diff.wall()->lost_as_att;
	if(wd_att_loss_units != att_loss_units) return;

	double sea_loss_fkt = 1.0;
	double k = att_loss_units.val[FastTransporter]; 
	double ok = att_units.val[FastTransporter];
	if (k) {
		sea_loss_fkt = (ok-k)/ k; 			
	} else {
		k = att_loss_units.val[Transporter]; 
		ok = att_units.val[Transporter];
		if (k) {
			sea_loss_fkt = (ok-k)/ k; 			
		}
	}

	UnitData def_units = rep.att()->def_units;
	UnitData def_loss_units = rep.att()->def_unit_loss;
	UnitData wd_def_loss_units = wall_diff.wall()->killed_as_att;

	UnitData sea_att = att_units.seaUnits();
	UnitData land_att = att_units.landFightUnits();
	UnitData sea_att_loss = att_loss_units.seaAttUnits();
	UnitData land_att_loss = att_loss_units.landFightUnits();

	UnitData sea_def = def_units.seaUnits();
	UnitData land_def = def_units.landFightUnits();
	UnitData sea_def_loss = wd_def_loss_units.seaDefUnits();
	UnitData land_def_loss = wd_def_loss_units.landFightUnits();

	double ufac [UnitMax];
	double uland [UnitMax];
	double cnt = 0.0;	
	double miv = 0.0;	
	UnitData attu = land_att;
	UnitData defu;
	UnitData defl;
	UnitData attl;

	for (int i=0;i< UnitMax;++i) {
		attu.val[i] =  sea_loss_fkt * attu.val[i];
		ufac[i] = land_def_loss.val[i];
		cnt += ufac[i];
		if(ufac[i]) {
			if( miv == 0.0 || ufac[i] < miv) 
				miv = ufac[i];
		}
	}
	if (cnt < 1.0) return;
	for (int i=0;i< UnitMax;++i) {
		ufac[i] /= miv;
		uland[i] = ufac[i];
		defu.val[i] = ufac[i];
	}
	int wl=0;
	bool redo = true;
	while (redo) {
		++wl;
		if(wl> 10000) redo = false;
		simulate (att_boni,def_boni,attu,defu,wl,attl,defl);
		if(attl.bhp() >= land_att_loss.bhp()) break;
		for (int i=0;i< UnitMax;++i) {
			uland[i] += ufac[i];
			defu.val[i] = uland[i];
		}
	}
	for (int i=0;i< UnitMax;++i) {
		if(defu.val[i]) def.val[i] = defu.val[i];
	}

	updateDisplay ();
}


void Simulator::simulate ()
{
	setWindowTitle ( tr("Simulation") );
	ui.att->setText(QString("<b>%1</b>").arg(tr("Attacker")));
	ui.def->setText(QString("<b>%1</b>").arg(tr("Defender")));
	
	simulate (att_boni, def_boni,att,def,_wall_loss,att_loss,def_loss);
	updateDisplay ();
}



void Simulator::updateDisplay () 
{
	for(int i=0;i< UnitMax; ++i) {
		_att[i]->updatePixmap ();
		_def[i]->updatePixmap ();
	}
	for(int i=0;i< BonusMax; ++i) {
		if(_att_boni[i]) _att_boni[i]->updatePixmap();
		if(_def_boni[i]) _def_boni[i]->updatePixmap();
	}
}


void Simulator::setReport (int report)
{	
	if (report <0) return;
	Report r = WorldData::currentWorld().report(report);
	AttReport *ar = r.att();
	if(!ar) return;

	popToFront ();

	setWindowTitle ( tr("[%1] Attack report %2").arg(ar->_server).arg(ar->att_time.toString("dd.MM.yyyy hh:mm")));
	att = ar->att_units;
	att_loss = ar->att_unit_loss;
	def = ar->def_units;
	def_loss = ar->def_unit_loss;
	att_boni = ar->boni;
	def_boni = ar->boni;
	_wall_loss = ar->wall_loss;
	WorldData w = WorldData::currentWorld();
	int tidx = w.townIndex(ar->att_town_id);
	int pid = -1;
	if (tidx>=0) {
		pid = w.towns()[tidx].player_id;
	}
	Report wd = w.wallDiff (pid, ar->att_time);
	WallReport * wr = wd.wall();
	rep = r;
	wall_diff = wd;

	AttReportData ad (r);

	if (wr && wr->lost_as_att == ar->att_unit_loss) {
		def_loss = wr->killed_as_att;
		ui.tb3->setEnabled (true);
	} else {
			ui.tb3->setEnabled (false);
	}
	ui.att->setText(w.TownLabelText( ad.att_town, w.playerIndex(ad.att_player_id), w.allyIndex(ad.att_ally_id),false));
	ui.def->setText(w.TownLabelText( ad.def_town, w.playerIndex(ad.def_player_id), w.allyIndex(ad.def_ally_id),false));
	
	updateDisplay () ;
}

void Simulator::popToFront ()
{
	// hide ();
	show ();
	raise ();
	activateWindow();
}

void Simulator::attPremiumChg ()
{
}

void Simulator::defPremiumChg ()
{
}

void Simulator::attUnitsChg ()
{
}

void Simulator::defUnitsChg ()
{
}

void Simulator::attSpellsChg ()
{
}

void Simulator::defSpellsChg ()
{
}

void Simulator::attResearchChg ()
{
}

void Simulator::defResearchChg ()
{
}

void Simulator::defBuildingChg ()
{
}

bool Simulator::handleIncomingData (const QString& s)
{
	Report rep (s);
	if (!rep.isValid ()) return false;
	
	AttReport * att = rep.att();
	
	//_hide_act->setChecked (true);
	int ret = WorldData::currentWorld().handleReport (rep);


	if (att && ret >0) {		
		emit reportSignal (WorldData::currentWorld().townIndex(att->att_town_id));
		setReport (ret);
	}

	return (ret >=0);
}


void Simulator::closeEvent(QCloseEvent*)
{
	hide ();
	//_hide_act->setChecked (false);
}

