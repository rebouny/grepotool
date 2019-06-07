
#include <QMainWindow>
#include <QDir>
#include <QSettings>
#include <QLibrary>
 
#include "GtApp.h"
#include "GtArchive.h"
#include "GtSplash.h"

GtApp::GtApp (int argc, char ** argv ):QApplication (argc,argv),_shm ("Grepotool"),_splash(0),_mw(0),_up_and_running(false)
{
	setApplicationName  ("Grepotool");
	setOrganizationName ("Grepotool");

 	QSettings set ("Grepotool", GT_VERSION_SHORT);

	
	// do we have a current language ?
	QString cl = set.value (CURRENT_LANGUAGE, QString("")).toString();
	_ask_initial_language = cl.isEmpty ();

	QStringList al = installedLanguages ();
	if (!al.contains(cl)) {
	
		// detect system locale language 	
		cl = QLocale::system().name().left(2);

		if ( !al.contains (cl) ) {
			cl = "en";  // fall back to english
			_ask_initial_language = true;
		}
	}
	QString trf = applicationDirPath()+QString("/Grepotool_%1.qm").arg(cl);
	if (!_trans.load (trf))
		_trans.load (applicationDirPath()+"/Grepotool_en.qm");
	installTranslator(&_trans);
}

GtApp::~GtApp ()
{
}

void GtApp::registerMainWindow (QMainWindow * mw)
{
	_mw = mw;
}


QStringList GtApp::installedLanguages () const
{
	QStringList filt;
	filt << "Grepotool*.qm";
	QStringList	el = QDir (applicationDirPath()).entryList(filt);
	QStringList ret;
	for (int i=0;i< el.size(); ++i) {
		QStringList ll = el[i].split("_");
		if(ll.size()<2) continue;
		ll = ll[ll.size()-1].split(".");
		if(ll.size()<2) continue;
		if(!ret.contains(ll[0]) )
			ret << ll[0];
	}
	return ret;
}

void GtApp::setLanguage (const QString& l)
{	
	QStringList al = installedLanguages ();
	if (!al.contains(l)) return;
	
	removeTranslator(&_trans);
	QString trf = applicationDirPath()+QString("/Grepotool_%1.qm").arg(l);
	if (!_trans.load (trf))
		_trans.load (applicationDirPath()+"/Grepotool_en.qm");
	installTranslator(&_trans);

	QSettings set ("Grepotool", GT_VERSION_SHORT);
	set.setValue (CURRENT_LANGUAGE, l);

}


void GtApp::checkSharedMem ()
{
	int dd = 0;
	if (_shm.lock()) {
		int * d = (int *) _shm.data();
		dd = *d; 
		*d = 0;
		_shm.unlock();
	}

	if (dd) {
		if (_up_and_running) {
			_mw->activateWindow();
		} else {
			if (_splash) _splash->activateWindow();
		}
	}
	QTimer::singleShot (50, this, SLOT(checkSharedMem ()));
}

typedef int(*moduleInitFunction)();


void GtApp::worldLoadProgress (const QString &world_desc, const QString& desc, int perm)
{
	if ( _up_and_running )
		return;
	QString permstr;
	int perc = perm / 10;
	int np = perm - perc*10;
	permstr = QString::number (perc)+"."+QString::number (np)+" %";
	_splash->setHeadline (world_desc);
	_splash->setBottom (desc, permstr);
	processEvents ();	
}

QString GtApp::availableVersion () const
{
	QString vi_url = QString("http://sourceforge.net/projects/grepo-tool/files/v2/Grepotool-%1-version.txt/download").arg(platformString());
	GtDownload vdl (0, vi_url, "", true);
	while (!vdl.completed()) {
		processEvents ();
		msleep (5);
	}
	if (!vdl.success()) return "";
	return QString(vdl.content());
}

QString GtApp::currentVersion () const
{
 	QSettings set ("Grepotool", GT_VERSION_SHORT);
	return set.value(CURRENT_VERSION,QString(GT_FILEVERSION_STR)).toString();
}

QString GtApp::currentLanguage () const
{
 	QSettings set ("Grepotool", GT_VERSION_SHORT);
	return set.value(CURRENT_LANGUAGE,QString("")).toString();
}

static int getVersionValue (const QString& v) {
	// 2.1.1 alpha ==> 1 +  1*10 + 1*1000 + 2 * 100000
	// 2.1.1 beta  ==> 2 +  1*10 + 1*1000 + 2 * 100000
	// 2.1.1       ==> 9 +  1*10 + 1*1000 + 2 * 100000 
	// 200 100 1 x
	if (v.isEmpty()) return 0;
	QStringList l = v.split(" ", QString::SkipEmptyParts); 
	if (!l.size()) return 0;
	QStringList n = l[0].split(".", QString::SkipEmptyParts); 
	int r = 0;
	bool ok;
	int cv = n[0].toInt(&ok);
	if(!ok) return 0;
	r  = cv;
	r *= 100;
	if (n.size() >1) {
		int cv = n[1].toInt(&ok);
		if(!ok) return 0;
		r  += cv;
		r  *= 100;
	}
	if (n.size() > 2) {
		int cv = n[2].toInt(&ok);
		if(!ok) return 0;
		r  += cv;
		r  *= 10;
	}

	if (l.size()==1) {
		r += 9;
	} else {
		if (l[1] == "alpha") r += 1;
		else if (l[1] == "beta") r += 2;
	}
	return r;
}

static bool isUpdate (const QString ov, const QString& nv)
{ 
	int o = getVersionValue(ov) ;
	int n = getVersionValue(nv) ;
	qDebug () << "installed version: " << ov <<" (" << o << ")";
	qDebug () << "available version: " << nv <<" (" << n << ")";
	if (!o) return true;
	if (!n) return false;
	return o<n;
}

int GtApp::startGrepotool ()
{

	QSettings set ("Grepotool", GT_VERSION_SHORT);

	// open up splashscreen	
	_splash = new Splash;
	_splash->setTitle (tr("Initialization..."));
	_splash->show();
	processEvents ();

	// attach to shared memory segment
	if ( _shm.attach () ) {
		QTimer::singleShot (10, this, SLOT(checkSharedMem ()));
	} else {
		qDebug ("Attach failed ");
		return 0;
	}

	// check or create data directory
	QString ddir (applicationDirPath()+"/data");
	QDir dad (ddir);
	if (!dad.exists() && !dad.mkdir (ddir)) {
		_splash->showError (tr("Initialization failed"),
			tr("Failed to create data directory."),
			tr("Please reinstall Grepotool into a writable directory."),
			tr("Exit"));
		return 0;
	}

	QString tmpdir (applicationDirPath()+"/tmp");
	QDir tdd (tmpdir);
	if (!tdd.exists()) tdd.mkdir (tmpdir);

	// check for update
	_is_updated = false;

	QString cv = currentVersion();

	_splash->setTitle(cv);

	QString av = availableVersion ();
	if (cv.isEmpty() && av.isEmpty()) {
		_splash->showError (tr("Incomplete installation"),
			tr("Failed to download essential files."),
			tr("Please try again later."),
			tr("Exit"));
		return -1;
	}

	if (isUpdate (cv,av)) {

		// download archive
		_splash->progress()->setHeadline (tr ("Updating to version %1").arg(av));

		QString archive_name = QString("Grepotool-%1.gta").arg(platformString());
		QString update_url = QString("http://sourceforge.net/projects/grepo-tool/files/v2/%1/download").arg(archive_name);
		GtDownload vdl (0, update_url, "", true);
		QString desc = tr ("downloading archive %1").arg(archive_name);
		vdl.setProgressMessage (desc);
		connect (&vdl, SIGNAL (progress  (int, qint64 , qint64 )),
			_splash->progress(),SLOT(setProgress (int , qint64 , qint64 )));		
		connect (&vdl, SIGNAL (message  (int, const QString&)),
			_splash->progress(),SLOT(setDescription (int , const QString& )));
		_splash->progress()->setDescription (desc);
		while (!vdl.completed()) {
			QCoreApplication::processEvents ();
			msleep (5);
		}
		if (vdl.success()) {

			_splash->progress()->setHeadline (tr("extracting archive"));
			// extract archive
			GtArchive ar (vdl.content());
	
			if (ar.extractTo (qApp->applicationDirPath(),_splash->progress())) {
				set.setValue(CURRENT_VERSION,av);
				_is_updated = true;
				_splash->setTitle(av);
			} else {
				_splash->showError (tr("Update incomplete"),
				tr("Failed to extract essential files."),
				_splash->progress()->error(),
				tr("Continue"));
				// return -1;
			}
		} else {
			_splash->showError (tr("Update incomplete"),
			tr("Failed to download essential files."),
			vdl.errorText(),
			tr("Continue"));
		}
	}
	
	// load GtLib  &  GtGui
#ifdef __DEBUG_BUILD
	QLibrary gtlib ("GtLibd");
	QLibrary gtgui ("GtGuid");
#else 
	QLibrary gtlib ("GtLib");
	QLibrary gtgui ("GtGui");
#endif

	gtlib.setLoadHints (QLibrary::ExportExternalSymbolsHint | QLibrary::ResolveAllSymbolsHint);		
	if (!gtlib.load ()) {
		_splash->showError (tr("Installation corrupted"),
			tr("Failed to load Grepotool library."),
			tr("Please reinstall Grepotool."),
			tr("Exit"));
		return -1;
	}

	moduleInitFunction init_fun = (moduleInitFunction) gtlib.resolve ("initGtLib");
	// init lib
	if (init_fun) {
		int r = init_fun ();
		if (r) return r;
	} else {
		_splash->showError (tr("Installation corrupted"),
			tr("Failed to init Grepotool library."),
			tr("Please reinstall Grepotool."),
			tr("Exit"));
		return -1;
	}

	gtgui.setLoadHints (QLibrary::ExportExternalSymbolsHint | QLibrary::ResolveAllSymbolsHint);		
	if (!gtgui.load ()) {
		_splash->showError (tr("Installation corrupted"),
			tr("Failed to load Grepotool GUI."),
			tr("Please reinstall Grepotool."),
			tr("Exit"));
		return -1;
	}

	moduleInitFunction gui_init_fun = (moduleInitFunction) gtgui.resolve ("initGtGui");
	// init lib
	if (gui_init_fun) {
		int r = gui_init_fun ();
		if (r) {
			_splash->waitForButton(tr("Exit"),"");
			return r;
		}
	} else {
		_splash->showError (tr("Installation corrupted"),
			tr("Failed to start Grepotool GUI."),
			tr("Please reinstall Grepotool."),
			tr("Exit"));
		return -1;
	}

	if(_mw) {
		_splash->finish (_mw);
		_mw->show();
		_up_and_running = true;
		return exec ();
	}
	return 0;
}


