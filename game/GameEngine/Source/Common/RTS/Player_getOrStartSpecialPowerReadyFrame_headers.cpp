// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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
