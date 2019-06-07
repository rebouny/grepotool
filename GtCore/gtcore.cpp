/* 

GtUpdater.cpp - Auto updater API

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

#include <QSysInfo>
#include <QCoreApplication>
#include <QThread>
#include <GtDownload.h>
#include <GtArchive.h>

#include "json.h"

#include <QTime>
#include <QFile>
#include <QMetaType>
#include <QDebug>
#include <QTextStream>
#include <QtZlib/zlib.h>


class PrivT : public QThread {
public:
	static void msleep (unsigned long l) {QThread::currentThread()->msleep (l);};
};

void msleep (unsigned long l) {PrivT::msleep (l);};


QString platformString () 
{
	int nbit = sizeof (void*) << 3;
#ifdef Q_OS_WIN	
	return QString("win%1").arg(nbit);
#elif defined Q_OS_LINUX
	return QString("linux%1").arg(nbit);
#elif defined Q_OS_MAC
	return QString("mac%1").arg(nbit);
#endif
}

QString archiveName (const QString& version) 
{
	return QString ("%1-%2-v%3.gta").arg(GT_PRODUCTNAME_STR).arg (platformString()).arg(version);
};

QString versionInfoName () 
{
	return QString ("%1-%2.versioninfo.txt").arg(GT_PRODUCTNAME_STR).arg (platformString());
};

QString correctVersionName (const QString& version)
{
	QStringList vl = version.split(".");
	QStringList vl2;
	for(int i=0;i < 3; ++i) {
		int n = 0;
		if(!i) n=1;
		bool ok= true;
		if (i<vl.size()) n = vl[i].toInt(&ok);
		if (!ok) n=0;
		vl2.push_back(QString::number(n));
	}
	return vl2.join (".");
};

/*inline*/ QString memText (qint64 si) {
	if (si < 1024) {
		return QString::number (si) + " Byte";
	} 
	qint64 nkb = ( si*10 ) / 1024;
	if ( nkb < 10240 ) {
		qint64 val = nkb / 10;
		qint64 dig = nkb - val*10;
		return QString::number (val) + "." + QString::number (dig) + " kB";
	}
	nkb /= 1024;
	if ( nkb < 10240 ) {
		qint64 val = nkb / 10;
		qint64 dig = nkb - val*10;
		return QString::number (val) + "." + QString::number (dig) + " MB";
	}
	nkb *= 10;
	nkb /= 1024;
	qint64 val = nkb / 100;
	qint64 dig = nkb - val*100;
	return QString::number (val) + "." + QString::number (dig) + " GB";
};

inline QString progressPercent (qint64 n, qint64 si) {
	if (!si)      return "  0.0 %";
	if (n>=si)    return "100.0 %";
	qint64 nperm = n * 1000 / si;
	qint64 nperc = nperm/10;
	qint64 dig = nperm-(nperc*10);
	QString r = QString::number (nperc) + "." + QString::number (dig) + " %";
	if (nperc < 10) return QString("  ") + r;
	return QString(" ") + r;
};





QByteArray readGZipFile (const QString &filename)
{
	QByteArray fn = filename.toLatin1();
	QByteArray r;
	gzFile zf = gzopen(fn.constData(), "rb");
	if (!zf) {
		return r;
	}
	char buff[10000];
	int b = gzread(zf,buff,10000);
	while(b > 0) {
		r.append(buff,b);
		if (b < 10000) break;
		b = gzread(zf,buff,10000);
	}
	if (b<0) {
		gzclose (zf);
		return r;
	}
	gzclose (zf);		
	return r;
}
QByteArray readZipFile  (const QString &filename)
{
	QByteArray ret;
	QFile f(filename);
	if (!f.open(QIODevice::ReadOnly)) {
		return ret;
	}
	ret = f.readAll ();
	ret = qUncompress(ret);
	return ret;
}

bool writeZipFile (const QString &filename, const QByteArray& d)
{
	QByteArray dn = qCompress(d);
	QFile f(filename);
	if (!f.open(QIODevice::WriteOnly)) return false;
	f.write (dn);
	return true;
}
QVariant readGZipJson (const QString &fn)
{
	return parseJson (readGZipFile (fn));
}

QVariant parseJson    (const QByteArray& a)
{
	bool success = false;
	QVariant u = QtJson::parse(a, success);
	return u;
}

QByteArray  createJson   (const QVariant& a)
{
	bool success = false;
	return QtJson::serialize(a, success);
}
QVariant    readJson     (const QString & fn)
{
	QFile f(fn);
	if (!f.open(QIODevice::ReadOnly)) return QVariant();
	QByteArray ba = f.readAll ();
	return parseJson(ba);
}

bool        writeJson    (const QVariant& a, const QString& fn)
{
	qDebug () << fn;
	QFile f(fn);
	if (!f.open(QIODevice::WriteOnly)) return false;
	f.write (createJson(a));
	return true;
}




int  char2hex (QChar a)
{
	if(a == '0') return 0;
	if(a == '1') return 1;
	if(a == '2') return 2;
	if(a == '3') return 3;
	if(a == '4') return 4;
	if(a == '5') return 5;
	if(a == '6') return 6;
	if(a == '7') return 7;
	if(a == '8') return 8;
	if(a == '9') return 9;
	if(a == 'A') return 10;
	if(a == 'B') return 11;
	if(a == 'C') return 12;
	if(a == 'D') return 13;
	if(a == 'E') return 14;
	if(a == 'F') return 15;
	return 0;
}

QString replaceStrangeChars (const QString &s)
{
	QString r;
	int i=0;
	while (i < s.length()) {
		if (s.at(i) == '%') {
			++i;
			int m = 16* char2hex(s.at(i));
			++i;
			m += char2hex(s.at(i));
			++i;
			if (i< s.length() && s.at(i) == '%') {
				++i;
				int mm = 16* char2hex(s.at(i));
				++i;
				mm += char2hex(s.at(i));
				++i;
				char ba [3];
				ba[0] = m;
				ba[1] = mm;
				ba[2] = 0;
				r += QString::fromUtf8 (ba,2);
			} else {
				r += QChar(m);
			}
		} else if(s.at(i) == '+') {
			r += " ";
			++i;
		} else {
			r += s.at(i);
			++i;
		}
	}

	return r;
}

QColor randomColor ()
{
	int r = qrand() & 255;
	int g = qrand() & 255;
	int b = qrand() & 255;	
	return QColor(r,g,b,255);
}

int countLines (const QByteArray& b)
{
	int r=0;
	QTextStream is (b);
	QString     l = is.readLine ();
	while (!l.isEmpty ()) {
		l = is.readLine ();
		++r;
	}
	return r;
}

quint64 stringValue (const QString & fn) 
{
	quint64 r = 0;	
	int fl = fn.size();
	for (int i=0;i < 8;++i ) {
		r <<= 8;
		if (i<fl) {
			r += fn[i].toLatin1();// .toLocal8Bit ();
		}
	}
	return r;
}


QVector<int> sortRanks (const QStringList & b)
{
	int si = b.size();
	QVector<int> r (si);
	QVector<quint64> vals (si);
	for(int i=0; i< si ; ++i)  {
		r[i] = i;
		vals[i] = stringValue (b[i]);
	}
	for(int i=0; i< (si-1) ; ++i) {
		for (int j=i+1; j< si; ++j) {
			if (vals[r[i]] > vals[r[j]]) 	{
				int d = r[i];
				r[i] = r[j];
				r[j] = d;
			}
		}
	}
	return r;
}


QVariant parseProFile (const QString & fn)
{
	QFile f(fn);
	if (!f.open(QIODevice::ReadOnly)) return QVariant();	
	QStringList l = QString(f.readAll ()).split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
	QString tol;
	QStringList nli;
	bool continue_line = false;
	for(int i=0; i< l.size(); ++i ) {		

		QString li = l[i].simplified();
		// chop off comments 
		int ci=li.indexOf("#");
		if (ci >= 0) {
			li.chop (li.length()-ci);
			li = li.simplified();
		}

		if (continue_line) {
			tol += " " + li;
		} else {
			if (!tol.isEmpty())
				nli.push_back (tol.simplified());
			tol = li;
		}
		continue_line = tol.endsWith("\\");
		if (continue_line) tol.chop(1);	
		// qDebug () << li;
	}
	if (!tol.isEmpty()) nli.push_back (tol.simplified());
	QVariantMap r;

	int scopes = 0;

	QStringList cmds;

	for(int i=0; i< nli.size(); ++i ) {		
		QString li = nli[i];
		scopes += li.count("{");
		bool dorec = scopes == 0;
		scopes -= li.count("}");
		if (!dorec) continue;

		QStringList ll = li.split(" ",QString::SkipEmptyParts);
		if (ll.size() > 2) {
			QString token = ll[0];
			QString sign = ll[1];
			QStringList sl;
			QStringList tl;
			if (r.contains(token)) tl = r[token].toStringList();
			for (int j=2;j<ll.size();++j) sl.push_back(ll[j]);
			if (ll[1] == "=") {
				tl = sl;
				r[token] = tl;
			} else if (ll[1] == "+=") {
				tl.append (sl);
				r[token] = tl;
			} else {
				cmds.push_back(li);
			}
		} else {
			cmds.push_back(li);
		}
	}
	if (cmds.size()) r["#"] = cmds;
	qDebug () << r;
	return r;
}

 QStringList extractFilesFromQrc  (const QString& fn)
 {
	QStringList r;
	QFile f(fn);

	if (!f.open(QIODevice::ReadOnly)) return r;	
	QString co = QString(f.readAll ()); // .split(QRegExp("[\r\n]"),QString::SkipEmptyParts);

	bool inscope = false;
	QString nn;
	for(int i=0;i< co.length(); ++i) {
		QChar c = co.at(i);
		if(c=='<') { 
			inscope = true;
			nn = nn.simplified();
			if (nn.length()) {
				r.push_back (nn);
				nn = "";
			}
		} else if (c == '>') {
			inscope = false;
		} else {
			if(!inscope) nn+=c;
		}
	}
	nn = nn.simplified();
	if (nn.length()) {
		r.push_back (nn);
	}
	return r;
 }



