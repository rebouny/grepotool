#ifndef __GT_PROGRESS_H
#define __GT_PROGRESS_H

#include <QObject>
#include <QPainter>
#include <QBrush>
#include <QWidget>

#include <QMutex>
#include <QMutexLocker>
#include <QString>

#include <GtCore.h>

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

class EXPORT GtProgress : public QObject {

	Q_OBJECT;
public:

	GtProgress (QObject* o=0);
	virtual ~GtProgress ();
	virtual void onStatusChange ();

	qint64  count () const {QMutexLocker ml(&_m); return _n;};
	qint64  total  () const {QMutexLocker ml(&_m); return _tot;};
	int     permill () const {QMutexLocker ml(&_m); if(!_tot) return 0; return _n*1000 / _tot;};
	QString headline  () const {QMutexLocker ml(&_m); return _headline;};
	QString description  () const {QMutexLocker ml(&_m); return _descript;};
	bool    isOk  () const {QMutexLocker ml(&_m); return _ok&&!_abort;};
	bool    isAbort () const {QMutexLocker ml(&_m); return _abort;};
	bool    idCompleted  () const {QMutexLocker ml(&_m); return _completed;};
	QString error  () const {QMutexLocker ml(&_m); return _error;};

signals:
	void progress (const QString& head, const QString& desc, int permill);
	void completed (bool success, const QString& error);
	void cancelled ();

public slots:

	void setHeadline    (const QString& s);	
	void setDescription (const QString& s);
	void setDescription (int, const QString& s) {setDescription (s);};
	void setCompleted   (int, bool succ, const QString& err) {setCompleted(succ,err);};
	void setCompleted   (bool succ, const QString& err);
	void setProgress    (int, qint64 n, qint64 tot)  {setProgress(n,tot);};
	void setProgress    (qint64 n, qint64 tot);
	void abort ();
	void reset ();
	void setError (const QString & err); 

private:
	mutable QMutex  _m;
	qint64  _n;
	qint64  _tot;
	QString _headline;
	QString _descript;
	bool    _ok;
	bool    _completed;
	bool    _abort;
	QString _error;
};

class ProgressBar : public QWidget {
	Q_OBJECT;
public:
	ProgressBar (QWidget* par);
public slots :
	void setPermill(int perm);
protected :
	void paintEvent(QPaintEvent * );
	int permill; 	
};


#endif

