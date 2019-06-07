/* toolwidget.cpp - tool widgets

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

#include "toolwidget.h"
#include "command.h"

ToolWidget::ToolWidget (const QString& id, const QString& ti):_id (id), _title(ti){}

ToolWidget::~ToolWidget (){}


void ToolWidget::addCmd (Cmd* cmd, const char* slot)
{
	CmdAct    * ca = dynamic_cast< CmdAct*> (cmd);
	CmdColor  * cc = dynamic_cast< CmdColor*> (cmd);
	CmdCheck  * ch = dynamic_cast< CmdCheck*> (cmd);
	CmdGroup  * cg = dynamic_cast< CmdGroup*> (cmd);

	if (cc) {
		connect (cc, SIGNAL(valueChanged(const QString&)),
			this, SLOT(cmdTriggered(const QString&)));
		if (slot) {
			connect (cc, SIGNAL(valueChanged(QColor)), this, slot);
		}

	} else if (cg) {
		connect (cg, SIGNAL(valueChanged(const QString&)),
			this, SLOT(cmdTriggered(const QString&)));

		if (slot) {
			connect (cg, SIGNAL(valueChanged(int)), this, slot);
		}
	
	} else if (ch) {
		connect (ch, SIGNAL(valueChanged(const QString&)),
			this, SLOT(cmdTriggered(const QString&)));
		if (slot) {
			connect (ch, SIGNAL(valueChanged(bool)), this, slot);
		}

	} else if (ca) {
		connect (ca, SIGNAL(triggeredSignal(const QString&)),
			this, SLOT(cmdTriggered(const QString&)));

		if (slot) {
			connect (ca, SIGNAL(triggeredSignal()), this, slot);
		}
	}
}

