#include "polis_search.h"
#include "mainwin.h"
#include <QCheckBox>
#include <QListWidget>
#include <QSpinBox>
#include <QTimeEdit>
#include <QGridLayout>
#include <QDebug>

#include "selector.h"
#include <GtWorlddata.h>
#include <GtAllys.h>
#include <GtPlayers.h>
#include <GtTowns.h>


DlgSearch::DlgSearch()
{
	ui.setupUi(this);
	ui.del->setIcon(QIcon(":/icons/icons/ally_no.ico"));
	ui.del->setToolTip(tr("Remove ally from list"));

	QGridLayout *la = ui.lay;
	Selector * sel = new Selector (this, Selector::SelectAllys);
	delete la->replaceWidget (ui.al,sel->lineEdit())->widget();
	s.allys = WorldData::setting ("PolisSearch/Allys").value < QVector<int> > ();
	ui.cbally->setChecked (WorldData::setting ("PolisSearch/ChkAllys",false).toBool ());
	ui.cbghosts->setChecked (WorldData::setting ("PolisSearch/ChkGhosts",false).toBool ());
	ui.cbmaxdist->setChecked (WorldData::setting ("PolisSearch/ChkDistance",false).toBool ());
	ui.cbmaxtime->setChecked (WorldData::setting ("PolisSearch/ChkTime",false).toBool ());
	ui.cbocean->setChecked (WorldData::setting ("PolisSearch/ChkOcean",false).toBool ());
	ui.inact1->setChecked (WorldData::setting ("PolisSearch/ChkInact1",false).toBool ());
	ui.inact3->setChecked (WorldData::setting ("PolisSearch/ChkInact3",false).toBool ());
	ui.dist->setValue (WorldData::setting ("PolisSearch/Distance",1).toInt());
	ui.time->setTime (WorldData::setting ("PolisSearch/MaxTime",QTime::fromString("01:00:00", "hh:mm:ss")).toTime());
	ui.ocean->setValue (WorldData::setting ("PolisSearch/Ocean",45).toInt());
	connect (sel, SIGNAL(itemSelectedSignal (int)), this, SLOT(allySelected(int)));
	connect (ui.cbally, SIGNAL(toggled(bool)), this, SLOT(cbAllychanged()));
	connect (ui.cbghosts, SIGNAL(toggled(bool)), this, SLOT(cbGhost()));
	connect (ui.cbmaxdist, SIGNAL(toggled(bool)), this, SLOT(cbDist()));
	connect (ui.cbocean, SIGNAL(toggled(bool)), this, SLOT(cbOcean()));
	connect (ui.cbmaxtime, SIGNAL(toggled(bool)), this, SLOT(cbTime()));
	connect (ui.inact1, SIGNAL(toggled(bool)), this, SLOT(cbInact1()));
	connect (ui.inact3, SIGNAL(toggled(bool)), this, SLOT(cbInact3()));
	connect (ui.del, SIGNAL(clicked()), this, SLOT(delclick()));
	connect (ui.dist, SIGNAL(valueChanged(int)), this, SLOT(updateList()));
	connect (ui.ocean, SIGNAL(valueChanged(int)), this, SLOT(updateList()));
	connect (ui.time, SIGNAL(timeChanged(const QTime&)), this, SLOT(updateList()));
	updateList();
}

void DlgSearch::allySelected (int al)
{
	int ai = WorldData::currentWorld().allys()[al].id;
	if (s.allys.contains(ai)) return;
	ui.cbally->setChecked(true);
	s.allys.push_back (ai);
	updateList();
}

void DlgSearch::delclick ()
{
	int as = ui._allys->currentRow();
	if (as<0) return;
	s.allys.erase(s.allys.begin()+as);
	updateList();
}

void DlgSearch::cbAllychanged ()
{
	updateList();
}
void DlgSearch::cbGhost ()
{
	updateList();

}
void DlgSearch::cbInact1 ()
{
	if (ui.inact1->isChecked()) 
		ui.inact3->setChecked(false);
	updateList();
}
void DlgSearch::cbInact3 ()
{
	if (ui.inact3->isChecked()) 
		ui.inact1->setChecked(false);
	updateList();
}
void DlgSearch::cbTime ()
{
	if (ui.cbmaxtime->isChecked()) {
		//ui.cbmaxdist->setChecked(false);
		//ui.cbocean->setChecked(false);
	}
	updateList();
}
void DlgSearch::cbDist ()
{
	if (ui.cbmaxdist->isChecked()) {
		//ui.cbmaxtime->setChecked(false);
		ui.cbocean->setChecked(false);
	}
	updateList();
}
void DlgSearch::cbOcean ()
{
	if (ui.cbocean->isChecked()) {
		ui.cbmaxdist->setChecked(false);
		//ui.cbmaxtime->setChecked(false);
	}
	updateList();
}

void DlgSearch::updateList ()
{
	// store current state
	WorldData::setSetting ("PolisSearch/Allys", QVariant::fromValue < QVector<int> > (s.allys));
	s.useallys = ui.cbally->isChecked ();
	WorldData::setSetting ("PolisSearch/ChkAllys",s.useallys);
	s.ghosts = ui.cbghosts->isChecked ();
	WorldData::setSetting ("PolisSearch/ChkGhosts",s.ghosts);
	s.usedist = ui.cbmaxdist->isChecked ();
	WorldData::setSetting ("PolisSearch/ChkDistance",s.usedist);
	s.usetime = ui.cbmaxtime->isChecked ();
	WorldData::setSetting ("PolisSearch/ChkTime",s.usetime);
	s.useocean = ui.cbocean->isChecked ();
	WorldData::setSetting ("PolisSearch/ChkOcean",s.useocean);
	bool cbinact1 = ui.inact1->isChecked ();
	WorldData::setSetting ("PolisSearch/ChkInact1",cbinact1);
	bool cbinact3 = ui.inact3->isChecked ();
	s.useinact = 0;
	if(cbinact1) s.useinact = 1 * 24 * 60 * 60;
	if(cbinact3) s.useinact = 3 * 24 * 60 * 60;
	WorldData::setSetting ("PolisSearch/ChkInact3",cbinact3);
	s.dist = ui.dist->value ();
	WorldData::setSetting ("PolisSearch/Distance",s.dist);
	s.dist *= 128;
	QTime tim = ui.time->time ();
	WorldData::setSetting ("PolisSearch/MaxTime",tim);
	s.ocean = ui.ocean->value();
	WorldData::setSetting ("PolisSearch/Ocean",s.ocean);
	
	s.time = ( tim.hour() * 60 + tim.minute () ) * 60 + tim.second ();

	s.mapcenter = MainWin::currentMapOffset ();

	ui._allys->clear();
	for(int i=0;i< s.allys.size();++i) {
		int ai = WorldData::currentWorld().allyIndex(s.allys[i]);
		if (ai < 0) continue;
		ui._allys->addItem (WorldData::currentWorld().allys()[ai].name);
	}

	towns = WorldData::search(s);
	ui.result->setText (QString("<b>%1</b>").arg(tr("Found %1 towns").arg(towns.size())));
}
