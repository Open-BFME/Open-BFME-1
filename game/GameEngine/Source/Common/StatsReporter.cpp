// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "PreRTS.h"
#include "Common/SkirmishBattleHonors.h"

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

class GameSlot
{
public:
	bool isAI() const;
	Int getTeamNumber() const
	{
		return *(const Int *)((const char *)this + 0x18);
	}
	SlotState getState() const
	{
		return (SlotState)*(const Int *)((const char *)this + 4);
	}
};

class GameInfo
{
public:
	const GameSlot *getConstSlot(Int slotNum) const;
	AsciiString getMap() const;
	int _bfme_getMapIsOfficial() const;
};

extern GameInfo *TheGameInfo;

enum
{
	MAX_SLOTS = 8
};

template <class T>
inline const T &bfmeMaxRef(const T &left, const T &right)
{
	return left > right ? left : right;
}

class BfmeGameInfoVirtualSlots
{
public:
	virtual void unused0() = 0;
	virtual void unused1() = 0;
	virtual void unused2() = 0;
	virtual void unused3() = 0;
	virtual void unused4() = 0;
	virtual Int getLocalSlotNum() = 0;
};

static Bool bfmeIsSlotLocalAlly(GameInfo *game, const GameSlot *slot)
{
	const GameSlot *localSlot = game->getConstSlot(
		reinterpret_cast<BfmeGameInfoVirtualSlots *>(game)->getLocalSlotNum());
	if (!localSlot)
		return TRUE;
	if (slot == localSlot)
		return TRUE;
	if (slot->getTeamNumber() < 0)
		return FALSE;
	return slot->getTeamNumber() == localSlot->getTeamNumber();
}

// BFME's endurance-medal update helper.  The address-derived spelling keeps
// the private retail helper's unavailable source identity explicit.
void bfmeRva000A3820(SkirmishBattleHonors &stats)
{
	Int numEasy = 0;
	Int numMedium = 0;
	Int numBrutal = 0;
	Bool anyAlliedAI = FALSE;
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		const GameSlot *slot = TheGameInfo->getConstSlot(i);
		if (slot->isAI() && !bfmeIsSlotLocalAlly(TheGameInfo, slot))
		{
			if (TheGameInfo->getConstSlot(i)->getState() == SLOT_EASY_AI)
				++numEasy;
			if (TheGameInfo->getConstSlot(i)->getState() == SLOT_MED_AI)
				++numMedium;
			if (TheGameInfo->getConstSlot(i)->getState() == SLOT_BRUTAL_AI)
				++numBrutal;
		}
		else if (slot->isAI())
		{
			anyAlliedAI = TRUE;
		}
	}
	if (!anyAlliedAI && (numEasy || numMedium || numBrutal))
	{
		Int oldEasy = stats.getEnduranceMedal(TheGameInfo->getMap(), SLOT_EASY_AI);
		Int oldMedium = stats.getEnduranceMedal(TheGameInfo->getMap(), SLOT_MED_AI);
		Int oldBrutal = stats.getEnduranceMedal(TheGameInfo->getMap(), SLOT_BRUTAL_AI);
		if (TheGameInfo->_bfme_getMapIsOfficial() - 1 == numBrutal)
		{
			stats.setEnduranceMedal(TheGameInfo->getMap(), SLOT_PLAYER,
				bfmeMaxRef(oldBrutal, numBrutal));
		}
		else if (numBrutal)
		{
			stats.setEnduranceMedal(TheGameInfo->getMap(), SLOT_BRUTAL_AI,
				bfmeMaxRef(oldBrutal, numBrutal));
		}
		else if (numMedium)
		{
			stats.setEnduranceMedal(TheGameInfo->getMap(), SLOT_MED_AI,
				bfmeMaxRef(oldMedium, numMedium + numBrutal));
		}
		else if (numEasy)
		{
			stats.setEnduranceMedal(TheGameInfo->getMap(), SLOT_EASY_AI,
				bfmeMaxRef(oldEasy, numEasy + numMedium + numBrutal));
		}
	}
}
