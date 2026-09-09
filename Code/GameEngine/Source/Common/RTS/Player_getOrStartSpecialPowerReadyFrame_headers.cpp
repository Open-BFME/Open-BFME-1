// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /D_STLP_USE_STATIC_LIB /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define BFME_STLP_NODE_ALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"
#include "Common/GameState.h"
#include "Common/Player.h"
#include "Common/SpecialPower.h"

struct BfmePlayerReadyTimerFields
{
	unsigned char m_unreconstructed_000[0x650];
	std::list<SpecialPowerReadyTimerType> m_specialPowerReadyTimerList;
};

struct BfmeGameLogicFrameSlice
{
	unsigned char m_unreconstructed_000[0x3c];
	UnsignedInt m_bfmeFrame;
};

class GameLogic;
extern GameLogic *TheBfmeGameLogic;

UnsignedInt Player::getOrStartSpecialPowerReadyFrame(const SpecialPowerTemplate *temp)
{
	BfmePlayerReadyTimerFields *self = (BfmePlayerReadyTimerFields *)this;
	UnsignedInt lookupID = temp->getID();
	UnsignedInt now = ((BfmeGameLogicFrameSlice *)TheBfmeGameLogic)->m_bfmeFrame;

	SpecialPowerReadyTimerType *timer;
	std::list<SpecialPowerReadyTimerType>::iterator it;
	for (it = self->m_specialPowerReadyTimerList.begin();
		it != self->m_specialPowerReadyTimerList.end(); ++it)
	{
		timer = &(*it);
		if (timer->m_templateID == lookupID)
			return timer->m_readyFrame;
	}

	SpecialPowerReadyTimerType newTimer;
	newTimer.m_templateID = temp->getID();
	newTimer.m_readyFrame = now;
	self->m_specialPowerReadyTimerList.push_back(newTimer);
	return now;
}
