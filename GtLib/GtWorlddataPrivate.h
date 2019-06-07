#ifndef __GT_WORLDDATA_PRIVATE_H
#define __GT_WORLDDATA_PRIVATE_H

#include <QMetaType>

#include <GtDatabase.h>
#include <GtIslands.h>
#include <GtUnits.h>
#include <GtAllys.h>
#include <GtPlayers.h>
#include <GtTowns.h>
#include <GtReports.h>
#include <GtPlans.h>
#include <GtStats.h>
#include <GtServer.h>
#include <GtBookmarks.h>

class GtProgress;

class EXPORT WorldDataPriv {
	Q_DECLARE_TR_FUNCTIONS(WorldData);
public:
	WorldDataPriv (): _refcount(0){}
	~WorldDataPriv ();

	int nRef () const {return _refcount;};
	void incRef () const {++_refcount;};
	bool decRef () const {--_refcount; return (_refcount == 0);};

	bool init(const QString & server, GtProgress* prog, const QDateTime& t);
	int readSettings (GtProgress* prog);
	void storeSettings (GtProgress* prog);

	GtServer            srv;
	QDateTime          world_time;
	QDateTime          world_start;
	QDateTime          world_end;

	Unit               units [UnitMax];
	QVector <Island>   islands;	
	QVector <Player>   players;	
	QVector <Ally>     allys;	
	QVector <Town>     towns;	

	// editable data
	QVector <PlanList> mytowns;
	QVector <PlanList> targets;
	QVector <PlanList> plans;

	QVector <Report> reports;
	QVector <Report> wallstates;
	QVector <Report> spys;

	// Hash tables for faster access
	QHash<int, int> island_hash;
	QHash<int, int> island_id_hash;
	QHash<int, int> ally_hash;
	QHash<int, int> player_hash;
	QHash<int, int> town_hash;

    // msc conquers
    QHash<int, int> conquers_hash;

	Stats  stats;

	QVariantMap settings;
	QVariant getSetting (const QString& key, const QVariant& def) const{
		if(settings.contains(key)) return settings[key];
		return def;
	};
	void setSetting (const QString& key, const QVariant& val) {
		if (val.isValid()) {
			settings[key] = val;
			return;
		}
		if(!settings.contains(key)) return;
		settings.erase(settings.find(key));
	};

	void initPlayerFilter (QVector <bool> &al) const;
	void initTownFilter   (QVector <bool> &al) const;
	void initAllyFilter   (QVector <bool> &al) const;
	void filterTownsByOcean    (int oc_num, QVector <bool> &to) const;
	void filterTownsByDistance (const QPoint& pos, int max, QVector <bool> &to) const;
	void filterTownsByRegion   (const QPoint& pmin,const QPoint& pmax, QVector <bool> &to) const;
	void filterPlayersByActivity (int act,  QVector <bool> &pl) const;
	void filterPlayersByAlly     (int ally, QVector <bool> &pl) const;
	void filterTownsByAlly       (int ally, QVector <bool> &to) const;
	void filterTownsByPlayer     (int player, QVector <bool> &to) const;

	void finalizeAllyFilter (QVector <bool> &al, QVector <bool> &pl,  QVector <bool> &to) const;
	void finalizePlayerFilter (QVector <bool> &al, QVector <bool> &pl,  QVector <bool> &to) const;
	void finalizeTownFilter (QVector <bool> &al, QVector <bool> &pl,  QVector <bool> &to) const;

	bool readOldMyTowns (); 
	bool readOldTargets (); 
	bool readOldTowns (); 
	bool restorePlans ();
	bool storePlans ();
private:
	mutable int _refcount;
};


#endif

