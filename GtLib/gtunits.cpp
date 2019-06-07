
#include <QStringList>
#include <QFile>
#include <QByteArray>
#include <QVariantMap>
#include "GtUnits.h"
#include "GtBoni.h"
#include "GtWorlddata.h"



Unit & Unit::operator = (const Unit& o)
{
	type =o.type;
	build_time = o.build_time;
	seaspeed = o.seaspeed;
	landspeed= o.landspeed;
	attack= o.attack;
	attack_type= o.attack_type;
	defence[0] = o.defence[0];
	defence[1] = o.defence[1];
	defence[2] = o.defence[2];
	defence[3] = o.defence[3];
	name = o.name;
	name_pl = o.name_pl;
	image = o.image;
	desc = o.desc;
	return *this;
}

Unit Unit::extractData (const QVariant & u, UnitIndex i)
{
	QVariantMap m = u.toMap();

	QVariantMap info;

	Unit ui;
	ui.type          = i;
	ui.build_time    = 0.;
	ui.seaspeed       = 0.;
	ui.landspeed      = 0.;
	ui.attack         = 0;
	ui.attack_type    = Hack;
	ui.defence[Hack]     = 0;
	ui.defence[Pierce]   = 0;
	ui.defence[Distance] = 0;
	ui.defence[Naval]    = 0;
	ui.name           = "";
	ui.name_pl        = "";
	ui.desc           = "";

	switch (i) {
		case Militia:
			info = m["militia"].toMap();
			ui.image = QImage(":/icons/units/militia.png");
			ui.attack_type    = Pierce;
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();			
			break;
		case Sword:
			info = m["sword"].toMap();
			ui.attack_type    = Hack;
			ui.image = QImage(":/icons/units/sword.png");
			ui.attack         = info["attack"].toInt();;
			ui.landspeed      = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		case Slinger:
			info = m["slinger"].toMap();
			ui.attack_type    = Distance;
			ui.image = QImage(":/icons/units/slinger.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		case Archer:
			info = m["archer"].toMap();
			ui.attack_type    = Distance;
			ui.image = QImage(":/icons/units/archer.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		case Hoplite:
			info = m["hoplite"].toMap();
			ui.attack_type    = Pierce;
			ui.image = QImage(":/icons/units/hoplite.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		case Rider:
			info = m["rider"].toMap();
			ui.attack_type    = Hack;
			ui.image = QImage(":/icons/units/rider.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		case Chariot:
			info = m["chariot"].toMap();
			ui.attack_type    = Pierce;
			ui.image = QImage(":/icons/units/chariot.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();

			break;
		case Kata:
			info = m["catapult"].toMap();
			ui.attack_type    = Distance;
			ui.image = QImage(":/icons/units/catapult.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		case Transporter:
			info = m["big_transporter"].toMap();
			ui.attack_type    = Naval;
			ui.image = QImage(":/icons/units/big_transporter.png");
			ui.seaspeed        = info["speed"].toDouble ();
			ui.defence[Naval]    = info["defense"].toInt();
			break;
		case Bireme:
			info = m["bireme"].toMap();
			ui.attack_type    = Naval;
			ui.image = QImage(":/icons/units/bireme.png");
			ui.seaspeed        = info["speed"].toDouble ();
			ui.defence[Naval]    = info["defense"].toInt();
			break;
		case Attackship:
			info = m["attack_ship"].toMap();
			ui.attack_type    = Naval;
			ui.image = QImage(":/icons/units/attack_ship.png");
			ui.seaspeed        = info["speed"].toDouble ();
			ui.defence[Naval]    = info["defense"].toInt();
			break;
		case Brander:
			info = m["demolition_ship"].toMap();
			ui.attack_type    = Naval;
			ui.image = QImage(":/icons/units/demolition_ship.png");
			ui.seaspeed        = info["speed"].toDouble ();
			ui.defence[Naval]    = info["defense"].toInt();
			break;
		case FastTransporter:
			info = m["small_transporter"].toMap();
			ui.attack_type    = Naval;
			ui.image = QImage(":/icons/units/small_transporter.png");
			ui.seaspeed        = info["speed"].toDouble ();
			ui.defence[Naval]    = info["defense"].toInt();

			break;
		case Trireme:
			info = m["trireme"].toMap();
			ui.attack_type    = Naval;
			ui.image = QImage(":/icons/units/trireme.png");
			ui.seaspeed        = info["speed"].toDouble ();
			ui.defence[Naval]    = info["defense"].toInt();
			break;
		case Kolo:
			info = m["colonize_ship"].toMap();
			ui.attack_type    = Naval;
			ui.image = QImage(":/icons/units/colonize_ship.png");
			ui.seaspeed        = info["speed"].toDouble ();
			ui.defence[Naval]    = info["defense"].toInt();
			break;
		case Minotaur:
			info = m["minotaur"].toMap();
			ui.attack_type    = Hack;
			ui.image = QImage(":/icons/units/minotaur.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();

			break;
		case Manti:
			info = m["manticore"].toMap();
			ui.attack_type    = Pierce;
			ui.image = QImage(":/icons/units/manticore.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.seaspeed       = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		case Zyklop:
			info = m["zyklop"].toMap();
			ui.attack_type    = Distance;
			ui.image = QImage(":/icons/units/zyklop.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		case Hydra:
			info = m["sea_monster"].toMap();
			ui.attack_type    = Naval;
			ui.image = QImage(":/icons/units/hydra.png");
			ui.seaspeed        = info["speed"].toDouble ();
			ui.defence[Naval]    = info["defense"].toInt();
			break;
		case Harpy:
			info = m["harpy"].toMap();
			ui.attack_type    = Hack;
			ui.image = QImage(":/icons/units/harpy.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.seaspeed       = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		case Medusa:
			info = m["medusa"].toMap();
			ui.attack_type    = Pierce;
			ui.image = QImage(":/icons/units/medusa.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		case Centaur:
			info = m["centaur"].toMap();
			ui.attack_type    = Distance;
			ui.image = QImage(":/icons/units/centaur.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		case Pegasus:
			info = m["pegasus"].toMap();
			ui.attack_type    = Pierce;
			ui.image = QImage(":/icons/units/pegasus.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.seaspeed       = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		case Zerberus:
			info = m["cerberus"].toMap();
			ui.attack_type    = Hack;
			ui.image = QImage(":/icons/units/cerberus.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		case Eriny:
			info = m["fury"].toMap();
			ui.attack_type    = Distance;
			ui.image = QImage(":/icons/units/fury.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		case Griffin:
			info = m["griffin"].toMap();
			ui.attack_type    = Hack;
			ui.image = QImage(":/icons/units/griffin.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.seaspeed       = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		case Kalydonian:
			info = m["calydonian_boar"].toMap();
			ui.attack_type    = Pierce;
			ui.image = QImage(":/icons/units/calydonian_boar.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		case Godsent:
			info = m["godsent"].toMap();
			ui.attack_type    = Hack;
			ui.image = QImage(":/icons/units/godsent.png");
			ui.landspeed      = info["speed"].toDouble ();
			ui.defence[Hack]     = info["def_hack"].toInt();
			ui.defence[Pierce]   = info["def_pierce"].toInt();
			ui.defence[Distance] = info["def_distance"].toInt();
			break;
		default: 			
			break;
	}
	ui.build_time  = info["build_time"].toDouble();
	ui.name = info["name"].toString();
	ui.name_pl = info["name_plural"].toString();
	ui.desc = info["description"].toString();
	ui.attack = info["attack"].toInt();
	if(i == Transporter || i == FastTransporter || i == Kolo) {
		ui.attack = 0;
	}
	return ui;
};


QString Unit::unitName (UnitIndex i,bool plural) 
{
	if(!plural) {
	if(i == Militia) return tr("Militia");
	else if (i == Sword) return tr("Sword");
	else if (i == Slinger) return tr("Slinger");
	else if (i == Archer) return tr("Archer");
	else if (i == Hoplite) return tr("Hoplite");
	else if (i == Rider) return tr("Rider");
	else if (i == Chariot) return tr("Chariot");
	else if (i == Kata) return tr("Catapult");
	else if (i == Transporter) return tr("Big transporter");
	else if (i == Bireme) return tr("Bireme");
	else if (i == Attackship) return tr("Attack ship");
	else if (i == Brander) return tr("Demolition ship");
	else if (i == FastTransporter) return tr("Small transporter");
	else if (i == Trireme) return tr("Trireme");
	else if (i == Kolo) return tr("Colonize ship");
	else if (i == Minotaur) return tr("Minotaur");
	else if (i == Manti) return tr("Manticore");
	else if (i == Zyklop) return tr("Zyklop");
	else if (i == Hydra) return tr("Sea monster");
	else if (i == Harpy) return tr("Harpy");
	else if (i == Medusa) return tr("Medusa");
	else if (i == Centaur) return tr("Centaur");
	else if (i == Pegasus) return tr("Pegasus");
	else if (i == Zerberus) return tr("Cerberus");
	else if (i == Eriny) return tr("Fury");
	else if (i == Griffin) return tr("Griffin");
	else if (i == Kalydonian) return tr("Kalydonian boar");
	else if (i == Godsent) return tr("Godsent");
	return tr("Unknown unit");
	}else {
	if(i == Militia) return tr("Militias");
	else if (i == Sword) return tr("Swords");
	else if (i == Slinger) return tr("Slingers");
	else if (i == Archer) return tr("Archers");
	else if (i == Hoplite) return tr("Hoplites");
	else if (i == Rider) return tr("Riders");
	else if (i == Chariot) return tr("Chariots");
	else if (i == Kata) return tr("Catapults");
	else if (i == Transporter) return tr("Big transporters");
	else if (i == Bireme) return tr("Biremes");
	else if (i == Attackship) return tr("Attack ships");
	else if (i == Brander) return tr("Demolition ships");
	else if (i == FastTransporter) return tr("Small transporters");
	else if (i == Trireme) return tr("Triremes");
	else if (i == Kolo) return tr("Colonize ships");
	else if (i == Minotaur) return tr("Minotaurs");
	else if (i == Manti) return tr("Manticores");
	else if (i == Zyklop) return tr("Zyklops");
	else if (i == Hydra) return tr("Sea monsters");
	else if (i == Harpy) return tr("Harpys");
	else if (i == Medusa) return tr("Medusas");
	else if (i == Centaur) return tr("Centaurs");
	else if (i == Pegasus) return tr("Pegasoi");
	else if (i == Zerberus) return tr("Cerberi");
	else if (i == Eriny) return tr("Furys");
	else if (i == Griffin) return tr("Griffins");
	else if (i == Kalydonian) return tr("Kalydonian boars");
	else if (i == Godsent) return tr("Godsents");
	return tr("Unknown units");
	}
};

QString Unit::unitIconFile (UnitIndex i) 
{
	if(i == Militia) return ":/icons/units/militia.png";
	else if (i == Sword) return ":/icons/units/sword.png";
	else if (i == Slinger) return ":/icons/units/slinger.png";
	else if (i == Archer) return ":/icons/units/archer.png";
	else if (i == Hoplite) return ":/icons/units/hoplite.png";
	else if (i == Rider) return ":/icons/units/rider.png";
	else if (i == Chariot) return ":/icons/units/chariot.png";
	else if (i == Kata) return ":/icons/units/catapult.png";
	else if (i == Transporter) return ":/icons/units/big_transporter.png";
	else if (i == Bireme) return ":/icons/units/bireme.png";
	else if (i == Attackship) return ":/icons/units/attack_ship.png";
	else if (i == Brander) return ":/icons/units/demolition_ship.png";
	else if (i == FastTransporter) return ":/icons/units/small_transporter.png";
	else if (i == Trireme) return ":/icons/units/trireme.png";
	else if (i == Kolo) return ":/icons/units/colonize_ship.png";
	else if (i == Minotaur) return ":/icons/units/minotaur.png";
	else if (i == Manti) return ":/icons/units/manticore.png";
	else if (i == Zyklop) return ":/icons/units/zyklop.png";
	else if (i == Hydra) return ":/icons/units/hydra.png";
	else if (i == Harpy) return ":/icons/units/harpy.png";
	else if (i == Medusa) return ":/icons/units/medusa.png";
	else if (i == Centaur) return ":/icons/units/centaur.png";
	else if (i == Pegasus) return ":/icons/units/pegasus.png";
	else if (i == Zerberus) return ":/icons/units/cerberus.png";
	else if (i == Eriny) return ":/icons/units/fury.png";
	else if (i == Griffin) return ":/icons/units/griffin.png";
	else if (i == Kalydonian) return ":/icons/units/calydonian_boar.png";
	else if (i == Godsent) return ":/icons/units/godsent.png";
	return "";
};



TownTypeIndex UnitData::tacticalType () const 
{
	int bb [UnitMax];
	for (int i=0;i<UnitMax;++i) bb[i]=val[i]*unitBHP[i];

	int ld  = bb [Sword] + bb[Archer] + bb[Hoplite] + bb[Chariot]+ bb[Zerberus];
	int bir = bb [Bireme];
	int fs  = bb [Attackship];
	int lo  = bb [Hoplite] + bb[Slinger] + bb[Rider] + bb[Chariot]+ bb[Kata];
	int mant = bb[Manti];
	int harp = bb[Harpy];
	int kol  = bb[Kolo];
	int peg  = bb[Pegasus];

	if ( kol ) return TownTypeAttKolo;
	if ( mant && mant > (fs+lo) ) return  TownTypeManti;		
	if ( harp && harp > (fs+lo) ) return  TownTypeHarpy;		
	if ( peg &&  peg > (bir+ld) ) return  TownTypePega;		
	if ( fs && fs > lo && fs > ld && fs >bir && lo < 500) return TownTypeAttShip;			
	if ( bir && bir > ld && ld < 500) return TownTypeBireme;
	if ( (ld+bir) > (lo+fs) ) return TownTypeDeff;
	if ( (ld+bir) < (lo+fs) ) return TownTypeAtt;
	return  TownTypeUndefined;
}
TownTypeIndex UnitData::attackType () const 
{
	TownTypeIndex ret = TownTypeUndefined;
	int fs = val [Attackship];
	int lo = val [Hoplite] + val[Slinger] + val[Rider] + val[Chariot];
	int mant = val[Manti];
	int harp = val[Harpy];
	int kol = val[Kolo];
	if (fs) {
		ret = TownTypeAtt;
		if (fs>100) ret = TownTypeAttShip;
		if ( kol ) ret = TownTypeAttKolo;
	} else if (lo) {
		ret = TownTypeAtt;		
		if ( kol ) ret = TownTypeAttKolo;
	} else if (mant > 10) {
		ret = TownTypeManti;		
	} else if (harp > 10) {
		ret = TownTypeHarpy;		
	}
	return ret;
}




double UnitData::attValue (AttackTypeIndex t, const BonusData& b) const
{
	double ret = 0.0;
	double seab = b.seaBonusAtt();
	double landb = b.landBonusAtt();
	double myth = 1.0; 
	if (b.val[BonusPriest] ) myth = 1.2;
	if ( t == Naval ) {
		ret += (double)WorldData::currentWorld ().unit (Attackship).attack * (double)val[Attackship]*seab; 		
		ret += (double)WorldData::currentWorld ().unit (Trireme).attack * (double)val[Trireme]*seab; 		
		ret += (double)WorldData::currentWorld ().unit (Bireme).attack * (double)val[Bireme]*seab; 		
		ret += (double)WorldData::currentWorld ().unit (Hydra).attack * (double)val[Hydra]*seab*myth; 		
		return ret;
	}
	for (int i= 0;i<UnitMax;++i ) {
		const Unit & u = WorldData::currentWorld ().unit ((UnitIndex) i); 		
		if (u.attack_type == t) {
			double k = u.attack*val[i];
			k *= landb;
			if (isMythUnit((UnitIndex)i)) k *= myth;
			ret += k;
		}
	}
	return ret;
}

double UnitData::defValue (AttackTypeIndex t, const BonusData& b) const
{
	double ret = 0.0;
	double seab = b.seaBonusDef();
	double landb = b.landBonusDef();
	double myth = 1.0; 
	
	if (b.val[BonusPriest] ) myth = 1.2;
	if ( t == Naval ) {
		ret += (double)WorldData::currentWorld ().unit (Attackship).defence[Naval] * (double)val[Attackship]*seab; 		
		ret += (double)WorldData::currentWorld ().unit (Trireme).defence[Naval] * (double)val[Trireme]*seab; 		
		ret += (double)WorldData::currentWorld ().unit (Bireme).defence[Naval] * (double)val[Bireme]*seab; 		
		ret += (double)WorldData::currentWorld ().unit (Hydra).defence[Naval] * (double)val[Hydra]*seab*myth; 		
		return ret;
	}
	// ret += 10 * (b.val[BonusWall]+1);

	for (int i= 0;i<UnitMax;++i ) {
		const Unit & u = WorldData::currentWorld ().unit ((UnitIndex) i); 
		double k= u.defence[t]*val[i];	
		k *= landb;
		if (isMythUnit((UnitIndex)i)) k *= myth;
		ret += k;
	}
	return ret;
}

