// ?bfmeRva000A3820@@YAXAAVSkirmishBattleHonors@@@Z
// partial score=0.7 date=2026-09-16
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
// stlport
#include "PreRTS.h"
#include "Common/SkirmishBattleHonors.h"
#include "GameNetwork/GameInfo.h"

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

// The full retail behavior is the endurance-medal tail of the ZH
// updateSkirmishBattleHonors helper.  The address-derived spelling avoids
// claiming the private static helper's unavailable BFME source name.
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
		if (numEasy)
			stats.setEnduranceMedal(TheGameInfo->getMap(), SLOT_EASY_AI,
				max(oldEasy, numEasy + numMedium + numBrutal));
		if (numMedium)
			stats.setEnduranceMedal(TheGameInfo->getMap(), SLOT_MED_AI,
				max(oldMedium, numMedium + numBrutal));
		if (numBrutal)
			stats.setEnduranceMedal(TheGameInfo->getMap(), SLOT_BRUTAL_AI,
				max(oldBrutal, numBrutal));
	}
}
