
#include <GtArchive.h>
#include <GtApp.h>
#include <GtProgress.h>

#include <QThread>
#include <QDir>
#include <QFileInfo>
#include <QLibrary>
#include <QProcess>
#include <QProcessEnvironment>
#include <QStringList>


typedef struct {const char* src; const char* dst;} FileSpec; 


static void copyFile (const QString& src, const QString& dst, bool rm)
{
	if (QFileInfo (dst).exists()) QFile::remove (dst);

	QFile::copy (src, dst);

	if (rm) QFile::remove (src);
}

static QString libName (const QString &ln)  {
	QLibrary l(ln);
	return l.fileName();
}

// File structure at sourceforge
//
// files / 
//    v2 / 
//       Grepotool-win32-version.txt (contains: 2.0.0)
//       Grepotool-win32.gta         (update of Grepotool.dll + translation files)
//       Grepotool-2.0.0-win32.zip   (Gt.exe, GtCore.dll, Qt-Dlls + MSVC-Dlls)   
//       Grepotool-2.0.0-sources.zip
//       Grepotool-translations.zip

int GtApp::createRelease ()
{
	QString version_info = QString("Grepotool-%1-version.txt").arg(platformString());
	QString archive_name = QString("Grepotool-%1.gta").arg(platformString());
	QString zipname      = QString("Grepotool-%1-%2.zip").arg(GT_FILEVERSION_STR).arg(platformString());
	QString src_zipname  = QString("Grepotool-%1-sources.zip").arg(GT_FILEVERSION_STR);


	QVariantMap gt = parseProFile (applicationDirPath()+"/../src/gt.pro").toMap ();


	QStringList src_subdirs;
	if (gt.contains("SUBDIRS")) {
		src_subdirs = gt["SUBDIRS"].toStringList();
		qDebug () << src_subdirs;
	} else {
		qDebug () << "No Grepotool sources found";
		return -1;
	}
	
	// create release directory
	QString reld = applicationDirPath()+"/release";
	if (!QDir(reld).exists()) 
		QDir(reld).mkpath(reld);

	// write version file

	QFile vf(reld+"/"+version_info);
	vf.open(QIODevice::WriteOnly);
	QTextStream vts (&vf);
	vts << QString(GT_FILEVERSION_STR);
	vf.close();

	QStringList langs;
	langs << "de";
	langs << "en";
	langs << "pl";
	langs << "br";
	langs << "es";

	// process translations
	QStringList tra; 
	QString trad = applicationDirPath()+"/../src/translations";
	if (!QDir(trad).exists() ) {
		QDir(trad).mkpath(trad);
	}
	if (QDir(trad).exists()) {

		QStringList ts_filt;
		ts_filt << "Grepotool_*.ts";
		tra = QDir(trad).entryList(ts_filt);
		for(int i=0;i< langs.size();++i) {
			QString tn = QString("Grepotool_%1.ts").arg(langs[i]);
			if(!tra.contains(tn)) tra.push_back(tn);
		}
		QString lud = "C:/Qt/5.1.1/5.1.1/msvc2010/bin/lupdate.exe";
		QString lrel = "C:/Qt/5.1.1/5.1.1/msvc2010/bin/lrelease.exe";
		if(! QFileInfo(lud).exists()) lud= "lupdate";
		if(! QFileInfo(lrel).exists()) lud= "lrelease";

		QDir::setCurrent (applicationDirPath()+"/../src");

		QString lupdate_call = lud + " -recursive " + src_subdirs.join(" ") + " -ts translations/";
		// lupdate.exe -recursive GtCore Grepotool -ts translations/Grepotool_en.ts
		// release.exe translations/Grepotool_en.ts -qm ../bin/Grepotool_en.qm
		for (int i = 0; i< tra.size(); ++i) {
			qDebug() << QString(lupdate_call + tra[i]);
			QProcess::execute (lupdate_call + tra[i]);			
			QString qmn = tra[i];
			qmn.chop(2);
			qmn += "qm";
			QProcess::execute (lrel + " translations/" +tra[i] + " -qm ../bin/" + qmn);			
		}

		QDir::setCurrent (trad);
		QString tzipname = "Grepotool-translations.zip";
		QProcess::execute (QString("zip -u9 %1 *.ts").arg(tzipname));
		copyFile (trad+"/"+tzipname, reld+"/"+tzipname, true);
	}

	// create source zip archive

	QStringList sources; 
	for(int i=0;i< src_subdirs.size();++i) {
		QString sd = applicationDirPath()+"/../src/" + src_subdirs[i];
		QVariantMap m = parseProFile (sd + "/"+src_subdirs[i]+ ".pro").toMap ();
		QStringList ll = m["SOURCES"].toStringList ();
		ll.append ( m["HEADERS"].toStringList ());
		ll.append ( m["FORMS"].toStringList ());
		QStringList resources = m["RESOURCES"].toStringList (); 
		ll.append ( resources );
		for (int k=0;k<resources.size(); ++k) {
			ll.append(extractFilesFromQrc (sd+"/"+resources[k])); 
		}
		ll.append ( m["RC_FILE"].toStringList ());
		for(int k=0;k<ll.size(); ++k) {
			ll[k] = QString ("src/") + src_subdirs[i] + "/" + ll[k];
		}

		sources.append (ll);
	}

	if (sources.size ()) {

		// translations 
		for(int k=0;k< tra.size(); ++k) {
			sources.push_back(QString("src/translations/")+tra[k]);
		}
		
		// create source zip archive
		
		sources.push_back ("src/gt.pro");
		sources.push_back ("src/gt.pri");
		for (int i=0;i< src_subdirs.size();++i) {
			sources.push_back ("src/"+src_subdirs[i]+"/"+src_subdirs[i]+".pro");
		}
	
		QDir::setCurrent (applicationDirPath()+"/..");
		QProcess pz;
		pz.start( QString ("zip -u9 ") +  QDir::currentPath()+"/"+src_zipname +" -@");
		pz.waitForStarted();
		
		for(int i=0;i< sources.size();++i) {
			QString zipcmd = sources[i]+"\n";
			pz.write(zipcmd.toLocal8Bit());
			// qDebug () << sources[i];
		}
		pz.closeWriteChannel();
		pz.waitForFinished();
		pz.terminate();
		copyFile ( QDir::currentPath()+"/"+ src_zipname, reld + "/" + src_zipname,true);
		QDir::setCurrent (applicationDirPath());
	}

	
	// create archive file
	QString arn = reld + "/" + archive_name;
	GtArchive ar (arn);

	// add *.qm-files to installation
	QStringList qm_filt;
	qm_filt << "*.qm";
	QStringList	el = QDir (applicationDirPath()).entryList(qm_filt);
	for (int j=0;j < el.size(); ++j) {
		ar.addFile (applicationDirPath() + "/"+ el[j], el[j]);
	}

	QStringList lib_filt;
	lib_filt << "*.dll";
	lib_filt << "*.so";
	QStringList libs = QDir (applicationDirPath()).entryList(lib_filt);

	for (int i= 0; i < libs.size (); ++i ) {
		QString ln = libs[i];
		if( ln.endsWith("d.dll")) continue;
		if( ln.endsWith("d.DLL")) continue;
		if( ln.endsWith("d.so")) continue;
		if( ln.startsWith("Grepotool")) continue;
		if( ln.startsWith("GtCore")) continue;
		if( ln.startsWith("Qt")) continue;
		if( ln.startsWith("msv")) continue;

		ar.addFile (applicationDirPath() + "/"+ ln,  ln);
	}

	bool succ = ar.compress (0);

	GtProgress prog;

//#ifdef __DEBUG_BUILD
	GtArchive ar2 (arn);
	succ = ar2.extractTo (reld+"/test",&prog);
//#endif

	// create application install zipfile

	QProcess::execute ("zip " + zipname + " Grepotool.exe");
	QProcess::execute ("zip " + zipname + " GtCore.dll");
	QProcess::execute ("zip " + zipname + " GtLib.dll");
	QProcess::execute ("zip " + zipname + " GtGui.dll");
	QProcess::execute ("zip " + zipname + " msvcp90.dll");
	QProcess::execute ("zip " + zipname + " msvcr90.dll");

	QProcess::execute ("zip " + zipname + " Qt5Core.dll");
	QProcess::execute ("zip " + zipname + " Qt5Gui.dll");
	QProcess::execute ("zip " + zipname + " Qt5Svg.dll");
	QProcess::execute ("zip " + zipname + " Qt5Widgets.dll");
	QProcess::execute ("zip " + zipname + " Qt5Network.dll");

	QProcess::execute ("zip -r " + zipname + " ./imageformats");
	QProcess::execute ("zip -r " + zipname + " ./bearer");
	QProcess::execute ("zip -r " + zipname + " ./accessible");
	QProcess::execute ("zip -r " + zipname + " ./platforms");
	
	copyFile (applicationDirPath()+"/"+zipname, reld+"/"+zipname, true);

	return 0;	
}