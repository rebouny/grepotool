#ifndef ___GT_PLANS_H
#define ___GT_PLANS_H
/* 
GtPlans
*/

#include <GtIndexes.h>
#include <GtTowns.h>

#include <QApplication>
#include <QImage>
#include <QColor>
#include <QDateTime>

#ifdef EXPORT 
# undef EXPORT
#endif
#ifdef BUILDING_GTLIB
# define EXPORT DLL_EXPORT
#else
# define EXPORT DLL_IMPORT
#endif



enum PlanCol {
	PlanSource,
	PlanSourcePlayer,
	PlanSourceAlly,
	PlanTarget,
	PlanTargetPlayer,
	PlanTargetAlly,
	PlanUnit,
	PlanSpecials,
	PlanStart,
	PlanArrival,
	PlanReturn,
	PlanTime,
	PlanMax
};


class EXPORT Plan {
	Q_DECLARE_TR_FUNCTIONS(Plan)
public:
	Plan () : source_id(-1),target_id(-1),
		slowest_unit(Attackship),
		start_time(QDateTime::currentDateTime()),
		arrival_time(QDateTime::currentDateTime()),
		atlanta_level(0),movement_boost(false),fixed_arrival(false) {};
	Plan (int src, int tgt, UnitIndex u = Attackship) : source_id(src),target_id(tgt),
		slowest_unit(u),
		start_time(QDateTime::currentDateTime()),
		arrival_time(QDateTime::currentDateTime()),
		atlanta_level(0),movement_boost(false),fixed_arrival(false)
	{};
	Plan (const Plan & o) {*this = o;};
	Plan & operator = (const Plan & o);
	void setupDisplayVals ();
		
	static QVariant          headerData ( int col, int role);
	QVariant                 itemData   ( int col, int role) const;
	static QStringList       headline   ( const QVector <int> &cols );  
	QStringList              texts      ( const QVector <int> &cols ) const;  
	QStringList              bbCodes    ( const QVector <int> &cols ) const;  
	QString                  labelText  ( int col, int icon_size  ) const;
	int compare (const Plan&o, int col) const;
	int                      itemSortIndex (int col) const;

	static QPixmap createSpecialPixmap (int si, bool movement_boost, bool lhouse, bool meteo, bool carto, int atlanta) ;

	void setFixedArrivalTime (const QDateTime & tim) {arrival_time = tim; fixed_arrival = true;};;
	void setFixedStartTime (const QDateTime & tim) {start_time = tim; fixed_arrival = false;};

	int maxDistanceForTravelTime (int tim) const;

	// Plan data
	int       source_id;
	int       target_id;
	UnitIndex slowest_unit;
	QDateTime start_time;
	QDateTime arrival_time;
	int       atlanta_level;
	bool      movement_boost;
	bool      fixed_arrival;

	// runtime display vals 

	bool lighthouse;
	bool cartography;
	bool meteorology;
	QString source;
	QString source_player;
	QString source_ally;
	QString target;
	QString target_player;
	QString target_ally;
	QString start;
	QString arrival;
	QString retur;
	QString travel_time_tx;
	int travel_time;
};


class EXPORT PlanList {
public:
	PlanList (); 
	PlanList (const PlanList& o) {*this = o;}; 
	PlanList& operator = (const PlanList& o); 

	void store (QDataStream& ds) const;
	static PlanList restore (QDataStream & ds);

	void setupDisplayData () { for (int i=0;i< plans.size();++i) plans[i].setupDisplayVals(); };

	QString       name;
	QVector<Plan> plans;

	bool   show_on_map;
	QColor color;
	int    symbol;
};

#endif