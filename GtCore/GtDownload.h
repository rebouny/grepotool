#ifndef __QT_DOWNLOAD_H
#define __QT_DOWNLOAD_H
/* 

QtDownload.h - HTTP Download class

Copyright (c) 2014 P. Vorpahl

This file is part of QtUpdater, a free library for automating 
and managing software updates via HTTP.

QtUpdater is free Software: you can redistribute it and/or modify 
it under the terms of the GNU Lesser General Public License as 
published by the Free Software Foundation, either version 3 of the 
License, or any later version. Alternatively, you may use it under 
the terms of the GNU General Public License as published by the Free 
Software Foundation, either version 3 of the License, or any later 
version.

QtUpdater is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License 
along with QtUpdater; see the files 'GPL.txt' and 'LGPL.txt' in 
the base directory of your installation. If not, see 
'http://www.gnu.org/licenses/'.

*/

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QMutex>
#include <QMutexLocker>

#include <GtCore.h>
#ifdef EXPORT 
# undef EXPORT
#endif
#ifdef BUILDING_GTCORE
# define EXPORT DLL_EXPORT
#else
# define EXPORT DLL_IMPORT
#endif


/*! \brief Single HTTP file download

Downloads a single file from a given URL and stores it locally.
*/
class EXPORT GtDownload : public QObject
{
	Q_OBJECT;

public:

	GtDownload (int id, const QString& url, const QString& fn, bool allow_redirect=true);

	inline int     id () const {return _id;};
	inline qint64  size () const {QMutexLocker ml(&_m); return _size;};
	inline qint64  bytesReceived () const {QMutexLocker ml(&_m); return _count;};
	inline bool    completed () const  {QMutexLocker ml(&_m); return _finished;};
	inline bool    error () const  {QMutexLocker ml(&_m); return _error;};
	inline bool    success () const  {QMutexLocker ml(&_m); return !_error;};
	inline bool    redirected () const  {QMutexLocker ml(&_m); return _redirected;};
	inline QString errorText () const  {QMutexLocker ml(&_m); return _error_text;};
	inline const QByteArray & content () const  {return _content;};
	inline void    setProgressMessage(const QString & msg ){_msg = msg;};

signals:

	void completed (int id, bool success, const QString& error);
	void progress  (int id, qint64 received, qint64 size);
	void message   (int id, const QString& msg);

public slots:

	void cancel ();

protected slots:

	void start();
	void replyMetaDataChanged();
	void replyFinished(QNetworkReply *rep);
	void downloadProgress(qint64 n , qint64 );

protected:

	void finish (bool err, const QString &err_tx);

private:
	int                   _id;
	QString               _url;
	QString               _fn;
	bool                  _allow_redirect;
	QNetworkAccessManager _nam;
	QNetworkReply *       _reply;

	mutable QMutex        _m;
	qint64                _size;
	qint64                _count;
	bool                  _redirected;
	bool                  _finished;
	bool                  _error;
	QString               _error_text;	
	QByteArray            _content;
	QString               _msg;
};

class GtProgress;

class EXPORT GtDownloader : public QObject
{
	Q_OBJECT;
public:
	GtDownloader (GtProgress * prog);
	~GtDownloader ();

	int addDownload (const QString& url, const QString& fn, bool allow_redirect=true);

	bool completed () const;

	const GtDownload * download (int i) const {return _dl[i];};

	int successCount () const {return _succ;};
	int failCount () const {return _fail;};
	int firstFail () const {return _first_fail;};

public slots:
	void cancel ();

protected slots:
	void dlProgress  (int id, qint64 received, qint64 size);
	void dlCompleted (int id, bool success, const QString& error);

private:
	mutable QMutex        _m;
	QVector <GtDownload*> _dl;
	GtProgress *          _prog;
	int                   _first_fail;
	int                   _succ;
	int                   _fail;
};

#endif