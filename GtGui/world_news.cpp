#include <QDebug>
#include "world_news.h"
#include <GtWorlddata.h>
#include <GtApp.h>
#include <GtTowns.h>
#include <GtPlayers.h>
#include <GtAllys.h>
#include <GtStats.h>
#include <GtIslands.h>

#include <QImage>
#include <QPainter>


#include <QtAlgorithms>

static QRect drawOutlines (QImage & img, const QVector<QDateTime> tims, const QVector <int> &vals) 
{
	return QRect (0,0,1,1);
}

static QImage renderGraph (const QSize &si, const QVector<QDateTime> tims, const QVector <int> &vals)
{
	QImage ret (si,QImage::Format_ARGB32_Premultiplied);
	ret.fill (Qt::white);

	return ret;
}





class IndexTx {
public:
	IndexTx():id(-1),cnt(0){};
	IndexTx(const IndexTx&o):id(o.id),cnt(o.cnt),tx(o.tx),idx(o.idx),gid(o.gid){};
	IndexTx& operator = (const IndexTx&o){id = o.id; tx = o.tx; idx = o.idx; cnt = o.cnt; gid=o.gid; return *this;};
	bool operator == (const IndexTx& o)const {return id==o.id;};
	bool operator == (int o)const {return id==o;};
	int id;
	int cnt;
	QString tx;
	int idx;
	int gid;
};
static bool lessThan (const IndexTx &a, const IndexTx &b) {
	return a.idx<b.idx;
}
static bool greaterThan (const IndexTx &a, const IndexTx &b) {
	return a.idx>b.idx;
}

NewsViewer::NewsViewer () : ToolWidget ("News", tr("World news"))
{
	_text = new QTextBrowser;
	//ui.setupUi (f);
	setCentralWidget (_text);
	// ui.label->setText (QString("<b>%1</b>").arg(tr("World news")));

	_text->setOpenLinks(false);
	connect(_text, SIGNAL(anchorClicked(const QUrl &)),
		this,SLOT (handleAnchorClick(const QUrl &)));
}

void NewsViewer::handleAnchorClick (const QUrl& url)
{
	QString s = url.toString();
	qDebug ()<< "anchor: " << s;
	if (s== "#world") {
		worldSummary ();

		return;
	}
	if (s== "#conquers") {

		latestConquers ();
		return;
	}
	if (s== "#ghosts") {
		latestGhosts ();

		return;
	}
	WorldData w = WorldData::currentWorld ();

	QStringList l = s.split(":");
	if (l.size () == 2) {
		if( l[0] == "player" ) {
			int idx = w.playerIndex(l[1].toInt());
			//setPlayer(idx);
			emit playerClickSignal (idx);
		}
		if( l[0] == "ally" ) {
			int idx = w.allyIndex(l[1].toInt());
			//setAlly(idx);
			emit allyClickSignal (idx);
		}
		if( l[0] == "town" ) {
			int idx = w.townIndex(l[1].toInt());
			//setTown (idx);
			emit townClickSignal (idx);
		}
		return;
	}

}

void NewsViewer::worldChanged ()
{
	worldSummary ();
}

QString NewsViewer::head ()
{
	WorldData w = WorldData::currentWorld ();
	QString r = QString("<h2 align=center><a name=top>(%1) %2</a></h2>").arg(w.serverName()).arg(w.worldName ());
	r+= "<b align = center>";
	r+= tr("Database from %1 to %2").arg(w.stats().worldStart().toString("dd.MM.yyyy")).arg(w.stats().worldEnd().toString("dd.MM.yyyy"));
	r+="<br>";
	r+= QString("<a href='#world'>%1</a>").arg (tr("Summary"));
	r+= "|";
	r+= QString("<a href='#conquers'>%1</a>").arg (tr("Conquers"));
	r+= "|";
	r+= QString("<a href='#ghosts'>%1</a>").arg (tr("Ghost towns"));
	r+="</b>";

	
	return r;
		
}
void NewsViewer::worldSummary ()
{
	QString r = head ();

	int num_g = 0;
	int num_t = 0;
	int num_p = 0;
	int num_pa = 0;
	int num_pi = 0;
	int num_i = 0;
	int num_a = 0;
	QVector <IndexTx> quitters;
	WorldData w = WorldData::currentWorld();
	uint ct = QDateTime::currentDateTime().toTime_t() - 3*24*60*60;
	QDateTime lt = QDateTime::fromTime_t (ct);
	for (int i=0;i< w.towns().size();++i) {
		const Town& to = w.towns()[i];
		if (!to.alive) continue;
		if (to.ghost)	++num_g;
		else ++ num_t;
	}
	for (int i=0;i< w.islands().size();++i) {
		if(w.islands()[i].towns.size()) ++num_i;
	}
	for (int i=0;i< w.players().size();++i) {
		const Player& pl = w.players()[i];
		if (pl.alive) {
			++num_p;
			if (pl.act > lt) ++num_pa;
			else ++num_pi;
		}
	}
	for(int i=0;i< w.allys().size(); ++i) {
		if(w.allys()[i].alive) ++num_a;
	}
	r+= "<br><br><b>";
	r+= tr ("%1 towns on %2 islands").arg(num_t).arg(num_i);
	r+= "<br>";
	r+= tr ("%1 players (%2 active)").arg(num_p).arg(num_pa);
	r+= "<br>";
	r+= tr ("%1 alliances").arg(num_a);
	r+= "</b>";
	_text->setText (r) ;
}


void NewsViewer::latestConquers ()
{
	QString r = head ();
	r+= "<br><br><b align=center>"+tr("collecting conquers in the last week")+"</b><br>";
	_text->setText (r) ;
	GtApp::processEvents ();
	QVector <IndexTx> conc;
	WorldData w = WorldData::currentWorld();
	uint ct = QDateTime::currentDateTime().toTime_t() - 7*24*60*60;
	QDateTime lt = QDateTime::fromTime_t (ct);
	for (int i=0;i< w.towns().size();++i) {
		const Town& to = w.towns()[i];
		if (to.ghost) continue;
		if (!to.alive)  continue;
		if (to.last_owner_chg < lt) continue;
		if (to.last_owner == to.player_id) continue;
		IndexTx k;
		k.id  = i;
		k.idx = to.last_owner_chg.toTime_t();
		QString ts = to.last_owner_chg.toString("dd.MM.yyyy hh:mm");
		QString nown = playerLink(w.players()[to.player_index].name,to.player_id);
		if (to.last_owner < 0) {
			k.tx = QString ("<b>%1 %2</b>").arg(ts). arg (tr("%1 conquered %2 (ghost town).").arg(nown).arg(townLink(to.name,to.id)));								
		} else {
			QString oown = tr("unknown player");
			int oi = w.playerIndex(to.last_owner);
			if(oi >= 0) oown = playerLink(w.players()[oi].name, to.last_owner);
			k.tx = QString ("<b>%1 %2</b>").arg(ts). arg (tr("%1 conquered %2 from %3.").arg(nown).arg(townLink(to.name,to.id)).arg(oown));								
		}
		conc.push_back (k);
	}

	QString hl = QString ("<br><br><b align=center>")+tr("%1 conquers in the last week").arg(conc.size())+"</b><br>";
	r = head ();
	qSort(conc.begin(), conc.end(), greaterThan );
	r+= hl;
	_text->setText (r) ;
	GtApp::processEvents ();
	r = head ();
	r+= hl;
	QDate oda;
	r+= "<table>";

    // msc: display only top 100 conquers
    for (int i=0;i<100 && i<conc.size(); ++i) {
		const Town& to = w.towns()[conc[i].id];		
		r+= "<tr valign=center>";

		// date
		r+= "<td>";
		QDate nd = to.last_owner_chg.date();
		if(nd != oda) {
			oda = nd;
			r += "<b>" + nd.toString ("dd.MM.yyyy") + "&nbsp;</b>";
		}
		r+= "</td>";

		// time
		r+= "<td>";
		r += "<b>&nbsp;" + to.last_owner_chg.time().toString ("hh:mm") + "&nbsp;</b>";
		r+= "</td>";

		// conquerer
		QString concpl =  playerLink(w.players()[to.player_index].name,to.player_id);
		int ai = w.players()[to.player_index].ally_index;

		// former owner
		int fo = to.last_owner;
		int foi = w.playerIndex (fo);
		QString tona = (fo < 0)? ghostLink (to.name, to.id):townLink (to.name, to.id);

		QString fopl = tr("ghost town");

		QString foal;

		QString dd;
		if (fo < 0) {
			if (ai>=0) {
				dd = tr ("%1 of alliance %2 conquered ghost town %3.").
					arg (concpl).arg(allyLink(w.allys()[ai].name, to.ally_id)).arg(ghostLink (to.name, to.id));				
			} else {
				dd = tr ("%1 conquered ghost town %2.").
					arg (concpl).arg(ghostLink (to.name, to.id));				
			}
			
		} else if (foi >= 0) {
			const Player & opl = w.players()[foi];
			fopl = playerLink (opl.name,opl.id);
			if (opl.ally_index >= 0) {
				if (ai>=0) {
					dd = tr ("%1 of alliance %2 conquered %3 of %4 of alliance %5.").
						arg (concpl).arg(allyLink(w.allys()[ai].name, to.ally_id)).arg(townLink (to.name, to.id)).arg(fopl).
						arg(allyLink(w.allys()[opl.ally_index].name,opl.ally_id));			
				} else {
					dd = tr ("%1 conquered %2 of %3 of alliance %4.").
						arg (concpl).arg(townLink (to.name, to.id)).arg(fopl).
						arg(allyLink(w.allys()[opl.ally_index].name,opl.ally_id));			
				}
			} else {
				if (ai>=0) {
					dd = tr ("%1 of alliance %2 conquered %3 of %4.").
						arg (concpl).arg(allyLink(w.allys()[ai].name, to.ally_id)).arg(townLink (to.name, to.id)).arg(fopl);
				} else {
					dd = tr ("%1 conquered %3 of %4.").
						arg (concpl).arg(townLink (to.name, to.id)).arg(fopl);
				}
			}
			
		} else {
			if (ai>=0) {
				dd = tr ("%1 of alliance %2 conquered %3 of an unknown player.").
					arg (concpl).arg(allyLink(w.allys()[ai].name, to.ally_id)).arg(townLink (to.name, to.id));			
			} else {
				dd = tr ("%1 conquered %2 of an unknown player.").
					arg (concpl).arg(townLink (to.name, to.id));			
			}
		}

		r+= "<td valign=center>";
		r+= "<b valign=center>"+dd+"</b>";
		r+= "</td>";

		r+= "</tr>";
	}
	_text->setText (r) ;
	GtApp::processEvents ();

}


void NewsViewer::setTown (int idx)
{
	if(idx<0) return;
	QString r = head ();

	QVector <QDateTime>st;
	QVector <QDateTime>en;
	QVector <int > own;
	WorldData w = WorldData::currentWorld();
	const Stats &s = w.stats();
	if (!s.townHistory (w.towns()[idx].id,st,en,own)) return;
	const Town &to = w.towns()[idx];
	if (to.ghost) r += "<br><h3 align=center><img src='qrc:/icons/icons/ghost.ico' width=20 height=20>&nbsp;"+ to.name + "</h3><br>";
	else r += "<br><h3 align=center><img src='qrc:/icons/icons/town.ico' width=20 height=20>&nbsp;"+ to.name + "</h3><br>";
	for(int i= own.size()-1;i>=0;--i) {
		QString o = tr("nobody");
		if (own[i] >= 0) {
			int pi = w.playerIndex(own[i]);
			if (pi < 0) o = tr("unknown player (%1)").arg(own[i]);
			else o = playerLink (w.players()[pi].name,own[i]);
		}
		r+= "<b align = left>" + tr("since %1 owned by %2.").arg(st[i].toString("dd.MM.yyyy hh:mm")).arg(o);
		r+= "</b><br>";
	}
	_text->setText (r) ;
}

void NewsViewer::setAlly (int idx)
{
	if(idx<0) return;
	QString r = head ();
	WorldData w = WorldData::currentWorld();
	const Ally &al = w.allys()[idx];
	r += "<br><h3 align=center><img src='qrc:/icons/icons/ally.ico' width=20 height=20>&nbsp;"+ al.name + "</h3><br>";
	_text->setText (r) ;
}

void NewsViewer::setPlayer (int idx)
{
	if(idx<0) return;
	QString r = head ();
	WorldData w = WorldData::currentWorld();
	const Player &pl = w.players()[idx];
	QVector <QDateTime> ti;
	QVector <int > al;
	const Stats &s = w.stats();
	if (!s.playerHistory (pl.id,ti,al)) return;
	r += "<br><h3 align=center><img src='qrc:/icons/icons/player.ico' width=20 height=20>&nbsp;"+ pl.name + "</h3><br>";

	for(int i= al.size()-1;i>=0;--i) {
		QString o = tr ("no alliance");
		if (al[i] >= 0) {
			int ai = w.allyIndex(al[i]);
			if (ai < 0) o = tr("unknown ally (%1)").arg(al[i]);
			else o = allyLink (w.allys()[ai].name,al[i]);
		}
		r+= "<b align = left>" + tr("since %1: %2.").arg(ti[i].toString("dd.MM.yyyy hh:mm")).arg(o);
		r+= "</b><br>";
	}
	
	_text->setText (r) ;
}


void NewsViewer::latestNewTowns ()
{
		
}
void NewsViewer::latestOffBashies ()
{
		
}
void NewsViewer::latestDefBashies ()
{
		
}
void NewsViewer::latestAllyChanges ()
{
		
}
void NewsViewer::latestGhosts ()
{
	QString r = head ();

	int num_g = 0;
	QVector <IndexTx> quitters;
	WorldData w = WorldData::currentWorld();

	uint ct = QDateTime::currentDateTime().toTime_t() - 7*24*60*60;
	QDateTime lt = QDateTime::fromTime_t (ct);
	for (int i=0;i< w.towns().size();++i) {
		const Town& to = w.towns()[i];
		if (!to.ghost) continue;
		if (!to.alive) continue;
		++num_g;
		// if (to.last_owner_chg < lt) continue;		
		IndexTx k; 
		k.id = to.last_owner;
		k.idx = to.last_owner_chg.toTime_t ();
		k.cnt = 1;
		k.gid = to.id;
		if (quitters.contains (k)) {
			++quitters[quitters.indexOf(k)].cnt;
			continue;
		}
		quitters.push_back (k);
	}

	r += QString ("<br><br><b align=center>")+tr("%1 ghost towns").arg(num_g)+"<br>";
	r+= "<br>" +  tr("The latest quitters:") +"</b>";
	r+= "<br>";
	r+= "<br>" ;
	qSort(quitters.begin(), quitters.end(), greaterThan );
	for (int i=0;i<quitters.size()&& i< 100; ++i) {
		r += "<b>" + QDateTime::fromTime_t (quitters[i].idx).toString ("dd.MM.yyyy") + "&nbsp;";
		int pi = w.playerIndex (quitters[i].id);
		if (pi<0) {
			continue;
			// r+= tr("unknown player (%1)").arg(quitters[i].id);
		} else {
			QString gtx;
			if( quitters[i].cnt )  gtx = QString("(%1 %2)").arg(quitters[i].cnt).arg(ghostLink (tr("Ghosts"), quitters[i].gid));
			const Player & pl = w.players()[pi];
			if (pl.alive) {
				r += tr("%1 has pressed restart %2").arg(playerLink (pl.name,pl.id)).arg(gtx);
			} else {
				r += tr("%1 has left the game %2").arg(playerLink (pl.name,pl.id)).arg(gtx);
			}
		}
		r+="<br>";
	}
	
	_text->setText (r) ;
		
}
