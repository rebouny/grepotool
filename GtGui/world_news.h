#ifndef ___WORLD_NEWS_H
#define ___WORLD_NEWS_H

#include <GtWorlddata.h>
#include "toolwidget.h"
// #include "ui_world_news.h"

#include <QToolButton>
#include <QSpinBox>
#include <QTextBrowser>

/*
World News:

World info: 

Players total dead new in the last day 
Allys   total dead new in the last day 
Towns  
Ghosts   

Conquers in the last day/week

Bash ranking 1/2/7 days
att / deff / total:  
Player aaa +xx points
*/


/* 

[player id=1234]XYZ[/player]
==> 

*/
static QString playerLink (const QString & player, int id) {
	return QString ("<a href='player:%2'><img src='qrc:/icons/icons/player.ico' width=16 height=16 ><b>%1</b></a>").arg(player).arg(id);
};

static QString allyLink (const QString & ally, int id) {
	return QString ("<a href='ally:%2'><img src='qrc:/icons/icons/ally.ico' width=16 height=16><b>%1</b></a>").arg(ally).arg(id);
};

static QString townLink (const QString & town,  int id) {
	return QString ("<a href='town:%2'><img src='qrc:/icons/icons/town.ico' width=16 height=16><b>%1</b></a>").arg(town).arg(id);
};

static QString ghostLink (const QString & town,  int id) {
	return QString ("<a href='town:%2'><img src='qrc:/icons/icons/ghost.ico' width=16 height=16><b>%1</b></a>").arg(town).arg(id);
};

static QString pointsBBCode ( int n ) {
	return QString ("<img src='qrc:/icons/icons/points.ico' width=16 height=16><b>%1</b></a>").arg(n);
};

static QString offBBCode ( int n ) {
	return QString ("<img src='qrc:/icons/icons/sword.ico' width=16 height=16>%1</a>").arg(n);
};

static QString deffBBCode ( int n ) {
	return QString ("<img src='qrc:/icons/icons/shield.ico' width=16 height=16>%1</a>").arg(n);
};

static QString bashBBCode ( int n ) {
	return QString ("<img src='qrc:/icons/icons/swords.ico' width=16 height=16>%1</a>").arg(n);
};
/*
   Player1 Ally1 :
    xx.xx.yyy hh:mm - conquered town x from player xy 
    xx.xx.yyy hh:mm - conquered town y ghost town 
    xx.xx.yyy hh:mm - funded town y 
   Player2 Ally1 :
    xx.xx.yyy hh:mm - conquered town x from player xy 

	Ghosts:
		Player abc Ally has pressed restart on xx.yy.yyyy (xx ghosts remaining)
		Player abc2 ally has left the game on xx.yy.yyyy (xx ghosts remaining)


   daily bash ranking        3 day bash ranking   weekly bash ranking 
     Player 1 xxx points    Player 1 xxx points



*/
class NewsViewer : public ToolWidget {
	Q_OBJECT;
public:
	NewsViewer ();
	void worldChanged ();
	QString head ();

public slots:
	void handleAnchorClick (const QUrl& s);
	void worldSummary ();
	void latestConquers ();
	void latestNewTowns ();
	void latestOffBashies ();
	void latestDefBashies ();
	void latestAllyChanges ();
	void latestGhosts ();

	void setTown (int idx);
	void setPlayer (int idx);
	void setAlly (int idx);
signals:
	void playerClickSignal (int);
	void allyClickSignal (int);
	void townClickSignal (int);
	void externalLinkSignal (const QString& );
private:
	QTextBrowser * _text;
	
};

#endif