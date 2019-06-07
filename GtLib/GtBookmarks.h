#ifndef ___GT_BOOKMARKS_H
#define ___GT_BOOKMARKS_H
/* 

GtBookmarks

*/

#include <GtIndexes.h>
#include <GtAllys.h>
#include <GtPlayers.h>
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

class EXPORT Bookmark {
	Q_DECLARE_TR_FUNCTIONS(Bookmark);
public:
	enum BmType {
		BmTown,      // 
		BmPlayer,    // 
        BmAlly,
        BmHeat
	};

	enum BmCols {
		BmColor, // color 
		BmName,  // bbcode 
		BmPoints, // 
		BmPlayerName,
		BmAllyName, 
		BmMax
	};

	Bookmark ():type(BmAlly),player(0),ally(0),town(0){}
	Bookmark (Ally * a):type(BmAlly),player(0),ally(a),town(0){};
	Bookmark (Player * a):type(BmPlayer),player(a),ally(0),town(0){};
	Bookmark (Town * a):type(BmTown),player(0),ally(0),town(a){};
	Bookmark (const Bookmark&o) {*this = o;};
	Bookmark& operator =  (const Bookmark&o);

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
	int                      itemSortIndex (int col) const;

	void unBookmark();
	int compare (const Bookmark&o, int col) const;

	BmType  type;
	Player * player;
	Ally   * ally;
	Town   * town;
};



#endif
