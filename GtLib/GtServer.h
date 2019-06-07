#ifndef __GT_SERVER_H 
#define __GT_SERVER_H 

#include <QApplication.h>
#include <QList>
#include <QDateTime>
#include <QStringList>

#include <GtProgress.h>

#ifdef EXPORT 
# undef EXPORT
#endif
#ifdef BUILDING_GTLIB
# define EXPORT DLL_EXPORT
#else
# define EXPORT DLL_IMPORT
#endif


/*! \brief Grepolis server descriptor

The global list of known servers is stored in 'data/servers.txt'.
The resource of gtbase.dll contains a file (servers.txt) with predefined servers and names
These are merged against this list after each update by the GtLoader
*/
class EXPORT GtServer {
	Q_DECLARE_TR_FUNCTIONS(GtServer);
public:

	GtServer () : _country (""), _number (-1), _world_name(""), _closed ( false), _last_visit(QDateTime()) {};
	GtServer (const GtServer&o) : _country (o._country), _number (o._number), _world_name(o._world_name), _closed (o._closed), _last_visit(o._last_visit) {};
	explicit GtServer (const QString &srv) : _country (""), _number (-1), _world_name(""), _closed ( false), _last_visit(QDateTime()) {
		if (srv.isEmpty()) return;
		initFromServerTxtLine (srv);
	};
	GtServer& operator = (const GtServer&o) {
		_country    = o._country;
		_number     = o._number;
		_world_name = o._world_name;
		_closed     = o._closed;
		_last_visit = o._last_visit;
		return *this;
	};

	bool operator == (const GtServer& o) const;
	bool operator != (const GtServer& o) const;

	static int        countryIndex (const QString & l);
	static QString    countryFlagFile (const QString& l);
	static QString    countryName (const QString &country);
	static QString    countryLanguage (const QString &country);

	bool isValid () const;	
	void markVisited ();
	void setWorldName (const QString& sn);
	void mergeWithUpdate (const GtServer& update) ;
	void initFromServerTxtLine (const QString & srv_line);
	QString serverTxtLine () const;
	void initFromUpdateLine (const QString & srv_update_line);

	QString   country () const     {return _country;};
	int       number () const      {return _number;};
	QString   worldName () const   {return _world_name;};
	QString   serverName () const  {return QString ("%1%2").arg(_country).arg(_number);};
    QString   dataUrl () const     {return QString("https://%1.grepolis.com/data").arg(serverName ());};
	QString   dataDir () const  ;
	bool      closed  () const     {return _closed; };


	static QString islandFileName()   {return "islands.txt.gz";};
	static QString unitFileName()     {return "units.json.gz";};
	static QString buildingFileName() {return "buildings.json.gz";};
	static QString researchFileName() {return "researches.json.gz";};

	static QString townFileName()     {return "towns.txt.gz";};
	static QString playerFileName()   {return "players.txt.gz";};
	static QString allyFileName()     {return "alliances.txt.gz";};
	static QString conquerFileName()  {return "conquers.txt.gz";};
	static QString playerOffFileName(){return "player_kills_att.txt.gz";};
	static QString playerDefFileName(){return "player_kills_def.txt.gz";};	 

	bool fileNeedsUpdate (const QString& fn, bool do_reload= true) const;
	QDateTime fileAccessTime (const QString& fn) const;
	QDateTime lastVisit () const {return _last_visit;};
	QDateTime lastDownload () const;
	QStringList essentialDownloads () const;
	QStringList potentialDownloads () const;
	bool        isAvailable () const;
	bool        allFilesPresent () const; 

	static QList <GtServer> lastVisited ();
	static QList <GtServer> serversOfCountry (const QString &country);
	static int highestServerNumberOfCountry (const QString &country);
	static QStringList      countries ();
	static QString worldNameOfServer (const QString & srv);
	static GtServer find(const QString & srv);
	static void     markVisited(const QString & srv);

	static void init();
	static bool scanForNewWorlds (GtProgress * prog);

	static QString mergeWithTonda (GtProgress * prog);
	static bool serverEnlisted (const QString& sn);
private:
	QString   _country;
	int       _number;
	QString   _world_name;
	bool      _closed;
	QDateTime _last_visit;
	static QList <GtServer> _list;
};

#endif

