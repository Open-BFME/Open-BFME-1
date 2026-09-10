// ?doBountyForKill@Player@@QAEXPBVObject@@0@Z
// partial score=0.995 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "PreRTS.h"
#include "Common/UnicodeString.h"
#include "GameClient/Color.h"
#include "GameClient/GameText.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern "C" __declspec(dllimport) double __cdecl bfmeMathVE(double value);

class Object
{
public:
	Int getBountyValue() const;
	Bool getAttributeModifierBonus(Int which, Real *value) const;

	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0x38);
	}
};

// The object value and modifier calls both use already matched retail ILTs.
#pragma comment(linker, "/alternatename:?getBountyValue@Object@@QBEHXZ=?j_0001cd91@@YAXXZ")
#pragma comment(linker, "/alternatename:?getAttributeModifierBonus@Object@@QBE_NHPAM@Z=?j_0000bece@@YAXXZ")

class ScoreKeeper
{
public:
	void addMoneyEarned(Int amount);
};

class Rva00027D6DMoney
{
public:
	void unidentified_00027d6d(UnsignedInt amount, Bool playSound);
};

class Player
{
public:
	void doBountyForKill(const Object *killer, const Object *victim);

	Rva00027D6DMoney *getMoney()
	{
		return reinterpret_cast<Rva00027D6DMoney *>(reinterpret_cast<char *>(this) + 0x48);
	}

	ScoreKeeper *getScoreKeeper()
	{
		return reinterpret_cast<ScoreKeeper *>(reinterpret_cast<char *>(this) + 0x348);
	}

private:
	unsigned char m_unreconstructed_00[0x260];
	Real m_cashBountyPercent;
};

class GameLogicShim
{
public:
	Bool unidentified_0001e0ab();
};

class GameLogicPortraitShim
{
};

class PlayerList;

class Rva002EE330PlayerListThunk
{
public:
	Int unidentified_000389f6(Bool includeFields);
};

class Rva00083240Thunk
{
public:
	Real unidentified_00009e12(Int index) const;
};

class Rva000C97C0PlayerThunk
{
public:
	Int unidentified_00024938(Int bounty);
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

extern const Real BfmeZeroRange;
extern Real g_bfmeUint32Scale;
extern const Real g_bfmeDirectionWeight1285;
extern GameLogicPortraitShim *TheBfmeGameLogic;
extern PlayerList *Rva002EE330ThePlayers;
extern GlobalData *TheWritableGlobalData;
extern InGameUI *TheInGameUI;

void Player::doBountyForKill(const Object *killer, const Object *victim)
{
	register const Object *killerObject = killer;
	register const Object *victimObject = victim;
	if (!killerObject || !victimObject)
		return;
	if ((*(reinterpret_cast<const unsigned char *>(victimObject) + 0x90) & 0x4) != 0)
		return;

	Int zero = 0;
	Int victimBounty = victimObject->getBountyValue();
	UnsignedInt bounty = victimBounty;
	Real bountyPercent;
	killerObject->getAttributeModifierBonus(0xf, &bountyPercent);
	if (bountyPercent == BfmeZeroRange)
		bountyPercent = m_cashBountyPercent;

	Real roundedBounty = (Real)bfmeMathVE((double)((Real)bounty * bountyPercent));
	bounty = (UnsignedInt)fast_float2long_round(roundedBounty);

	if (((GameLogicShim *)TheBfmeGameLogic)->unidentified_0001e0ab())
	{
		const Int playerIndex = ((Rva002EE330PlayerListThunk *)Rva002EE330ThePlayers)->unidentified_000389f6(false);
		const Real factor = ((Rva00083240Thunk *)((char *)TheWritableGlobalData + 0xee0))->unidentified_00009e12(playerIndex);
		bounty = (UnsignedInt)(bounty * factor);
	}

	bounty = (UnsignedInt)((Rva000C97C0PlayerThunk *)this)->unidentified_00024938((Int)bounty);
	if (bounty == zero)
		return;

	getMoney()->unidentified_00027d6d(bounty, true);
	getScoreKeeper()->addMoneyEarned((Int)bounty);

	Coord3D pos;
	UnicodeString moneyString;
	moneyString.format(TheGameText->fetch("GUI:AddCash"), bounty);
	pos.set(victimObject->getPosition());
	pos.z += 10.0f;
	TheInGameUI->addFloatingText(moneyString, &pos, GameMakeColor(255, 255, 0, 255));
}
