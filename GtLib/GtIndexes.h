#ifndef __GT_INDEXES_H
#define __GT_INDEXES_H
/* gtindexes.h  - data indexes

Copyright (c) 2013 P. Vorpahl

This file is part of Grepotool, a free utility for the browsergame 
Grepolis which is the intellectual property of InnoGames GmbH.

Grepotool is free Software: you can redistribute it and/or modify 
it under the terms of the GNU Lesser General Public License as 
published by the Free Software Foundation, either version 3 of the 
License, or any later version. Alternatively, you may use it under 
the terms of the GNU General Public License as published by the Free 
Software Foundation, either version 3 of the License, or any later 
version.

Grepotool is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License 
along with 'Grepotool; see the files 'GPL.txt' and 'LGPL.txt' in 
the base directory of your installation. If not, see 
'http://www.gnu.org/licenses/'.
*/
#include <QString>



enum GodIndex {
	AnyGod,
	Zeus,
	Poseidon,
	Hera,
	Athene,
	Hades,
	Artemis
};



enum UnitIndex {
	Militia,
	Sword,
	Slinger,
	Archer,
	Hoplite,
	Rider,
	Chariot,
	Kata,
	Transporter,
	Bireme,
	Attackship,
	Brander,
	FastTransporter,
	Trireme,
	Kolo,
	Minotaur,
	Manti,
	Zyklop,
	Hydra,
	Harpy,
	Medusa,
	Centaur,
	Pegasus,
	Zerberus,
	Eriny,
	Griffin,
	Kalydonian,
	Godsent,
	UnitMax
};

static const char * unitJsonNames [UnitMax] = {
		"militia",		"sword",		"slinger",		"archer",		"hoplite",
		"rider",		"chariot",		"catapult",		"big_transporter",		"bireme",
		"attack_ship",	"demolition_ship","small_transporter",		"trireme",	"colonize_ship",
		"minotaur",		"manticore",	"zyklop",		"sea_monster",		"harpy",
		"medusa",		"centaur",		"pegasus",		"cerberus",		"fury",
		"griffin",		"calydonian_boar",		"godsent"	
};

static int unitBHP [UnitMax] = {0,1,1,1,1,
		3,4,10,7,8,
		10,8,5,16,170,
		30,45,40,50,14,
		18,12,20,30,55,35,20,3};

static UnitIndex unitIndex (const QString & name) {
	for (int i=0; i < UnitMax; ++i) if (name == QString(unitJsonNames [i])) return (UnitIndex) i;
	return UnitMax;
};

static bool isSeaUnit (UnitIndex i) {
	if (i == Transporter) return true;
	if (i == Bireme) return true;
	if (i == Attackship) return true;
	if (i == Brander) return true;
	if (i == FastTransporter) return true;
	if (i == Trireme) return true;
	if (i == Kolo) return true;
	if (i == Hydra) return true;
	return false;
};
static bool isSeaAttUnit (UnitIndex i) {
	if (i == Bireme) return true;
	if (i == Attackship) return true;
	if (i == Trireme) return true;
	if (i == Hydra) return true;
	return false;
};
static bool isSeaDefUnit (UnitIndex i) {
	if (i == Bireme) return true;
	if (i == Attackship) return true;
	if (i == Trireme) return true;
	if (i == Brander) return true;
	if (i == Hydra) return true;
	return false;
};
static bool isMythUnit (UnitIndex i) {
	return (int) i > (int) Kolo;
};
static bool isLandUnit (UnitIndex i) {
	if (i == Sword) return true;
	else if (i == Slinger) return true;
	else if (i == Archer) return true;
	else if (i == Hoplite) return true;
	else if (i == Rider) return true;
	else if (i == Chariot) return true;
	else if (i == Kata) return true;
	else if (i == Minotaur) return  true;
	else if (i == Zyklop) return  true;
	else if (i == Medusa) return  true;
	else if (i == Centaur) return  true;
	else if (i == Zerberus) return  true;
	else if (i == Eriny) return  true;
	else if (i == Kalydonian) return  true;
	else if (i == Godsent) return  true;
	return false;
};

static bool isFlyingUnit (UnitIndex i) {
	if (i == Manti)  return true;
	else if (i == Harpy) return true;
	else if (i == Pegasus) return true;
	else if (i == Griffin) return true;
	return false;
};


enum TownTypeIndex {
	TownTypeUndefined, // circle
	TownTypeAtt,       // rect  
	TownTypeDeff,      // Triangle
	TownTypeAttShip,   // raute
	TownTypeAttKolo,   // rect+hat
	TownTypeBireme,    // Tri down
	TownTypeManti,     // star
	TownTypePega,      // Rect with slash
	TownTypeHarpy,     // rect with backslash
	TownTypeMax        // 
};

static const char * townTypeJsonNames [TownTypeMax] = {
	"undefined", 
	"attack", 
	"defense",
	"att_ships", 
	"colonize_ship", 
	"biremes", 
	"mantis", 
	"pegasoi", 
	"harpys"
};

static TownTypeIndex townTypeIndex (const QString & name) {
	for (int i=0; i < TownTypeMax; ++i) if (name == townTypeJsonNames [i]) return (TownTypeIndex) i;
	return TownTypeMax;
}

enum AttackTypeIndex {
	Hack,
	Pierce,
	Distance,
	Naval
};

enum RessiIndex {
	Wood,
	Stone,
	Silver,
	Favor
};


enum PremiumIndex {
	Counselor = 1,
	Trader=2,
	HighPriest=4,
	Captain=8,
	Commander=16
};

enum WonderIndex {
	ZeusStatue = 1,
	ArtemisTemple = 2,
	Mausoleum   = 4,
	KolossOfRhodos = 8,
	AlexandrianLighthouse = 16,
	Pyramid = 32,
	Gardens = 64
};

enum BuildingIndex {
	Ironer,
	Lumber,
	Stoner,
	Senat,
	Barracks,
	Wall,
	Market,
	Temple,
	Academy,
	Storage,
	Hide,
	Farm,
	Agora,
	Docks,
	Theater,
	Therme,
	Library,
	Lighthouse,
	Tower,
	Oracle,
	TradeOffice,
	Statue,
	BuildingMax
};

static const char * buildingJsonNames [BuildingMax] = {
	"ironer", // Ironer,
	"lumber", // Lumber,
	"stoner", // Stoner,
	"main", // Senat,
	"barracks", // Barracks,
	"wall", // Wall,
	"market", // Market,
	"temple", // Temple,
	"academy", // Academy,
	"storage", // Storage,
	"hide", // Hide,
	"farm", // Farm,
	"place", // Agora,
	"docks", // Docks,
	"theater", // Theater,
	"thermal", // Therme,
	"library", // Library,
	"lighthouse", // Lighthouse,
	"tower", // Tower,
	"oracle", // Oracle,
	"trade_office", // TradeOffice,
	"statue" // Statue,
};

static BuildingIndex buildingIndex (const QString & name) {
	for (int i=0; i < BuildingMax; ++i) if (name == buildingJsonNames [i]) return (BuildingIndex) i;
	return BuildingMax;
};

enum HeroIndex {
	Atlanta,		
	Hercules,
	Leonidas,
	Urephon,
	Zuretha,
	Andromeda,
	Cheiron,
	Ferkyon,
	Helena,
	Orpheus,
	Terylea,
	HeroMax
};

static const char * heroJsonNames [HeroMax] = {
	"atlanta",
	"hercules",
	"leonidas",
	"urephon",
	"zuretha",
	"andromeda",
	"cheiron",
	"ferkyon",
	"helen",
	"orpheus",
	"terylea"
};

static HeroIndex heroIndex (const QString & name) {
	for (int i=0; i < HeroMax; ++i) if (name == heroJsonNames [i]) return (HeroIndex) i;
	return HeroMax;
};


enum ResearchIndex {
	ResearchSlinger,
	ResearchArcher,
	ResearchHoplite,
	ResearchCitiGuard,
	ResearchDiplo,
	ResearchSpy,
	ResearchBounty,
	ResearchCeramics,
	ResearchRider,
	ResearchArchitecture,
	ResearchTrainer,
	ResearchBireme,
	ResearchCrane,
	ResearchMeteorology,
	ResearchChariot,
	ResearchAttackship,
	ResearchConscription,
	ResearchBoatBuilder,
	ResearchBrander,
	ResearchCatapult,
	ResearchCryptografy,
	ResearchColoship,
	ResearchFastTrans,
	ResearchPlough,
	ResearchBunks,
	ResearchTrireme,
	ResearchPhalanx,
	ResearchBreakthrough,
	ResearchMathematics,
	ResearchRam,
	ResearchCartography,
	ResearchConquering,

	ResearchStoneHail,
	ResearchTempleLooting,
	ResearchGodlySelection,
	ResearchExperience,
	ResearchStrongWine,
	ResearchSail,

	ResearchMax
};

static const char * researchJsonNames [ResearchMax] = {
	"slingers",
	"archers",
	"hoplites",
	"city_guard",
	"diplomacy",
	"espionage",
	"bounty",
	"ceramics",
	"riders",
	"architecture",
	"trainer",
	"biremes",
	"crane",
	"meteorology",
	"chariots",
	"attack_ship",
	"construction",
	"boat_builder",
	"demolition_ships",
	"catapult",
	"cryptography",
	"colonize_ship",
	"small_transporter",
	"plough",
	"bunks",
	"trireme",
	"phalanx",
	"breakthrough",
	"mathematics",
	"ram",
	"cartography",
	"conquer",
	"stone_hail",
	"temple_looting",
	"godly_selection",
	"experience",
	"strong_wine",
	"sail"
};

static ResearchIndex researchIndex (const QString & name) {
	for (int i=0; i < ResearchMax; ++i) if (name == researchJsonNames [i]) return (ResearchIndex) i;
	return ResearchMax;
};


enum SpellIndex {
	// Zeus
	GodsSign,
	Lightning,
	GoodWind,
	ZeusRage,
	// Poseidon
	GiftOfSea,
	CallofSea,
	Earthquake,
	SeeStorm,
	// Hera
	Marriage,
	Happyness,
	Babyboom,
	Whishfullness,
	// Athene
	GuardianGoddess,
	Wisdom,
	Protection,
	HeroPower,
	// Hades
	Pest,
	ReturnFromUnderworld,
	UnderworldTreasure,
	HelmetOfInvisibility,
	// Artemis
	GiftOfNature,
	HountressDesire,
	Illusion,
	Purification,

	SpellMax
};



static QString bbCode (const QString& tx, const QString& bb) {return QString("[%1]%2[/%1]").arg(bb).arg(tx);};
static QString bbCodeLabel (const QString& tx, const QString& ico, int si=16) {
	return QString("<img src='%1' width=%2 height=%2>&nbsp;<b>%3</b>").arg(ico).arg (si).arg(tx);
};



#endif