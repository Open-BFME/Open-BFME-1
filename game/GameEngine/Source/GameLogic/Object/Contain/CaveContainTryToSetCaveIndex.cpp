// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "Common/TunnelTracker.h"
#include "GameLogic/Module/CaveContain.h"
#include "GameLogic/CaveSystem.h"
#include "GameLogic/Object.h"

void CaveContain::tryToSetCaveIndex(Int newIndex)
{
	if (TheCaveSystem->canSwitchIndexToIndex(m_caveIndex, newIndex)) {
		TunnelTracker *oldTracker = TheCaveSystem->getTunnelTrackerForCaveIndex(m_caveIndex);
		TheCaveSystem->unregisterCave(m_caveIndex);
		oldTracker->onTunnelDestroyed(*(Object **)((unsigned)this + 0x5cc));

		m_caveIndex = newIndex;
		TheCaveSystem->registerNewCave(m_caveIndex);
		TunnelTracker *newTracker = TheCaveSystem->getTunnelTrackerForCaveIndex(m_caveIndex);
		newTracker->onTunnelCreated(*(Object **)((unsigned)this + 0x5cc));
	}
}
