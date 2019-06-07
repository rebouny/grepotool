#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextCodec>

#pragma warning(disable : 4661)

#include <GtServer.h>
#include <GtApp.h>

/*
GtServerList GtServerList::_global_list; 


GtServerList GtServerList::globalList () 
{
	return _global_list;
}

void GtServerList::initSplash ( )
{
	
	QFile sl (qApp->applicationDirPath () + "/data/servers.txt");
	if (sl.open (QIODevice::ReadOnly)) {
		QTextStream st (&sl);
		QString li = st.readLine ();
		while (!li.isEmpty()) {
			GtServer sr;
			sr.initFromServerTxtLine (li);
			if(sr.isValid ()) 
				_global_list.push_back (sr);
			li = st.readLine ();
		}
		sl.close ();
	}
	if (!GtApp::instance()->isUpdated()) 
		return;

	GtServerList nl;
	QFile sl2 (":/files/servers.txt");
	if (sl2.open (QIODevice::ReadOnly)) {
		QTextStream st (&sl2);

		st.setCodec ("UTF-8");

		QString li = st.readLine ();
		while (!li.isEmpty()) {
			GtServer sr;
			sr.initFromUpdateLine (li);
			if (sr.isValid ()) 
				nl.push_back (sr);
			li = st.readLine ();
		}
		sl.close ();
		_global_list.mergeWithUpdate (nl);

		QFile nsl (qApp->applicationDirPath () + "/data/servers.txt");
		if (nsl.open (QIODevice::WriteOnly)) {
			QTextStream ss (&nsl);
			ss << _global_list.serverTextList ().join("\r\n");
			nsl.close ();
		}
	}
}







QStringList GtServerList::countries () const 
{
	QStringList r;
	for (int i = 0;i < size(); ++i) {
		if ( !r.contains ( at(i).country() ) ) {
			r.push_back ( at(i).country() );
		}
	}
	return r;
};

GtServerList GtServerList::sortByNumber () const 
{
	GtServerList r (*this);
	int si = size();
	if (si < 2) return r;
	for (int i = 0; i < si-1; ++i) {
		for (int j = i+1; j < si; ++j) {
			if (r.at(i).number () > r.at(j).number()) {
				r.swap (i,j);
			}
		}
	}
	return r;
};

GtServerList GtServerList::sortByDate () const 
{
	GtServerList r (*this);
	int si = size();
	if (si < 2) return r;
	for (int i = 0; i < si-1; ++i) {
		for (int j = i+1; j < si; ++j) {
			QDateTime it = r.at(i).lastVisit ();
			QDateTime jt = r.at(j).lastVisit ();
			bool doswap = false;
			if (jt.isValid()) {
				if ( !it.isValid () ) {
					doswap = true;
				} else {
					doswap = jt > it;
				}
				if (doswap) {
					r.swap (i,j);
				}
			}
		}
	}
	return r;
};

GtServerList GtServerList::openServers () const 
{
	GtServerList r;
	for (int i = 0;i < size(); ++i) {
		if (!at(i).closed ()) {
			const GtServer & sr = at(i);
			r.push_back (sr);
		}				
	}
	return r;
};

GtServerList GtServerList::lastVisited () const
{
	GtServerList r;
	for (int i = 0;i < size(); ++i) {
		if (at(i).lastVisit().isValid()) {
			const GtServer & sr = at(i);
			r.push_back (sr);
		}			
	}
	return r.sortByDate ();
};

GtServerList GtServerList::serversOfCountry (const QString& c) const 
{
	GtServerList r;
	for (int i = 0;i < size(); ++i) {
		if (at(i).country() == c) {
			const GtServer & sr = at(i);
			r.push_back (sr);
		}
	}
	return r;
};

void GtServerList::mergeWithUpdate (const GtServerList &o) 
{
	for (int i = 0;i < o.size(); ++i) {
		if (contains(o[i])) {
			GtServer & gs = (*this)[indexOf (o[i])];
			gs.mergeWithUpdate (o[i]);
		} else {
			push_back (o[i]);
		}
	}
};

int GtServerList::indexOfServer (const GtServer & srv) const 
{
	if (!contains(srv)) return -1;
	return indexOf (srv);			
};

QStringList GtServerList::serverTextList () const 
{
	QStringList nsl;
	for (int i = 0;i < size(); ++i) {
		nsl.push_back (at(i).serverTxtLine());
	}
	return  nsl;
};

*/