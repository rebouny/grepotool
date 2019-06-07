/*

GtDownload.cpp - Download class

Copyright (c) 2014 P. Vorpahl

This file is part of GtUpdater, a free library for automating
and managing software updates via HTTP.

GtUpdater is free Software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation, either version 3 of the
License, or any later version. Alternatively, you may use it under
the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or any later
version.

GtUpdater is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GtUpdater; see the files 'GPL.txt' and 'LGPL.txt' in
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
#include <GtDownload.h>
#include <GtProgress.h>

GtDownload::GtDownload (int id, const QString& url, const QString& fn, bool allow_redirect):_id(id),_url (url), _fn(fn),_allow_redirect(allow_redirect),_redirected (false),_finished(false)
{		
	QTimer::singleShot(0, this, SLOT(start()));
};

void GtDownload::cancel () 
{
	if (_reply)
		_reply->abort();
};

void GtDownload::start() 
{
	_size       = 0;
	_count      = 0;
	_finished   = false;
	_error      = false;
	_redirected = false;

	QNetworkRequest req(_url);

	// This is but a hack since Sourceforge treats an empty UserAgent like a webbrowser and
	// redirects won't work if QNetworkRequest::UserAgentHeader is left empty
	req.setHeader (QNetworkRequest::UserAgentHeader, " ");

	_reply = _nam.get(req);
	connect(_reply, SIGNAL(metaDataChanged()), this, SLOT(replyMetaDataChanged()));
	connect(&_nam, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
};

void GtDownload::replyMetaDataChanged()
{

	if (_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 307 || _reply->rawHeaderList().contains("Location")) {

		_m.lock();
		_redirected = true;
		_m.unlock();
		if (!_allow_redirect) {
			return;
		}
		QString nu = _reply->header(QNetworkRequest::LocationHeader).toString();
		QNetworkRequest req(nu);
		req.setHeader (QNetworkRequest::UserAgentHeader, " ");
		_reply = _nam.get(req);
		connect(_reply, SIGNAL(metaDataChanged()), this, SLOT(replyMetaDataChanged()));

	} else if (_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {

		QVariant cl = _reply->header(QNetworkRequest::ContentLengthHeader);
		if (cl.isValid()) {
			_m.lock();
			_size = cl.toLongLong();
            qint64 ns = _size;
			_m.unlock();
			
			if (!_msg.isEmpty ()) {
                emit message (_id, _msg + " " + memText (ns));
			}
			connect (_reply, SIGNAL (downloadProgress(qint64 , qint64)), this, SLOT (downloadProgress(qint64 , qint64)));
		}
	}
};

void GtDownload::replyFinished(QNetworkReply *rep) 
{	

	if (rep->error() != QNetworkReply::NoError) {
		finish (true, _reply->errorString());
		rep->deleteLater ();
		qDebug()<< "download of " << rep->url() <<" failed '" << _reply->errorString() << "' Error number: "<< (int) rep->error();
		return;
	} 

	if (rep != _reply) { 
		// simply ignore finish of a redirected request
		rep->deleteLater ();
		qDebug()<< "request "<< rep->url()<< "\nredirected to " << _reply->url();
		return;
	}

	if (_redirected && ! _allow_redirect) {
		finish (true, tr ("illegal redirect"));
		qDebug()<< rep->url () << " illegal redirect";
		rep->deleteLater ();
		return;
	} 

	_content = rep->readAll();

	if (!_content.size()) {		
		finish (true , tr ("no data received"));
		qDebug()<< rep->url () << " no data received";
		rep->deleteLater ();
		return;
	}

	if (_fn.isEmpty ()) {
		// no file specified ==> this is but a successful ping 
		finish (false , "" );
		qDebug()<< rep->url () << " ok";
		rep->deleteLater ();
		return;
	}

	QFile f(_fn);
	if (!f.open (QIODevice::WriteOnly)) {
		qDebug()<< "failed to open file";
		finish (true , f.errorString() );
		rep->deleteLater ();
		return;
	}

	if (-1 == f.write ( _content ) ) {
		f.close ();
		qDebug()<< "Failed to write file '" << _fn <<"' " << f.errorString();
		finish (true , f.errorString() );
	} else {
		f.flush ();
		f.close ();
		qDebug()<< rep->url () << " download complete" ;
		finish (false , "" );
	}
	rep->deleteLater ();
};

void GtDownload::downloadProgress(qint64 n , qint64 ) 
{
	_m.lock ();
	_count = n;
	qint64 si = _size;
	_m.unlock();
	emit progress (_id, n, si);
};

void GtDownload::finish (bool err, const QString &err_tx) 
{
	_m.lock();
	_finished   = true;
	_error      = err;
	_error_text = err_tx;
	qDebug()<< err_tx;

	_m.unlock();
	emit completed (_id, !err, err_tx);
};



GtDownloader::GtDownloader (GtProgress * prog) : _prog(prog) ,_succ(0),_fail(0), _first_fail (-1)
{
}

GtDownloader::~GtDownloader ()
{
	for (int i=0;i< _dl.size(); ++i) {
		delete _dl[i];
	}
}

int GtDownloader::addDownload (const QString& url, const QString& fn, bool allow_redirect)
{
	QMutexLocker ml(&_m);
	int ret = _dl.size();
	GtDownload *d = new GtDownload (ret, url, fn, allow_redirect);
	connect (d, SIGNAL(progress(int,qint64,qint64)), this,SLOT(dlProgress(int,qint64,qint64)));
	connect (d, SIGNAL(completed (int, bool, const QString& )), this, SLOT (dlCompleted (int, bool, const QString& )));
	_dl.push_back (d);
	if(!_prog) return ret;
	connect (_prog, SIGNAL(cancelled()), d, SLOT(cancel()));
	_prog->setDescription (tr ("Downloading %1 file(s)").arg(_dl.size())) ;
	return ret;
}


bool GtDownloader::completed () const
{
	QMutexLocker ml(&_m);
	int cpl = 0;
	for (int i=0;i< _dl.size(); ++i) {
		if(_dl[i]->completed()) ++cpl;
	}
	return cpl ==_dl.size();
}

void GtDownloader::cancel ()
{
	for (int i=0;i< _dl.size(); ++i) {
		_dl[i]->cancel ();
	}
}

void GtDownloader::dlCompleted (int id, bool success, const QString& )
{
	if (success) {
		++_succ;
		return;
	}
	++_fail;
	if (_fail>1) return;
	_first_fail = id;
}


void GtDownloader::dlProgress  (int , qint64 , qint64)
{
	if (!_prog) return;
	QMutexLocker ml(&_m);
	qint64 n = 0;
    qint64 tot = 0;
	for (int i=0;i< _dl.size(); ++i) {
		tot += _dl[i]->size();
		n   += _dl[i]->bytesReceived ();
	}
    _prog->setDescription (tr ("Downloading %1 file(s)").arg(_dl.size())+" "+ memText(tot));
	_prog->setProgress (n, tot);
}

