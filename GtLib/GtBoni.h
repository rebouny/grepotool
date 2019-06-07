#ifndef ___GT_BONI_H
#define ___GT_BONI_H
/* 
GtBoni
*/

#include <GtUnits.h>
#include <GtBuildings.h>
#include <GtResearch.h>
#include <GtHeros.h>

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



/* fight boni:
captain
commander
high_priest
luck    
moral
night_bonus
ram
phalanx
tower
strength_of_heros  heldenkraft
fair_wind          
desire           
trojan_defense
myrmidion_attack
longterm_attack_boost
longterm_defense_boost
attack_boost       "percent":10,"lifetime":28800,"level":8
defense_boost      "percent":10,"lifetime":28800,"level":8
*/

enum BonusIndex {
	BonusCaptain,
	BonusCommander,
	BonusPriest,
	BonusLuck,
	BonusMorale,
	BonusRam,
	BonusPhalanx,
	BonusTower,
	BonusWall,
	BonusNight,
	BonusHeroStrength,
	BonusFairWind,
	BonusDesire,
	BonusTrojanDef,
	BonusMyrmidionAtt,
	BonusLongtermAttBoost,
	BonusLongtermDefBoost,
	BonusAttBoost,
	BonusDefBoost,
	BonusMax
};

static const char * bonusJsonNames [BonusMax]= {"captain", "commander", "high_priest", "luck",
"morale","ram","phalanx","tower","wall","nightbonus","strength_of_heroes","fair_wind", "desire", "trojan_defense",
"myrmidion_attack","longterm_attack_boost","longterm_defense_boost","attack_boost","defense_boost"};

static BonusIndex bonusIndex (const QString & name) {
	for (int i=0; i < BonusMax; ++i) if (name == QString(bonusJsonNames [i])) return (BonusIndex) i;
	return BonusMax;
};

static const char* bonusImageFile[BonusMax] =  {
	":/icons/premium/captain.png", //BonusCaptain,
	":/icons/premium/commander.png", //BonusCommander,
	":/icons/premium/priest.png", //BonusPriest,
	":/icons/icons/luck.png", //BonusLuck,
	":/icons/icons/morale.png", //
	":/icons/research/ram.png", //BonusRam,
	":/icons/research/phalanx.png", //BonusPhalanx,
	":/icons/buildings/tower.png", //BonusTower,
	":/icons/buildings/wall.png", //BonusWall,
	":/icons/icons/night.png", //BonusNight,
	":/icons/spells/hero_power.png", //BonusHeroStrength,
	":/icons/spells/fair_wind.png", //BonusFairWind,
	":/icons/spells/desire.png", //BonusDesire,
	":/icons/spells/trojan_defense.png", //BonusTrojanDef,
	":/icons/spells/myrmidion_attack.png", //BonusMyrmidionAtt,
	":/icons/spells/longterm_attack_boost.png", //BonusLongtermAttBoost,
	":/icons/spells/longterm_defense_boost.png", //BonusLongtermDefBoost,
	":/icons/spells/attack_bost.png", //BonusAttBoost,
	":/icons/spells/defense_boost.png" //BonusDefBoost,	
};

class EXPORT BonusData {
	Q_DECLARE_TR_FUNCTIONS (BonusData);
public:
	BonusData () {
		for (int i=0;i<BonusMax;++i) 
			val[i]=0; 
		val[BonusMorale]=100;
	};
	BonusData (const BonusData& o){*this = o;};
	BonusData & operator = (const BonusData& o) {
		for (int i=0;i<BonusMax;++i) 
			val[i] = o.val[i]; 
		return *this;
	};
	double landBonusAtt () const;
	double seaBonusAtt () const;
	double seaBonusDef () const;
	double landBonusDef () const;
	QVariantMap toVariant () const;
	static BonusData fromVariant (const QVariantMap & m);
	static QString toolTip (BonusIndex b);
	inline bool isValid() const  {for (int i=0;i<BonusMax;++i) if(val[i]) return true; return false;};
	int        val[BonusMax];
};


#endif