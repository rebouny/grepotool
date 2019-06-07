
#include <GtServer.h> 
#include <GtWorldLoader.h> 
#include <GtWorlddata.h> 
#include <GtWorldLoader.h> 
#include <GtProgress.h> 
#include <GtApp.h> 
#include <GtSplash.h> 
#include "mainwin.h"
#include "simulator.h"



QDataStream &operator<<(QDataStream &out, const QVector<int>&x)
{
	out << x.size();
	for(int i=0;i< x.size(); ++i) out << x[i];
	return out;
}
QDataStream &operator>>(QDataStream &in,QVector<int>&x)
{
	int n ;
	in >> n;
	x.resize(n);
	for(int i=0;i< n; ++i) in>>x[i];
	return in;
}

extern "C" {

	int DLL_EXPORT initGtGui () {

		qRegisterMetaType<QImage>("QImage");
		qRegisterMetaType<QPoint>("QPoint");
		qRegisterMetaType<QColor>("QColor");
		qRegisterMetaType<QPointF>("QPointF");
		qRegisterMetaType<QPolygonF>("QPolygonF");
		qRegisterMetaType< QVector<QPoint> >("QVector<QPoint>");
		qRegisterMetaType< QVector<QColor> >("QVector<QColor>");
		qRegisterMetaType< QVector<QPointF> >("QVector<QPointF>");
		qRegisterMetaType< QVector<QPolygonF> >("QVector<QPolygonF>");
		qRegisterMetaType< QVector<int> >("QVector<int>");
		qRegisterMetaTypeStreamOperators< QVector<int> >("QVector<int>");
		qRegisterMetaType<QPixmap>("QPixmap");
		qRegisterMetaType<WorldData>("WorldData");


		MainWin * mw = new MainWin;
		GtApp::instance()->registerMainWindow(mw);

		GtServerSelector ss;
		QString nw = ss.initialSelect();
		if (nw.isEmpty()) return -1;
		WorldData wd;
		if (wd.init (nw, GtApp::instance()->splash()->progress())) {
			WorldData::setCurrentWorld (wd);
		}
		

		mw->createMenus ();

		mw->restoreMainState();

		return 0;
	}
}

