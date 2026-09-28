// ?d_0024ed40@@YAXXZ
// partial score=0.25 date=2026-09-26
// ?rva0024ed40@SlaughterHordeContain@@UAEXPAVObject@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Retail 0x0024ED40, 1066 bytes. The primary table 0x010B11C0 slot 30
// (installed by SlaughterHordeContain's constructor at 0x0024E7A0) proves the
// owner and one Object* stack argument. Ghidra's source-path string identifies
// SlaughterHordeContain.cpp; the original method name is not recovered.
// Ghidra's draft shows bounty payout, floating text, object cleanup and the
// 0x0024E990 accounting helper. This address-derived body preserves that evidence.

#include "PreRTS.h"
#include "Common/UnicodeString.h"
#include "GameClient/GameText.h"
#include "GameClient/Color.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class Player;
class Object;

class Object
{
public:
#define OBJECT_SLOT(N) virtual void slot##N()
	OBJECT_SLOT(00); OBJECT_SLOT(01); OBJECT_SLOT(02); OBJECT_SLOT(03);
	OBJECT_SLOT(04); OBJECT_SLOT(05); OBJECT_SLOT(06); OBJECT_SLOT(07);
	OBJECT_SLOT(08); OBJECT_SLOT(09);
	virtual Int slot10();
#undef OBJECT_SLOT

	Player *getControllingPlayer() const;
	Int getBountyValueRva001C9310() const;
	void updateUpgradeModules();
	void setActive(Bool active);
	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0x38);
	}

	Int field23c() const
	{
		return *reinterpret_cast<const Int *>(reinterpret_cast<const char *>(this) + 0x23c);
	}
	UnsignedInt flags94() const
	{
		return *reinterpret_cast<const UnsignedInt *>(reinterpret_cast<const char *>(this) + 0x94);
	}
	Int field214() const
	{
		return *reinterpret_cast<const Int *>(reinterpret_cast<const char *>(this) + 0x214);
	}
};

void j_00020824();
void j_0001cd91();
inline Player *Object::getControllingPlayer() const
{
	typedef Player *(Object::*Query)() const;
	union { void (*raw)(); Query method; } call;
	call.raw = j_00020824;
	return (const_cast<Object *>(this)->*call.method)();
}
inline Int Object::getBountyValueRva001C9310() const
{
	typedef Int (Object::*Query)() const;
	union { void (*raw)(); Query method; } call;
	call.raw = j_0001cd91;
	return (const_cast<Object *>(this)->*call.method)();
}
#pragma comment(linker, "/alternatename:?setActive@Object@@QAEX_N@Z=?j_00008337@@YAXXZ")

class Rva00027D6DMoney
{
public:
	void deposit(UnsignedInt amount, Bool playSound);
};

class ScoreKeeper
{
public:
	void addMoneyEarned(Int amount);
};

class Player
{
public:
	Int adjustBountyForLivingWorld(Int bounty);
	Rva00027D6DMoney *getMoney()
	{
		return reinterpret_cast<Rva00027D6DMoney *>(reinterpret_cast<char *>(this) + 0x48);
	}
	ScoreKeeper *getScoreKeeper()
	{
		return reinterpret_cast<ScoreKeeper *>(reinterpret_cast<char *>(this) + 0x348);
	}
	UnsignedInt color() const
	{
		return *reinterpret_cast<const UnsignedInt *>(reinterpret_cast<const char *>(this) + 0x1c4);
	}
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

class GameLogicPortraitShim
{
public:
	Bool isInMultiplayerOrSkirmishGame();
};
class GameLogic
{
public:
	Object *findObjectByID(Int id);
	void destroyObject(Object *object);
};
class GlobalData;
extern GameLogicPortraitShim *TheBfmeGameLogic;
extern GameLogic *TheGameLogic;
extern PlayerList *Rva002EE330ThePlayers;
extern GlobalData *TheWritableGlobalData;
extern const Real BfmeZeroRange;
extern Real GetGameClientRandomValueReal(Real low, Real high, char *file, Int line);

class InGameUI
{
public:
#define INGAME_UI_SLOT(N) virtual void slot##N() = 0
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

struct Rva0024ED40ModuleData
{
	char pad000[0x74];
	Int field74;
	Int field78;
	Int field7c;
	char pad080[0x128];
	Real bountyScale;
	char pad1ac[0x58];
	Int field204;
	Int field208;
	Int field20c;
	Int field210;
};

class Rva0024ED40Interface
{
public:
#define INTERFACE_SLOT(N) virtual void slot##N() = 0
	INTERFACE_SLOT(00); INTERFACE_SLOT(01); INTERFACE_SLOT(02); INTERFACE_SLOT(03);
	INTERFACE_SLOT(04); INTERFACE_SLOT(05); INTERFACE_SLOT(06); INTERFACE_SLOT(07);
	INTERFACE_SLOT(08); INTERFACE_SLOT(09); INTERFACE_SLOT(10); INTERFACE_SLOT(11);
	INTERFACE_SLOT(12); INTERFACE_SLOT(13); INTERFACE_SLOT(14); INTERFACE_SLOT(15);
	INTERFACE_SLOT(16); INTERFACE_SLOT(17); INTERFACE_SLOT(18); INTERFACE_SLOT(19);
	INTERFACE_SLOT(20); INTERFACE_SLOT(21); INTERFACE_SLOT(22); INTERFACE_SLOT(23);
	INTERFACE_SLOT(24); INTERFACE_SLOT(25); INTERFACE_SLOT(26); INTERFACE_SLOT(27);
	INTERFACE_SLOT(28); INTERFACE_SLOT(29); INTERFACE_SLOT(30); INTERFACE_SLOT(31);
	INTERFACE_SLOT(32); INTERFACE_SLOT(33); INTERFACE_SLOT(34); INTERFACE_SLOT(35);
	INTERFACE_SLOT(36); INTERFACE_SLOT(37); INTERFACE_SLOT(38); INTERFACE_SLOT(39);
	INTERFACE_SLOT(40); INTERFACE_SLOT(41); INTERFACE_SLOT(42); INTERFACE_SLOT(43);
	INTERFACE_SLOT(44); INTERFACE_SLOT(45); INTERFACE_SLOT(46); INTERFACE_SLOT(47);
	INTERFACE_SLOT(48); INTERFACE_SLOT(49); INTERFACE_SLOT(50); INTERFACE_SLOT(51);
	INTERFACE_SLOT(52); INTERFACE_SLOT(53); INTERFACE_SLOT(54); INTERFACE_SLOT(55);
	virtual Bool slot56() = 0;
	INTERFACE_SLOT(57); INTERFACE_SLOT(58); INTERFACE_SLOT(59); INTERFACE_SLOT(60);
	INTERFACE_SLOT(61); INTERFACE_SLOT(62); INTERFACE_SLOT(63); INTERFACE_SLOT(64);
	INTERFACE_SLOT(65); INTERFACE_SLOT(66); INTERFACE_SLOT(67); INTERFACE_SLOT(68);
	INTERFACE_SLOT(69); INTERFACE_SLOT(70); INTERFACE_SLOT(71); INTERFACE_SLOT(72);
	INTERFACE_SLOT(73); INTERFACE_SLOT(74); INTERFACE_SLOT(75); INTERFACE_SLOT(76);
	INTERFACE_SLOT(77); INTERFACE_SLOT(78); INTERFACE_SLOT(79); INTERFACE_SLOT(80);
	INTERFACE_SLOT(81); INTERFACE_SLOT(82); INTERFACE_SLOT(83);
	virtual Int slot84() = 0;
#undef INTERFACE_SLOT
};

class Rva0024ED40PairCall
{
public:
	void set(Object *object);
};

class Rva0002F8DD
{
public:
	void forward(void *argument);
};

class Rva0024ED40AsciiString
{
public:
	char *m_buffer;
	Rva0024ED40AsciiString &operator=(const Rva0024ED40AsciiString &other);
};

class SlaughterHordeContain
{
public:
	Rva0024ED40ModuleData *m_moduleData;
	Object *m_object;
#define CONTAIN_SLOT(N) virtual void slot##N() = 0
	CONTAIN_SLOT(00); CONTAIN_SLOT(01); CONTAIN_SLOT(02); CONTAIN_SLOT(03);
	CONTAIN_SLOT(04); CONTAIN_SLOT(05); CONTAIN_SLOT(06); CONTAIN_SLOT(07);
	CONTAIN_SLOT(08); CONTAIN_SLOT(09); CONTAIN_SLOT(10); CONTAIN_SLOT(11);
	CONTAIN_SLOT(12); CONTAIN_SLOT(13); CONTAIN_SLOT(14); CONTAIN_SLOT(15);
	CONTAIN_SLOT(16); CONTAIN_SLOT(17); CONTAIN_SLOT(18); CONTAIN_SLOT(19);
	CONTAIN_SLOT(20); CONTAIN_SLOT(21); CONTAIN_SLOT(22); CONTAIN_SLOT(23);
	CONTAIN_SLOT(24); CONTAIN_SLOT(25); CONTAIN_SLOT(26);
	virtual Rva0024ED40Interface *getRva0024ED40Interface() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void rva0024ed40(Object *object);

	char pad00c[0xc8];
	Int fieldD4;
	char pad0D8[0x8e4];
	Int m_slaughterCount;
	Rva0024ED40AsciiString m_templateName;
};

void j_00008337();
void j_00001f41();
void j_0002ead2();
void j_0001aa7d();
void j_00014506();
void j_00024d70();
void j_00016b67();
void j_0001f253();
void j_0001d0de();
void j_0001e0ab();
void j_00024938();
void j_00027d6d();
void j_0003a45e();
void j_000389f6();
void j_00009e12();

#pragma comment(linker, "/alternatename:?isInMultiplayerOrSkirmishGame@GameLogicPortraitShim@@QAE_NXZ=?j_0001e0ab@@YAXXZ")
#pragma comment(linker, "/alternatename:?findObjectByID@GameLogic@@QAEPAVObject@@H@Z=?j_0001f253@@YAXXZ")
#pragma comment(linker, "/alternatename:?destroyObject@GameLogic@@QAEXPAVObject@@@Z=?j_0001d0de@@YAXXZ")
#pragma comment(linker, "/alternatename:?unidentified_00024938@Rva000C97C0PlayerThunk@@QAEHH@Z=?j_00024938@@YAXXZ")
#pragma comment(linker, "/alternatename:?deposit@Rva00027D6DMoney@@QAEXI_N@Z=?j_00027d6d@@YAXXZ")
#pragma comment(linker, "/alternatename:?addMoneyEarned@ScoreKeeper@@QAEXH@Z=?j_0003a45e@@YAXXZ")
#pragma comment(linker, "/alternatename:?unidentified_000389f6@Rva002EE330PlayerListThunk@@QAEH_N@Z=?j_000389f6@@YAXXZ")
#pragma comment(linker, "/alternatename:?unidentified_00009e12@Rva00083240Thunk@@QAEHM@Z=?j_00009e12@@YAXXZ")
#pragma comment(linker, "/alternatename:?set@Rva0024ED40PairCall@@QAEXPAVObject@@@Z=?j_00001f41@@YAXXZ")
#pragma comment(linker, "/alternatename:?setActive@Object@@QAEX_N@Z=?j_00008337@@YAXXZ")
#pragma comment(linker, "/alternatename:?operator=@Rva0024ED40AsciiString@@QAEAAV1@ABV1@@Z=?j_00003765@@YAXXZ")

extern "C" __declspec(dllimport) double __cdecl bfmeCeil(double value);
#pragma comment(linker, "/alternatename:?bfmeCeil@@YAMN@Z=__imp_ceil")

void SlaughterHordeContain::rva0024ed40(Object *object)
{
	if (object == 0)
		return;

	Player *owner = m_object->getControllingPlayer();
	if (owner == 0)
		return;

	Int rawBounty = object->getBountyValueRva001C9310();
	if (rawBounty > 0 && m_moduleData->bountyScale > BfmeZeroRange)
	{
		Int bounty = (Int)bfmeCeil((double)((Real)rawBounty * m_moduleData->bountyScale));
		if ((Int)owner != -0x48)
		{
			if (TheBfmeGameLogic->isInMultiplayerOrSkirmishGame())
			{
				Int playerCount = ((Rva002EE330PlayerListThunk *)Rva002EE330ThePlayers)->
					unidentified_000389f6(false);
				Real factor = ((Rva00083240Thunk *)((char *)TheWritableGlobalData + 0xee0))->
					unidentified_00009e12(playerCount);
				bounty = (Int)((Real)bounty * factor);
			}

			bounty = ((Rva000C97C0PlayerThunk *)owner)->unidentified_00024938(bounty);
			bounty = (Int)bfmeCeil((double)bounty);
			owner->getMoney()->deposit((UnsignedInt)bounty, true);
			owner->getScoreKeeper()->addMoneyEarned(bounty);
		}

		UnicodeString moneyString;
		moneyString.format(TheGameText->fetch("GUI:AddCash"), bounty);
		Coord3D position;
		const Coord3D *origin = object->getPosition();
		position.x = origin->x + GetGameClientRandomValueReal(-10.0f, 10.0f,
			(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\SlaughterHordeContain.cpp", 0xf4);
		position.y = origin->y + GetGameClientRandomValueReal(-10.0f, 10.0f,
			(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\SlaughterHordeContain.cpp", 0xf5);
		position.z = origin->z + GetGameClientRandomValueReal(10.0f, 20.0f,
			(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\SlaughterHordeContain.cpp", 0xf6);
		Player *victimOwner = object->getControllingPlayer();
		TheInGameUI->addFloatingText(moneyString, &position,
			victimOwner->color() | 0xe6000000);

		if (m_moduleData->field210 != 0 && object->slot10() != 0)
			object->setActive(true);
	}

	if (object->slot10() != 0)
		object->setActive(true);

	Bool updateAccounting = m_moduleData->bountyScale == BfmeZeroRange;
	if (updateAccounting)
	{
		((Rva0002F8DD *)this)->forward(object);
		Int oldState = fieldD4;
		Int newState = object->field23c();
		if (oldState != newState)
		{
			object->updateUpgradeModules();
			fieldD4 = newState;
		}
		if (oldState == newState)
			object->updateUpgradeModules();
	}

	if ((object->flags94() & 0x20) == 0)
	{
		((Rva0024ED40PairCall *)m_object)->set(object);
		TheGameLogic->destroyObject(object);
	}
	else
	{
		((Rva0024ED40PairCall *)this)->set(object);
	}

	if (updateAccounting)
	{
		if (m_moduleData->field204 != 0)
			((Rva0024ED40Interface *)m_object)->slot56();
		if (m_moduleData->field7c != 0 && m_moduleData->field7c != m_moduleData->field74)
		{
			Object *found = TheGameLogic->findObjectByID(m_moduleData->field7c);
			if (found != 0)
			{
				found->updateUpgradeModules();
				((Rva0024ED40PairCall *)m_object)->set(found);
			}
		}
	}

	Rva0024ED40Interface *interface = getRva0024ED40Interface();
	if (interface != 0 && interface->slot56())
	{
		if (updateAccounting)
		{
			m_slaughterCount = interface->slot84();
			m_templateName = *(Rva0024ED40AsciiString *)((char *)interface + 0x20);
		}
		if (object->field214() != 0)
			TheGameLogic->destroyObject(object);
	}
}
