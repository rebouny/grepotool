#ifndef __GT_SPLASH_H
#define __GT_SPLASH_H
/* gtsplash.h  - SplashScreen

Copyright (c) 2014 P. Vorpahl

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
#include <QSplashScreen>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QImage>

#include <GtCore.h>
#include <GtProgress.h>

#ifdef EXPORT 
# undef EXPORT
#endif
#ifdef BUILDING_GTCORE
# define EXPORT DLL_EXPORT
#else
# define EXPORT DLL_IMPORT
#endif

class EXPORT Splash : public QSplashScreen {
	Q_OBJECT;
public:

	Splash ();
	GtProgress * progress () {return &prog;};

signals:
	void acceptedSignal ();

public slots:

	void setTitle (const QString &tx);
	void setHeadline (const QString &tx);
	void setBottom (const QString &line1,const QString & line2);
	void btnOkClicked () {m.lock();ok=true;running=false;m.unlock();};
	void btnCnlClicked () {m.lock();ok=false;running=false;m.unlock();};
	void hideControls ();
	void sel1Changed (int index);
	void sel2Changed (int index);
	void enableOk (bool show, const QString& tx); 
	void progress (const QString&, const QString& , int );
public:
	void setSel1 (const QStringList& icons, const QStringList& texts, int);
	void setSel2 (const QStringList& texts, int);
	void showError (const QString & tit, const QString & desc, const QString & det,
		const QString &btn_tx);
	bool waitForButton (const QString& cnl_tx, const QString &ok_tx);
	bool waitForServer (const QString& cnl_tx, const QString &ok_tx);
	int sel1() const;
	int sel2() const;

signals :
	void okClicked ();
	void cancelClicked ();
	void langSelChanged (int index);
	void srvSelChanged (int index);

private:
	QMutex        m;
	bool          running;
	bool          ok;

	QComboBox   * sel_1;
	QComboBox   * sel_2;
	QLabel      * s1;	
	QLabel      * s2;	
	QPushButton * exit_bt;
	QPushButton * ok_bt;
	QLabel      * top; 
	QLabel      * headline; 
	QLabel      * bottom; 
	QLabel      * copy;	
	QWidget     * selector;
	GtProgress    prog;
	ProgressBar * pb;
};




#endif