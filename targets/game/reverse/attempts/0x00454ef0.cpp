// ?update@WaypointMap@@QAEXXZ
// partial score=0.78 date=2026-09-10
// Body from the owning MapUtil.cpp probe; retail is 366 bytes at
// 0x00454EF0 and ends at the ret at 0x0045505D.
//
// New lever tried: keep the method in the owning TU so the internal
// m_waypoints object is the real MapUtil object, while using the established
// WaypointMap/STLport and AsciiString declarations.  This preserves the
// canonical algorithm and its by-value temporary lifetime, but the compiler
// still selects alternate unresolved callee candidates and omits the retail
// ESP SEH frame.

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

	it = m_waypoints->find(startingCamName);
	if (it != m_waypoints->end())
	{
		(*this)[startingCamName] = it->second;
	}

	m_numStartSpots = 0;
	for (Int i = 0; i < MAX_SLOTS; ++i)
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

	m_numStartSpots = max(1, m_numStartSpots);
}
