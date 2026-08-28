// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// readable body of ?calcExtraPathDistance@AIFollowWaypointPathState@@IAEMXZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
#define Matrix4x4 Matrix4  // BFME renamed it

// Open-BFME5: AIFollowWaypointPathState::calcExtraPathDistance, isolated.
//
// The vendored Zero Hour Waypoint declaration (GameLogic/TerrainLogic.h, MAX_LINKS=8)
// does not match this build's real layout: retail reads the link count from
// [waypoint+0x4c] and the first link pointer from [waypoint+0x20], where the
// vendored header/shim would put them at +0x3c and +0x1c respectively (confirmed by
// byte-for-byte compiling the reference body verbatim against retail 0x0016C500 -- every
// byte matched except those two field loads). That is consistent with retail's Waypoint
// carrying a larger link table (and/or an extra member ahead of it) than ZH's. Rather
// than assert a specific wrong-but-plausible replacement class shape, this thunk reads
// those two fields directly at their disassembly-confirmed byte offsets and otherwise
// keeps the reference logic (including Coord2D::length(), whose offsets 0xc/0x10 for
// m_location already matched retail exactly) untouched.
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameLogic/AIStateMachine.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/TerrainLogic.h"

// ?calcExtraPathDistance@AIFollowWaypointPathState@@IAEMXZ
Real AIFollowWaypointPathState::calcExtraPathDistance(void)
{
	Real extra = PATHFIND_CELL_SIZE_F/10.0f;
	const Waypoint *curWay = m_currentWaypoint;
	Int limit = 5; // just look ahead 5, in case of circular paths.  jba
	while (curWay && limit>0) {
		limit--;
		const unsigned char *curWayRaw = (const unsigned char *)curWay;
		Int linkCount = *(const Int *)(curWayRaw + 0x4c);
		if (linkCount == 0) return extra;
		const Waypoint *nextWay = *(const Waypoint * const *)(curWayRaw + 0x20);
		Coord2D delta;
		delta.x = nextWay->getLocation()->x - curWay->getLocation()->x;
		delta.y = nextWay->getLocation()->y - curWay->getLocation()->y;
		extra += delta.length();
		curWay = nextWay;
	}
	return extra;
}
