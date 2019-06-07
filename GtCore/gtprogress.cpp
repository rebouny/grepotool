
#include <GtProgress.h>
#include <GtApp.h>

GtProgress::GtProgress  (QObject* o) :QObject(o),
_n(0),_tot(0),_ok(true), _completed(false), _abort(false)
{
}

GtProgress::~GtProgress () 
{
}

void GtProgress::onStatusChange ()
{
	// GtApp::processEvents();
}


void GtProgress::abort ()
{
	_m.lock();
	_abort=true;
	_m.unlock();
	emit cancelled ();
	onStatusChange ();	
}

void GtProgress::reset ()
{
	_m.lock();
	_abort=false;
	_ok=true;
	_error="";
	_headline="";
	_descript="";
	_n=0;
	_tot = 0;
	_completed = false;
	_m.unlock();
	onStatusChange ();	
}

void GtProgress::setHeadline    (const QString& s)
{
	_m.lock();
	_headline = s;
	_m.unlock();
	 emit progress (headline(), description(), permill());
	 onStatusChange ();
};

void GtProgress::setDescription (const QString& s)
{
	_m.lock();
	_descript = s;
	_m.unlock();
	 emit progress (headline(), description(), permill());
	 onStatusChange ();
}

void GtProgress::setCompleted   (bool succ, const QString& err) 
{
	_m.lock ();
	_completed = true;
	_error = err;
	_ok    = succ;		
	_m.unlock ();
	emit progress (headline(), description(), 1000);
	emit completed (succ, err);
	onStatusChange ();
}

void GtProgress::setProgress    (qint64 n, qint64 tot) 
{
	int operm = permill();
	_m.lock ();	
	_n = n;
	_tot = tot;
	_m.unlock ();		
	if(operm == permill()) return;
	emit progress (headline(), description(), permill());
	onStatusChange ();

}

void GtProgress::setError (const QString & err)
{
	_m.lock ();
	_completed = true;
	_error = err;
	_ok    = false;		
	_m.unlock ();
	emit progress (headline(), error(), permill());
	emit completed (false, err);
	onStatusChange ();
}




ProgressBar::ProgressBar (QWidget* par) : QWidget(par) 
{
	permill = 0;
	setAutoFillBackground(false);
};

void ProgressBar::setPermill(int perm) 
{
	if (perm <0) perm = 0;
	if (perm >1000) perm = 1000;
	permill = perm;		
	update();
};

void ProgressBar::paintEvent(QPaintEvent * ) 
{
	QPainter p(this);
	int w = width()*permill / 1000;
	p.fillRect(0,0,width(),height(),QColor(0,0,0,15));
	p.fillRect(0,0,w,height(),Qt::black);
};
