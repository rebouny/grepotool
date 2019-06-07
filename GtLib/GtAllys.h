#ifndef ___GT_ALLYS_H
#define ___GT_ALLYS_H
/* 
GtAllys 
*/

#include <GtIndexes.h>
#include <GtCore.h>

#include <QApplication>
#include <QImage>
#include <QIcon>
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


class Bookmark;

class EXPORT Ally {
	Q_DECLARE_TR_FUNCTIONS(Ally);
public:

	enum AllyCols {
		AllyColor,
		AllyName,
		AllyPoints,
		AllyNumPlayers,
		AllyNumTowns,
		AllyDef,
		AllyOff,
		AllyBash,
		AllyMax
	};

	Ally ():id(-1),color(randomColor()), show(false), bookmark(false) ,flags (0) {};
	bool isValid() const {return id>=0;};
	Ally (const Ally &o) {*this = o;};
	Ally& operator = (const Ally &o); 

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

	int                      itemSortIndex (int col) const;

	int compare (const Ally&o, int col) const;

	int           id;
	QString       name;
	int           points;
	int           off;
	int           def;
	int           bash;

	QColor        color;
	bool          show;
	bool          bookmark;
	QVector<int>  naps;
	QVector<int>  bnds;
	uint          flags;

	QVector <int> players; // indexes
	QVector <int> towns;   // indexes
	QDateTime     first_obs;
	QDateTime     last_obs;
	bool          alive;
	QVector <int> oceans;   // indexes

	int           name_rank;

};

#endif