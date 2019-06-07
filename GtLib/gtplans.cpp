#include <GtIndexes.h>
#include "GtWorlddata.h"
#include "GtPlans.h"
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QVariant>
#include <QtCore/QtMath>

Plan & Plan::operator = (const Plan & o)
{
	source_id     = o.source_id;
	target_id     = o.target_id;
	slowest_unit  = o.slowest_unit;
	start_time    = o.start_time;
	arrival_time  = o.arrival_time;
	movement_boost= o.movement_boost;
	atlanta_level = o.atlanta_level;
	fixed_arrival = o.fixed_arrival;
	return *this;
};




void Plan::setupDisplayVals ()
{
	WorldData w = WorldData::currentWorld ();

	int si = -1;
	int ti = -1;

	int src_isl = -1;
	bool land = false;

	QPoint src_pos;
	QPoint tgt_pos;

	if (source_id >=0) {		
		si = w.townIndex (source_id);
	}
	if (target_id >=0) {		
		ti = w.townIndex (target_id);		
	}
	if (si >= 0) {
		Town& to = w.towns()[si];
		src_isl = to.island;
		src_pos = to.pos;
		lighthouse = to.buildingLevel(Lighthouse)>0;
		ResearchData r = to.research();
		cartography = r.val[ResearchCartography];
		meteorology = r.val[ResearchMeteorology];
		source = to.name;
		source_player = to.player_name;
		source_ally = to.ally_name;
		if (!to.alive) {
			source = tr ("%1 does not exist").arg(to.name);
			si = -1;
		}
	} 
	if(si < 0) {
		cartography = false;
		meteorology = false;
		lighthouse = false;
	}

	if (ti >= 0) {
		Town& to = w.towns()[ti];
		target = to.name;
		tgt_pos = to.pos;
		if(to.island == src_isl) land = true;
		target_player = to.player_name;
		target_ally = to.ally_name;
		if (!to.alive) {
			target = tr ("%1 does not exist").arg(to.name);
			ti = -1;
		}
	}

	travel_time = -1;
	travel_time_tx = "--:--:--";
	start = "--.-- --:--:--";
	arrival = "--.-- --:--:--";
	retur = "--.-- --:--:--";

	if (fixed_arrival) {
		arrival = arrival_time.toString ("dd.MM hh:mm:ss");
	} else {
		start = start_time.toString ("dd.MM hh:mm:ss");
	}

	if (si < 0 || ti < 0) return ;

	if (si == ti) return;

	if(isLandUnit(slowest_unit) && !land) return;

	// calculate travel time

	// Kata speed1: 21600 speed2: 10800 speed3: 7200
	double worldspeed = 21600. / w.unit(Kata).build_time;


	QPoint d = src_pos-tgt_pos;
	double dx =d.x();
	double dy =d.y();
    double distance = /*sqrt*/qSqrt (dx*dx + dy*dy);

	double factor = 1.0;
	if (meteorology) { //  land  +10%
		if (isLandUnit(slowest_unit) || isFlyingUnit(slowest_unit))
			factor *= 1.1;
	}
	if (cartography) { //     sea +10%
		if (!isLandUnit(slowest_unit) && !isFlyingUnit(slowest_unit))
			factor *= 1.1;
	}
	if (movement_boost) { //  all  +30% 
		factor *= 1.3;
	}
	if (lighthouse) { //      sea  +15%
		if (!isLandUnit(slowest_unit) && !isFlyingUnit(slowest_unit))
			factor *= 1.15;
	}

	if (atlanta_level) { //   11 .. 30%
		factor *= 1.1 + 0.01 * (double) atlanta_level;
	}

	// preparation time is 15 mins / worldspeed
	double ruest = (15. * 60.) / worldspeed;  // seconds

	double us = 0;
	if (isLandUnit(slowest_unit)) us = w.unit(slowest_unit).landspeed;
	else us = w.unit(slowest_unit).seaspeed;

	// t = d* 50 / us 
	// [s] =  [pixel] 
	//       ------------  
	//         pixel
	//        ------------  
	//         50 * s


	// add the town specials to unit speed
	us *= factor;

	// Unit speed is given in pixels per 50 secs
	travel_time = ruest + (int)distance * 50. / us;

	int k = travel_time;
	int ss = k % 60; // secs
	k /= 60;
	int mm = k % 60; // minutes
	k /= 60;
	int hh = k;  // hours
	travel_time_tx = QString("%1:%2:%3").arg(hh,2,10,QChar('0')).arg(mm,2,10,QChar('0')).arg(ss,2,10,QChar('0'));

	if (fixed_arrival) {
		start_time = QDateTime::fromTime_t (arrival_time.toTime_t() - travel_time);
		start = QDateTime::fromTime_t (arrival_time.toTime_t() - travel_time).toString("dd.MM hh:mm:ss");
		retur = QDateTime::fromTime_t (arrival_time.toTime_t() + travel_time).toString("dd.MM hh:mm:ss");
	} else {
		arrival_time = QDateTime::fromTime_t (start_time.toTime_t() + travel_time);
		arrival = QDateTime::fromTime_t (start_time.toTime_t() + travel_time).toString("dd.MM hh:mm:ss");
		retur = QDateTime::fromTime_t (start_time.toTime_t() + 2 * travel_time).toString("dd.MM hh:mm:ss");
	}
}

int Plan::maxDistanceForTravelTime (int tim) const
{
	WorldData w = WorldData::currentWorld ();

	int si = -1;

	if (source_id >=0) {		
		si = w.townIndex (source_id);
	}
	if (si < 0) return 0;
	Town& to = w.towns()[si];
	if (!to.alive) return 0;
	ResearchData r = to.research();

	// calculate travel time

	// Kata speed1: 21600 speed2: 10800 speed3: 7200
	double worldspeed = 21600. / w.unit(Kata).build_time;

	double factor = 1.0;
	if (r.val[ResearchMeteorology]) { //  land  +10%
		if (isLandUnit(slowest_unit) || isFlyingUnit(slowest_unit))
			factor *= 1.1;
	}
	if (r.val[ResearchCartography]) { //     sea +10%
		if (!isLandUnit(slowest_unit) && !isFlyingUnit(slowest_unit))
			factor *= 1.1;
	}
	if (movement_boost) { //  all  +30% 
		factor *= 1.3;
	}
	if (to.buildingLevel(Lighthouse)>0) { //      sea  +15%
		if (!isLandUnit(slowest_unit) && !isFlyingUnit(slowest_unit))
			factor *= 1.15;
	}

	if (atlanta_level) { //   11 .. 30%
		factor *= 1.1 + 0.01 * (double) atlanta_level;
	}

	// preparation time is 15 mins / worldspeed
	double ruest = (15. * 60.) / worldspeed;  // seconds

	double us = 0;
	if (isLandUnit(slowest_unit)) us = w.unit(slowest_unit).landspeed;
	else us = w.unit(slowest_unit).seaspeed;

	// t = d* 50 / us 
	// [s] =  [pixel] 
	//       ------------  
	//         pixel
	//        ------------  
	//         50 * s


	// add the town specials to unit speed
	us *= factor;

	// Unit speed is given in pixels per 50 secs
	// travel_time = ruest + (int)distance * 50. / us;
	double mxd = (tim - ruest) * (us / 50.);
	if (mxd<0) return 0;
	return mxd;
}

PlanList::PlanList ()
{
	// name = tr("New list");
	color = Qt::white;
	show_on_map = false;
	symbol = 0;
}

PlanList& PlanList::operator = (const PlanList& o)
{
	name = o.name;
	plans = o.plans;
	color = o.color;
	show_on_map = o.show_on_map;
	symbol = o.symbol;
	return *this;
}

void PlanList::store (QDataStream& ds) const
{
	int version = 2;
	ds << version;
	ds << name;
	ds << show_on_map;
	ds << symbol;
	ds << color;
	ds << plans.size ();
	for (int i=0;i< plans.size (); ++i) {
		ds << plans[i].source_id;
		ds << plans[i].target_id;
		ds << (int) plans[i].slowest_unit;
		ds << plans[i].start_time.toTime_t ();
		ds << plans[i].arrival_time.toTime_t ();
		ds << plans[i].atlanta_level;
		ds << plans[i].movement_boost;
		ds << plans[i].fixed_arrival;
	}
}
PlanList PlanList::restore (QDataStream & ds)
{
	PlanList ret;
	int n = 0;
	int version = 0;
	ds >> version;
	if(version < 1) return ret;
	if(version > 2) return ret;
	ds >> ret.name;
	if(version > 1) {
		ds >> ret.show_on_map;
		ds >> ret.symbol;
		ds >> ret.color;
	}

	ds >> n;
	
	for (int i=0;i< n; ++i) {
		Plan pl;
		uint ti;
		ds >> pl.source_id;
		ds >> pl.target_id;
		int su;
		ds >> su; pl.slowest_unit = (UnitIndex) su;
		ds >> ti ; pl.start_time = QDateTime::fromTime_t (ti);
		ds >> ti ; pl.arrival_time = QDateTime::fromTime_t (ti);
		ds >> pl.atlanta_level;
		ds >> pl.movement_boost;
		ds >> pl.fixed_arrival;
		ret.plans.push_back (pl);
	}
	return ret;
}


QVariant Plan::headerData ( int col, int role)
{
	if (role == Qt::DisplayRole) {
		if (col == PlanSource) {              return tr ("Source");
		} else if (col == PlanSourcePlayer) { return tr ("Player"); 
		} else if (col == PlanSourceAlly) {   return tr ("Ally"); 
		} else if (col == PlanTarget) {       return tr ("Target"); 
		} else if (col == PlanTargetPlayer) {  return tr ("Player"); 
		} else if (col == PlanTargetAlly) {   return tr ("Ally"); 
		} else if (col == PlanUnit) {         return tr ("Unit"); 
		} else if (col == PlanSpecials) {  return tr ("Specials"); 
		} else if (col == PlanStart) {   return tr ("Start"); 
		} else if (col == PlanArrival) {  return tr ("Arrival"); 
		} else if (col == PlanReturn) {  return tr ("Return"); 
		} else if (col == PlanTime) {   return tr ("Time"); 
		} 
	} else if ( role == Qt::DecorationRole) {
		if (col == PlanSource) { 
		} else if (col == PlanSourcePlayer) { 
		} else if (col == PlanSourceAlly) { 
		} else if (col == PlanTarget) { 
		} else if (col == PlanTargetPlayer) { 
		} else if (col == PlanTargetAlly) { 
		} else if (col == PlanUnit) { 
		} else if (col == PlanSpecials) { 
		} else if (col == PlanStart) { 
		} else if (col == PlanArrival) { 
		} else if (col == PlanReturn) {  
		} else if (col == PlanTime) { 
		} 
	} else if ( role == Qt::ToolTipRole) {
		if (col == PlanSource) {              return tr ("Source town");
		} else if (col == PlanSourcePlayer) { return tr ("Owner of source town"); 
		} else if (col == PlanSourceAlly) {   return tr ("Ally of source town"); 
		} else if (col == PlanTarget) {       return tr ("Target town"); 
		} else if (col == PlanTargetPlayer) {  return tr ("Owner of target town"); 
		} else if (col == PlanTargetAlly) {   return tr ("Ally of target"); 
		} else if (col == PlanUnit) {         return tr ("Slowest unit"); 
		} else if (col == PlanSpecials) {  return tr ("Special conditions"); 
		} else if (col == PlanStart) {   return tr ("Starttime"); 
		} else if (col == PlanArrival) {  return tr ("Arrivaltime"); 
		} else if (col == PlanReturn) {  return tr("Return tine");
		} else if (col == PlanTime) {   return tr ("Traveltime"); 
		} 
	}

	return QVariant ();
}

QVariant Plan::itemData   ( int col, int role) const
{
	if (role == Qt::DisplayRole) {          
		if (col == PlanSource) {              return source;
		} else if (col == PlanSourcePlayer) { return source_player;
		} else if (col == PlanSourceAlly) {   return source_ally;
		} else if (col == PlanTarget) {       return target;
		} else if (col == PlanTargetPlayer) { return target_player; 
		} else if (col == PlanTargetAlly) {   return target_ally;
		} else if (col == PlanUnit) {         return Unit::unitName (slowest_unit,false);
		} else if (col == PlanSpecials) {     return createSpecialPixmap (18, movement_boost, lighthouse, meteorology, cartography, atlanta_level) ;
		} else if (col == PlanStart) {        return start;
		} else if (col == PlanArrival) {      return arrival; 
		} else if (col == PlanReturn) {       return retur;  
		} else if (col == PlanTime) {         return travel_time_tx;
		} 
	} else if ( role == Qt::DecorationRole) {
		if (col == PlanSource) {              
		} else if (col == PlanSourcePlayer) { 
		} else if (col == PlanSourceAlly) { 
		} else if (col == PlanTarget) { 
		} else if (col == PlanTargetPlayer) { 
		} else if (col == PlanTargetAlly) { 
		} else if (col == PlanUnit) {        return QPixmap (Unit::unitIconFile(slowest_unit)).scaled(QSize(16,16));
		} else if (col == PlanSpecials) { 
		} else if (col == PlanStart) { 
		} else if (col == PlanArrival) { 
		} else if (col == PlanTime) { 
		} 
	} else if ( role == Qt::ToolTipRole) {
		if (col == PlanSource) {              
		} else if (col == PlanSourcePlayer) { 
		} else if (col == PlanSourceAlly) { 
		} else if (col == PlanTarget) { 
		} else if (col == PlanTargetPlayer) { 
		} else if (col == PlanTargetAlly) { 
		} else if (col == PlanUnit) { 
		} else if (col == PlanSpecials) { 
		} else if (col == PlanStart) { 
		} else if (col == PlanArrival) { 
		} else if (col == PlanTime) { 
		} 
		return headerData (col,role);
	} else if ( role == Qt::TextAlignmentRole) {
		if (col == PlanSource) {              
		} else if (col == PlanSourcePlayer) { 
		} else if (col == PlanSourceAlly) { 
		} else if (col == PlanTarget) { 
		} else if (col == PlanTargetPlayer) { 
		} else if (col == PlanTargetAlly) { 
		} else if (col == PlanUnit) { 
		} else if (col == PlanSpecials) { 
		} else if (col == PlanStart) { 
		} else if (col == PlanArrival) { 
		} else if (col == PlanTime) { 
		} 
	}
	return QVariant ();
}



QStringList Plan::headline   ( const QVector <int> &cols ) 
{
	QStringList r;
	for(int i=0;i< cols.size(); ++i) {
		r.push_back (headerData (cols[i],Qt::DisplayRole).toString());
	}
	return r;
}

QStringList Plan::texts      ( const QVector <int> &cols ) const
{
	QStringList r;
	for(int i=0;i< cols.size(); ++i) {
		r.push_back (itemData(cols[i],Qt::DisplayRole).toString());
	}
	return r;
}

QStringList Plan::bbCodes    ( const QVector <int> &cols ) const  
{
	QStringList r = texts (cols);
	for(int i=0;i< cols.size(); ++i) {
		if (cols[i] == PlanSource) {              
			if (source_id>=0) r[i] = bbCode (QString::number(source_id),"town");
		} else if (cols[i] == PlanSourcePlayer) { 
			r[i] = bbCode (r[i],"player");
		} else if (cols[i] == PlanSourceAlly) { 
			r[i] = bbCode (r[i],"ally");
		} else if (cols[i] == PlanTarget) { 
			if (target_id>=0) r[i] = bbCode (QString::number(target_id),"town");
		} else if (cols[i] == PlanTargetPlayer) { 
			r[i] = bbCode (r[i],"player");
		} else if (cols[i] == PlanTargetAlly) { 
			r[i] = bbCode (r[i],"ally");
		} else if (cols[i] == PlanUnit) { 
		} else if (cols[i] == PlanSpecials) { 
		}
	}
	return r;
}



QString Plan::labelText  ( int col, int icon_size  ) const
{
	if (col == PlanSource) {              
	} else if (col == PlanSourcePlayer) { 
	} else if (col == PlanSourceAlly) { 
	} else if (col == PlanTarget) { 
	} else if (col == PlanTargetPlayer) { 
	} else if (col == PlanTargetAlly) { 
	} else if (col == PlanUnit) { 
	} else if (col == PlanSpecials) { 
	} else if (col == PlanStart) { 
	} else if (col == PlanArrival) { 
	} else if (col == PlanTime) { 
	} 

	return "";
}


QPixmap Plan::createSpecialPixmap (int si, bool mb, bool lh, bool me, bool ca, int at) 
{
	int w = 0;
	if (mb) w+= si;
	if (lh) w+= si;
	if (me) w+= si;
	if (ca) w+= si;
	if (at) w+= si;
	if(!w) return QPixmap();
	QImage r(QSize(w,si),QImage::Format_ARGB32_Premultiplied);
	QPainter p(&r);
	w = 0;
	if (mb) {
		p.drawPixmap (QPoint(w,0),QPixmap (":/icons/spells/movement_boost.gif").scaled(QSize(si,si)));
		w+=si;
	}
	if (lh) {
		p.drawPixmap (QPoint(w,0),QPixmap (":/icons/buildings/lighthouse.png").scaled(QSize(si,si)));
		w+=si;
	}
	if (ca) {
		p.drawPixmap (QPoint(w,0),QPixmap (":/icons/research/cartography.png").scaled(QSize(si,si)));
		w+=si;
	}
	if (me) {
		p.drawPixmap (QPoint(w,0),QPixmap (":/icons/research/meteorology.png").scaled(QSize(si,si)));
		w+=si;
	}
	if (at) {
		p.drawPixmap (QPoint(w,0),QPixmap (":/icons/heroes/atlanta.png").scaled(QSize(si,si)));
		w+=si;
	}
	return QPixmap::fromImage (r);
}


int Plan::compare (const Plan&o, int col) const
{
	if (col == PlanSource) {              return source.compare(o.source, Qt::CaseInsensitive);
	} else if (col == PlanSourcePlayer) { return source_player.compare(o.source_player, Qt::CaseInsensitive);;
	} else if (col == PlanSourceAlly) {   return source_ally.compare(o.source_ally, Qt::CaseInsensitive);;
	} else if (col == PlanTarget) {       return target.compare(o.target, Qt::CaseInsensitive);;
	} else if (col == PlanTargetPlayer) { return target_player.compare(o.target_player, Qt::CaseInsensitive);;
	} else if (col == PlanTargetAlly) {   return target_ally.compare(o.target_ally, Qt::CaseInsensitive);;
	} else if (col == PlanUnit) {         return slowest_unit-o.slowest_unit;
	} else if (col == PlanSpecials) {     
	} else if (col == PlanStart) {        return (int) start_time.toTime_t() - (int)o.start_time.toTime_t();
	} else if (col == PlanArrival) {      return (int) arrival_time.toTime_t() - (int)o.arrival_time.toTime_t();; 
	} else if (col == PlanTime) {         return travel_time - o.travel_time;
	} else if (col == PlanReturn) {       
		return (int) arrival_time.toTime_t()+travel_time - ((int)o.arrival_time.toTime_t()+o.travel_time); 
	} 
	return 0;
}

