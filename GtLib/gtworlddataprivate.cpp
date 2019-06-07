
#include "GtWorlddataPrivate.h"
#include <QByteArray>
#include <QTextStream>
#include <QDataStream>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QRect>
#include <QVariantList>
#include <QVariantMap>
#include <QtCore/QtMath>

#include <GtCore.h>
#include <GtApp.h>
#include <GtStats.h>
#include <GtWorldData.h>
#include <GtSplash.h>
#include <GtServer.h>
#include <GtProgress.h>
#include <GtDownload.h>



static void readDmyTableSetting (QDataStream &s ) {
	int version = 1;
	QList <int>      selection;
	QByteArray       state;
	s>> version;
	if(version <2) {
		QList <int>      colOrder;
		QList <bool>     colVisibility;
		int              sortCol;
		int              sortOrder;
		s>>colOrder;
		s>>selection;
		s>>colVisibility;
		s>>sortCol;
		s>>sortOrder; 
	} else {
		s>>selection;
		s>>state;
	}
}


bool WorldDataPriv::readOldTowns ()
{
	QString fn = srv.dataDir()+"/town_settings.dat";
	if (!QFileInfo (fn).exists()) 
		return false;

	QByteArray ba4 = readZipFile(fn);
	if (!ba4.size()) 
		return false;
		
	QDataStream ds4(&ba4,QIODevice::ReadOnly);
	int version;
	ds4 >> version;
	int nt = 0; // towns().size();
	ds4 >> nt;
	qDebug() << "Old town Data for " << nt << " towns";
	for (int i=0;i<nt; ++i) {
		int town_id;
		int player_id;
		ds4 >> town_id;
		ds4 >> player_id;

		BuildingData bd;
		ResearchData rd;
		UnitData     ud;
		int god;
		bool movb;
		int ty = 0;

		for (int k=0;k< BuildingMax;++k) 
			ds4>>bd.val[k];
		for (int k=0;k< ResearchMax;++k) 
			ds4>>rd.val[k];
		for (int k=0;k< UnitMax;++k) 
			ds4>>ud.val[k];
		ds4 >> god;
		ds4 >> movb;
		if (version>2) {
			ds4 >> ty;			
		}
		qDebug() << "Data for " << town_id;

		if (!town_hash.contains(town_id)) continue;		
		int to_idx = town_hash[town_id];
		Town& to = towns[to_idx];
		// see if player changed
		if (player_id != to.player_id) continue;
				
		to.setUnits (ud);
		to.setResearch (rd);
		to.setBuildings(bd);
		to.setGod((GodIndex)god);
		to.type = (TownTypeIndex) ty;
		qDebug() << "Data for " << to.name;
	}
	if (version > 1) 
		readDmyTableSetting (ds4);

	return true;

}


bool WorldDataPriv::readOldMyTowns ()
{
	
	QString fn = srv.dataDir()+"/mytowns.dat";
	if (!QFileInfo (fn).exists()) 
		return false;
	
	int na = 0;
	QByteArray ba2 = readZipFile(fn);
	if(!ba2.size()) return false;
	QDataStream ds2(&ba2,QIODevice::ReadOnly);
	ds2.setVersion(QDataStream::Qt_4_7);
	ds2 >> na;
	mytowns.clear ();
	
	for (int i=0;i<na; ++i) {
		PlanList pl;	
		//MyTownList al;
		//ds2>>al;
		//data.mytowns().push_back(al);
		int              time;
		bool             arrival;
		int              target;

		ds2>>pl.name;
		ds2>>time;
		ds2>>arrival;
		ds2>>target;

		int n;
		ds2 >> n;		
		

		for(int i =0;i< n; ++i) {
			Plan pla;
			int dmy;
			ds2>> pla.source_id;
			ds2>> dmy; 
			QString sn = "??";
			if (pla.source_id >= 0) sn = towns[town_hash[pla.source_id]].name;
			

			pla.target_id     = target;
			pla.slowest_unit  = (UnitIndex) dmy;
			pla.fixed_arrival = arrival;
			pla.start_time    = QDateTime::fromTime_t(time);
			pla.arrival_time  = QDateTime::fromTime_t(time);
			pl.plans.push_back(pla);
		}
		mytowns.push_back (pl);
		readDmyTableSetting ( ds2 );
	}	
	return true;
}

bool WorldDataPriv::readOldTargets ()
{
	QString fn = srv.dataDir()+"/targets.dat";
	if (!QFileInfo (fn).exists()) 
		return false;
	int na = 0;
	QByteArray ba2 = readZipFile(fn);
	if(!ba2.size()) return false;
	QDataStream ds2(&ba2,QIODevice::ReadOnly);
	ds2.setVersion(QDataStream::Qt_4_7);
	ds2 >> na;
	targets.clear ();
	for (int i=0;i<na; ++i) {
		PlanList pl;	

		int              time;
		bool             arrival;
		int              dmy;	
		int              town;  // attacking town

		ds2 >> pl.name;
		ds2 >> time;
		ds2 >> arrival;
		ds2 >> dmy; 
		ds2 >> town;
		int n;
		ds2 >> n;		
		for(int i =0;i< n; ++i) {
			Plan pla;
			ds2 >> pla.target_id;

			pla.source_id     = town;
			pla.slowest_unit  = (UnitIndex) dmy;
			pla.fixed_arrival = arrival;
			pla.start_time    = QDateTime::fromTime_t(time);
			pla.arrival_time  = QDateTime::fromTime_t(time);
			pl.plans.push_back(pla);
		}
		targets.push_back (pl);
		readDmyTableSetting ( ds2 );
	}	
	return true;
}

bool WorldDataPriv::restorePlans ()
{
	QString fn = srv.dataDir()+"/plandata.dat";
	if (!QFileInfo (fn).exists()) 
		return false;
	int version = 0;
	QByteArray ba = readZipFile(fn);
	if(!ba.size())
		return false;
	QDataStream ds(&ba,QIODevice::ReadOnly);
	ds.setVersion(QDataStream::Qt_4_7);
	ds >> version;
	if (version != 1) return false;	
	int num_mytowns;
	int num_targets;
	int num_plans;
	ds >> num_mytowns;
	ds >> num_targets;
	ds >> num_plans;
	for (int i=0;i< num_mytowns; ++i) {
		mytowns.push_back (PlanList::restore (ds));
	}
	for (int i=0;i< num_targets; ++i) {
		targets.push_back (PlanList::restore (ds));
	}
	for (int i=0;i< num_plans; ++i) {
		plans.push_back (PlanList::restore (ds));
	}
	return true;
}

bool WorldDataPriv::storePlans ()
{
	int version = 1;
	QString fn = srv.dataDir()+"/plandata.dat";
	QByteArray ba;
	QDataStream ds(&ba, QIODevice::WriteOnly);
	ds.setVersion(QDataStream::Qt_4_7);
	ds << version;

	ds << mytowns.size ();
	ds << targets.size ();
	ds << plans.size ();

	for (int i=0;i< mytowns.size(); ++i) {
		mytowns[i].store (ds);
	}
	for (int i=0;i< targets.size(); ++i) {
		targets[i].store (ds);
	}
	for (int i=0;i< plans.size(); ++i) {
		plans[i].store (ds);
	}

	writeZipFile (fn,ba);
	return true;
}

WorldDataPriv::~WorldDataPriv ()
{
}

void WorldDataPriv::storeSettings (GtProgress*)
{
	qDebug() << "storing settings " << srv.serverName();
	if (!world_time.isValid()) return;
	qDebug() << "storing settings really";


	int version = 3;
	int nt = 0; // town data
	int nr = reports.size() + spys.size()+wallstates.size(); // reports
	for (int i=0;i< towns.size();++i) 
		if (towns[i].data) ++nt;

	QByteArray a;
	QDataStream ds(&a, QIODevice::WriteOnly);
	ds.setVersion(QDataStream::Qt_4_7);
	ds << version;
	ds << allys.size();
	ds << players.size();
	ds << towns.size();
	ds << nt;
	ds << nr;

	for(int i=0;i<allys.size(); ++i) {
		const Ally &al = allys[i];
		ds << al.id;
		ds << al.color;
		ds << al.show;		
		ds << al.flags;		
		ds << al.bnds;		
		ds << al.naps;		
		ds << al.bookmark;
	}
	for(int i=0;i<players.size(); ++i) {
		const Player &pl = players[i];
		ds << pl.id;
		ds << pl.color;
		ds << pl.show;
		ds << pl.flags;		
		ds << pl.premium;		
		ds << pl.bookmark;

	}
	for (int i=0;i< towns.size();++i) {
		ds << towns[i].id;
		ds << towns[i].bookmark;
		ds << towns[i].type;
	}
	for (int i=0;i< towns.size();++i) {
		if (!towns[i].data) continue;
		
		ds << towns[i].data->toVariant ();
	}

	for (int i=0;i< reports.size();++i) {
		ds << reports[i].toVariant(); 		
	}
	for (int i=0;i< spys.size();++i) {
		ds << spys[i].toVariant(); 		
	}
	for (int i=0;i< wallstates.size();++i) {
		ds << wallstates[i].toVariant(); 		
	}
	ds << settings;	
	writeZipFile (srv.dataDir()+"/settings.dat", a);
}


int WorldDataPriv::readSettings (GtProgress* )
{
	QByteArray a = readZipFile (srv.dataDir()+"/settings.dat");
	if (!a.size()) return 0;
	int version = 1;
	int nt = 0; // town data
	int nr = 0; // reports
	int as = 0; // allys
	int ps = 0; // players
	int ts = 0; // towns
	for (int i=0;i< towns.size();++i) {
		if (towns[i].data) ++nt;
		nr += towns[i].reports.size();
	}

	QDataStream ds(a);
	ds.setVersion(QDataStream::Qt_4_7);
	ds >> version;
	ds >> as ; 
	ds >> ps;
	ds >> ts;
	ds >> nt;
	ds >> nr;
	
	for(int i=0;i<as ; ++i) {
		int id;
		QColor col;
		bool show;
		int flags;
		QVector <int> bnds;
		QVector <int> naps;
		bool bm;
		ds >> id;
		ds >> col;
		ds >> show;		
		ds >> flags;		
		ds >> bnds;		
		ds >> naps;		
		ds >> bm;
		if (!ally_hash.contains (id)) continue;
		Ally& al = allys[ally_hash[id]];
		al.show = show;
		al.color = col;
		al.flags = flags;
		al.naps = naps;
		al.bnds = bnds;
		al.bookmark = bm;
	}
	

	for(int i=0;i<ps; ++i) {
		int id;
		QColor col;
		bool show;
		bool bm;
		int flags;
		int premium;
		ds >> id;
		ds >> col;
		ds >> show;
		ds >> flags;		
		ds >> premium;		
		ds >> bm;
		if(!player_hash.contains(id)) continue;
		Player &pl = players[player_hash[id]];
		pl.show = show;
		pl.color = col;
		pl.flags = flags;
		pl.premium = premium;
		pl.bookmark = bm;
	}
	
	for (int i=0;i< ts;++i) {
		int id;
		int ty = 0;
		bool bm;
		ds >> id;
		ds >> bm;
		if (version>2) 
			ds>>ty;
		if(!town_hash.contains(id)) continue;
		towns[town_hash[id]].bookmark= bm;
		towns[town_hash[id]].type = (TownTypeIndex) ty;
	}
	

	for (int i=0;i< nt;++i) {

		QVariantMap v;
		ds >> v;
		TownData *da = TownData::fromVariant (v);
		
		if(!town_hash.contains(da->town_id)) {
			delete da;
			continue;
		}
		towns[town_hash[da->town_id]].data = da;
		da->incRef ();
	}
	
	for (int i=0;i< nr;++i) {
		QVariantMap v;
		ds >> v;
		Report r = Report::fromVariant(v);
		if (r.server ().isEmpty ())continue; 
		if (r.server() != srv.serverName ()) continue;
		if (r.type() == ReportInvalid) continue;
		if (r.type() == ReportAttack) {
			reports.push_back(r);
		} else if (r.type() == ReportSpy) {
			spys.push_back(r);
		} else if (r.type() == ReportWallState) {
			wallstates.push_back(r);
		} 
	}
	
	ds >> settings;
	return version;
}


bool WorldDataPriv::init(const QString & server, GtProgress* prog, const QDateTime& tim)
{
	srv = GtServer::find (server);
	if (!srv.isValid()) {
		prog->setError (tr("invalid Grepolis server"));
		qApp->processEvents();
		return false;
	}

	prog->setHeadline (tr ("loading world %1 (%2)").arg (srv.worldName()).arg (srv.serverName()));
	qApp->processEvents();

	bool do_update_stats = false;

	QStringList dl = srv.essentialDownloads (); 
	if (dl.size()) {
		if (srv.isAvailable ()) {
			QDir ddir (srv.dataDir());
			if(!ddir.exists()) ddir.mkpath (srv.dataDir());

			GtDownloader gdl (prog);
			for (int i=0;i<dl.size();++i) {
				QString url = srv.dataUrl ()+"/"+dl[i];
				QString dfn = srv.dataDir ()+"/"+dl[i];
				gdl.addDownload (url,dfn,false);
			}
			qApp->processEvents();

			while (!gdl.completed()) {
				qApp->processEvents();
				msleep (5);
			}

			if (gdl.failCount ()) {
				prog->setError (tr("Download of essential files failed"));
				return false;
			}
			
		} else if (!srv.lastDownload().isValid()) {
			// server not available
			prog->setError (tr("Server not available"));
			return false;
		}		
	}

	dl = srv.potentialDownloads (); 
	if (dl.size()) {
		GtDownloader gdl (prog);
		for (int i=0;i<dl.size();++i) {
			QString url = srv.dataUrl ()+"/"+dl[i];
			QString dfn = srv.dataDir ()+"/"+dl[i];
			gdl.addDownload (url,dfn,false);
		}
		qApp->processEvents();

		while (!gdl.completed()) {
			qApp->processEvents();
			msleep (5);
		}
		do_update_stats = gdl.failCount () == 0;
	}

	if (!srv.allFilesPresent ()) {
		prog->setError (tr("Download of essential files failed"));
		return false;
	}

	prog->setProgress(0,0);
	prog->setDescription(tr("loading world database"));
	QString stfn = srv.dataDir() +"/stats.dat";
	if(!stats.loadV1 (stfn, prog)) 
		do_update_stats = true;
	if(stats.version() <3)  
		do_update_stats = true;

	if(do_update_stats) {
		if( !stats.update (srv.dataDir(),prog) ) 
			return false;
		// store stats
		prog->setProgress(0,0);
		prog->setDescription(tr("storing wold database"));		
		stats.save (stfn, prog); 
	}

	// load units
	QVariant uv = readGZipJson (srv.dataDir()+"/units.json.gz");
	for (int i=0;i <UnitMax;++i) {
		units[i] = Unit::extractData (uv, (UnitIndex)i);
	}

	// create snapshot 

	world_time  = stats.worldEnd();
	world_start = stats.worldStart();
	world_end   = stats.worldEnd();
	if (tim.isValid() && tim < world_time) {
		world_time = tim;
	} 
	if (world_time < world_start) {
		world_time = world_start;
	}

	prog->setProgress(0,0);
	prog->setDescription(tr("creating snapshot"));	
	qApp->processEvents();


	QList<int> aid = stats.allyIds ();
	QList<int> pid = stats.playerIds();
	QList<int> tid = stats.townIds ();
	int        nil = stats.numIslands ();
	int        nal = aid.size(); 
	int        npl = pid.size(); 
	int        nto = tid.size(); 

	qint64 tot = nil +nal + npl + nto;
	qint64 n   = 0;

	QMap <QString, int> an;

	for (int i=0;i< nil;++i) {
		prog->setProgress(n++, tot);
		GtApp::processEvents();
		Island il;
		stats.initIsland(i,il);
		il.image = WorldData::islandImage (il.type);

		int hash_id = il.x*1000+il.y;
		island_id_hash[il.id] = i;
		island_hash[hash_id] = i;
		islands.push_back (il);
	}

	for (int i=0;i< nal;++i) {
		prog->setProgress(n++, tot);
		GtApp::processEvents();
		Ally al;
		stats.initAlly (aid[i],al,world_time);
		al.points = 0;
		ally_hash[aid[i]] = i;
		allys.push_back (al);
		an.insertMulti (al.name.toLower(),i);
	}

	QStringList aan = an.keys();
	for (int i=0; i < aan.size(); ++i) {
		QList<int> v = an.values(aan[i]);
		for (int k=0;k< v.size(); ++k) {
			allys[v[k]].name_rank = i;
		}
	}

	QMap <QString, int> pn;

	for (int i=0;i< npl;++i) {
		prog->setProgress(n++, tot);
		GtApp::processEvents();
		Player pl;
		stats.initPlayer (pid[i],pl,world_time);		
		pl.points = 0;
		
		player_hash[pl.id] = i;

		pl.ally_name = tr("none");
		pl.ally_index = -1;

		pn.insertMulti (pl.name.toLower(),i);

		pl.ally_name_rank = -1;
		// add player to allys
		if (pl.ally_id >=0) {

			if(ally_hash.contains(pl.ally_id)) {
				pl.ally_index = ally_hash[pl.ally_id];
				Ally & al = allys[pl.ally_index];
				pl.ally_name  = al.name;
				pl.ally_name_rank = al.name_rank;
				if (pl.alive) {
					al.players.push_back(i);
					al.off   += pl.off;
					al.def   += pl.def;
					al.bash  += pl.off;
					al.bash  += pl.def;			
				}
			}
		}
		players.push_back (pl);
	}

	QStringList ppn = pn.keys();
	for (int i=0; i < ppn.size(); ++i) {
		QList<int> v = pn.values(ppn[i]);
		for (int k=0;k< v.size(); ++k) {
			players[v[k]].name_rank = i;
		}
	}


    // msc: init towns
	QMap <QString, int> tn;

	for (int i=0;i< nto;++i) {
		prog->setProgress(n++, tot);
		GtApp::processEvents();
		Town to;
		stats.initTown (tid[i],to,world_time);
		tn.insertMulti (to.name.toLower(),i);
		to.ally_name = tr("none");
		to.player_name = tr("none");
		// to.ally_id = -1;
		to.ally_index = -1;
		to.player_index = -1;
		to.ally_name_rank = -1;
		to.player_name_rank = -1;


		if (to.player_id >= 0) {			
			if (player_hash.contains(to.player_id) ) {
				to.player_index = player_hash[to.player_id];
				Player & pl = players[to.player_index];
				to.player_name      = pl.name;
				to.player_name_rank = pl.name_rank;
				to.ally_id          = pl.ally_id;  
				if (to.alive) {
					pl.towns.push_back(i);
					pl.points += to.points;
				}
			}
		}
		if (to.ally_id >= 0) {			
			if (ally_hash.contains(to.ally_id) ) {
				to.ally_index       = ally_hash[to.ally_id];
				Ally & al           = allys[to.ally_index];
				to.ally_name        = al.name;
				to.ally_name_rank   = al.name_rank;
				if (to.alive && !to.ghost) {
					al.towns.push_back(i);
					al.points += to.points;
				}
			}
		}

		int hash_id = to.x * 1000 + to.y;		
		int ili = island_hash[hash_id];
		Island & il = islands[ili];
		to.island = il.id;
		to.island_index = ili;
		if (to.alive) {
			il.towns.push_back(i);
		}

		to.ocean = 0;
		if (to.no >= 0) {
			to.pos = il.pos + WorldData::townOffset(il.type,to.no);
			to.ocean = 10* (to.pos.x() / 12800) + to.pos.y() / 12800;
		}
		town_hash[to.id] = i;
		towns.push_back (to);
	}

	QStringList ttn = tn.keys();
	for (int i=0; i < ttn.size(); ++i) {
		QList<int> v = tn.values(ttn[i]);
		for (int k=0;k< v.size(); ++k) {
			towns[v[k]].name_rank = i;
		}
	}

	
	if(readSettings (prog)<2)
		readOldTowns (); 

	if (!restorePlans ()) {
		readOldMyTowns (); 
		readOldTargets (); 		
		// readOldTowns (); 
	}

	islands.squeeze ();
	players.squeeze ();
	towns.squeeze ();
	allys.squeeze ();
	return true;
}


void WorldDataPriv::initPlayerFilter (QVector <bool> &pl) const
{
	pl = QVector<bool> (players.size(),true);
	for (int i=0;i < players.size();++i) {
		if(!players[i].alive)       pl[i] = false;
		else if(!players[i].points) pl[i] = false;
		else if(!players[i].towns.size()) pl[i] = false;
	}
}

void WorldDataPriv::initTownFilter (QVector <bool> &to) const
{
	to = QVector<bool> (towns.size(),true);
	for (int i=0;i < towns.size();++i) {
		if(!towns[i].alive) to[i] = false;
	}
}

void WorldDataPriv::initAllyFilter (QVector <bool> &al) const
{
	al = QVector<bool> (allys.size(),true);
	for (int i=0;i < allys.size();++i) {
		if(!allys[i].alive) al[i] = false;
		else if(!allys[i].points) al[i] = false;
	}
}


void WorldDataPriv::filterTownsByOcean    (int oc_num, QVector <bool> &to) const
{
	for(int i=0;i< towns.size(); ++i) 
		if(towns[i].ocean != oc_num) to[i] = false;
}
void WorldDataPriv::filterTownsByDistance (const QPoint& pos, int max_d,  QVector <bool> &to) const
{
	for (int i=0;i< towns.size(); ++i) {
		QPoint d = pos-towns[i].pos;
		double dx = d.x();
		double dy = d.y();
        double di = /*sqrt*/qSqrt (dx*dx+dy*dy);
		int nd = di;
		if(nd>max_d) to[i] = false;
	}
}
void WorldDataPriv::filterTownsByRegion   (const QPoint& pmin, const QPoint& pmax,  QVector <bool> &to) const
{
	QRect r (pmin,pmax); 
	for(int i=0;i< towns.size(); ++i) 
		if(!r.contains(towns[i].pos)) to[i] = false;
}
void WorldDataPriv::filterPlayersByActivity (int act, QVector <bool> &pl) const
{
	QDateTime cd = QDateTime::currentDateTime();
	for (int i=0;i< players.size();++i) {
		if(!pl[i] ) continue;
		int pa = players[i].act.secsTo(cd);
		if (pa < act) pl[i] = false;
	}
}

void WorldDataPriv::filterTownsByAlly     (int ally, QVector <bool> &to) const
{
	for (int i=0;i< towns.size();++i) {
		if(!to[i] ) continue;
		if(towns[i].ally_id != ally) to[i] = false;
	}
}

void WorldDataPriv::filterTownsByPlayer     (int player, QVector <bool> &to) const
{
	for (int i=0;i< towns.size();++i) {
		if(!to[i] ) continue;
		if(towns[i].player_id != player) to[i] = false;
	}
}

void WorldDataPriv::filterPlayersByAlly     (int ally, QVector <bool> &pl) const
{
	for (int i=0;i< players.size();++i) {
		if(!pl[i] ) continue;
		if(players[i].ally_id != ally) pl[i] = false;
	}
}

void WorldDataPriv::finalizeTownFilter (QVector <bool> &al,  QVector <bool> &pl,  QVector <bool> &to) const
{
	for (int i=0;i < towns.size();++i) {
		if (!to[i]) continue;
		int ai = towns[i].ally_index;
		int pi = towns[i].player_index;
		if ( ai >= 0 && !al[ai] ) to[i] = false;
		else if ( pi >= 0 && !pl[pi] ) to[i] = false;
	}

}


void WorldDataPriv::finalizePlayerFilter (QVector <bool> &al,  QVector <bool> &pl,  QVector <bool> &to) const
{
	for (int i=0;i< players.size();++i) {
		if (!pl[i]) continue;
		int ai = players[i].ally_index;
		if (ai>= 0 && !al[ai] ) {
			pl[i] = false;
		} else {
			bool pv = false;			
			const QVector<int> tl = players[i].towns;
			for (int j=0;j < tl.size();++j) {
				if (to[tl[j]]) {
					pv = true;
					break;
				}
			}
			pl[i] = pv;
		}		
	}
}
void WorldDataPriv::finalizeAllyFilter (QVector <bool> &al,  QVector <bool> &pl,  QVector <bool> &to) const
{
	for (int i=0;i< allys.size();++i) {
		if (!al[i]) continue;
		bool pv = false;			
		const QVector<int> tl = allys[i].towns;
		const QVector<int> ppl = allys[i].players;
		for (int j=0;j < ppl.size();++j) {
			if (pl[ppl[j]]) {
				pv = true;
				break;
			}
		}
		if(!pv) for (int j=0;j < tl.size();++j) {
			if (to[tl[j]]) {
				pv = true;
				break;
			}
		}
		al[i] = pv;
	}		
}
