#ifndef __QT_ARCHIVE_H
#define __QT_ARCHIVE_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QIODevice>
#include <QFile>
#include <QByteArray>

#include <GtCore.h>

#ifdef EXPORT 
# undef EXPORT
#endif
#ifdef BUILDING_GTCORE
# define EXPORT DLL_EXPORT
#else
# define EXPORT DLL_IMPORT
#endif

class GtProgress;

/*! Compressed file archive
*/
class GtArchive : public QObject {
	Q_OBJECT;
public:

	explicit GtArchive (const QByteArray & content);
	explicit GtArchive (const QString & file_name);
	void addFile (const char *source, const char *target);
	void addFile (const QString& source, const QString& target);
	bool extractTo (const QString& dir, GtProgress* prog);
	bool compress (GtProgress* prog);

protected:
	bool emitError (const QString&  msg);
	bool extractChunkV1 (QIODevice* f, int n, int num , const QString& dir);
	bool addChunkV1 (QFile& f, int n, int num );

signals:

	void progress (int n, int total_files, const QString& filename);

private:
	QString           _fn;
	QByteArray        _cnt;
	QString           _error;
	QVector <QString> _src;
	QVector <QString> _tgt;
};


#endif