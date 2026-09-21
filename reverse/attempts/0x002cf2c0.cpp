// ?action@SupplyCenterDockUpdate@@QAE_NPAVObject@@0@Z
// partial score=0.36 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /DZH_EMIT_POOL_GLUE /DBFME_MODULE_NO_MPO /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// SupplyCenterDockUpdate::action, retail RVA 0x002CF2C0 (586B). Sits directly
// between the matched scalar deleting destructor (0x002CF290) and the matched
// SupplyCenterDockUpdateModuleData constructor (0x002CF5A0) -- the class's
// missing action() slot. ZH's SupplyCenterDockUpdate::action (reference
// GeneralsMD/.../DockUpdate/SupplyCenterDockUpdate.cpp) drains the docking
// SupplyTruckAIInterface's boxes into Player money, but BFME replaced the
// getUpgradedSupplyBoost() bonus with an attribute-modifier multiplier, a
// multiplayer/skirmish player-count scale (or, offline, a Living World bounty
// adjustment), a science-gated bonus multiplier, and an ExperienceTracker
// award -- and dropped the stealth-grant block entirely. The tail (deposit,
// score, "GUI:AddCash" floating text) reuses the class declarations already
// proven byte-exact by the same six retail helper thunks (0x1e0ab, 0x389f6,
// 0x9e12, 0x24938, 0x27d6d, 0x3a45e) in the matched
// AutoDepositUpdate::awardInitialCaptureBonus (0x00280EE0).

#include "PreRTS.h"

#include "Common/GlobalData.h"
#include "GameClient/Color.h"
#include "GameClient/GameText.h"
#include "GameLogic/Object.h"

class GameLogicShim
{
public:
	Bool unidentified_0001e0ab();
};

class GameLogicPortraitShim
{
};

class Rva002EE330PlayerListThunk
{
public:
	Int unidentified_000389f6(Bool includeFields);
};

class Rva00083240Thunk
{
public:
	float unidentified_00009e12(Int index) const;
};

class Rva000C97C0PlayerThunk
{
public:
	Int unidentified_00024938(Int bounty);
};

class Rva00027D6DMoney
{
public:
	void unidentified_00027d6d(UnsignedInt amount, Bool playSound);
};

class Rva0003A45EScoreKeeper
{
public:
	void unidentified_0003a45e(Int amount);
};

class Player
{
public:
	UnsignedInt getSupplyBoxValue() const;
	Bool hasScience(ScienceType t) const;

	Rva00027D6DMoney *getMoney()
	{
		return (Rva00027D6DMoney *)((char *)this + 0x48);
	}

	Rva0003A45EScoreKeeper *getScoreKeeper()
	{
		return (Rva0003A45EScoreKeeper *)((char *)this + 0x348);
	}

	Color getPlayerColor() const
	{
		return *(const Color *)((const char *)this + 0x1c4);
	}
};

// Object's own attribute-modifier query (BFME addition, not present in the
// vendored ZH Object.h): reached by casting the already-real Object* to this
// shim, matching the Rva000C97C0PlayerThunk / Rva002EE330PlayerListThunk
// pattern used for the other BFME-only helpers above.
class ObjectAttributeModifierShim
{
public:
	Bool getAttributeModifierMultiplier(Int which, Real *out) const;
};

// AIUpdateInterface / SupplyTruckAIInterface -- only the slots this body
// uses. Object::getAI() is a plain field read at Object+0x204 (no virtual
// call, BFME addition not modeled in the vendored ZH Object header); the
// interface it returns dispatches through slot 0x144 (index 81) for the
// still-unnamed accessor this body treats the way ActionManager's already
// matched canTransferSuppliesAt treats getSupplyTruckAIInterface, and
// SupplyTruckAIInterface's third slot (+8) is that same file's loseOneBox.
class SupplyTruckAIInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual Bool loseOneBox() = 0;
};

#define BFME_AI_SLOT(N) virtual void bfmeSlot##N() = 0

class BFMEAIUpdateInterface
{
public:
	BFME_AI_SLOT(00); BFME_AI_SLOT(01); BFME_AI_SLOT(02); BFME_AI_SLOT(03); BFME_AI_SLOT(04); BFME_AI_SLOT(05);
	BFME_AI_SLOT(06); BFME_AI_SLOT(07); BFME_AI_SLOT(08); BFME_AI_SLOT(09); BFME_AI_SLOT(10); BFME_AI_SLOT(11);
	BFME_AI_SLOT(12); BFME_AI_SLOT(13); BFME_AI_SLOT(14); BFME_AI_SLOT(15); BFME_AI_SLOT(16); BFME_AI_SLOT(17);
	BFME_AI_SLOT(18); BFME_AI_SLOT(19); BFME_AI_SLOT(20); BFME_AI_SLOT(21); BFME_AI_SLOT(22); BFME_AI_SLOT(23);
	BFME_AI_SLOT(24); BFME_AI_SLOT(25); BFME_AI_SLOT(26); BFME_AI_SLOT(27); BFME_AI_SLOT(28); BFME_AI_SLOT(29);
	BFME_AI_SLOT(30); BFME_AI_SLOT(31); BFME_AI_SLOT(32); BFME_AI_SLOT(33); BFME_AI_SLOT(34); BFME_AI_SLOT(35);
	BFME_AI_SLOT(36); BFME_AI_SLOT(37); BFME_AI_SLOT(38); BFME_AI_SLOT(39); BFME_AI_SLOT(40); BFME_AI_SLOT(41);
	BFME_AI_SLOT(42); BFME_AI_SLOT(43); BFME_AI_SLOT(44); BFME_AI_SLOT(45); BFME_AI_SLOT(46); BFME_AI_SLOT(47);
	BFME_AI_SLOT(48); BFME_AI_SLOT(49); BFME_AI_SLOT(50); BFME_AI_SLOT(51); BFME_AI_SLOT(52); BFME_AI_SLOT(53);
	BFME_AI_SLOT(54); BFME_AI_SLOT(55); BFME_AI_SLOT(56); BFME_AI_SLOT(57); BFME_AI_SLOT(58); BFME_AI_SLOT(59);
	BFME_AI_SLOT(60); BFME_AI_SLOT(61); BFME_AI_SLOT(62); BFME_AI_SLOT(63); BFME_AI_SLOT(64); BFME_AI_SLOT(65);
	BFME_AI_SLOT(66); BFME_AI_SLOT(67); BFME_AI_SLOT(68); BFME_AI_SLOT(69); BFME_AI_SLOT(70); BFME_AI_SLOT(71);
	BFME_AI_SLOT(72); BFME_AI_SLOT(73); BFME_AI_SLOT(74); BFME_AI_SLOT(75); BFME_AI_SLOT(76); BFME_AI_SLOT(77);
	BFME_AI_SLOT(78); BFME_AI_SLOT(79); BFME_AI_SLOT(80);
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface() = 0;
};

inline BFMEAIUpdateInterface *bfmeGetAI(const Object *obj)
{
	return *(BFMEAIUpdateInterface *const *)((const char *)obj + 0x204);
}

// ExperienceTracker -- only isAcceptingExperiencePoints (already matched,
// class ExperienceTracker) and the still-dump award call (thunk 0x00010096,
// still targeting the unconverted body at 0x001B28C0: 5 args, this-call).
class ExperienceTracker
{
public:
	Bool isAcceptingExperiencePoints() const;
	void bfmeAwardExperience001B28C0(Int amount, Bool a, Bool b, Bool c, Int d);
};

#pragma comment(linker, "/alternatename:?bfmeAwardExperience001B28C0@ExperienceTracker@@QAEXHHHHH@Z=?j_00010096@@YAXXZ")

inline ExperienceTracker *bfmeGetExperienceTracker(const Object *obj)
{
	return *(ExperienceTracker *const *)((const char *)obj + 0x210);
}

extern "C" __declspec(dllimport) double __cdecl ceil(double value);

extern GameLogicPortraitShim *TheBfmeGameLogic;
class PlayerList;
extern PlayerList *Rva002EE330ThePlayers;
extern GlobalData *TheWritableGlobalData;

// InGameUI / TerrainLogic -- hand-rolled with placeholder slots, same as
// AutoDepositUpdate_awardInitialCaptureBonus.cpp: the vendored ZH headers'
// InGameUI/TerrainLogic hierarchies (SubsystemInterface/Snapshot bases, etc.)
// don't reproduce BFME's actual vtable slot count, so the real headers are
// not used for these two globals.
class InGameUI
{
public:
#define INGAME_UI_SLOT(n) virtual void slot##n() = 0
	INGAME_UI_SLOT(00); INGAME_UI_SLOT(01); INGAME_UI_SLOT(02); INGAME_UI_SLOT(03);
	INGAME_UI_SLOT(04); INGAME_UI_SLOT(05); INGAME_UI_SLOT(06); INGAME_UI_SLOT(07);
	INGAME_UI_SLOT(08); INGAME_UI_SLOT(09); INGAME_UI_SLOT(10); INGAME_UI_SLOT(11);
	INGAME_UI_SLOT(12); INGAME_UI_SLOT(13); INGAME_UI_SLOT(14); INGAME_UI_SLOT(15);
	INGAME_UI_SLOT(16); INGAME_UI_SLOT(17); INGAME_UI_SLOT(18); INGAME_UI_SLOT(19);
	INGAME_UI_SLOT(20); INGAME_UI_SLOT(21); INGAME_UI_SLOT(22); INGAME_UI_SLOT(23);
	INGAME_UI_SLOT(24); INGAME_UI_SLOT(25); INGAME_UI_SLOT(26); INGAME_UI_SLOT(27);
	INGAME_UI_SLOT(28); INGAME_UI_SLOT(29); INGAME_UI_SLOT(30); INGAME_UI_SLOT(31);
	INGAME_UI_SLOT(32); INGAME_UI_SLOT(33); INGAME_UI_SLOT(34); INGAME_UI_SLOT(35);
	INGAME_UI_SLOT(36); INGAME_UI_SLOT(37); INGAME_UI_SLOT(38); INGAME_UI_SLOT(39);
	INGAME_UI_SLOT(40); INGAME_UI_SLOT(41); INGAME_UI_SLOT(42); INGAME_UI_SLOT(43);
	INGAME_UI_SLOT(44); INGAME_UI_SLOT(45); INGAME_UI_SLOT(46); INGAME_UI_SLOT(47);
	INGAME_UI_SLOT(48); INGAME_UI_SLOT(49); INGAME_UI_SLOT(50); INGAME_UI_SLOT(51);
	INGAME_UI_SLOT(52); INGAME_UI_SLOT(53); INGAME_UI_SLOT(54); INGAME_UI_SLOT(55);
	INGAME_UI_SLOT(56); INGAME_UI_SLOT(57); INGAME_UI_SLOT(58); INGAME_UI_SLOT(59);
	INGAME_UI_SLOT(60); INGAME_UI_SLOT(61); INGAME_UI_SLOT(62); INGAME_UI_SLOT(63);
	INGAME_UI_SLOT(64); INGAME_UI_SLOT(65); INGAME_UI_SLOT(66); INGAME_UI_SLOT(67);
	INGAME_UI_SLOT(68); INGAME_UI_SLOT(69); INGAME_UI_SLOT(70); INGAME_UI_SLOT(71);
	INGAME_UI_SLOT(72); INGAME_UI_SLOT(73); INGAME_UI_SLOT(74); INGAME_UI_SLOT(75);
	INGAME_UI_SLOT(76); INGAME_UI_SLOT(77); INGAME_UI_SLOT(78); INGAME_UI_SLOT(79);
	INGAME_UI_SLOT(80); INGAME_UI_SLOT(81); INGAME_UI_SLOT(82); INGAME_UI_SLOT(83);
	INGAME_UI_SLOT(84); INGAME_UI_SLOT(85); INGAME_UI_SLOT(86); INGAME_UI_SLOT(87);
	INGAME_UI_SLOT(88); INGAME_UI_SLOT(89); INGAME_UI_SLOT(90); INGAME_UI_SLOT(91);
	INGAME_UI_SLOT(92); INGAME_UI_SLOT(93);
#undef INGAME_UI_SLOT
	virtual void addFloatingText(const UnicodeString &text, const Coord3D *position,
		UnsignedInt color) = 0;
};

extern InGameUI *TheInGameUI;

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14();
	virtual Real getGroundHeight(Real x, Real y, void *layer = 0) const;
};

extern TerrainLogic *TheTerrainLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterDockUpdate.h
// Open-BFME5: float@10 (attribute-multiplier scale), int@14 (gated science,
// -1 = none), float@18 (science bonus scale) -- ctor default 1.0f/-1/1.0f,
// see SupplyCenterDockUpdateModuleDataConstructorThunk.cpp.
class SupplyCenterDockUpdateModuleData
{
public:
	Real m_10;
	Int m_14;
	Real m_18;
};

class SupplyCenterDockUpdate
{
public:
	Bool action(Object *docker, Object *drone);

	SupplyCenterDockUpdateModuleData *getSupplyCenterDockUpdateModuleData() const
	{
		return *(SupplyCenterDockUpdateModuleData **)((char *)this - 0x1c);
	}

	Object *getObject() const
	{
		return *(Object **)((char *)this - 0x18);
	}
};

// ?action@SupplyCenterDockUpdate@@QAE_NPAVObject@@0@Z
Bool SupplyCenterDockUpdate::action(Object *docker, Object *drone)
{
	BFMEAIUpdateInterface *ai = bfmeGetAI(docker);
	if (ai == 0)
		return false;

	SupplyTruckAIInterface *supplyTruckAI = ai->getSupplyTruckAIInterface();
	if (supplyTruckAI == 0)
		return false;

	Player *ownerPlayer = getObject()->getControllingPlayer();

	Real value = 0.0f;
	while (supplyTruckAI->loseOneBox())
	{
		value += (Real)ownerPlayer->getSupplyBoxValue();
	}

	if (!(value > 0.0f))
		return false;

	SupplyCenterDockUpdateModuleData *data = getSupplyCenterDockUpdateModuleData();

	Real multiplier = 1.0f;
	((ObjectAttributeModifierShim *)getObject())->getAttributeModifierMultiplier(0xc, &multiplier);
	value *= multiplier;
	value *= data->m_10;

	if (((GameLogicShim *)TheBfmeGameLogic)->unidentified_0001e0ab())
	{
		Int playerCount = ((Rva002EE330PlayerListThunk *)Rva002EE330ThePlayers)->unidentified_000389f6(false);
		Real scale = ((Rva00083240Thunk *)((char *)TheWritableGlobalData + 0xee0))->unidentified_00009e12(playerCount);
		value *= scale;
	}

	Int intValue = (Int)value;
	intValue = ((Rva000C97C0PlayerThunk *)ownerPlayer)->unidentified_00024938(intValue);
	value = (Real)intValue;

	if (ownerPlayer->hasScience((ScienceType)data->m_14))
	{
		value *= data->m_18;
	}

	Int finalValue = (Int)ceil((double)value);

	ownerPlayer->getMoney()->unidentified_00027d6d((UnsignedInt)finalValue, true);
	ownerPlayer->getScoreKeeper()->unidentified_0003a45e(finalValue);

	ExperienceTracker *tracker = bfmeGetExperienceTracker(docker);
	if (tracker != 0 && tracker->isAcceptingExperiencePoints())
	{
		tracker->bfmeAwardExperience001B28C0(finalValue, true, true, true, 0);
	}

	UnicodeString moneys;
	moneys.format(TheGameText->fetch("GUI:AddCash"), finalValue);

	Coord3D pos;
	const Coord3D *dockerPos = docker->getPosition();
	pos.y = dockerPos->y;
	pos.x = dockerPos->x;
	pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);

	Color color = ownerPlayer->getPlayerColor() | GameMakeColor(0, 0, 0, 230);
	TheInGameUI->addFloatingText(moneys, &pos, color);

	return false;
}
