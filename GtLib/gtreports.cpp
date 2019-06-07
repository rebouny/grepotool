#include <QDebug>
#include "GtReports.h"


QVariantMap BonusData::toVariant () const {
	QVariantMap r;
	for (int i=0;i<BonusMax;++i) 
		if (val[i])
			r[bonusJsonNames[i]] = val[i];
	return r;
};

BonusData BonusData::fromVariant (const QVariantMap & m) {
	BonusData r;
	for (int i=0;i<BonusMax;++i) {
		if (m.contains(bonusJsonNames[i])) {
			r.val[i] = 0;
			QString s = m[bonusJsonNames[i]].toString();
			s = s.simplified ();
			if (s == "true") {
				r.val[i] = 1;
			} else if(s.endsWith ("%")) {
				s.chop (1);
				s = s.simplified ();
				r.val[i] = s.toInt();
			} else {
				r.val[i] = s.toInt();
			}
		}
	}
	return r;
};

QString BonusData::toolTip (BonusIndex b)
{
	switch (b) {
	case BonusCaptain :
		return tr("Captain (+20% power of sea units)");
		break;
	case BonusCommander:
		return tr("Commander (+20% power of land units)");
		break;
	case BonusPriest:
		return tr("Priest (+20% power of mythical units)");
		break;
	case BonusLuck:
		return tr("Luck");
		break;
	case BonusMorale:
		return tr("Morale");
		break;
	case BonusRam:
		return tr("Ram (+10% power of sea units)");
		break;
	case BonusPhalanx:
		return tr("Phalanx (+10% power of land units)");
		break;
	case BonusTower:
		return tr("Tower (+10% defense power of all units)");
		break;
	case BonusWall:
		return tr("Wall");
		break;
	case BonusNight:
		return tr("Nightbonus (+100% defense power of all units)");
		break;
	case BonusHeroStrength:
		return tr("Strength of heroes (+10% attack power of land units)");
		break;
	case BonusFairWind:
		return tr("Fair wind (+10% attack power of sea units)");
		break;
	case BonusDesire:
		return tr("Desire (-10% power of all units)");
		break;
	case BonusTrojanDef:
		return tr("Trojan defense (+10% defense power of all units)");
		break;
	case BonusMyrmidionAtt:
		return tr("Myrmidion attack (+10% attack power of all units)");
		break;
	case BonusLongtermAttBoost:
		return tr("Longterm attack boost (+5% attack power of all units)");
		break;
	case BonusLongtermDefBoost:
		return tr("Longterm defense boost (+5% defense power of all units)");
		break;
	case BonusAttBoost:
		return tr("Attack boost (+X% attack power of all units)");
		break;
	case BonusDefBoost:
		return tr("Defense boost (+X% defense power of all units)");
		break;
	default:
		break;
	}
	return "";
}

double BonusData::landBonusAtt () const
{
	double ret = 1.0;
	//if(BonusCaptain)  {ret *= 1.2;} // 20%
	if(val[BonusCommander]) {ret *= 1.2;} // 20%
	//if(BonusPriest)  {ret *= 1.2;} // 20% 
	{ret *= 1.0 + (double)val[BonusLuck] / 100.0;}
	{ret *= (double)val[BonusMorale] / 100.0;}
	//if(BonusRam) {ret*=1.1;}
	if(val[BonusPhalanx]) {ret*=1.1;}
	//if(BonusTower)  {ret*=1.1;}
	//if(BonusNight) {ret*=2.0;}
	if(val[BonusHeroStrength]) {ret*=1.1;}
	//if(BonusFairWind)  {ret*=1.1;}
	if(val[BonusDesire]) {ret *= 0.9;}
	//if(BonusTrojanDef)  {ret*=1.1;}
	if(val[BonusMyrmidionAtt]) {ret*= 1.1;}
	if(val[BonusLongtermAttBoost]) {ret*= 1.05;}
	//if(BonusLongtermDefBoost) {ret*= 1.05;}
	if(val[BonusAttBoost]) {ret *= 1.0 + (double)val[BonusAttBoost] / 100.0;}
	//if(BonusDefBoost)  {ret *= 1.0 + (double)val[BonusDefBoost] / 100.0;}
	return ret;
}
double BonusData::seaBonusAtt () const
{
	double ret = 1.0;
	if(val[BonusCaptain])  {ret *= 1.2;} // 20%
	//if(BonusCommander) {ret *= 1.2;} // 20%
	//if(BonusPriest)  {ret *= 1.2;} // 20% 
	{ret *= 1.0 + (double)val[BonusLuck] / 100.0;}
	{ret *= (double)val[BonusMorale] / 100.0;}
	if(val[BonusRam]) {ret*=1.1;}
	//if(BonusPhalanx) {ret*=1.1;}
	//if(BonusTower)  {ret*=1.1;}
	//if(BonusNight) {ret*=2.0;}
	//if(BonusHeroStrength) {ret*=1.1;}
	if(val[BonusFairWind])  {ret*=1.1;}
	if(val[BonusDesire]) {ret *= 0.9;}
	//if(BonusTrojanDef)  {ret*=1.1;}
	if(val[BonusMyrmidionAtt]) {ret*= 1.1;}
	if(val[BonusLongtermAttBoost]) {ret*= 1.05;}
	//if(BonusLongtermDefBoost) {ret*= 1.05;}
	if(val[BonusAttBoost]) {ret *= 1.0 + (double)val[BonusAttBoost] / 100.0;}
	//if(BonusDefBoost)  {ret *= 1.0 + (double)val[BonusDefBoost] / 100.0;}
	return ret;
}
double BonusData::seaBonusDef () const
{
	double ret = 1.0;
	if(val[BonusCaptain])  {ret *= 1.2;} // 20%
	//if(BonusCommander) {ret *= 1.2;} // 20%
	//if(BonusPriest)  {ret *= 1.2;} // 20% 
	//{ret *= 1.0 + (double)val[BonusLuck] / 100.0;}
	//{ret *= 1.0 + (double)val[BonusMorale] / 100.0;}
	if(val[BonusRam]) {ret*=1.1;}
	//if(BonusPhalanx) {ret*=1.1;}
	if(val[BonusTower])  {ret*=1.1;}
	if(val[BonusNight]) {ret*=2.0;}
	//if(BonusHeroStrength) {ret*=1.1;}
	//if(BonusFairWind)  {ret*=1.1;}
	//if(BonusDesire) {ret *= 0.9;}
	if(val[BonusTrojanDef])  {ret*=1.1;}
	//if(BonusMyrmidionAtt) {ret*= 1.1;}
	//if(BonusLongtermAttBoost) {ret*= 1.05;}
	if(val[BonusLongtermDefBoost]) {ret*= 1.05;}
	//if(BonusAttBoost) {ret *= 1.0 + (double)val[BonusAttBoost] / 100.0;}
	if(val[BonusDefBoost])  {ret *= 1.0 + (double)val[BonusDefBoost] / 100.0;}
	return ret;
}
double BonusData::landBonusDef () const
{
	double ret = 1.0;
	//if(BonusCaptain)  {ret *= 1.2;} // 20%
	if(val[BonusCommander]) {ret *= 1.2;} // 20%
	//if(BonusPriest)  {ret *= 1.2;} // 20% 
	//{ret *= 1.0 + (double)val[BonusLuck] / 100.0;}
	//{ret *= 1.0 + (double)val[BonusMorale] / 100.0;}
	//if(BonusRam) {ret*=1.1;}
	if(val[BonusPhalanx]) {ret*=1.1;}
	if(val[BonusTower])  {ret*=1.1;}
	if(val[BonusNight]) {ret*=2.0;}
	//if(BonusHeroStrength) {ret*=1.1;}
	//if(BonusFairWind)  {ret*=1.1;}
	//if(BonusDesire) {ret *= 0.9;}
	if(val[BonusTrojanDef])  {ret*=1.1;}
	//if(BonusMyrmidionAtt) {ret*= 1.1;}
	//if(BonusLongtermAttBoost) {ret*= 1.05;}
	if(val[BonusLongtermDefBoost]) {ret*= 1.05;}
	//if(BonusAttBoost) {ret *= 1.0 + (double)val[BonusAttBoost] / 100.0;}
	if(val[BonusDefBoost])  {ret *= 1.0 + (double)val[BonusDefBoost] / 100.0;}
	return ret;
}

// [GrepoTool=2.0;server=de41;language=de_DE;date=21.02.2014 03:02;source=report;desire=true;morale=100;luck=-20;wall=25;wall_loss=0;nightbonus=100;attacker_name=1781926;attacker_town=43727;attacker_units=(bireme:156;);attacker_losses=(bireme:156;);defender_name=1641188;defender_town=37353;defender_units=(big_transporter:1;bireme:346;small_transporter:4;sword:4;archer:2;hoplite:21;);defender_losses=(big_transporter:0;bireme:5;small_transporter:0;sword:0;archer:0;hoplite:0;)]



// [GrepoTool=2.0;server=de41;language=de_DE;date=18.02.2014 22:06;source=report;morale=100;luck=27;wall=22;wall_loss=9;nightbonus=0;attacker_name=1641188;attacker_town=17470;attacker_units=(attack_ship:21;small_transporter:51;slinger:345;catapult:10;);attacker_losses=(attack_ship:0;small_transporter:0;slinger:78;catapult:2;);defender_name=1597320;defender_town=42649;defender_units=(small_transporter:1;archer:4;chariot:3;militia:375;);defender_losses=(small_transporter:1;archer:4;chariot:3;militia:375;)]




bool Report::operator == (const Report&o) const
{
	if (_d == o._d) return true;
	if (!_d && o._d) return false;
	if (_d && !o._d) return false;
	if (type() != o.type()) return false;

	const AttReport * at = dynamic_cast<const AttReport *> (_d);
	const SpyReport * sp = dynamic_cast<const SpyReport *> (_d);
	const WallReport * wa=  dynamic_cast<const WallReport *> (_d);
	const AttReport * oat = dynamic_cast<const AttReport *> (o._d);
	const SpyReport * osp = dynamic_cast<const SpyReport *> (o._d);
	const WallReport * owa=  dynamic_cast<const WallReport *> (o._d);

	if (at && oat) {
		if(at->att_time != oat->att_time) return false;
		if(at->att_town_id != oat->att_town_id) return false;
		if(at->def_town_id != oat->def_town_id) return false;
		return true;
	}
	if (sp&& osp) {
		if(sp->time != osp->time) return false;
		if(sp->town_id != osp->town_id) return false;
		return true;
	}

	if (wa && owa) {
		if(wa->player_id != owa->player_id) return false;
		if(wa->_recv_time != owa->_recv_time) return false;
		return true;
	}

	return false;
}



Report& Report::operator = (const Report&o)
{	
	if (_d == o._d) return *this;
	if (_d && _d->decRef()) delete _d;
	_d = o._d ;
	if (_d) _d->incRef();
	return *this;
}

QVariantMap Report::toVariant () const 
{
	if(!_d) return QVariantMap ();
	if(_d->type() == ReportInvalid ) return QVariantMap ();	 
	return _d->_content;
}

Report Report::fromVariant (const QVariantMap & m) 
{
	QVariantMap nm = m;
	Report r;
	if (m.isEmpty ()) return r;
	if (!m.contains ("GrepoTool")) return r;
	if (!m.contains ("server")) return r;
	if (!m.contains ("source")) return r;	
	QString srv = m["server"].toString();
	QString src = m["source"].toString();

	if (src == "spy") {
		r._d = new SpyReport;				
	} else if (src == "wall") {
		r._d = new WallReport;		
	} else { // we assume an Att report
		r._d = new AttReport;		
	}
	if (! r._d->parseMap (m) ) {
		delete r._d;
		r._d = 0;
	}
	if (!r._d) return r;
	r._d->incRef();
	r._d->_server = srv;
	r._d->_source = src;
	r._d->_recv_time = QDateTime::currentDateTime();
	if (m.contains("receive_time")) r._d->_recv_time = m["receive_time"].value<QDateTime>();
	r._d->_content = m;
	if (m.contains("receive_time")) r._d->_recv_time = r._d->_content["receive_time"].value<QDateTime>();
	else r._d->_content["receive_time"] = r._d->_recv_time;
	r._d->_lang = m["language"].toString();
	if(r._d->_lang.isEmpty ()) r._d->_lang = m["locale_lang"].toString();
	return r;
}

Report::Report (const QString & v):_d(0) 
{
	*this = fromVariant (parseReport (v));
}


// [GrepoTool=1.1;server=de41;language=de_DE;date=heute um 18:13 Uhr;source=spy;player=926285;town=57516;
// units=(sword:2031;archer:1699;hoplite:8861;chariot:645;cerberus:44;big_transporter:17;bireme:746;attack_ship:33;small_transporter:1170;colonize_ship:3;);
// buildings=(main:25;storage:30;hide:10;farm:40;place:1;lumber:40;stoner:40;ironer:40;market:30;docks:21;wall:22;academy:30;temple:21;barracks:30;tower:1;thermal:1;)]
bool SpyReport::parseMap (const QVariantMap & m)
{
	time = m["date"].value<QDateTime> ();
	town_id = m["town"].toInt();
	units = UnitData::fromVariant (m["units"].toMap());
	buildings = BuildingData::fromVariant (m["buildings"].toMap());
	return true;
}

//[GrepoTool=2.0;server=de41;language=de_DE;date=09.03.2013 19:52;source=report;fair_wind=true;luck=14;wall=25;oldwall=-0;attacker_name=1634613;attacker_town=20591;attacker_units=(pegasus:2;);attacker_losses=(pegasus:2;);defender_name=1641188;defender_town=19022;defender_units=(big_transporter:2:0;bireme:205:0;small_transporter:52:0;sword:281:1;slinger:18:0;archer:76:1;hoplite:90:0;chariot:2:0;militia:335:2;);defender_losses=(big_transporter:0;bireme:0;small_transporter:0;sword:1;slinger:0;archer:1;hoplite:0;chariot:0;militia:2;)]



// [GrepoTool=1.1;server=de41;language=de_DE;date=am 01.12.13 um 18:18 Uhr;source=forum;attacker_name=;attacker_town=58012;attacker_units=(harpy:5;);defender_name=743001;defender_town=50892;defender_units=(bireme:926;)]
// [GrepoTool=1.1;server=de41;language=de_DE;date=09.02.2014 20:37;source=report;attacker_name=1641188;attacker_town=17470;attacker_units=(attack_ship:49;small_transporter:69;slinger:902;catapult:13;);defender_name=1663462;defender_town=23805;defender_units=(unit:?;unit:?;)]
// [GrepoTool=1.0;server=de41;locale_lang=de_DE;attacker=.Pete.;attackerTown=M46 Shiny Beach;attack_date=16.11.2013 17:39;units=(attack_ship:1;small_transporter:5;slinger:20;hoplite:10;rider:10;catapult:1;)]
// [GrepoTool=2.0;server=de41;language=de_DE;date=10.02.2014 04:47;source=report;
//  luck=5;wall=21;oldwall=-7;attacker_name=1752628;attacker_town=60331;
// attacker_units=(attack_ship:80;small_transporter:29;slinger:150;hoplite:150;catapult:10;);
// attacker_losses=(attack_ship:0;small_transporter:0;slinger:25;hoplite:42;catapult:2;);
// defender_name=1641188;defender_town=61484;
// defender_units=(big_transporter:9:9;attack_ship:1:1;small_transporter:2:2;sword:4:4;slinger:47:47;archer:2:2;hoplite:7:7;chariot:2:2;);
// defender_losses=(big_transporter:9;attack_ship:1;small_transporter:2;sword:4;slinger:47;archer:2;hoplite:7;chariot:2;)]
bool AttReport::parseMap (const QVariantMap & m)
{

	att_time  = m["date"].value<QDateTime> ();;
	att_town_id = m["attacker_town"].toInt();
	def_town_id = m["defender_town"].toInt();
	att_player_id = -1;
	def_player_id = -1;
	QString s = m["attacker_name"].toString();
	if (!s.isEmpty()) att_player_id = s.toInt();
	else {
		
	}
	s = m["defender_name"].toString();
	if (!s.isEmpty()) def_player_id = s.toInt();
	wall_loss = m["wall_loss"].toInt();
	boni = BonusData::fromVariant (m);
	att_units = UnitData::fromVariant (m["attacker_units"].toMap());
	att_unit_loss = UnitData::fromVariant (m["attacker_losses"].toMap());
	def_units = UnitData::fromVariant (m["defender_units"].toMap());
	def_unit_loss = UnitData::fromVariant (m["defender_losses"].toMap());	
	return true;
}

// [GrepoTool=2.0;server=de41;language=de_DE;source=wall;player=1641188;killed_as_attacker=(militia:18621;sword:35620;slinger:12461;archer:26488;hoplite:29531;rider:3411;chariot:4515;catapult:211;minotaur:12;manticore:3;medusa:16;centaur:11;pegasus:234;cerberus:85;fury:2;godsent:417;big_transporter:647;bireme:18545;attack_ship:2087;demolition_ship:40;small_transporter:3353;trireme:12;colonize_ship:5;sea_monster:13;);killed_as_defender=(sword:14817;slinger:348609;archer:10289;hoplite:191201;rider:69867;chariot:20633;catapult:2485;minotaur:61;manticore:623;zyklop:14;harpy:585;medusa:59;centaur:44;pegasus:106;cerberus:54;fury:176;godsent:2351;big_transporter:2223;bireme:1756;attack_ship:74417;small_transporter:18397;trireme:321;colonize_ship:41;sea_monster:282;);lost_as_attacker=(sword:7727;slinger:190691;archer:3749;hoplite:91779;rider:9180;chariot:254;catapult:2319;manticore:101;pegasus:2;cerberus:6;godsent:36;big_transporter:208;bireme:159;attack_ship:20982;small_transporter:7572;colonize_ship:15;);lost_as_defender=(militia:7561;sword:21217;slinger:1971;archer:11160;hoplite:22956;rider:152;chariot:113;catapult:40;medusa:4;cerberus:10;godsent:8;big_transporter:11;bireme:8206;attack_ship:671;small_transporter:614;colonize_ship:2;)]
// [GrepoTool=1.1;server=de57;language=de_DE;source=wall;player=1781926;
// killed_as_attacker=(militia:195;sword:538;slinger:508;archer:193;hoplite:404;rider:8;godsent:16;big_transporter:4;bireme:108;attack_ship:17;);
// killed_as_defender=(sword:893;slinger:11600;archer:968;hoplite:4612;rider:1583;chariot:42;catapult:77;manticore:8;harpy:7;fury:3;godsent:238;big_transporter:276;bireme:82;attack_ship:1609;small_transporter:286;colonize_ship:1;);
// lost_as_attacker=(sword:86;slinger:2203;archer:100;hoplite:333;rider:445;chariot:57;catapult:4;fury:2;godsent:14;big_transporter:14;attack_ship:113;small_transporter:53;);
// lost_as_defender=(militia:594;sword:219;slinger:40;archer:123;hoplite:108;chariot:31;big_transporter:2;bireme:133;)]
bool WallReport::parseMap (const QVariantMap & m)
{
	player_id = m["player"].toInt();
	killed_as_att = UnitData::fromVariant (m["killed_as_attacker"].toMap());
	killed_as_def = UnitData::fromVariant (m["killed_as_defender"].toMap());
	lost_as_att = UnitData::fromVariant (m["lost_as_attacker"].toMap());
	lost_as_def = UnitData::fromVariant (m["lost_as_defender"].toMap());
	return true;
}





QDateTime Report::guessDate (const QString &s) {
	QDateTime r = QDateTime::fromString (s);
	if (!r.isValid ()) r = QDateTime::fromString (s, ("dd.MM.yyyy hh:mm"));
	if (!r.isValid ()) r = QDateTime::fromString (s, ("dd.MM.yy hh:mm"));
	if (!r.isValid ()) {
		r = QDateTime::fromString (s, tr("'heute um 'hh:mm' Uhr'"));
		if (r.isValid ()) {
			r.setDate (QDate::currentDate());		
		}
	}
	if (!r.isValid ()) r = QDateTime::fromString (s, tr("'am 'dd.MM.yy' um 'hh:mm' Uhr'"));
	if (!r.isValid ()) r = QDateTime::currentDateTime();
	QDate d = r.date();
	int y = d.year();
	if (y < 2000) y+=100;
	d.setDate (y,d.month(),d.day());
	r.setDate(d);
	return r;
}

QVariant Report::parseReportValue (const QString & nam, const QString & s) {
	if (s.isEmpty()) return s;
	if (nam.contains("date")) return guessDate (s);
	if (!s.contains(";")) return s;
	QStringList l = s.split (";",QString::SkipEmptyParts);
	// if (l.size()<2) return s;
	QVariantMap r;
	for (int i=0;i< l.size(); ++i) {
		QStringList ll = l[i].split (":",QString::SkipEmptyParts);
		if (ll.size() >= 2)
			r[ll[0]] = ll[1];

	}
	return r;
};
// [GrepoTool=2.0;server=de41;language=de_DE;date=am 15.02.14 um 18:05 Uhr;source=forum;strength_of_heroes=true;defense_boost=5%;luck=-7;wall=23;wall_loss=0;attacker_name=926285;attacker_town=57516;attacker_units=(rider:213;);attacker_losses=(rider:213;);defender_name=;defender_town=59916;defender_units=(small_transporter:82;sword:158;archer:155;hoplite:700;chariot:91;militia:375;);defender_losses=(small_transporter:0;sword:30;archer:29;hoplite:132;chariot:17;militia:70;)]

// [sword=0;slinger=0;archer=4;hoplite=0;rider=0;chariot=3;catapult=0;centaur=0;cerberus=0;minotaur=0;medusa=0;pegasus=0;manticore=0;fury=0;attack_ship=0;bireme=0;trireme=0;small_transporter=1;big_transporter=0;demolition_ship=0;colonize_ship=0;sea_monster=0;militia=375;godsent=0;]
// [GrepoTool=2.0;server=de41;language=de_DE;source=wall;player=1641188;killed_as_attacker=(militia:18621;sword:35620;slinger:12461;archer:26488;hoplite:29531;rider:3411;chariot:4515;catapult:211;minotaur:12;manticore:3;medusa:16;centaur:11;pegasus:234;cerberus:85;fury:2;godsent:417;big_transporter:647;bireme:18545;attack_ship:2087;demolition_ship:40;small_transporter:3353;trireme:12;colonize_ship:5;sea_monster:13;);killed_as_defender=(sword:14817;slinger:348609;archer:10289;hoplite:191201;rider:69867;chariot:20633;catapult:2485;minotaur:61;manticore:623;zyklop:14;harpy:585;medusa:59;centaur:44;pegasus:106;cerberus:54;fury:176;godsent:2351;big_transporter:2223;bireme:1756;attack_ship:74417;small_transporter:18397;trireme:321;colonize_ship:41;sea_monster:282;);lost_as_attacker=(sword:7727;slinger:190691;archer:3749;hoplite:91779;rider:9180;chariot:254;catapult:2319;manticore:101;pegasus:2;cerberus:6;godsent:36;big_transporter:208;bireme:159;attack_ship:20982;small_transporter:7572;colonize_ship:15;);lost_as_defender=(militia:7561;sword:21217;slinger:1971;archer:11160;hoplite:22956;rider:152;chariot:113;catapult:40;medusa:4;cerberus:10;godsent:8;big_transporter:11;bireme:8206;attack_ship:671;small_transporter:614;colonize_ship:2;)]
// [GrepoTool=2.0;server=de41;language=de_DE;date=am 15.02.14 um 18:05 Uhr;source=forum;strength_of_heroes=true;defense_boost=5%;luck=-7;wall=23;wall_loss=0;attacker_name=926285;attacker_town=57516;attacker_units=(rider:213;);attacker_losses=(rider:213;);defender_name=;defender_town=59916;defender_units=(small_transporter:82;sword:158;archer:155;hoplite:700;chariot:91;militia:375;);defender_losses=(small_transporter:0;sword:30;archer:29;hoplite:132;chariot:17;militia:70;)]
QVariantMap Report::parseReport (const QString & s) 
{
	QVariantMap r;
	if(!s.length()) return r;
	QString nam;
	QString val;
	bool is_name = true;

	int i= 0;
	while (i< s.length()) {
		QChar c = s.at(i);
		if (c=='[') {++i; continue;};
		if (c==']') {
			if(!nam.isEmpty())	
				r[nam] = parseReportValue (nam, val);
			break;
		};

		if (!is_name && c=='(') {
			++i;
			while (i<s.length()){
				c = s.at(i);
				if (c == ')') {
					++i;
					break;
				}
				val += c;
				++i;
			}
			continue;
		};
		if (is_name && c == '=') {
			++i;
			is_name = false;
			// nam = "";
			val = "";
			continue;
		}
		if (!is_name && c == ';') {
			if(!nam.isEmpty()) 
				r[nam] = parseReportValue (nam, val);
			is_name = true;
			nam = "";
			val = "";
			++i; 
			continue;
		}
		if (is_name) {
			nam+=c;
		} else {
			val+=c;
		}
		++i;		
	}	
	// qDebug() << r;
	return r;
}



