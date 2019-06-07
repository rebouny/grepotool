#ifndef ___GT_TOWNS_H
#define ___GT_TOWNS_H
/* 
GtTowns

*/

#include <GtIndexes.h>
#include <GtUnits.h>
#include <GtResearch.h>
#include <GtBuildings.h>
#include <GtHeros.h>
#include <GtReports.h>

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

class EXPORT TownData {
public:
	TownData (int tid = -1):refcount(0),town_id(tid),type(TownTypeUndefined) {};
	
	bool isValid() const {
		if (units.isValid()) return true;
		if (buildings.isValid()) return true;
		if (research.isValid()) return true;
		if (heros.isValid()) return true;
		if (type != TownTypeUndefined) return true;
		if (god != AnyGod) return true;
		return false;
	};

	QVariantMap toVariant () const {
		QVariantMap r;
		r["town"] = town_id;
		r["edited"] = user_edited;
		r["god"] = (int) god;
		r["type"] = (int) type;
		r["units"] = units.toVariant();
		r["buildings"] = buildings.toVariant();;
		r["research"] = research.toVariant();;
		r["heros"] = heros.toVariant();;
		return r;
	};

	static TownData* fromVariant (const QVariantMap & m) {
		TownData *r = new TownData;
		if (!m.contains("town")) return r;
		r->town_id = m["town"].toInt ();
		r->user_edited = m["edited"].toBool();
		r->god = (GodIndex) m["god"].toInt();
		r->type = (TownTypeIndex) m["type"].toInt();
		r->units = UnitData::fromVariant (m["units"].toMap());
		r->buildings = BuildingData::fromVariant (m["buildings"].toMap());
		r->research = ResearchData::fromVariant (m["research"].toMap());
		r->heros = HeroData::fromVariant (m["heros"].toMap());
		return r;
	};

	void incRef () const {++refcount;};
	bool decRef () const {--refcount; return refcount == 0;};
	mutable int   refcount;

	int           town_id;
	bool          user_edited;
	TownTypeIndex type;
	GodIndex      god;
	UnitData      units;
	HeroData      heros;
	ResearchData  research;
	BuildingData  buildings;
};

class EXPORT Town {
	Q_DECLARE_TR_FUNCTIONS(Town);
public:

	enum TownCols {
		TownName,
		TownPoints,
		TownPlayerName,
		TownAllyName,
		TownOcean,
		TownIsland,
		TownSpecial,
		TownUnits,
		TownType,
		TownMax
	};


    Town ():id(-1),points(0),player_id(-1),ally_id(-1),bookmark(false),data(0),type(TownTypeUndefined),ghost(false),conquer(false) {};
	bool isValid() const {return id>=0;};
	Town (const Town &o) : data (0) {*this = o;};
	Town& operator =  (const Town &o);
	~Town () {if (data && data->decRef()) delete data;};

	static int               numColumns        ();
	static int               defaultSortColumn ();
	static Qt::SortOrder     defaultSortOrder  ();	
	static bool              canHideColumn     (int col);
	static QVariant          headerData ( int col, int role);
	QVariant                 itemData   ( int col, int role) const;
	static QStringList       headline   ( const QVector <int> &cols );  
	QStringList              texts      ( const QVector <int> &cols ) const;  
	QStringList              bbCodes    ( const QVector <int> &cols ) const;  
	QString                  labelText  ( int col, int icon_size  ) const;
	static bool              itemCheckable   (int col);
	bool                     itemChecked     (int col) const;
	void                     setItemChecked  (int col, bool c);
	int                      compare (const Town&o, int col) const;
	int                      itemSortIndex (int col) const;

	QPixmap                  unitsPixmap () const;
	QString                  tacticalText () const;
	QString                  tacticalTooltip () const;
	QString                  unitsText () const;
	QString                  unitsTooltip () const;
	QPixmap                  specialPixmap () const;
	QString                  specialText () const;
	QString                  specialTooltip () const;


	void handleReport (const Report& r);

	static void renderTypeSymbol(QPainter* paint, TownTypeIndex type, const QPoint& pos, const double &r);
	void renderTypeSymbol(QPainter* paint, const QPoint& pos, const double &r) const {
		renderTypeSymbol(paint, type, pos, r);
	};

	int unitLevel (UnitIndex u) const  {if (!data) return 0; return data->units.val[u];};
	void setUnitLevel (UnitIndex u, int v) {
		if (!data) {
			data = new TownData(id);
			data->incRef ();
		} 
		data->units.val[u] = v;
		checkData ();
	};

	GodIndex god() const {
		if (data) return data->god;
		return AnyGod;
	};
	void setGod (const GodIndex & d) {
		if (!data) {
			data = new TownData (id);			
		} 
		data->god = d;
		checkData ();
	};

	UnitData units () const {
		if(data) return data->units;
		return UnitData();
	};
	void setUnits (const UnitData & d) {
		if (!data) {
			data = new TownData(id);			
		} 
		data->units = d;
		type = d.tacticalType ();
		checkData ();
	};

	HeroData      heros () const {
		if(data) return data->heros;
		return HeroData ();
	};
	void setHeros (const HeroData & d) {
		if (!data) {
			data = new TownData(id);			
		} 
		data->heros = d;
		checkData ();
	};
	ResearchData  research () const {
		if(data) return data->research;
		return ResearchData ();
	};
	void setResearch(const ResearchData & d) {
		if (!data) {
			data = new TownData(id);
		} 
		data->research = d;
		checkData ();
	};
	BuildingData  buildings () const {
		if(data) return data->buildings;
		return BuildingData ();
	};
	void setBuildings(const BuildingData & d) {
		if (!data) {
			data = new TownData(id);
		} 
		data->buildings = d;
		checkData ();
	};


	int buildingLevel (BuildingIndex u) const  {if (!data) return 0; return data->buildings.val[u];};
	void setBuildingLevel (BuildingIndex u, int v) {
		if (!data) {
			data = new TownData(id);
			data->incRef ();
		} 
		data->buildings.val[u] = v;
		checkData ();
	};
	void checkData () {
		if(!data) return;
		if(!data->isValid()) {
			if (data->decRef()) {
				delete data;
			}
			data = 0;
		}	
	};

	int           id;
	QString       name;
	int           points;
	int           player_id; // id
	int           ally_id;   // id
	int           player_index;
	int           ally_index;  
	QString       player_name; 
	QString       ally_name;   
	int           island; // id
	int           island_index; 
	int           x;
	int           y;
	int           no;// on island;

	QPoint        pos;
	QDateTime     first_obs;
	QDateTime     last_obs;
	QDateTime     last_owner_chg;
	int           last_owner;

	bool          alive;
	int           name_rank;
	int           ally_name_rank;
	int           player_name_rank;

	bool          ghost;
    bool          conquer;

	int           ocean;
	int           special;
	TownTypeIndex type;

	bool          bookmark;
	QList<Report> reports;
	TownData*     data;
};

#endif
