#ifndef __GT_APP_H 
#define __GT_APP_H 

#include <QApplication>
#include <QTranslator>
#include <QVector>
#include <QColor>
#include <QPointF>
#include <QByteArray>
#include <QDateTime>
#include <QSharedMemory>

#include <GtDownload.h>

#ifdef EXPORT 
# undef EXPORT
#endif
#ifdef BUILDING_GTCORE
# define EXPORT DLL_EXPORT
#else
# define EXPORT DLL_IMPORT
#endif

class QMainWindow;
class Splash;

#define CURRENT_LANGUAGE       "CurrentLanguage"
#define CURRENT_VERSION        "InstalledVersion"


class EXPORT GtApp : public QApplication {

	Q_OBJECT;

public:

	GtApp (int argc, char ** argv );
	~GtApp ();

	static GtApp * instance () {return static_cast < GtApp * > (qApp);};
	int startGrepotool ();

	int createRelease ();

	void setLanguage (const QString& l);

	QStringList installedLanguages () const;

	QString availableVersion () const;
	QString currentVersion () const;
	QString currentLanguage () const;

	bool askLanguage () const {return _ask_initial_language;};
	bool isUpdated   () const {return _is_updated ;};
	bool isUpAndRunning   () const {return _up_and_running ;};
	Splash  *splash  () {return _splash;};

	void registerMainWindow (QMainWindow * mw);


public slots:
	void worldLoadProgress (const QString &world_desc, const QString& desc, int perm);

protected slots:
	void checkSharedMem ();

private:
	QSharedMemory _shm; 
	bool          _ask_initial_language;
	bool          _is_updated;
	QTranslator   _trans;
	QMainWindow  *_mw;
	Splash       *_splash;
	bool          _up_and_running;

};




#endif

