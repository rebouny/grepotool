#ifndef ___GT_PLAYERS_H
#define ___GT_PLAYERS_H
/* 
GtPlayers
*/

#include <GtIndexes.h>
#include <GtCore.h>
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


class EXPORT Player {
	Q_DECLARE_TR_FUNCTIONS(Player);
public:

	enum PlayerCols {
		PlayerColor,
		PlayerName,
		PlayerPoints,
		PlayerAllyName,
		PlayerNumTowns,
		PlayerDef,
		PlayerOff,
		PlayerBash,
		PlayerDefAct,
		PlayerOffAct,
		PlayerPointsAct,
		PlayerAct,
		PlayerMax
	};

	Player ():id(-1),ally_id(-1),points(0),off(0),def(0),bash(0),color(randomColor()),
		show(false),bookmark(false),flags(0),premium(0),alive(false){};
	bool isValid() const {return id>=0;};

	Player (const Player &o) {*this = o;};
	Player& operator =  (const Player &o);
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
	int                      compare (const Player&o, int col) const;
	int                      itemSortIndex (int col) const;


	void handleReport (const Report& r);


	int           id;
	QString       name;
	int           ally_id;  // id
	QString       ally_name;
	int           points;
	int           off;
	int           def;
	int           bash;

	QColor        color;
	bool          show;
	bool          bookmark;  // index
	int           flags; // index
	int           premium; // index

	QVector <int> towns;
	int           ally_index;

	QDateTime     points_act;
	QDateTime     off_act;
	QDateTime     def_act;
	QDateTime     act;

	QDateTime     first_obs;
	QDateTime     last_obs;
	bool          alive;

	int           off1;
	int           off3;
	int           off7;
	int           def1;
	int           def3;
	int           def7;
	int           name_rank;
	int           ally_name_rank;
	QVector <int> oceans;   // indexes

	QVector <Report> reports;
};


#endif