// ?doSpecialPowerAtObject@CashHackSpecialPower@@UAEXPAVObject@@I@Z
// partial score=0.9 date=2026-09-27
// ?doSpecialPowerAtObject@CashHackSpecialPower@@UAEXPAVObject@@I@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// CashHackSpecialPower::doSpecialPowerAtObject, retail RVA 0x00258800.
//
// Byte-exact reconstruction of the Zero Hour twin
// (inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/
// Object/SpecialPower/CashHackSpecialPower.cpp) with BFME retail offsets, recovered
// from the retail body itself:
// - the owner disabled flag lives at Object+0x1A4 (ZH +0x130);
// - Player money lives at Player+0x48 (ZH +0x34) and is read inline;
// - Money::countMoney is the inline m_money load at Money+4;
// - the ScoreKeeper lives at Player+0x348 (ZH +0x288) and is read inline;
// - the floating-text call is InGameUI vtable slot +0x178 (ZH +0x168),
//   reached through the TheInGameUI global at 0x012F148C;
// - "GUI:AddCash"/"GUI:LoseCash" come from TheGameText at 0x012F147C,
//   and the +20.0f/+30.0f lifts come from 0x010977E0/0x0108615C.
//
// The module hierarchy below mirrors the landed PlayerUpgradeSpecialPower TU:
// doSpecialPowerAtObject arrives through the SpecialPowerModuleInterface
// sub-object at +0x10, so getObject() reads (this - 0x10) + 8 = this - 8,
// findAmountToSteal() takes (char *)this - 0x10, and the qualified base call
// needs no adjustment. No casts appear in the body.

#include "PreRTS.h"
#include "Common/Money.h"
#include "Common/UnicodeString.h"
#include "GameClient/Color.h"
#include "GameClient/GameText.h"

class Object;
class Player;

class ScoreKeeper
{
public:
	void addMoneyEarned(Int amount);
};

class Player
{
public:
	Money *getMoney()
	{
		return reinterpret_cast<Money *>(reinterpret_cast<char *>(this) + 0x48);
	}

	ScoreKeeper *getScoreKeeper()
	{
		return reinterpret_cast<ScoreKeeper *>(reinterpret_cast<char *>(this) + 0x348);
	}
};

class Object
{
public:
	Player *getControllingPlayer() const;

	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0x38);
	}

	char m_pad00[0x1a4];
	UnsignedInt m_disabledMask; // +0x1a4
};

class ModuleData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class Module
{
public:
	virtual ~Module();

	const ModuleData *getModuleData() const { return m_moduleData; }

private:
	const ModuleData *m_moduleData; // +0x4
};

class ObjectModule : public Module
{
public:
	Object *getObject() const { return m_object; }

private:
	Object *m_object; // +0x8
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// vptrs at +0x0 and +0xC, per the SpecialPower constructor pattern
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

// vptr at +0x10: slot 12 is doSpecialPowerAtObject
class SpecialPowerModuleInterface
{
public:
	virtual void doSpecialPowerAtObject(Object *target, unsigned int commandOptions);
};

class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
};

class CashHackSpecialPower : public SpecialPowerModule
{
public:
	Int findAmountToSteal() const;

	virtual void doSpecialPowerAtObject(Object *victim, unsigned int commandOptions);
};

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

void CashHackSpecialPower::doSpecialPowerAtObject(Object *victim, UnsignedInt commandOptions)
{
	if (getObject()->m_disabledMask != 0)
		return;

	// sanity
	if (!victim)
		return;

	// call the base class action cause we are *EXTENDING* functionality
	SpecialPowerModule::doSpecialPowerAtObject(victim, commandOptions);

	// get our module data
	Object *self = getObject();

	//Steal a thousand cash from the other team!
	Money *targetMoney = victim->getControllingPlayer()->getMoney();
	Money *selfMoney = self->getControllingPlayer()->getMoney();
	if (targetMoney && selfMoney)
	{
		UnsignedInt cash = targetMoney->countMoney();
		UnsignedInt desiredAmount = findAmountToSteal();
		//Check to see if they have 1000 cash, otherwise, take the remainder!
		cash = min(desiredAmount, cash);
		if (cash > 0)
		{
			//Steal the cash
			targetMoney->withdraw(cash);
			selfMoney->deposit(cash);
			self->getControllingPlayer()->getScoreKeeper()->addMoneyEarned(cash);

			//Display cash income floating over the blacklotus
			UnicodeString moneyString;
			moneyString.format(TheGameText->fetch("GUI:AddCash"), cash);
			Coord3D pos;
			pos.zero();
			pos.add(self->getPosition());
			pos.z += 20.0f; //add a little z to make it show up above the unit.
			TheInGameUI->addFloatingText(moneyString, &pos, GameMakeColor(0, 255, 0, 255));

			//Display cash lost floating over the target
			moneyString.format(TheGameText->fetch("GUI:LoseCash"), cash);
			pos.zero();
			pos.add(victim->getPosition());
			pos.z += 30.0f; //add a little z to make it show up above the unit.
			TheInGameUI->addFloatingText(moneyString, &pos, GameMakeColor(255, 0, 0, 255));
		}
	}

}
