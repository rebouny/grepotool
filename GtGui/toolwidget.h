#ifndef ___TOOLWIDGET_H
#define ___TOOLWIDGET_H
/* toolwidget.h  - tool windows

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
#include <QMainWindow>
#include <GtWorlddata.h>

class QMenu;

#ifdef EXPORT 
# undef EXPORT
#endif
#ifdef BUILDING_GTGUI
# define EXPORT DLL_EXPORT
#else
# define EXPORT DLL_IMPORT
#endif

class Cmd;

class EXPORT ToolWidget : public QMainWindow {
	Q_OBJECT;
public:
	ToolWidget (const QString& id, const QString& ti);
	virtual ~ToolWidget ();

	QString title () const {return _title;};
	QString globalWidgetKey () const {return _id;};

	virtual void createSettingsSubMenu (QMenu*, bool ) {};
	virtual void worldChanged () =0;
	virtual void worldAboutToChange () {};

	void addCmd (Cmd* cmd, const char* handle_val_slot = 0);

	virtual void handleCmd (const QString& ) {};





public slots: 
	void cmdTriggered (const QString& key) {handleCmd(key);};

signals:
	void updateMapSignal ();
	void updateInfMapSignal ();
	void gotoTownSignal (int);
	void zoomToTownSignal (int);
	void gotoPlayerSignal (int);
	void gotoAllySignal (int);
	void bookmarkChangedSignal ();

protected:
	QString   _id;
	QString   _title;
};



#endif