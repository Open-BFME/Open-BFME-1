// ?update@WaypointMap@@QAEXXZ
// partial score=0.8634 date=2026-10-02
// cl: /DBFME_STLP_NODE_ALLOC /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
#include "ascii_string.h"
#define ASCIISTRING_H
// Bank for RVA 0x00454EF0, complete 366-byte retail body ending ret +0x16D.
// Canonical AsciiString restores the ESP EH frame and the by-value format
// temporary. By-reference max and caching only the first source map recover
// the correct size: 366 bytes, 50 non-relocation differences, shape 0.992.
// Remaining: this/zero/iterator register coloring and push-EDI scheduling.
// Self alias, earlier iterator declaration, mutable iterator, pointer-select
// max, and earlier map-cache definition did not improve it. The complete
// owning TU with static m_waypoints is worse (376 bytes, 195 differences).
// Before landing, verify the native map operator[] route independently;
// its ledger body still uses Rva000C0D00Value/Rva000C0D00Less.
#include "PreRTS.h"
#include "GameClient/MapUtil.h"
#include "Common/NameKeyGenerator.h"
#include "Common/WellKnownKeys.h"

extern WaypointMap *m_waypoints;

void WaypointMap::update( void )
{
	if (!m_waypoints)
	{
		m_numStartSpots = 1;
		return;
	}

	this->clear();

	AsciiString startingCamName = TheNameKeyGenerator->keyToName(TheKey_InitialCameraPosition);
	WaypointMap::const_iterator it;

	WaypointMap *firstWaypoints = m_waypoints;
	it = firstWaypoints->find(startingCamName);
	if (it != firstWaypoints->end())
	{
		(*this)[startingCamName] = it->second;
	}

	m_numStartSpots = 0;
	for (Int i = 0; i < 8; ++i)
	{
		startingCamName.format("Player_%d_Start", i + 1);
		it = m_waypoints->find(startingCamName);
		if (it != m_waypoints->end())
		{
			(*this)[startingCamName] = it->second;
			++m_numStartSpots;
		}
		else
		{
			break;
		}
	}

	m_numStartSpots = (_STL::max)(m_numStartSpots, 1);
}
