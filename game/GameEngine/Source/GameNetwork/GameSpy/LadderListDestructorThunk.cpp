// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "PreRTS.h"
#include "GameNetwork/GameSpy/ThreadUtils.h"
#include "GameNetwork/GameSpy/LadderDefs.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/GSConfig.h"
#include "Common/GameState.h"
#include "Common/File.h"
#include "Common/FileSystem.h"
#include "Common/PlayerTemplate.h"
#include "GameClient/GameText.h"
#include "GameClient/MapUtil.h"

// The destructor at retail 0x0062AB10 removes each LadderInfo pointer from the
// three list members. The LadderList declaration supplies the exact STLport
// node layout, and the matched constructor confirms the owner.
LadderList::~LadderList()
{
	LadderInfoList::iterator it;
	for (it = m_specialLadders.begin(); it != m_specialLadders.end(); it = m_specialLadders.begin())
	{
		delete *it;
		m_specialLadders.pop_front();
	}
	for (it = m_standardLadders.begin(); it != m_standardLadders.end(); it = m_standardLadders.begin())
	{
		delete *it;
		m_standardLadders.pop_front();
	}
	for (it = m_localLadders.begin(); it != m_localLadders.end(); it = m_localLadders.begin())
	{
		delete *it;
		m_localLadders.pop_front();
	}
}
