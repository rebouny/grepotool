#include "table_model.h"
#include <QListWidget>
#include <QTableWidget>
#include <QTextEdit>
#include <QTabWidget>
#include <QToolButton>
#include <GtWorlddata.h>

DlgTableExport::DlgTableExport(TableView * par):_par(par)
{
	ui.setupUi(this);
	QString k = par->globalWidgetKey();

	ui._add->setIcon (QIcon(":/icons/right.png"));
	ui._remove->setIcon (QIcon(":/icons/left.png"));
	ui._up->setIcon (QIcon(":/icons/up.png"));
	ui._down->setIcon (QIcon(":/icons/down.png"));
	connect(ui._tab, SIGNAL(currentChanged(int)), this, SLOT(updatePreview()));
	connect(ui._only_sel, SIGNAL(toggled(bool)), this, SLOT(updatePreview()));
	// get the available columns
	int nc = par->model()->columnCount ();
	for (int i=0; i < nc; ++i) {
		cols.push_back(par->model()->headerData (i,Qt::Horizontal).toString());
	}
	ui._only_sel->setChecked (WorldData::setting (k+"OnlySelected",false).toBool());
	int curt = WorldData::setting (k+"CurrentTab",0).toInt();
	ui._tab->setCurrentIndex (curt);
	selcols = WorldData::setting (k+"SelectedColumns", QVariant::fromValue< QVector <int> >(selcols)).value < QVector <int> >();
	updateLists ();
	connect (ui._add, SIGNAL(clicked()),this,SLOT(add()));
	connect (ui._remove, SIGNAL(clicked()),this,SLOT(remove()));
	connect (ui._up, SIGNAL(clicked()),this,SLOT(up()));
	connect (ui._down, SIGNAL(clicked()),this,SLOT(down()));
	connect (ui._avail, SIGNAL (currentRowChanged(int)), this, SLOT(checkButtons()));
	connect (ui._sel, SIGNAL (currentRowChanged(int)), this, SLOT(checkButtons()));
}
void DlgTableExport::updateLists ()
{
	int ar = ui._avail->currentRow();
	int sr = ui._sel->currentRow();
	ui._avail->clear();
	ui._sel->clear();
	for (int i=0;i<cols.size();++i) {
		if (selcols.contains(i)) continue;
		ui._avail->addItem (cols [i]);
	}
	for (int i=0;i<selcols.size();++i) {
		ui._sel->addItem (cols [selcols[i]]);
	}

	QString k = _par->globalWidgetKey();
	WorldData::setSetting (k+"SelectedColumns", QVariant::fromValue< QVector <int> >(selcols));
	WorldData::setSetting (k+"CurrentTab", ui._tab->currentIndex ());
	WorldData::setSetting (k+"OnlySelected",ui._only_sel->isChecked ());

	if ( ar >= 0 && ar < ui._avail->count ()) ui._avail->setCurrentRow (ar);
	if ( sr >= 0 && sr < ui._sel->count ()) ui._sel->setCurrentRow (ar);

	updatePreview ();
	checkButtons ();
}

void DlgTableExport::up ()
{
	int sr = ui._sel->currentRow();
	if (sr<1) return;
	int dmy = selcols[sr];
	selcols[sr] = selcols[sr-1];
	selcols[sr-1] = dmy;
	updateLists ();
	ui._sel->setCurrentRow (sr-1);
	checkButtons ();
}
void DlgTableExport::down ()
{
	int sr = ui._sel->currentRow();
	if (sr<0) return;
	if(sr == ui._sel->count()-1) return ;
	int dmy = selcols[sr];
	selcols[sr] = selcols[sr+1];
	selcols[sr+1] = dmy;
	updateLists ();
	ui._sel->setCurrentRow (sr+1);
	checkButtons ();
}
void DlgTableExport::add ()
{
	int ar = ui._avail->currentRow();
	int sr = ui._sel->currentRow();
	if (ar<0) return;
	QVector <int > ac;
	for (int i=0;i<cols.size();++i) if(!selcols.contains(i)) ac.push_back(i);	
	int c = ac[ar];
	--ar;
	if(sr<0) sr = 0;
	if(ar<0) ar = 0;
	selcols.insert (sr,c);
	updateLists ();
	ui._sel->setCurrentRow (sr);
	ui._avail->setCurrentRow (ar);
	checkButtons ();
}
void DlgTableExport::remove ()
{
	int sr = ui._sel->currentRow();
	if (sr<0) return;
	selcols.erase (selcols.begin()+sr);
	--sr;
	if(sr < 0) sr = 0;
	updateLists ();
	if (sr < ui._sel->count()) ui._sel->setCurrentRow (sr);
	checkButtons ();
}
void DlgTableExport::checkButtons ( )
{
	int ar = ui._avail->currentRow();
	int sr = ui._sel->currentRow();
	ui._up->setEnabled (sr > 0);
	ui._down->setEnabled (sr >= 0 && sr < (ui._sel->count()-1));
	ui._add->setEnabled (ar>=0);
	ui._remove->setEnabled (sr>=0);
}

void DlgTableExport::updatePreview ()
{
	QVector <int> idx = _par->model()->getIndex();
	if(ui._only_sel->isChecked ()) {
		idx = _par->selectedItems ();
	}
	int nr = idx.size();
	QStringList ret;	
	QStringList bbcodes;
	QStringList bbtab;
	QStringList headline;
	for ( int i=0;i< selcols.size(); ++i) {
		headline<<cols[selcols[i]];
	}
	ui._text->clear();
	ui._text->setColumnCount (selcols.size());
	ui._text->setRowCount (20);
	ui._text->setHorizontalHeaderLabels (headline);


	for(int row=0;row<nr;++row) {
		QStringList tx = _par->model()->itemTexts (idx[row],selcols);
		QStringList bb = _par->model()->itemBBCodes (idx[row],selcols);
		
		if (ui._tab->currentIndex () == 1) ret << QString ("%1 \t").arg(row+1) + bb.join (" \t");
		else if (ui._tab->currentIndex () == 2) ret << QString ("[*]%1[|] ").arg(row+1) + bb.join (" [|] ")+ "[/*]";
		else if (ui._tab->currentIndex () == 0) ret << QString ("%1\t").arg(row+1)+ tx.join (" \t");

		if (row > 20) continue;

		for (int i=0;i<tx.size();++i) {
			QTableWidgetItem * it = ui._text->item (row,i);
			if(!it) it = new QTableWidgetItem(tx[i]);
			ui._text->setItem(row,i,it);
			it->setText (tx[i]);

			if (bb[i].startsWith ("[player]")) {
				bb[i] = bbCodeLabel (tx[i],":/icons/icons/player.ico");
			} else if (bb[i].startsWith ("[island]")) {
				bb[i] = bbCodeLabel (tx[i],":/icons/icons/island.ico");
			} else if (bb[i].startsWith ("[town]")) {
				bb[i] = bbCodeLabel (tx[i],":/icons/icons/town.ico");
			} else if (bb[i].startsWith ("[ally]")) {
				bb[i] = bbCodeLabel (tx[i],":/icons/icons/ally.ico");
			}
		}
		bbcodes << QString ("%1 ").arg(row+1)+ bb.join(" ")+ "<br>";
		bbtab << QString ("<tr><td>%1</td><td>").arg(row+1) + bb.join ("</td><td>") + QString ("</td></tr>");		
	}
	if (ui._tab->currentIndex () == 1) 
		res = QString ("#\t") + headline.join ("\t") + "\n" + ret.join ("\n");
	else if (ui._tab->currentIndex () == 2) 
		res = QString ("[table][**]#[||] ") + headline.join (" [||] ")+ "[/**]\n"+ ret.join ("\n")+"[/table]";
	else if (ui._tab->currentIndex () == 0)
		res = QString ("#\t")+ headline.join ("\t")+"\n"+ ret.join ("\n");

	// add headlines 

	QString bbc = QString ("<p> <b># ") + headline.join ("</b> <b>") + "</b><br>" +
		bbcodes.join(" ")+"</p>";
	QString bbt = QString (" <table border=1><tr><td>#</td><td><b>") + headline.join ("</b></td><td><b>") + "</b></td></tr>"+
		bbtab.join(" " ) + "</table>";
	
	ui._bbcode ->setText (bbc);
	ui._bbcode_table->setText (bbt);

	QString k = _par->globalWidgetKey();
	WorldData::setSetting (k+"CurrentTab", ui._tab->currentIndex ());


}
