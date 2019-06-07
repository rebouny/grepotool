#include <QFile>
#include <QVector>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include <QDataStream>
#include <QByteArray>
#include <QBuffer>

#include <GtProgress.h>
#include <GtArchive.h>


GtArchive::GtArchive (const QString & file_name):_fn(file_name)
{
	qDebug() << "file archive";
}


GtArchive::GtArchive (const QByteArray & content) :_cnt(content) 
{
	qDebug() << "download archive";
}

/*! File and pathname of target is relative 
*/
void GtArchive::addFile (const char *source, const char *target) 
{
	_src.push_back (source);
	_tgt.push_back (target);
};

void GtArchive::addFile (const QString& source, const QString& target)
{
	_src.push_back (source);
	_tgt.push_back (target);
};

bool GtArchive::emitError (const QString&  msg) 
{
	_error = msg;
	return false;
};


bool GtArchive::extractChunkV1 (QIODevice * f, int n, int num , const QString& dir) {

	qint64 si = 0;
	char fn   [251];
	if (f->read ((char*) &si, sizeof(qint64))!= sizeof(qint64)) return emitError (tr("unable to read chunk"));
	if (f->read (fn, 250) != 250) return  emitError (tr("unable to read chunk"));

	QString fnam (dir+QString("/")+fn);

	QFileInfo fi (fnam);
	QString pat = fi.absoluteDir().absolutePath();
	if (!QDir(pat).exists()) 
		QDir(pat).mkpath(pat);

	emit progress (n, num, tr ("extracting '%1'").arg (fnam));
	if(qApp) qApp->processEvents();
	QByteArray b = f->read(si);
	QByteArray bu = qUncompress (b); 

	QFile ff (fnam);
	if (!ff.open (QIODevice::WriteOnly)) 
		emitError (tr("unable to write '%1'").arg(fnam));
	ff.write (bu);
	return true;
};


bool GtArchive::addChunkV1 (QFile& f, int n, int num ) {

	char fn   [251];
	char * tc = fn;

	for (int i=0;i< _tgt[n].size(); ++i) {
		QChar cc = _tgt[n].at(i);
		*tc++ = cc.toLatin1();
	}
	*tc = 0;

	QString sfnam (_src[n]);
	QFile ff (sfnam);
	if (!ff.open (QIODevice::ReadOnly)) return emitError (tr("unable to read file"));;
	QByteArray b = ff.readAll ();
	QByteArray bc = qCompress (b,9);

	QString fnam (fn);
	emit progress (n, num, tr ("adding '%1'").arg (fnam));
	if(qApp) qApp->processEvents();

	qint64 si = bc.size();
	if (f.write ((char*) &si, sizeof(qint64)) != sizeof(qint64)) return   emitError (tr("unable to write chunk"));;
	if (f.write (fn, 250) != 250) return   emitError (tr("unable to write chunk"));
	f.write (bc);
	return true;
};

bool GtArchive::extractTo (const QString& dir, GtProgress* prog) {
	int version = 0;
	int num = 0;
	QFile f (_fn);
	QIODevice* iod = 0;  
	QBuffer ds(&_cnt);
	if (!_fn.isEmpty ()) {
		iod = &f;
	} else {
		iod = &ds;
	}
	if (!iod->open (QIODevice::ReadOnly)) {
		if (prog) prog->setError (tr("failed to open archive"));
		return false;
	}
	if (iod->read ((char*) &version, sizeof(int)) != sizeof(int)) {
		iod->close();
		if (prog) prog->setError (tr("failed to read archive"));
		return false;
	}
	if (iod->read ((char*) &num, sizeof(int)) != sizeof(int))  {
		iod->close();
		if (prog) prog->setError (tr("failed to read archive"));
		return false;
	}
	if (version != 1) {
		iod->close();
		if (prog) prog->setError (tr("invalid archive version"));
		return false;
	}
	if (num < 0)  {
		iod->close();
		if (prog) prog->setError (tr("archive corrupted"));
		return false;
	}

	for (int i = 0;i< num; ++i) {
		// ----------------
		qint64 si = 0;
		char fn   [251];
		if (iod->read ((char*) &si, sizeof(qint64))!= sizeof(qint64)) {
			iod->close();
			if (prog) prog->setError (tr("failed to read chunk from archive"));
			return false;
		}
		if (iod->read (fn, 250) != 250) {
			iod->close();
			if (prog) prog->setError (tr("failed to read chunk from archive"));
			return false;
		}
		if(prog) {
			prog->setDescription (tr("extracting '%1'").arg(fn));
			prog->setProgress (i+1, num);
			if (qApp) qApp->processEvents ();
		}
		QString fnam (dir+QString("/")+fn);

		QFileInfo fi (fnam);
		QString pat = fi.absoluteDir().absolutePath();
		if (!QDir(pat).exists()) 
			QDir(pat).mkpath(pat);

		if(qApp) qApp->processEvents();
		QByteArray b = iod->read(si);
		QByteArray bu = qUncompress (b); 

		QFile ff (fnam);
		if (!ff.open (QIODevice::WriteOnly)) {
			iod->close();
			if (prog) prog->setError (tr("failed to write file %1").arg(fn));
			if (qApp) qApp->processEvents ();
			return false;
		}
		ff.write (bu);
		ff.close ();

		// ----------------

		/*if (!extractChunkV1 (iod, i, num, dir) )  {
			iod->close();
			return false;
		}*/
	}
	iod->close();
	return true;
};

bool GtArchive::compress (GtProgress* ) {
	int version = 1;
	int num = _src.size();
	QFile f (_fn);
	if (!f.open (QIODevice::WriteOnly)) return false;
	if (f.write ((char*) &version, sizeof(int)) != sizeof(int)) return false;
	if (f.write ((char*) &num, sizeof(int)) != sizeof(int)) return false;
	for (int i = 0;i< num; ++i) {
		if (!addChunkV1 (f,i,num) ) return false;
	}
	return true;
}
