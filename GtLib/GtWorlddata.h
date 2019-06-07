#ifndef __GT_WORLDDATA_H
#define __GT_WORLDDATA_H

#include <QApplication>
#include <QDateTime>
#include <QPoint>
#include <QImage>
#include <QColor>
#include <QMetaType>
#include <GtCore.h>
#include <GtReports.h>
#include <GtIndexes.h>

class Unit;
class Island;
class Player;
class Ally;
class Town;
class PlayerData;
class AllyData;
class TownData;
class PlanList;
class Report;
class Bookmark;
class Stats;
class GtProgress;
class WorldDataPriv;

#ifdef EXPORT 
# undef EXPORT
#endif
#ifdef BUILDING_GTLIB
# define EXPORT DLL_EXPORT
#else
# define EXPORT DLL_IMPORT
#endif

class EXPORT SearchData {
public:
	SearchData(){};
	bool ghosts;
	bool useallys;
	int  useinact;
	bool usedist;
	bool usetime;
	bool useocean;
	int ocean;
	int time;
	int dist;
	QPoint mapcenter;
	QVector<int> allys;
};


class EXPORT WorldData {
	Q_DECLARE_TR_FUNCTIONS (WorldData);
public:
	WorldData ();
	WorldData (const WorldData & o);
	~WorldData ();
	WorldData & operator = (const WorldData & o);
	
	QDateTime worldStart () const;
	QDateTime worldEnd () const;
	QDateTime worldTime () const;
	QDateTime &worldStart ();
	QDateTime &worldEnd ();
	QDateTime &worldTime ();

	inline bool operator == (const WorldData & o) const;
    /*inline*/ bool isValid () const;
	inline void invalidate ();
	Unit & unit (UnitIndex u);
	const Unit & unit (UnitIndex u) const;

    /*inline*/ QString serverName () const ;
    /*inline*/ QString worldName () const ;

    /*inline*/ QVector <Island>     &islands ()  ;
    /*inline*/ QVector <Ally>       &allys ()    ;
    /*inline*/ QVector <Town>       &towns ()    ;
    /*inline*/ QVector <Player>     &players ()  ;

    /*inline*/ QVector <PlanList>   &mytowns() ;
    /*inline*/ QVector <PlanList>   &targets() ;
    /*inline*/ QVector <PlanList>   &plans()   ;

    /*inline*/ const QVector <Island>   &islands () const;
    /*inline*/ const QVector <Ally>     &allys () const  ;
    /*inline*/ const QVector <Town>     &towns () const  ;
    /*inline*/ const QVector <Player>   &players () const;

    /*inline*/ const QVector <PlanList> &mytowns() const;
    /*inline*/ const QVector <PlanList> &targets() const;
    /*inline*/ const QVector <PlanList> &plans() const;

    /*inline*/ int playerIndex (int id) const;
    /*inline*/ int allyIndex (int id) const;
    /*inline*/ int townIndex (int id) const;
    /*inline*/ int islandIndex (int id) const;
    /*inline*/ int islandIndex (int x, int y) const;

	QHash<int, int> & islandHash ();
	QHash<int, int> & islandIdHash ();
	QHash<int, int> & allyHash ();
	QHash<int, int> & playerHash ();
	QHash<int, int> & townHash ();

	Stats & stats();
	const Stats & stats() const;

	// static global functions

    static WorldData &currentWorld();
	static void setCurrentWorld (const WorldData& w);

	static const QImage & islandImage (int island_no);		
	static QPoint         islandCenterOffset (int island);
	static QPoint         townOffset  (int island_no, int town_no);
	static int            townLabelDirection (int island_no, int town_no);
	static int            townOrientation    (int island_no, int town_no);
	static QImage         islandImageColored (int island_no, const QColor& c);

	bool init(const QString & server, GtProgress* prog);
	void storeSettings (GtProgress* prog);


	int townSpecials (int town) const;
	void setTownSpecials (int town, int spc) ;
	QString townSpecialText (int town, bool text=false) const;
	QPixmap townSpecialPixmap (int town) const;
	QString townUnitsText (int town, bool text=false) const;
	QPixmap townUnitsPixmap (int town) const;

	QString playerLabelText (int p) const;
	QString allyLabelText (int a) const;
	QString TownLabelText (int t, bool tooltipp) const;
	QString TownLabelText (const QString& to, int p, int a, bool tooltipp) const;

	QVector <QPoint> townPositionsOfAlly (int a) const; 


	QPoint townCoordinates (int idx) const;
	QPoint islandCoordinates (int idx) const;
	static int oceanNumberFromMapCoords  (const QPoint& p);
	static int oceanNumberFromTownCoords  (const QPoint& p);
	int oceanNumberOfTown (int idx) const;
	int oceanNumberOfIsland (int idx) const;

	static QPixmap townTypeSymbol(TownTypeIndex);
	static void renderTownTypeSymbol(QPainter* paint, TownTypeIndex typ, const QPoint& pos, const double &radius);
	static QString townTypeText(TownTypeIndex t, bool tooltipp);


	int handleReport (const Report & r);
	int reportCount () const;
	int spyCount () const;
	Report report (int no) const;
	Report spy (int no) const;
	Report lastSpy (int town_id) const;
	Report wallDiff (int player_id, const QDateTime tim) const;
	Report lastAttack (int town_id) const;

	static QString activityText (const QDateTime & tim); 
	static QString dateText (const QDateTime & tim); 
	static QString timeText (int secs); 
	static int activityValue (const QDateTime & tim); 

	static QVariant globalSetting (const QString& key, const QVariant& def=QVariant());
	static QVariant setting (const QString& key, const QVariant& def=QVariant());
	static void setSetting (const QString& key, const QVariant& val);


	static QVector <int> filteredAllys (); 
	static QVector <int> filteredTowns (); 
	static QVector <int> filteredPlayers (); 
	static QVector <int> search (const SearchData & s); 


	static void setTownFilter (int player, int ally);
	static void getTownFilter (int &player, int &ally);
	static void setPlayerFilter (int ally);
	static void getPlayerFilter (int &ally);
	static void setLastSelAlly (int ally);
	static void getLastSelAlly (int &ally);
	static void setLastSelPlayer (int pl);
	static void getLastSelPlayer (int &pl);
	static void setLastSelTown (int pl);
	static void getLastSelTown (int &pl);

	static PlanList& currentMyTownsList ();
	static int currentMyTownsListIndex ();
	static void setCurrentMyTownsListIndex (int i);

	static PlanList& currentTargetList ();
	static int currentTargetListIndex ();
	static void setCurrentTargetListIndex (int i);

	static PlanList& currentPlansList ();
	static int currentPlansListIndex ();
	static void setCurrentPlansListIndex (int i);

private:
	WorldDataPriv *_d;
	static QVariantMap _settings;
	static WorldData _global;
};

Q_DECLARE_METATYPE (WorldData);


#endif

