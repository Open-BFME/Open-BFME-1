// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// AIStates.cpp
// Implementation of AI behavior states
// Author: Michael S. Booth, January 2002
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ActionManager.h"
#include "Common/AudioHandleSpecialValues.h"
#include "Common/CRCDebug.h"
#include "Common/GameAudio.h"
#include "Common/GlobalData.h"
#include "Common/Money.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/RandomValue.h"
#include "Common/Team.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/Xfer.h"
#include "Common/XFerCRC.h"

#include "GameClient/ControlBar.h"
#include "GameClient/FXList.h"
#include "GameClient/InGameUI.h"

#include "GameLogic/AIDock.h"
#include "GameLogic/AIGuard.h"
#include "GameLogic/AIGuardRetaliate.h"
#include "GameLogic/AITNGuard.h"
#include "GameLogic/AIStateMachine.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/PolygonTrigger.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Squad.h"
#include "GameLogic/TurretAI.h"
#include "GameLogic/Weapon.h"

#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/JetAIUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/StealthUpdate.h"
extern bool Glo012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);
typedef void (__cdecl *BfmeCritterDesyncLog)(void *, const char *);
// AIFollowWaypointPathState::computeGoal, retail RVA 0x0017A600, 586 bytes.
// Identity: named update/onEnter callers reach this body through their ILT;
// the calcExtraPathDistance call and witnessed fields +0x50/+0x60/+0x64
// agree with the Zero Hour computeGoal twin. Retail adds rotation via
// ILT 0x0003D104 but omits ZH wall handling and boundary clamping.
// Rotation mutates a local copy of m_groupOffset. The default prior point
// is dest minus one on X; a prior waypoint replaces it, otherwise a next
// waypoint replaces the destination reference. All formation paths rotate.
// BFME kind value 0x19 and terrain virtual slots +0x18/+0x30 differ from ZH.
extern void j_0003d104(void);
typedef void (__cdecl *BfmeRotateGroupOffset)(const Coord3D *farPoint, const Coord3D *nearPoint, Coord2D *groupOffset);
extern float g_bfmeDefaultBU;					///< retail 0x01075334

struct BFMEObjectFormationField
{
	unsigned char m_unreconstructed_000[0x31c];
	Int m_formationID;					///< retail this+0x31c
};

// Retail receiver views: State machine +0x1c; Object AI +0x204.
// These are distinct from the inherited Zero Hour header layouts.
struct BFMEFollowStateMachineFields
{
	unsigned char m_unreconstructed_000[0x10];
	Object *m_owner;					///< retail this+0x10
};

struct BFMEFollowStateFields
{
	unsigned char m_unreconstructed_000[0x1c];
	BFMEFollowStateMachineFields *m_machine;		///< retail this+0x1c
};

struct BFMEFollowStateObject
{
	unsigned char m_unreconstructed_000[0x204];
	AIUpdateInterface *m_ai;				///< retail this+0x204
};

class Follow17A600DistanceSlot { public: void set(float); };
extern void j_0000ebab();
class Follow17A600Locomotor { public: unsigned char pad[0x40]; unsigned flags; void setUsePreciseZPos(bool v) { if(v) flags |= 8; else flags &= ~8; } void setAllowInvalidPosition(bool v) { if(v) flags |= 2; else flags &= ~2; } };
// BFME terrain virtual slots measured at 0x0017A7C3 and 0x0017A7D6.
class Follow17A600Terrain {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0c(); virtual void slot10(); virtual void slot14();
 virtual Real getGroundHeight(Real x, Real y, void *normal = 0);
 virtual void slot1c(); virtual void slot20(); virtual void slot24();
 virtual void slot28(); virtual void slot2c();
 virtual void getMaximumPathfindExtent(Region3D *);
};
void AIFollowWaypointPathState::computeGoal(Bool useGroupOffsets)
{
	if (m_currentWaypoint == NULL)
		return;

	Object *obj = ((BFMEFollowStateFields *)this)->m_machine->m_owner;
	AIUpdateInterface *ai = ((BFMEFollowStateObject *)obj)->m_ai;
	Coord3D dest;
	dest.x = m_currentWaypoint->getLocation()->x;
	dest.y = m_currentWaypoint->getLocation()->y;
	dest.z = m_currentWaypoint->getLocation()->z;

	m_goalLayer = LAYER_GROUND; // waypoints are always on the ground.

	typedef void (Follow17A600DistanceSlot::*Setter)(Real);
	void (*distanceEntry)() = j_0000ebab;
	Setter distanceSetter = *reinterpret_cast<Setter *>(&distanceEntry);
	(reinterpret_cast<Follow17A600DistanceSlot *>(ai)->*distanceSetter)(calcExtraPathDistance());
	if (*(const Int *)((const char *)m_currentWaypoint + 0x4c) > 0) {
		// We are in the middle of a path, so don't set the final goal location yet.
		if (Glo012F0239 && g_012ED4FC)
		{
			((BfmeCritterDesyncLog)j_0003a17a)(g_012ED4FC,
				"CritterDesync: setAdjustDestination(FALSE) 51");
		}
		setAdjustsDestination(false);
	} else {
		if (Glo012F0239 && g_012ED4FC)
		{
			((BfmeCritterDesyncLog)j_0003a17a)(g_012ED4FC,
				"CritterDesync: setAdjustDestination(TRUE) 52");
		}
		setAdjustsDestination(true);
		// urg. hacky. if we are a projectile on the last segment, turn on precise z-pos.
		if (obj->isKindOf((KindOfType)0x19))
		{
			if (ai && (*(Follow17A600Locomotor **)((char *)ai + 0x1cc)))
				(*(Follow17A600Locomotor **)((char *)ai + 0x1cc))->setUsePreciseZPos(true);
		}
	}

	Coord2D groupOffset = m_groupOffset;
	if (((BFMEObjectFormationField *)obj)->m_formationID)
	{
		Coord3D nearPoint; nearPoint.set(&dest);
		Coord3D farPoint; farPoint.set(&dest);
		farPoint.x -= g_bfmeDefaultBU;
		if (m_priorWaypoint) {
			farPoint = *m_priorWaypoint->getLocation();
		} else if (m_currentWaypoint->getLink(0)) {
			farPoint = nearPoint;
			nearPoint = *m_currentWaypoint->getLink(0)->getLocation();
		}
		((BfmeRotateGroupOffset)j_0003d104)(&farPoint, &nearPoint, &groupOffset);
	}

	m_goalPosition = dest;
	m_goalPosition.x += groupOffset.x;
	m_goalPosition.y += groupOffset.y;
	m_goalPosition.z = ((Follow17A600Terrain *)TheTerrainLogic)->getGroundHeight(m_goalPosition.x, m_goalPosition.y);

	Region3D extent;
	((Follow17A600Terrain *)TheTerrainLogic)->getMaximumPathfindExtent(&extent);



	if (!extent.isInRegionNoZ(&m_goalPosition)) {
		if (Glo012F0239 && g_012ED4FC)
		{
			((BfmeCritterDesyncLog)j_0003a17a)(g_012ED4FC,
				"CritterDesync: setAdjustDestination(FALSE) 53");
		}
		setAdjustsDestination(false); // moving off the map.
		(*(Follow17A600Locomotor **)((char *)ai + 0x1cc))->setAllowInvalidPosition(true); // allow it to move off the map.
		m_appendGoalPosition = true; // Moving off the map.
	}
}

