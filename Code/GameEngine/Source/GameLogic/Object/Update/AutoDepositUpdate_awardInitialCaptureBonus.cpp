// cl: /DNDEBUG /DWIN32 /D_WINDOWS /DZH_EMIT_POOL_GLUE /DBFME_MODULE_NO_MPO /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define Matrix4x4 Matrix4

#include "PreRTS.h"

#include "Common/GlobalData.h"
#include "GameClient/Color.h"
#include "GameClient/GameText.h"
#include "GameLogic/Object.h"

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	UnsignedByte m_pad00[0x3c];
	UnsignedInt m_frame;
};

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

class AutoDepositUpdateModuleData
{
public:
	UnsignedByte m_pad00[8];
	UnsignedInt m_depositFrame;
	Int m_depositAmount;
	Int m_initialCaptureBonus;
};

class AutoDepositUpdateBase
{
public:
	virtual UpdateSleepTime update() = 0;

protected:
	const AutoDepositUpdateModuleData *m_moduleData;
	Object *m_object;
	UnsignedByte m_pad0c[0x14];
};

class AutoDepositUpdate : public AutoDepositUpdateBase
{
public:
	void awardInitialCaptureBonus(Player *player);

	const AutoDepositUpdateModuleData *getAutoDepositUpdateModuleData() const
	{
		return m_moduleData;
	}

	Object *getObject() const
	{
		return m_object;
	}

private:
	UnsignedInt m_depositOnFrame;
	Bool m_awardInitialCaptureBonus;
	Bool m_initialized;
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

extern GameLogicPortraitShim *TheBfmeGameLogic;
class PlayerList;
extern PlayerList *Rva002EE330ThePlayers;
extern GlobalData *TheWritableGlobalData;
extern InGameUI *TheInGameUI;

void AutoDepositUpdate::awardInitialCaptureBonus(Player *player)
{
	m_depositOnFrame = ((GameLogic *)TheBfmeGameLogic)->getFrame() + getAutoDepositUpdateModuleData()->m_depositFrame;
	Int money = 0;
	Player *recipient;
	if (!player)
		return;
	recipient = player;
	if (!m_awardInitialCaptureBonus)
		return;
	if (getAutoDepositUpdateModuleData()->m_initialCaptureBonus <= 0)
		return;

	money = getAutoDepositUpdateModuleData()->m_initialCaptureBonus;
	if (((GameLogicShim *)TheBfmeGameLogic)->unidentified_0001e0ab())
	{
		const Int playerIndex = ((Rva002EE330PlayerListThunk *)Rva002EE330ThePlayers)->unidentified_000389f6(false);
		const float factor = ((Rva00083240Thunk *)((char *)TheWritableGlobalData + 0xee0))->unidentified_00009e12(playerIndex);
		money = (Int)(money * factor);
	}

	money = ((Rva000C97C0PlayerThunk *)recipient)->unidentified_00024938(money);
	((Rva00027D6DMoney *)recipient->getMoney())->unidentified_00027d6d(money, true);
	((Rva0003A45EScoreKeeper *)recipient->getScoreKeeper())->unidentified_0003a45e(money);

	if (getAutoDepositUpdateModuleData()->m_initialCaptureBonus > 0)
	{
		UnicodeString moneyString;
		moneyString.format(TheGameText->fetch("GUI:AddCash"), getAutoDepositUpdateModuleData()->m_initialCaptureBonus);
		Coord3D pos;
		pos.set(getObject()->getPosition());
		pos.z += 10.0f;
		Color color = recipient->getPlayerColor() | GameMakeColor(0, 0, 0, 230);
		TheInGameUI->addFloatingText(moneyString, &pos, color);
	}

	m_awardInitialCaptureBonus = FALSE;
}
