/* popup.cpp - Popup widgets

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

#include "popup.h"
#include <GtApp.h>
#include <GtUnits.h>
#include <QLabel>
#include <QPushButton>
#include <QDesktopWidget>
#include <QColorDialog>
#include <QLineEdit>
#include <QKeyEvent>



Popup::Popup (QWidget* par):QWidget (par, Qt::Popup|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint), loop(0),isInit(false),accepted(false) {};


void Popup::popup (const QPoint & pos, QEventLoop * l)
{
	accepted = false;
	if (!isInit) {
		isInit = true;
		QGridLayout * l1 = new QGridLayout;
		QString h = headline();
		int r = 0;
		if (!h.isEmpty()) {
			QLabel * lab = new QLabel(QString("<b>%1</b>").arg(h));
			l1->addWidget(lab,0,0,1,3);
			++r;
		}
		QWidget *wid = createWidget();
		l1->addWidget(wid,r,0,1,3);
		l1->setMargin(0);
		++r;
		bool ok = okBtn();
		bool cnl = cancelBtn();
		if (ok || cnl) {
			int bc=2;
			if (cnl){
				QPushButton *bt = new QPushButton(tr("Cancel"));
				l1->addWidget(bt, r, bc--);
				connect (bt,SIGNAL(clicked()), this, SLOT(cancel()));
			}
			if (ok){
				QPushButton *bt = new QPushButton(tr("Ok"));
				l1->addWidget(bt, r,bc);
				connect (bt,SIGNAL(clicked()), this, SLOT(accept()));
			}
			l1->addItem(new QSpacerItem(0,0),r,0);
		}
		setLayout (l1);
		
	}
	updateGeometry();
	show();
	
	updateGeometry();
	loop = l;
	QSize s= size();
	QSize ds= GtApp::desktop()->size();
	int x = pos.x();
	int y = pos.y();
	if (x+s.width() > ds.width()) x-=s.width();
	if (y+s.height() > ds.height()) y-=s.height();
	move(QPoint(x,y));
	show();	
	l->exec();
}

bool Popup::event ( QEvent * ev ) {
	if (loop) {
		if (ev->type() == QEvent::Close ) 
			exitLoop();
		if (ev->type() == QEvent::FocusOut) 
			exitLoop();			
	}
	if (ev->type()== QEvent::KeyPress) {
		QKeyEvent * k= dynamic_cast<QKeyEvent * >(ev);
		if(k->key() == Qt::Key_Escape) {
			cancel();
		} else if (k->key() == Qt::Key_Enter ||k->key() == Qt::Key_Return) {
			accept();
		}
	}
	return QWidget::event(ev);
};	

void Popup::exitLoop () {
	if (!loop) return;
	loop->exit();
	loop = 0;
};




ColorPopup::ColorPopup (QWidget * parent, const QColor &col, const QString & t) : Popup (parent), val (col),tx(t)
{
}

QWidget * ColorPopup::createWidget ()
{
	QColorDialog * dlg = new QColorDialog(val,0);
	dlg->setOption (QColorDialog::NoButtons);
	connect (dlg, SIGNAL (currentColorChanged ( const QColor & )), this, SLOT(colorChanged ( const QColor & ) ));
	return dlg;
}


QColor ColorPopup::value() const 
{
	return val;
}

QColor ColorPopup::selectColor (const QPoint & pos, const QColor &c, const QString & tx)
{
	ColorPopup w(0, c, tx);
	QEventLoop l;
	w.popup (pos, &l);
	return w.isAccepted()?w.value():c;	
}

void ColorPopup::colorChanged( const QColor& c)
{
	val = c;
}

TextPopup::TextPopup (QWidget * parent, const QString &col, const QString & t)  : Popup (parent), val (col),tx(t)
{
};


QWidget * TextPopup::createWidget () {
	QLineEdit *l = new QLineEdit(val);
	l->selectAll();
	connect (l,SIGNAL(textEdited ( const QString & )), this, SLOT(textChanged(const QString &)));
	connect (l,SIGNAL(editingFinished ( )), this, SLOT(accept()));
	return l;
};


QString TextPopup::selectText (const QPoint & pos, const QString &c, const QString & tx)
{
	TextPopup w(0, c, tx);
	QEventLoop l;
	w.popup (pos, &l);
	return w.isAccepted()?w.value():c;	
};


QWidget * DialogPopup::createWidget ()
{
	return new QLabel (text);
}

DialogPopup::DialogPopup (QWidget * parent, const QString &col, const QString & t, bool o, bool c) :  Popup (parent), tx(t),text(col), bok(o),bcnl(c)
{
}

bool DialogPopup::show (const QPoint & pos, const QString &tx, const QString & ti, bool o, bool c)
{
	DialogPopup w(0, tx,ti,o,c);
	QEventLoop l;
	w.popup (pos, &l);
	return w.isAccepted();
}










UnitSelector::UnitSelector (QWidget * parent, UnitIndex u) : Popup (parent), unit (u) {
};


QWidget * UnitSelector::createWidget ()
{
	QWidget *ret = new QWidget(this);
	ui.setupUi(ret);
	
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

	bg = new QButtonGroup (this);
	for (int i=1;i<units.size(); ++i) {
		if ((int)unit == i) units[i]->setChecked(true);
		bg->addButton (units[i],i);
		units[i]->setIcon (QIcon(Unit::unitIconFile((UnitIndex)i)));
		units[i]->setToolTip(Unit::unitName((UnitIndex)i,true));
	}
	connect (bg, SIGNAL (buttonClicked(int)), this, SLOT(unitClicked(int)));
	return ret;
}


void UnitSelector::unitClicked (int u) 
{
	unit = (UnitIndex) u;		
	close ();
}


UnitIndex UnitSelector::selectUnit (const QPoint & pos, UnitIndex u) 
{
	UnitSelector w(0, u);
	QEventLoop l;
	w.popup (pos, &l);
	return w.value();
}









SpecialSelector::SpecialSelector (QWidget * parent, int& s,bool m)  : Popup (parent), spc (s),multi(m)
{
}

QWidget * SpecialSelector::createWidget ()
{
	QWidget *ret = new QWidget (this);
	ui.setupUi (ret);
	bg = new QButtonGroup (this);
	bg->setExclusive (false);

	if (multi) {
		ui._meteorology->hide();
		ui._cartography->hide();
		ui._lighthouse->hide();
	}


	ui._meteorology->setChecked(spc & 1);
	ui._cartography->setChecked(spc & 2);
	ui._movement_boost->setChecked(spc & 4);
	ui._lighthouse->setChecked(spc & 8);

	ui._meteorology->setIcon(QIcon(":/icons/research/meteorology.png"));
	ui._cartography->setIcon(QIcon(":/icons/research/cartography.png"));
	ui._movement_boost->setIcon(QIcon(":/icons/spells/movement_boost.gif"));
	ui._lighthouse->setIcon(QIcon(":/icons/buildings/lighthouse.png"));
	
	al = spc >> 8;
	NumEdit * ne = new NumEdit (ui._atlanta, &al, ":/icons/heroes/atlanta.png");
	ne->setRange (0,20);
	connect (ne,SIGNAL(valueChanged(int)), this, SLOT(specialClicked(int)));
	bg->addButton (ui._meteorology,0);
	bg->addButton (ui._cartography,1);
	bg->addButton (ui._movement_boost,2);
	bg->addButton (ui._lighthouse,3);
	connect (bg, SIGNAL (buttonClicked(int)), this, SLOT(specialClicked(int)));
	return ret;
}

void SpecialSelector::specialClicked (int )
{
	spc = 0;
	if (ui._meteorology->isChecked()) spc += 1;
	if (ui._cartography->isChecked()) spc += 2;
	if (ui._movement_boost->isChecked()) spc += 4;
	if (ui._lighthouse->isChecked()) spc += 8;
	spc += al<<8;
	accepted = true;
	// accept ();
}

bool SpecialSelector::selectSpecials (const QPoint & pos, bool multi,
		bool & lh, bool& ca , bool & me, bool& mb , int& al)
{
	int spci = 0;
	if (me) spci += 1;
	if (ca) spci += 2;
	if (mb) spci += 4;
	if (lh) spci += 8;
	spci += al<<8;

	int ospc = spci;
	
	SpecialSelector w(0, spci,multi);
	QEventLoop l;
	w.popup (pos, &l);

	me = spci & 1;
	ca = spci & 2;
	mb = spci & 4;
	lh = spci & 8;
	al = spci >>8;
	
	return w.isAccepted (); // ospc != spc;
}



