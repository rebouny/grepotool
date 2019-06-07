
#include <QStringList>
#include <QFile>
#include <QPixmap>
#include <QIcon>
#include <QByteArray>
#include <QVariantMap>
#include "GtWorlddata.h"
#include "GtPlayers.h"


Player& Player::operator =  (const Player &o)
{
	id= o.id;
	name=o.name;
	ally_id=o.ally_id;
	ally_index=o.ally_index;
	ally_name=o.ally_name;
	points=o.points;
	off=o.off;
	def=o.def;
	off1=o.off1;
	def1=o.def1;
	off3=o.off3;
	def3=o.def3;
	off7=o.off7;
	def7=o.def7;
	bash=o.bash;
	towns=o.towns;
	points_act=o.points_act;
	off_act=o.off_act;
	def_act=o.def_act;
	act=o.act;
	first_obs=o.first_obs;
	last_obs=o.last_obs;
	alive=o.alive;
	bookmark = o.bookmark;
	name_rank= o.name_rank;
	ally_name_rank= o.ally_name_rank;
	premium = o.premium;
	flags = o.flags;
	color = o.color;
	show = o.show;
	reports = o.reports;
	oceans = o.oceans;

	return *this;
};

int               Player::numColumns        (){return PlayerMax;};
int               Player::defaultSortColumn (){return PlayerPoints;};
Qt::SortOrder     Player::defaultSortOrder  (){return Qt::DescendingOrder;};	
bool              Player::canHideColumn     (int col){return col>1;};
QVariant          Player::headerData ( int col, int role)
{
	if (role == Qt::DisplayRole) {
		if(col == PlayerColor) {              return tr("Color");
		} else if (col == PlayerName) {       return tr("Name");
		} else if (col == PlayerPoints) {     return tr("Points");
		} else if (col == PlayerAllyName) {  return tr("Ally");
		} else if (col == PlayerNumTowns) {  return tr("Towns");
		} else if (col == PlayerDef) { return tr("Def");
		} else if (col == PlayerOff) { return tr("Off");
		} else if (col == PlayerBash) {  return tr("Total");
		} else if (col == PlayerDefAct) {  return tr("Def activity");
		} else if (col == PlayerOffAct) { return tr("Off activity");
		} else if (col == PlayerPointsAct) {  return tr("Points activity");
		} else if (col == PlayerAct) { return tr("Activity");
		}
	} else if (role == Qt::DecorationRole) {
		if(col == PlayerColor) {return QIcon(":/icons/icons/color.ico") ;
		} else if (col == PlayerName) { return QIcon(":/icons/icons/.ico") ;
		} else if (col == PlayerPoints) { return QIcon(":/icons/icons/.ico") ;
		} else if (col == PlayerAllyName) { return QIcon(":/icons/icons/ally.ico") ;
		} else if (col == PlayerNumTowns) { return QIcon(":/icons/icons/town.ico") ;
		} else if (col == PlayerDef) { return QIcon(":/icons/icons/shield.ico") ;
		} else if (col == PlayerOff) { return QIcon(":/icons/icons/sword.ico") ;
		} else if (col == PlayerBash) { return QIcon(":/icons/icons/swords.ico") ;
		} else if (col == PlayerDefAct) { return QIcon(":/icons/icons/sjield_activity.ico") ;
		} else if (col == PlayerOffAct) { return QIcon(":/icons/icons/sword_activity.ico") ;
		} else if (col == PlayerPointsAct) { return QIcon(":/icons/icons/player_activity.ico") ;
		} else if (col == PlayerAct) { return QIcon(":/icons/icons/activity.ico") ;
		}

	} else if (role == Qt::ToolTipRole) {
		if(col == PlayerColor) {              return tr("Player color");
		} else if (col == PlayerName) {       return tr("Player name");
		} else if (col == PlayerPoints) {     return tr("Player points");
		} else if (col == PlayerAllyName) {  return tr("Ally");
		} else if (col == PlayerNumTowns) {  return tr("Number of towns");
		} else if (col == PlayerDef) { return tr("Defense bashpoints");
		} else if (col == PlayerOff) { return tr("Attack bashpoints");
		} else if (col == PlayerBash) {  return tr("Total bashpoints");
		} else if (col == PlayerDefAct) {  return tr("Last defense activity");
		} else if (col == PlayerOffAct) { return tr("Last attack activity");
		} else if (col == PlayerPointsAct) {  return tr("Last points activity");
		} else if (col == PlayerAct) { return tr("Overall activity (att+def)");
		}
	}
	return QVariant();
}
QVariant          Player::itemData   ( int col, int role) const
{
	if (role == Qt::DisplayRole) {
		if(col == PlayerColor) {              return color;
		} else if (col == PlayerName) {       return name;
		} else if (col == PlayerPoints) {     return QString::number(points);
		} else if (col == PlayerAllyName) {     return ally_name;
		} else if (col == PlayerNumTowns) {     return QString::number(towns.size());
		} else if (col == PlayerDef) {   return QString::number(def);
		} else if (col == PlayerOff) {     return QString::number(off);
		} else if (col == PlayerBash) {  return QString::number(bash);
		} else if (col == PlayerDefAct) {   return WorldData::activityText(def_act);
		} else if (col == PlayerOffAct) {   return WorldData::activityText(off_act);
		} else if (col == PlayerPointsAct) {   return WorldData::activityText(points_act);
		} else if (col == PlayerAct) {   return WorldData::activityText(act);
		}
	} else if (role == Qt::DecorationRole) {
	} else if (role == Qt::ToolTipRole) {

		return headerData (col,role);

	} else if (role == Qt::TextAlignmentRole) {
		if(col == PlayerColor) {
		} else if (col == PlayerName) {return Qt::AlignLeft;
		} else if (col == PlayerPoints) {return Qt::AlignRight;
		} else if (col == PlayerAllyName) {return Qt::AlignLeft;
		} else if (col == PlayerNumTowns) {return Qt::AlignRight;
		} else if (col == PlayerDef) {return Qt::AlignRight;
		} else if (col == PlayerOff) {return Qt::AlignRight;
		} else if (col == PlayerBash) {return Qt::AlignRight;
		} else if (col == PlayerDefAct) {return Qt::AlignLeft;
		} else if (col == PlayerOffAct) {return Qt::AlignLeft;
		} else if (col == PlayerPointsAct) {return Qt::AlignLeft;
		} else if (col == PlayerAct) {return Qt::AlignLeft;
		}
	} else if (role == Qt::CheckStateRole) {
		if ( col == PlayerColor)
			return (show)? Qt::Checked : Qt::Unchecked;
	}
	return QVariant();
}
QStringList       Player::headline   ( const QVector <int> &cols )  
{
	QStringList r;
	for (int i=0;i< cols.size(); ++i) {
		r.push_back (headerData (cols[i], Qt::DisplayRole).toString());
	}
	return r;
}
QStringList  Player::texts      ( const QVector <int> &cols ) const  
{
	QStringList r;
	for (int i=0;i< cols.size(); ++i) {
		if (cols[i] == PlayerColor) {	
			r.push_back (color.name());
		} else {		
			r.push_back (itemData (cols[i], Qt::DisplayRole).toString());
		}
	}
	return r;
}
QStringList Player::bbCodes    ( const QVector <int> &cols ) const  
{
	QStringList r;
	for (int i=0;i< cols.size(); ++i) {
		QString s = itemData (cols[i], Qt::DisplayRole).toString();
		if (cols[i] == PlayerColor) {	
			s= color.name();
		} else if (cols[i] == PlayerName) {	
			s = bbCode (name,"player");
		} else if (cols[i] == PlayerAllyName) {	
			if(ally_index >=0)
				s = bbCode (ally_name,"ally");
		}
		r.push_back (s);
	}
	return r;
}
QString Player::labelText  ( int col, int icon_size  ) const
{
	if(col == PlayerColor) {
		return QString("<img src=':/icons/icons/color.ico' width=%1 height=%2>&nbsp;<b>#%3</b>")
			.arg(icon_size).arg(icon_size).arg(color.name());
	} else if (col == PlayerName) {
		return QString("<img src=':/icons/icons/player.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(name);
	} else if (col == PlayerPoints) {
		return QString("<img src=':/icons/icons/points.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(QString::number(points));
	} else if (col == PlayerAllyName) {
		return QString("<img src=':/icons/icons/ally.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(ally_name);
	} else if (col == PlayerNumTowns) {
		return QString("<img src=':/icons/icons/towns.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(QString::number(towns.size()));
	} else if (col == PlayerDef) {
		return QString("<img src=':/icons/icons/shield.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(QString::number(def));
	} else if (col == PlayerOff) {
		return QString("<img src=':/icons/icons/sword.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(QString::number(off));
	} else if (col == PlayerBash) {
		return QString("<img src=':/icons/icons/swords.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(QString::number(bash));
	} else if (col == PlayerPointsAct) {
		return QString("<img src=':/icons/icons/player_activity.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(WorldData::activityText(def_act));
	} else if (col == PlayerDefAct) {
		return QString("<img src=':/icons/icons/shield_activity.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(WorldData::activityText(def_act));
	} else if (col == PlayerOffAct) {
		return QString("<img src=':/icons/icons/sword_activity.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(WorldData::activityText(off_act));
	} else if (col == PlayerAct) {
		return QString("<img src=':/icons/icons/activity.ico' width=%1 height=%2>&nbsp;<b>%3</b>")
			.arg(icon_size).arg(icon_size).arg(WorldData::activityText(act));
	}

	return QString();
}
bool Player::itemCheckable   (int col) {return (col == PlayerColor);}
bool Player::itemChecked     (int col) const
{
	if(col == PlayerColor) return show;
	return false;
}
void  Player::setItemChecked  (int col, bool c)
{
	if(col == PlayerColor) show = c;
}
int Player::compare (const Player&o, int col) const
{
	if(col == PlayerColor) {
	} else if (col == PlayerName) {
		return name_rank - o.name_rank;
	} else if (col == PlayerPoints) {
		return points - o.points;
	} else if (col == PlayerAllyName) {
		return ally_name_rank - o.ally_name_rank;
	} else if (col == PlayerNumTowns) {
		return towns.size() - o.towns.size();
	} else if (col == PlayerDef) {
		return def - o.def;
	} else if (col == PlayerOff) {
		return off - o.off;
	} else if (col == PlayerBash) {
		return bash-o.bash;
	} else if (col == PlayerDefAct) {
		return (int) def_act.toTime_t () - (int) o.def_act.toTime_t ();
	} else if (col == PlayerOffAct) {
		return (int) off_act.toTime_t () - (int) o.off_act.toTime_t ();
	} else if (col == PlayerPointsAct) {
		return (int) points_act.toTime_t () - (int) o.points_act.toTime_t ();
	} else if (col == PlayerAct) {
		return (int) act.toTime_t () - (int) o.act.toTime_t ();
	}
	return 0;
}

int Player::itemSortIndex (int col) const
{
	if(col == PlayerColor) {
		return 0;
	} else if (col == PlayerName) {
		return name_rank;
	} else if (col == PlayerPoints) {
		return points;
	} else if (col == PlayerAllyName) {
		return ally_name_rank;
	} else if (col == PlayerNumTowns) {
		return towns.size();
	} else if (col == PlayerDef) {
		return def ;
	} else if (col == PlayerOff) {
		return off ;
	} else if (col == PlayerBash) {
		return bash;
	} else if (col == PlayerDefAct) {
		return (int) def_act.toTime_t () ;
	} else if (col == PlayerOffAct) {
		return (int) off_act.toTime_t () ;
	} else if (col == PlayerPointsAct) {
		return (int) points_act.toTime_t ();
	} else if (col == PlayerAct) {
		return (int) act.toTime_t ();
	}
	return 0;
}

void Player::handleReport (const Report&)
{
}
