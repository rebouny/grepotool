#include <QByteArray>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>

#include <GtCore.h>
#include <GtApp.h>
#include <GtStats.h>
#include <GtWorlddata.h>
#include <GtSplash.h>
#include <GtServer.h>
#include <GtProgress.h>
#include <GtDownload.h>
#include "GtWorldLoader.h"


LoaderThread::LoaderThread (QObject * p, GtProgress* prog): QThread(p),_restart(false),_abort(false), _prog(prog)
{
}

LoaderThread::~LoaderThread (){}

void LoaderThread::loadWorld (const QString& sn)
{
	QMutexLocker ml(&_m);

	_world = sn;
	_prog->abort();

	if (!isRunning()) {
		start (LowPriority);
	} else {
		_restart = true;
		_condition.wakeOne();
	}
}


void LoaderThread::run()
{
	forever {
		if (_abort) return;

		// copy data
		_m.lock();
		QString nw = _world;
		_m.unlock ();

		_prog->reset();

		WorldData wd;
		if (!wd.init (nw,_prog) )
			wd = WorldData();

		_m.lock();
		if (!_restart) {
			if (wd.isValid()) 
				emit worldLoaded (wd);
		}
		if (!_restart)
			// wait for next wakeup
			_condition.wait(&_m);
		if (_abort) {
			_m.unlock(); 
			return;
		}
		_restart = false;
		_m.unlock(); 
	}

}


GtServerSelector::GtServerSelector (QObject * par):QObject (par) 	
{
	countries = GtServer::countries ();
	splash = GtApp::instance()->splash ();
}
QString GtServerSelector::initialSelect()
{
	int lctr = 0;
	int lsrv = 0;

	QString cn = "";
	QList <GtServer> s = GtServer::lastVisited();
	if (s.size()) {
		if(s[0].isAvailable ()) return s[0].serverName();
		cn= s[0].country();
		lsrv = s[0].number();
	}

	splash->setHeadline(tr("Please select a Grepolis world"));

	connect (splash, SIGNAL (langSelChanged(int)), 
		this,SLOT(countryChanged(int)));

	connect (splash, SIGNAL (srvSelChanged(int)), 
		this,SLOT(srvChanged(int)));

	QStringList ctr;
	QStringList flags;
	for(int i=0;i< countries.size(); ++i) {
		flags << GtServer::countryFlagFile (countries[i]);
		ctr   << GtServer::countryName (countries[i]);
		if(countries[i] == cn) lctr=i;
	}
	splash->setSel1 (flags, ctr, lctr);
	country = lctr;
	QList <GtServer> sc = GtServer::serversOfCountry (countries[lctr]);
	QStringList ss;
	for(int i=0;i< sc.size();++i) {
		ss << QString ("%1 %2").arg(sc[i].serverName()).arg(sc[i].worldName());
	}
	splash->setSel2 (ss, lsrv);
	srvChanged(lsrv);	
	if (!splash->waitForServer (tr("Cancel"), tr("Proceed")))
		return "";
	splash->hideControls();
	s = GtServer::serversOfCountry (countries[country]);
	return s[number].serverName();
}


void GtServerSelector::countryChanged (int v)
{
	country = v;
	QList <GtServer> s = GtServer::serversOfCountry (countries[v]);
	QStringList ctr;
	for(int i=0;i< s.size();++i) {
		ctr << QString ("%1 %2").arg(s[i].serverName()).arg(s[i].worldName());
	}
	splash->setSel2 (ctr,0);
	srvChanged(0);
}

void GtServerSelector::srvChanged     (int v)
{
	number = v;
	
	splash->enableOk (false, tr("Proceed"));
	if (v<0) return;
	QList <GtServer> s = GtServer::serversOfCountry (countries[country]);
	if (s[v].isAvailable()) {
		splash->setBottom(tr ("Server %1.grepolis.com is available.").arg(s[v].serverName()),
			tr("Click proceed to load %1").arg(s[v].worldName()));
		splash->enableOk (true, tr("Proceed"));
	} else {
		splash->setBottom(tr ("Server %1.grepolis.com is not available.").arg(s[v].serverName()),
			tr("Please select another world."));
		splash->enableOk (false, tr("Proceed"));
	}
}



