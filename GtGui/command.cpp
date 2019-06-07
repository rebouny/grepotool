/* command.cpp - Menu command

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
#include "command.h"
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>

#include <GtWorlddata.h>

static QVector <Cmd*> __cmd_list;

Cmd::Cmd (QObject * par, const QString& id, 
		  const QString & title,		
		  const QString & tt,
		  const QString & wt,
		  const QIcon   & icon): QObject (par),_id(id), _title(title),
		  _icon(icon), _tip (tt), _what(wt), _enbl(true)
{
	if(_id.isEmpty ()) return;
	__cmd_list.push_back(this);
}

Cmd::~Cmd()
{
	if(_id.isEmpty ()) return;
	for(int i = 0;i< __cmd_list.size(); ++i) {
		if (__cmd_list[i] && __cmd_list[i]->_id == _id) {__cmd_list[i] = 0; return;};
	}
}

Cmd* Cmd::get (const char *id)
{
	for(int i = 0;i< __cmd_list.size(); ++i) {
		if (__cmd_list[i] && __cmd_list[i]->_id == id) return __cmd_list[i];
	}
	return 0;
}

Cmd* Cmd::get (const QString & id)
{
	for(int i = 0;i< __cmd_list.size(); ++i) {
		if (__cmd_list[i] && __cmd_list[i]->_id == id) return __cmd_list[i];
	}
	return 0;
}



void Cmd::connect (const QString& s, QObject* tgt, const char* slot)
{
	Cmd* cmd = get(s);
	if(!cmd) return;
	CmdAct    * ca = dynamic_cast< CmdAct*> (cmd);
	CmdColor  * cc = dynamic_cast< CmdColor*> (cmd);
	CmdCheck  * ch = dynamic_cast< CmdCheck*> (cmd);
	CmdGroup  * cg = dynamic_cast< CmdGroup*> (cmd);

	if (cc) {
		if (slot) {
			tgt->connect (cc, SIGNAL(valueChanged(QColor)), tgt, slot);
		}

	} else if (cg) {
		if (slot) {
			tgt->connect (cg, SIGNAL(valueChanged(int)), tgt, slot);
		}
	
	} else if (ch) {
		if (slot) {
			tgt->connect (ch, SIGNAL(valueChanged(bool)), tgt, slot);
		}

	} else if (ca) {
		if (slot) {
			tgt->connect (ca, SIGNAL(triggeredSignal()), tgt, slot);
		}
	}

}



// ===============================================================================
//                            Simple actions
// ===============================================================================


CmdAct::CmdAct (QObject * par, const QString& key,
				const QString & title,		
				const QString & tt,
				const QString & wt,
				const QIcon   & ic) : Cmd (par,key,title,tt,wt,ic) 
{
	_btn = qobject_cast<QAbstractButton*> (par);
	_act = new QAction (title, this);
	_act->setToolTip(tt);
	_act->setWhatsThis(wt);
	if (!ic.isNull()) _act->setIcon(ic);
	QObject::connect (_act,SIGNAL(triggered()),this, SLOT(triggered()));
	if (!_btn) return;
	QObject::connect (_btn,SIGNAL(clicked()),this, SLOT(triggered()));
	_btn->setToolTip(tt);
	_btn->setWhatsThis(wt);
	QToolButton * tb = qobject_cast<QToolButton *> (par);
	if (!tb) return;
	if (!ic.isNull()) tb->setIcon(ic);
	updateWidgets ();
}

void  CmdAct::updateAll  ()
{
	_act->setText (title());
	_act->setToolTip(tooltip());
	_act->setWhatsThis(what());
	_act->setEnabled (isEnabled ());
	if (!icon().isNull()) _act->setIcon(icon());
	if (_btn) {
		_btn->setToolTip(tooltip());
		_btn->setWhatsThis(what());
		_btn->setEnabled (isEnabled ());
		QToolButton * tb = qobject_cast<QToolButton *> (_btn);
		if (tb && !icon().isNull()) tb->setIcon(icon());
	}
	updateWidgets();
}

void  CmdAct::addToMenu           (QMenu *m)
{
	m->addAction (_act);
}

void  CmdAct::addToToolBar        (QToolBar *m) 
{
	m->addAction (_act);
}


// ===============================================================================
//                            Colors
// ===============================================================================

CmdColor::CmdColor (QObject * par,
					const QString& key,
					const QColor & col,
					const QString & title,		
					const QString & tt,
					const QString & wt) : Cmd (par,key,title,tt,wt,QIcon()),_def(col)
{
	_btn = qobject_cast<QToolButton*> (par);
	_act = new QAction (title, this);
	QObject::connect (_act,SIGNAL(triggered()),this, SLOT(triggered()));
	if (_btn)
		QObject::connect (_btn,SIGNAL(clicked()),this, SLOT(triggered()));
	updateAll();
};

void CmdColor::updateAll            ()
{
	_act->setToolTip(tooltip());
	_act->setWhatsThis(what());
	_act->setText (title());
	QPixmap pm(32,32);
	pm.fill(color());
	_act->setIcon(pm);
	if (!_btn) return;
	_btn->setToolTip(tooltip());
	_btn->setWhatsThis(what());
	_btn->setIcon(pm);
}

void CmdColor::addToMenu  (QMenu *m)
{
	m->addAction (_act);
}

void CmdColor::addToToolBar (QToolBar *m) 
{
	m->addAction (_act);
}

void CmdColor::triggered ()
{
	setColor(ColorPopup::selectColor (QCursor::pos(), color(), title()));
}

void CmdColor::setColor (const QColor & c) 
{
	if (c == value()) return;
	WorldData::setSetting (_id, c.name());
	updateAll ();
	emit valueChanged ();
	emit valueChanged (c);
	emit valueChanged (_id);
}

QColor CmdColor::color () const 
{
	return QColor(value().toString());
}

QVariant CmdColor::value () const 
{
	return WorldData::setting(_id,_def);
}

// ===============================================================================
//                            Boolean values
// ===============================================================================

CmdCheck::CmdCheck (QObject * par, 
					const QString& key,
					bool  def,
					const QString & title,		
					const QString & tt,
					const QString & wt,
					const QIcon   & ic): CmdAct (par,key,title,tt,wt,ic),_cb(0),_def(def)
{
	_act->setCheckable(true);
	QObject::connect (_act, SIGNAL(toggled(bool)), this, SLOT(toggled(bool)));

	if(_btn) {
		_btn->setCheckable(true);
		QObject::connect (_btn, SIGNAL(toggled(bool)), this, SLOT(toggled(bool)));
	}
	updateWidgets ();
}

void CmdCheck::addToToolBar (QToolBar *m) 
{
	if (!icon().isNull()) {
		m->addAction (_act);
		return;
	}
	_cb = new QCheckBox;
	_cb->setChecked(isChecked ());
	_cb->setEnabled(isEnabled ());
	_cb->setText(title());
	_cb->setToolTip (tooltip());
	_cb->setWhatsThis(what());
	m->addWidget (_cb);
	QObject::connect (_cb, SIGNAL(toggled(bool)), this, SLOT(toggled(bool)));
}

void CmdCheck::updateWidgets () 
{
	bool ov = isChecked();
	if (_act->isChecked() != ov) _act->setChecked(ov);
	if (_btn) {
		if (_btn->isChecked() != ov) _btn->setChecked(ov);
	}
	if (_cb) {
		if (_cb->isChecked() != ov) _cb->setChecked(ov);
		_cb->setEnabled(isEnabled());
		_cb->setText(title());
		_cb->setToolTip (tooltip());
		_cb->setWhatsThis(what());
	}
}

void CmdCheck::toggled (bool b) 
{
	setChecked (b);
}


bool CmdCheck::isChecked () const 
{
	return WorldData::setting(_id,_def).toBool();
}; 

void CmdCheck::setChecked (bool c)
{
	if(c == isChecked()) {
		update();
	} else {
		WorldData::setSetting (_id, c);
		emit valueChanged  ();
		emit valueChanged  (c);
		emit valueChanged  (_id);
	}
}	




// ===============================================================================
//                           Lists
// ===============================================================================

CmdGroup::CmdGroup (QObject * par,
					const QString& key,
					int            def,
					const QString & title,		
					const QString & tt,
					const QString & wt,
					const QIcon   & ic) : Cmd (par,key,title,tt,wt,ic),
					_cb(0),_sm(0),_la (0),_def(def)
{
	_ag = new QActionGroup (this);

	if (!icon().isNull()) {		
		_sm = new QMenu;
		_sm->setTitle(title);
		_sm->setIcon(ic);
		_sm->setToolTip (tooltip());
		_sm->setWhatsThis(what());
	}
	QObject::connect (_ag, SIGNAL (triggered(QAction*)), this, SLOT(triggered(QAction*)));
}

CmdGroup::~CmdGroup ()
{
	if(_sm) delete _sm;
}

int CmdGroup::currentIndex () const
{
	return WorldData::setting(_id,_def).toInt();
}

void CmdGroup::setCurrentIndex (int v)
{
	if(v == currentIndex()) return;
	WorldData::setSetting(_id,v);
	update ();
	emit valueChanged ();
	emit valueChanged (v);
	emit valueChanged (_id);
	
}
QAction* CmdGroup::addAction (const QString & ti,
							  const QString & tt,
							  const QString & wt,
							  const QIcon  & ic) 
{
	QAction *a = new QAction (ti,this);
	a->setCheckable (true);
	a->setChecked(_ag->actions().size() == value());
	a->setToolTip (tt);
	a->setWhatsThis(wt);
	a->setData(_ag->actions().size());
	if (!ic.isNull()) a->setIcon(ic);
	_ag->addAction(a);
	return a;
}

void CmdGroup::updateAll ()
{
	bool enbl = isEnabled();
	int v = currentIndex();
	for (int i=0;i< _ag->actions().size(); ++i) {
		_ag->actions()[i]->setEnabled (enbl);
	}
	if (!_ag->actions()[v]->isChecked()) _ag->actions()[v]->setChecked(true);
	
	if (_sm) {
		_sm->setTitle(title());
		_sm->setIcon (icon());
		_sm->setToolTip (tooltip());
		_sm->setWhatsThis(what());
		_sm->setEnabled (enbl);
	} 
	if (_cb) {
		_cb->setEnabled (enbl);
		_cb->setToolTip (tooltip());
		_cb->setWhatsThis(what());
		if(_cb->currentIndex() != v) _cb->setCurrentIndex(v);
		_la->setEnabled (enbl);		
		// _la->setText(title());
		_la->setToolTip (tooltip());
		_la->setWhatsThis(what());
	}
}

void CmdGroup::addToMenu (QMenu *m)
{
	if (_sm) {		
		m->addMenu (_sm);
		_sm->clear();
		_sm->setToolTip (tooltip());
		_sm->setWhatsThis(what());
		QList <QAction*> l = _ag->actions();
		for (int i=0;i< l.size(); ++i)
			_sm->addAction (l[i]);
		m->addMenu (_sm);
	} else {	
		QList <QAction*> l = _ag->actions();
		for (int i=0;i< l.size(); ++i)
			m->addAction (l[i]);
	}
}

void CmdGroup::addToToolBar (QToolBar *m)
{
	if (icon().isNull()) {

		for (int i=0; i < _ag->actions().size(); ++i) {
			m->addAction(_ag->actions() [i]);
		}

	} else {

		// add a label and a combobox
		_la  = new QLabel;				
		_la->setPixmap(icon().pixmap(m->iconSize()));
		_la->setToolTip (tooltip());
		_la->setWhatsThis(what());
		m->addWidget (_la);

		_cb = new QComboBox;
		_cb->setEditable(false);		
		for (int i=0;i< _ag->actions().size(); ++i) {
			if(_ag->actions()[i]->icon().isNull())
				_cb->addItem (_ag->actions()[i]->text());
			else
				_cb->addItem (_ag->actions()[i]->icon(),_ag->actions()[i]->text());
		}
		_cb->setToolTip (tooltip());
		_cb->setWhatsThis(what());
		_cb->setCurrentIndex(currentIndex());
		QObject::connect (_cb, SIGNAL (currentIndexChanged(int)), this, SLOT(selectionChanged(int)));
		QObject::connect (this, SIGNAL(valueChanged(int)),_cb,SLOT(setCurrentIndex(int)));
		m->addWidget (_cb);
		return;
	}
}

void CmdGroup::triggered (QAction *a)
{
	selectionChanged (a->data().toInt());
}

void CmdGroup::selectionChanged (int a)
{	
	setCurrentIndex (a);
}


