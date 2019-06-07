#ifndef ___SIMULATOR_H
#define ___SIMULATOR_H
/* simulator.h  - fight sim

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
#include <GtWorlddata.h>
#include <GtUnits.h>
#include <GtReports.h>
#include <toolwidget.h>
#include "ui_simulator.h"
class QMenu;

#ifdef EXPORT 
# undef EXPORT
#endif
#ifdef BUILDING_GTGUI
# define EXPORT DLL_EXPORT
#else
# define EXPORT DLL_IMPORT
#endif

class SimLabel : public QWidget {
	Q_OBJECT;
public:
	SimLabel () {};
	virtual void updatePixmap () = 0;
};

class NumberedLabel : public SimLabel {
	Q_OBJECT;
public:
	NumberedLabel (const QString& iconfile, int min, int max, int & v, int & vd);
	int value () const {return val;};
	int valueDead () const {return val_d;};

public slots:
	void setValue (int);
	void setValueDead (int);
	void setDeadEditable (bool b){dab= b;};
	void updatePixmap ();

signals:
	void valueChanged (int);
	void valueDeadChanged (int);

protected:
	void wheelEvent (QWheelEvent* e); 
	void mousePressEvent (QMouseEvent* e) ;
	void mouseReleaseEvent (QMouseEvent* e) ;	

private:
	QLabel *lab;
	QLabel *lab_d;
	QString ico;
	int &val;
	int &val_d;
	int minv;
	int maxv;
	bool dab; 
};

class CheckedLabel : public SimLabel {
	Q_OBJECT;
public:
	CheckedLabel (const QString& iconfile, int &vd);
	int value () const {return val;};

public slots:
	void setValue (int);

	void updatePixmap ();
signals:
	void valueChanged (int);

protected:
	void mousePressEvent (QMouseEvent* e) ;
	void mouseReleaseEvent (QMouseEvent* e) ;	

private:	
	QLabel *lab;
	QString ico;
	int     &val; 
};

class Simulator : public ToolWidget {
	Q_OBJECT;
public:

	enum Mode {
		Simulate,
		ReSimulate,
		ShowReport
	};

	static void simulate (const BonusData &att_boni,
		const BonusData &def_boni,
		const UnitData &att,
		const UnitData &def,
		int &_wall_loss,
		UnitData &att_loss,
		UnitData &def_loss);



	Simulator ();
	void worldChanged (){};
	QAction * hideAct () {return _hide_act;};

	bool handleIncomingData (const QString& s);


	void closeEvent(QCloseEvent*);

public slots:
	void setReport (int r);

	void popToFront ();
	void updateDisplay () ;

	void simulate ();
	void reset ();
	void reverse();

	void attPremiumChg ();
	void defPremiumChg ();
	void attUnitsChg ();
	void defUnitsChg ();
	void attSpellsChg ();
	void defSpellsChg ();
	void attResearchChg ();
	void defResearchChg ();
	void defBuildingChg ();

signals:
	void reportSignal(int);

private:
	Mode _mode;
	QAction  *_hide_act;
	Ui::Simulator ui;
	QVector<NumberedLabel*> _att;
	QVector<NumberedLabel*> _def;
	SimLabel* _att_boni[BonusMax];
	SimLabel* _def_boni[BonusMax];

	NumberedLabel *_luck;
	NumberedLabel *_morale;
	NumberedLabel *_att_boost;
	CheckedLabel*  _att_longterm_boost;
	CheckedLabel*  _att_priest;
	CheckedLabel*  _att_commander;
	CheckedLabel*  _att_captain;
	CheckedLabel*  _hero_strength;
	CheckedLabel*  _fair_wind;
	CheckedLabel*  _desire;
	CheckedLabel*  _myrmidonian;
	CheckedLabel*  _att_phalanx;
	CheckedLabel*  _att_ram;

	NumberedLabel *_wall;
	CheckedLabel*  _night;
	CheckedLabel*  _tower;
	CheckedLabel*  _def_phalanx;
	CheckedLabel*  _def_ram;
	CheckedLabel*  _trojan;
	NumberedLabel *_def_boost;
	CheckedLabel*  _def_longterm_boost;
	CheckedLabel*  _def_priest;
	CheckedLabel*  _def_commander;
	CheckedLabel*  _def_captain;

	int ld_zero;
	
	int _wall_loss;
	BonusData att_boni;
	BonusData def_boni;
	UnitData att;
	UnitData att_loss;
	UnitData def;
	UnitData def_loss;
	Report wall_diff;
	Report rep;
};








#endif