/* splash.cpp  - SplashScreen

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
#include <QLabel>
#include <QStringList>
#include <QPushButton>
#include <QGridLayout>

#include <GtSplash.h>
#include <GtApp.h>

#ifdef __DEBUG_BUILD
Splash::Splash () : QSplashScreen(QPixmap (":/splash.png"))
#else
Splash::Splash () : QSplashScreen(QPixmap (":/splash.png"),Qt::SplashScreen|Qt::WindowStaysOnTopHint)
#endif
{
	top = new QLabel (this); 
	top->resize(300,20);
	bottom = new QLabel (this); 
	bottom->resize(300,50);
	headline = new QLabel (this); 
	headline->resize(300,50);

	copy = new QLabel (this);
	copy->setText( "<p align=vcenter>&copy;&nbsp;P.&nbsp;Vorpahl&nbsp;<img src=':/bbcode_player.png'>&nbsp;<b>.Pete.</b></p>");
	copy->move   (375, 60);
	// top->move    (86, 20);
	top->move    (10, 10);
	headline->move (86, 154);
	bottom->move (86, 178);

	pb = new ProgressBar(this);
	pb->resize(264,3);
	pb->move (86,220);

	exit_bt = new QPushButton (tr("Exit"), this);
	ok_bt = new QPushButton (tr("Ok"), this);

	int bx = (width() - exit_bt->width()) - 6;
	int by = ((height() - exit_bt->height())) -6;
	exit_bt->move (QPoint(bx,by));

	selector = new QWidget (this);
	QGridLayout * l= new QGridLayout;
	l->setMargin(0);
	sel_1 = new QComboBox;
	sel_2 = new QComboBox;
	s1 = new QLabel;
	s2 = new QLabel;
	l->addWidget (s1,0,0);
	l->addWidget (sel_1,0,1);
	l->addWidget (s2,1,0);
	l->addWidget (sel_2,1,1);
	selector->setLayout(l);
	selector->updateGeometry();

	connect (exit_bt, SIGNAL(clicked()), this, SLOT (btnCnlClicked()));
	connect (ok_bt, SIGNAL(clicked()), this, SLOT (btnOkClicked()));
	connect (exit_bt, SIGNAL(clicked()), this, SIGNAL (cancelClicked()));
	connect (ok_bt, SIGNAL(clicked()), this, SIGNAL(okClicked()));
	connect (sel_1,SIGNAL (currentIndexChanged(int)),this, SLOT(sel1Changed(int))); 	
	connect (sel_2,SIGNAL (currentIndexChanged(int)),this, SLOT(sel2Changed(int))); 	

	connect (&prog, SIGNAL (progress (const QString&, const QString& , int )),
		this,SLOT(progress (const QString&, const QString& , int )));


	hideControls ();
};

void Splash::progress (const QString& head, const QString& desc, int perm)
{
	setHeadline (head);	
	pb->show ();
	QString ps = "";
	if (perm>= 0) {
		int perc = perm/10;
		ps +=" " + QString::number(perc)+"."+QString::number(perm-perc*10)+" %";
	}
	pb->setPermill (perm);
	setBottom (desc,ps);
}


void Splash::setBottom (const QString &line1,const QString & line2)
{
	if(line2.isEmpty()) {
		bottom->setText ( line1);
	} else {
		bottom->setText ( QString ("%1<br>%2").arg(line1).arg(line2) );
	}
}
	
void Splash::setHeadline (const QString &tx)
{
//	headline->setText ( QString ("<b>%1</b>").arg(tx));	
	headline->setText ( QString ("%1").arg(tx));	
}

void Splash::setTitle (const QString &tx)
{
//	top->setText ( QString ("<b>%1</b>").arg(tx));
	top->setText ( QString ("%1").arg(tx));
}

void Splash::hideControls ()
{
	ok_bt->hide();
	exit_bt->hide();
	
	selector->hide();
}
void Splash::sel1Changed (int index)
{
	emit langSelChanged (index);
	
}
void Splash::sel2Changed (int index)
{
	emit srvSelChanged (index);
}

void Splash::enableOk (bool shw, const QString& tx) 
{
	ok_bt->setEnabled (shw);
	ok_bt->setText (tx);
}

void Splash::setSel1 (const QStringList& icons, const QStringList& texts, int s)
{
	sel_1->clear();
	for (int i=0;i<texts.size();++i) {
		sel_1->addItem(QIcon(icons[i]), texts[i]);
	}
	sel_1->setCurrentIndex (s);
	sel_1->show();
}

void Splash::setSel2 (const QStringList& texts, int s)
{
	sel_2->clear();
	for (int i=0;i<texts.size();++i) {
		sel_2->addItem( texts[i]);
	}
	sel_2->setCurrentIndex (s);
	sel_2->show();
}

void Splash::showError (const QString & tit, const QString & desc, const QString & det,
		const QString &btn_tx)
{
	setHeadline (tit);
	setBottom (desc, det);
	waitForButton(btn_tx,"");
}

bool Splash::waitForButton (const QString& cnl_tx, const QString &ok_tx)
{	
	pb->hide ();
	int bx = width();
	int by= height();
	if (!cnl_tx.isEmpty()) {
		exit_bt->setText (cnl_tx);
		exit_bt->show();
		exit_bt->setFocus();
		bx = (width() - exit_bt->width()) - 6;
		by = ((height() - exit_bt->height())) -6;
		exit_bt->move (QPoint(bx,by));
	}
	if(!ok_tx.isEmpty()) {
		ok_bt->setText (ok_tx);
		ok_bt->show();
		ok_bt->setFocus();
		bx = (bx - ok_bt->width()) - 6;
		by = ((height() - ok_bt->height())) -6;
		ok_bt->move (QPoint(bx,by));
	}
	running = true;
	m.lock();
	while (running) {
		m.unlock();
		GtApp::processEvents();
		msleep (5);
		m.lock();
	}
	m.unlock();
	hideControls ();
	return ok;
}
bool Splash::waitForServer (const QString& cnl_tx, const QString &ok_tx)
{
	s1->setText (tr("Country"));
	s2->setText (tr("World"));
	selector->move (240, 110);
	selector->show();
	bool ret = waitForButton (cnl_tx,ok_tx);
	return ret;
}

int Splash::sel1() const
{
	return sel_1->currentIndex();
}
int Splash::sel2() const
{
	return sel_2->currentIndex();
}



