#ifndef ___POLIS_SEARCH_H
#define ___POLIS_SEARCH_H



#include <GtWorlddata.h>
#include "toolwidget.h"
#include "popup.h"
#include "ui_polis_search.h"

#include <QToolButton>
#include <QSpinBox>
#include <QPainter>


class DlgSearch : public QDialog {
	Q_OBJECT;
public:
	DlgSearch();

	const QVector<int>& result () const {return towns;};
public slots:
	void allySelected (int);
	void cbAllychanged ();
	void cbGhost ();
	void cbInact1 ();
	void cbInact3 ();
	void cbTime ();
	void cbDist ();
	void cbOcean ();
	void delclick ();
	void updateList ();

private:
	QVector<int> towns;
	SearchData s;
	Ui::PolisSearch ui;
};


#endif