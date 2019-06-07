#include <QFile>
#include "GtWorlddata.h"


/*! remove the ocean Part from an island image
*/
static QImage processIslandImage (QImage img) {

	QRgb tc = img.pixel(0,0);

	QVector <QRgb> cols = img.colorTable ();

	int ti = -1;
	for (int i=0;i< cols.size();++i) {
		QRgb v = img.color(i);
		if (v == tc) {
			ti = i;
			break;
		}
	}
	// now remove all entries from the color table, where 
	// blue dominates
	if (ti<0) return img;
	for (int i=0;i< cols.size();++i) {
		if (i == ti) continue;
		int r = qRed (img.color(i));
		int g = qGreen(img.color(i));
		int b = qBlue (img.color(i));
		if ( b > r && b > g) img.setColor(i,tc);		
	}
	return img;
}

static QImage coloredImage (QImage img, const QColor & c) {

	QRgb tc = img.pixel(0,0);
	QVector <QRgb> cols = img.colorTable ();

	int ti = -1;
	for (int i=0;i< cols.size();++i) {
		QRgb v = img.color(i);
		if (v == tc) {
			ti = i;
			break;
		}
	}

	int ta = c.alpha();
	int sa = 255 - ta;
	int tr = c.red()   * ta;
	int tg = c.green() * ta;
	int tb = c.blue()  * ta;

	// now add c to all non transparent colors 
	if (ti < 0) return img;
	for (int i=0;i< cols.size();++i) {		
		QRgb cv = img.color(i);
		if (cv == tc) continue;
		int r = ( qRed (cv)  * sa + tr ) / 255;
		int g = ( qGreen(cv) * sa + tg ) / 255;
		int b = ( qBlue (cv) * sa + tb ) / 255;
		img.setColor(i, qRgb (r,g,b));		
	}
	return img;
}

static QImage           _islands[61];
static QVector <QPoint> _town_offsets[61];
static QVector <int>    _town_orientations[61];
static QVector <int>    _town_label_directions[61];
static QPoint           _island_center_offsets [61];

static bool _data_is_init (false);

static void initData ()
{
	if(_data_is_init) return;

	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());
	int imgno = 1;

	QString dir = ":/icons/islands";
	_islands[0] = QImage (":/icons/islands/ocean.png");

	QString fn ("/island%1.png");
	for(int i= 1; i <= 10; ++i ) {
		_islands[imgno] = processIslandImage (QImage(dir + fn.arg(i)));
		++imgno;		
	} 
	fn = "/uninhabited%1.png";
	for(int i= 1; i <= 6; ++i ) {
		_islands[imgno] = processIslandImage (QImage(dir + fn.arg(i)));
		++imgno;		
	} 
	fn = "/rock%1.png";
	for(int i= 1; i <= 20; ++i ) {
		_islands[imgno] = processIslandImage (QImage(dir + fn.arg(i)));
		++imgno;		
	} 

	fn = "/island%1.png";
	for(int i= 11; i <= 20; ++i ) {
		_islands[imgno] = processIslandImage (QImage(dir + fn.arg(i)));
		++imgno;		
	} 

	fn = "/uninhabited%1.png";
	for(int i= 7; i <= 20; ++i ) {
		_islands[imgno] = processIslandImage (QImage(dir + fn.arg(i)));
		++imgno;		
	} 

	QFile f(":/files/offsets.json");
	f.open(QIODevice::ReadOnly);
	QVariantMap m = parseJson (f.readAll ()).toMap();
	m = m["islands"].toMap ();
	for (int i=1;  i < 61; ++i) {
		QString in = QString::number(i);
		if(m.contains(in)) {
			QVariantMap il = m[in].toMap();
			QVariantMap sl = il["slots"].toMap();

			int ilx = il["centering_offset_x"].toInt();
			int ily = il["centering_offset_y"].toInt();

			_island_center_offsets [i] = QPoint (ilx,ily);
			for (int n=0;n<20;++n) {
				QString slotno = QString::number(n);
				if (!sl.contains(slotno)) break;
				QVariantMap slinf = sl[slotno].toMap ();
				int x = slinf["x"].toInt()+50;
				int y = slinf["y"].toInt()+32;
				int to = slinf["orientation"].toInt();
				int lp = slinf["label_dir"].toInt();
				_town_offsets[i].push_back (QPoint(x,y));	
				_town_label_directions[i].push_back(lp);
				_town_orientations[i].push_back(to);
			}
		}
	}
	_data_is_init = true;
}

QImage WorldData::islandImageColored (int island_no, const QColor& c)
{
	return coloredImage (islandImage (island_no), c);
}

const QImage &  WorldData::islandImage (int island_no) 
{
	initData ();
	return _islands[island_no];
}

QPoint  WorldData::islandCenterOffset (int island)
{
	initData ();
	return _island_center_offsets[island];
}

QPoint  WorldData::townOffset  (int island_no, int town_no)
{
	initData ();
	return _town_offsets[island_no][town_no];
}

int  WorldData::townLabelDirection (int island_no, int town_no)
{
	initData ();
	return _town_label_directions[island_no][town_no];
}

int  WorldData::townOrientation    (int island_no, int town_no)
{
	initData ();
	return _town_orientations[island_no][town_no];
}


QString WorldData::activityText (const QDateTime & tim)
{
	QDateTime time = tim;
	if (!time.isValid()) {
		return "---";
	}
	QDateTime ct = QDateTime::currentDateTime();
	int da = tim.daysTo(ct);
	int ho = tim.secsTo(ct);
	ho /= 60; // mins
	if (da) {
		if(da>1) return tr("%1 days ago").arg(da);
		else return tr("1 day ago");
	} else if (ho) {
		if (ho > 120) {
			ho /= 60; // hours
			return tr("%1 hours ago").arg(ho);				
		}
	} 
	return tr("active");
}
QString WorldData::dateText (const QDateTime & tim) 
{
	if (!tim.isValid()) return ("---");
 	return tim.toString ("dd.MM.yy hh:mm:ss");
}

QString WorldData::timeText (int secs)
{
	int time = secs;
	if(time < 0){
		return QString("--:--:--");
	}
	int k = time;
	int ss = k % 60; // secs
	k /= 60;
	int mm = k % 60; // minutes
	k /= 60;
	int hh = k;  // hours
	return QString (QString("%1:%2:%3").arg(hh,2,10,QChar('0')).arg(mm,2,10,QChar('0')).arg(ss,2,10,QChar('0')));
}

int WorldData::activityValue (const QDateTime & tim) 
{
	if (!tim.isValid()) return -1;
	return tim.toTime_t();
}

