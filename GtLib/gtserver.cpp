#include <QDir>
#include <QFile>
#include <QMenu>
#include <QVariantMap>
#include <QAction>
#include <QApplication>
#include <QFileInfo>
#include <QFile>
#include <QThread>
#include <QTextCodec>
#include <QTextStream>
#include <QTranslator>

//#pragma warning(disable : 4661)

#include <GtApp.h>
#include <GtDownload.h>
#include <GtServer.h>



bool GtServer::isValid () const
{
	return !_country.isEmpty() ;
};


QString   GtServer::dataDir () const     {
	return qApp->applicationDirPath() + "/data/" + serverName ();
};
	


int GtServer::countryIndex (const QString & l) 
{
	static const char * country_short [25] = {"br","cz","de","dk","en","es","fr","gr","hu","it","jp",
		"kr","nl","no","pl","pt","ro","ru","se","sk","th","tr","us","ar","fi"};
	for (int i= 0; i< 25; ++i) {
		if (l == country_short[i]) return i;
	}
	return -1;
};

QString GtServer::countryName (const QString & country)
{
	const QString cn [25] = {tr("Brazil"),tr("Czech Republic"),tr("Germany"),
		tr("Denmark"),tr("England"),tr("Spain"),tr("France"),tr("Greece"),
		tr("Hungary"),tr("Italy"),tr("Japan"),tr("Korea"),tr("Netherlands"),tr("Norway"),
		tr("Poland"),tr("Portugal"),tr("Romania"),tr("Russia"),tr("Sweden"),
		tr(	"Slovakia"),tr("Thailand"),tr("Turkey"),tr("United States"),
		tr("Argentina"), tr("Finland")};
	int k = countryIndex (country);
	if (k < 0) return tr("Unknown");
	return cn[k];
}

QString GtServer::countryLanguage (const QString & country)
{
	const QString cn [25] = {tr("Portuguese (br)"),tr("Czech"),tr("German"),
		tr("Danish"),tr("English (en)"),tr("Spanish (es)"),tr("French"),tr("Greek"),
		tr("Hungarian"),tr("Italian"),tr("Japanese"),tr("Korean"),tr("Dutch"),tr("Norwegian"),
		tr("Polish"),tr("Portugese (pt)"),tr("Romanian"),tr("Russian"),tr("Swedish"),
		tr("Slovak"),tr("Thai"),tr("Turkish"),tr("English (us)"),
		tr("Spanish (ar)"), tr("Finnish")};
	int k = countryIndex (country);
	if (k < 0) return tr("Unknown");
	return cn[k];
}


QString GtServer::countryFlagFile (const QString& l)
{
	int ci = countryIndex(l);
	if (ci<0) return QString(":/icons/flags/flag_un.png");
	return QString(":/icons/flags/flag_%1.png").arg(l);
};

void GtServer::markVisited () 
{
	_last_visit = QDateTime::currentDateTime();
}

void GtServer::markVisited (const QString& sn) 
{
	QStringList srl;
	for(int i=0; i < _list.size(); ++i) {
		if(_list[i].serverName() == sn) _list[i].markVisited ();
		srl.push_back (_list[i].serverTxtLine());
	}

	QFile nsl (qApp->applicationDirPath () + "/data/servers.txt");
	if (nsl.open (QIODevice::WriteOnly)) {
		QTextStream ss (&nsl);
		ss << srl.join("\r\n");
		nsl.close ();
	}
};

void GtServer::setWorldName (const QString& sn) 
{
	_world_name = sn;
};

bool GtServer::operator == (const GtServer& o) const 
{
	return _country == o._country && _number == o._number;
};

inline bool GtServer::operator != (const GtServer& o) const
{
	return _country != o._country || _number != o._number;
};

/*! Merges world name and closed flag into a defined server entry
*/
void GtServer::mergeWithUpdate (const GtServer& update)
{
	_world_name = update._world_name;
	_closed = update._closed;
};

void GtServer::initFromServerTxtLine (const QString & srv_line) 
{
	// "en 73 Jalysos 331257"
	// "en 1  Alpha   0      (closed)"

	// format is separated by one ore more spaces ' ':
	// country number worldname timestamp ended(optional) 
	QStringList l = srv_line.split(" ", QString::SkipEmptyParts);		
	if (l.size() < 4) return;
	_country = l[0];
	_number = l[1].toInt();
	if (_number == 0) _number = -1;
	_world_name = l[2];
	uint tim = l[3].toUInt();
	if (tim) _last_visit = QDateTime::fromTime_t (tim);
	// List contains a linefeed  
	if (l.size() > 4 && l[4].size() > 5) 
		_closed = true;
};

QString GtServer::serverTxtLine () const 
{
	QString numt = "0";
	QString clt = "";
	QString timt = "0";
	if (_last_visit.isValid()) timt = QString::number (_last_visit.toTime_t());
	if (_closed)               clt = "(closed)";
	if (_number > 0)           numt = QString::number(_number);
	return QString ("%1 %2 %3 %4 %5").arg(_country).arg(numt).arg(_world_name).arg(timt).arg(clt);			
};

void GtServer::initFromUpdateLine (const QString & srv_update_line) 
{
	// "en73\tJalysos"
	// "en1\tAlpha (ended)"
	QStringList l = srv_update_line.split("\t");	
	if (l.size() < 2) return;
	bool donu = false;
	QString nu;
	for (int i = 0;i< l[0].size(); ++i) {
		QChar c = l[0].at(i);
		if (!donu && c.isDigit()) donu = true;
		if (donu) nu += c;
		else _country += c;
	}
	if(!nu.isEmpty()) _number = nu.toInt();
	QStringList ll = l[1].split(" ");
	_world_name = ll[0];
	_closed = false;
	if(ll.size()> 1) 
		_closed = true;
};


bool GtServer::fileNeedsUpdate (const QString& fn, bool do_reload) const 
{
	QDateTime ft =fileAccessTime (fn);
	if (!ft.isValid()) return true;
	if (!do_reload) return false;
	int sec = ft.secsTo(QDateTime::currentDateTime());
	return (sec > 3600); // last download was more than 1 hour ago
};

QDateTime GtServer::fileAccessTime (const QString& fn) const 
{
	QFileInfo fi (dataDir()+"/"+fn);
	if (!fi.exists ()) return QDateTime ();
	return fi.lastModified();
};

QDateTime GtServer::lastDownload () const
{
	QDateTime r = fileAccessTime (townFileName ());
	return r;
}

QStringList GtServer::essentialDownloads () const 
{
	QStringList r;		
	QString fn;
	fn = islandFileName     (); if (fileNeedsUpdate (fn,false)) r.push_back(fn);
	fn = unitFileName       (); if (fileNeedsUpdate (fn,false)) r.push_back(fn);
	fn = buildingFileName   (); if (fileNeedsUpdate (fn,false)) r.push_back(fn);
	fn = researchFileName   (); if (fileNeedsUpdate (fn,false)) r.push_back(fn);
	return r;
}
QStringList GtServer::potentialDownloads () const 
{
	QStringList r;		
	if (fileNeedsUpdate (townFileName ()) ||
	fileNeedsUpdate (playerFileName ()) ||
	fileNeedsUpdate (allyFileName ()) ||
	//fileNeedsUpdate (conquerFileName ()) ||
	fileNeedsUpdate (playerOffFileName ()) ||
	fileNeedsUpdate (playerDefFileName ())) {
		r.push_back(townFileName       ()); 
		r.push_back(playerFileName     ()); 
		r.push_back(allyFileName       ()); 
		r.push_back(conquerFileName    ()); 
		r.push_back(playerOffFileName  ());
		r.push_back(playerDefFileName  ());
	}
	return r;
};

bool GtServer::allFilesPresent () const
{
	if (!QFileInfo (dataDir()+"/"+townFileName ()).exists()) return false;
	if (!QFileInfo (dataDir()+"/"+playerFileName ()).exists()) return false;
	if (!QFileInfo (dataDir()+"/"+allyFileName ()).exists()) return false;
	//if (!QFileInfo (dataDir()+"/"+conquerFileName ()).exists()) return false;
	if (!QFileInfo (dataDir()+"/"+playerOffFileName ()).exists()) return false;
	if (!QFileInfo (dataDir()+"/"+playerDefFileName ()).exists()) return false;
	if (!QFileInfo (dataDir()+"/"+islandFileName     ()).exists()) return false;
	if (!QFileInfo (dataDir()+"/"+unitFileName       ()).exists()) return false;
	if (!QFileInfo (dataDir()+"/"+buildingFileName   ()).exists()) return false;
	if (!QFileInfo (dataDir()+"/"+researchFileName   ()).exists()) return false;
	return true;
}


bool GtServer::isAvailable () const
{
	GtDownload dl (0, dataUrl()+"/"+unitFileName(),"",false);
	while (!dl.completed()) {
		qApp->processEvents();
		msleep(5);
	}
	return dl.success();
}


QList <GtServer> GtServer::_list;

QList <GtServer> GtServer::lastVisited ( )
{
	QList <GtServer> ret;

	for (int i = 0;i < _list.size(); ++i) {
		if (_list[i].lastVisit().isValid()) {			
			ret.push_back (_list[i]);
		}			
	}
	int si = ret.size();
	for (int i = 0; i < si-1; ++i) {
		for (int j = i+1; j < si; ++j) {
			QDateTime it = ret.at(i).lastVisit ();
			QDateTime jt = ret.at(j).lastVisit ();
			bool doswap = false;
			if (jt.isValid()) {
				if ( !it.isValid () ) {
					doswap = true;
				} else {
					doswap = jt > it;
				}
				if (doswap) {
					ret.swap (i,j);
				}
			}
		}
	}
	return ret;
}

QList <GtServer> GtServer::serversOfCountry (const QString &country)
{
	QList <GtServer> ret;
	for (int i = 0;i < _list.size(); ++i) {
		if (_list[i].country() == country) {
			ret.push_back (_list[i]);
		}
	}

	int si = ret.size();
	for (int i = 0; i < si-1; ++i) {
		for (int j = i+1; j < si; ++j) {
			if (ret[i].number () > ret[j].number()) {
				ret.swap (i,j);
			}
		}
	}
	return ret;
}

int GtServer::highestServerNumberOfCountry (const QString &country)
{
	int r = 0;
	for (int i = 0;i < _list.size(); ++i) {
		if (_list[i].country() == country && _list[i].number() > r)  {
			r = _list[i].number();
		}
	}
	return r;
}


QString GtServer::worldNameOfServer (const QString & srv)
{
	for (int i = 0;i < _list.size(); ++i) {
		if(_list[i].serverName() == srv) 
			return _list[i].worldName();
	}
	return tr("Unknown");
}

GtServer GtServer::find(const QString & srv)
{
	for (int i = 0;i < _list.size(); ++i) {
		if(_list[i].serverName() == srv) 
			return _list[i];
	}
	return GtServer();
}


QStringList GtServer::countries ()
{
	QStringList ret;
	for (int i = 0;i < _list.size(); ++i) {
		if ( !ret.contains ( _list[i].country() ) ) {
			ret.push_back ( _list[i].country() );
		}
	}
	return ret;
}

void GtServer::init()
{
	QFile sl (qApp->applicationDirPath () + "/data/servers.txt");
	if (sl.open (QIODevice::ReadOnly)) {
		QTextStream st (&sl);
		QString li = st.readLine ();
		while (!li.isEmpty()) {
			GtServer sr;
			sr.initFromServerTxtLine (li);
			if (sr.isValid ()) 
				_list.push_back (sr);
			li = st.readLine ();
		}
		sl.close ();
	}
	//if (!GtApp::instance()->isUpdated()) 
	//	return;

	QFile sl2 (":/files/servers.txt");
	if (sl2.open (QIODevice::ReadOnly)) {
		QTextStream st (&sl2);

		st.setCodec ("UTF-8");

		QString li = st.readLine ();
		while (!li.isEmpty()) {
			GtServer sr;
			sr.initFromUpdateLine (li);
			if (sr.isValid ()) {
				if(_list.contains(sr)) {
				} else
					_list.push_back (sr);
			}
			li = st.readLine ();
		}
		sl.close ();

		QStringList srl;
		for(int i=0; i < _list.size(); ++i) 
			srl.push_back (_list[i].serverTxtLine());

		QFile nsl (qApp->applicationDirPath () + "/data/servers.txt");
		if (nsl.open (QIODevice::WriteOnly)) {
			QTextStream ss (&nsl);
			ss << srl.join("\r\n");
			nsl.close ();
		}
	}
}

bool GtServer::scanForNewWorlds (GtProgress * prog)
{
	bool re = false;
	QStringList cl = countries(); 
	for(int i=0;i<cl.size();++i) {
		int k = highestServerNumberOfCountry (cl[i]);
		bool re = true;
		while (re) {
			++k; 
			QString srv_line = QString("%1 %2 (%1%2) 0").arg(cl[i]).arg(k);
			GtServer sr (srv_line);

			if(sr.isAvailable()) {
				_list.push_back (sr);
				re = true;
			}
		}
	}
	if (re) {
		QStringList srl;
		for(int i=0; i < _list.size(); ++i) 
			srl.push_back (_list[i].serverTxtLine());

		QFile nsl (qApp->applicationDirPath () + "/data/servers.txt");
		if (nsl.open (QIODevice::WriteOnly)) {
			QTextStream ss (&nsl);
			ss << srl.join("\r\n");
			nsl.close ();
		}

	}
	return re; 
}


bool GtServer::serverEnlisted (const QString& sn)
{
	for (int i=0; i< _list.size(); ++i) {
		if (_list[i].serverName() == sn) return true;
	}
	return false;
}




static int hex2num (QChar a)
{
	if(a == '0') return 0;
	if(a == '1') return 1;
	if(a == '2') return 2;
	if(a == '3') return 3;
	if(a == '4') return 4;
	if(a == '5') return 5;
	if(a == '6') return 6;
	if(a == '7') return 7;
	if(a == '8') return 8;
	if(a == '9') return 9;
	if(a == 'a') return 10;
	if(a == 'b') return 11;
	if(a == 'c') return 12;
	if(a == 'd') return 13;
	if(a == 'e') return 14;
	if(a == 'f') return 15;
	if(a == 'A') return 10;
	if(a == 'B') return 11;
	if(a == 'C') return 12;
	if(a == 'D') return 13;
	if(a == 'E') return 14;
	if(a == 'F') return 15;
	return 0;
}


/*! Converts "\uxxxx" 
*/
static QString replaceUnicodeChars (const QString &s)
{
	QString r;
	int i=0;
	while (i < s.length()) {
		if (s.at(i) == '\\') {
			++i; // now at points to 'u'
			++i;
			ushort m = hex2num(s.at(i));
			++i;
			m <<= 4;
			m += hex2num(s.at(i));
			++i;
			m <<= 4;
			m += hex2num(s.at(i));
			++i;
			m <<= 4;
			m += hex2num(s.at(i));
			++i;
			QChar nc (m);
			r += nc;
		} else {
			r += s.at(i);
			++i;
		}
	}
	return r;
}



QString GtServer::mergeWithTonda (GtProgress * prog)
{
	bool doload = false;
	
	QString fn = qApp->applicationDirPath () + "/data/tonda.txt";
	QFileInfo fi(fn);
	if (fi.exists () ) {
		// only once per day
		QDate dt = fi.lastModified ().date();
		QDate cd = QDate::currentDate ();
		doload = cd > dt;
	} else {
		doload= true;
	}

	if (!doload) {
		// no update needed
		return tr("Servers are up to date. No update needed.");
	}

	
	GtDownload dl (0, "http://marco93.de/grepolis/worlds.txt", fn, false);
	while (!dl.completed()) {
		qApp->processEvents();
		msleep(5);
	}
	if(!dl.success()) {
		return tr("Failed to download Tondas server list.");
	}

	// ok we have a new file - let's parse and merge it
	QString s;
	QStringList tonda;
	QFile nsl (fn);
	if (nsl.open (QIODevice::ReadOnly)) {
		QTextStream ss (&nsl);
		s = ss.readAll ();
		nsl.close ();
	} else {
		return tr("Failed to open Tondas list file.");
	}
	if (s.isEmpty()) 
		return false;

	s = replaceUnicodeChars (s);
	s = s.trimmed();
	s.chop(1);
	s = s.remove(0,1);
	QStringList sl = s.split(",",QString::SkipEmptyParts);

	int do_update_file = 0;

	QStringList srl;
	for(int i=0; i < _list.size(); ++i) 
		srl.push_back (_list[i].serverTxtLine());

	for (int i=0;i< sl.size();++i) {
		QStringList srv = sl[i].split(":");
		if(srv.size()!= 2) 
			continue;
		QString srv_name = srv[0].remove(0,1);
		QString world_name = srv[1].remove(0,1);
		srv_name.chop(1);
		world_name.chop(1);

		if (serverEnlisted (srv_name)) 
			continue;

		QString srv_line = QString("%1 %2 %3 0").arg(srv_name.left(2)).arg(srv_name.mid(2)).arg(world_name);
		
		srl.push_back (srv_line);
		++do_update_file;
		GtServer sr (srv_line);
		_list.push_back (sr);
	}

	if (do_update_file == 0) 
		return tr("No new servers found. List is up to date.");
		
	// return true;

	QFile nslf (qApp->applicationDirPath () + "/data/servers.txt");
	if (nslf.open (QIODevice::WriteOnly)) {
		QTextStream ss (&nslf);
		ss << srl.join("\r\n");
		nslf.close ();
	} else {

		return tr("Failed to write server list.");
	}
	return tr("Found %1 new servers.").arg(do_update_file);
}

