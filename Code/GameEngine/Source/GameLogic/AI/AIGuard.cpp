// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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


// FILE: AIGuard.cpp 
/*---------------------------------------------------------------------------*/
/* EA Pacific                                                                */
/* Confidential Information	                                                 */
/* Copyright (C) 2001 - All Rights Reserved                                  */
/* DO NOT DISTRIBUTE                                                         */
/*---------------------------------------------------------------------------*/
/* Project:    RTS3                                                          */
/* File name:  AIGuard.cpp                                                   */
/* Created:    John K. McDonald, Jr., 3/29/2002                              */
/* Desc:       // Set up guard states for AI                                 */
/* Revision History:                                                         */
/*		3/29/2002 : Initial creation                                           */
/*---------------------------------------------------------------------------*/
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:

#include "Common/PerfTimer.h"
#include "Common/Team.h"
#include "Common/Xfer.h"
#include "Common/ThingTemplate.h"
#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/AIGuard.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/CollideModule.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/PolygonTrigger.h"

const Real CLOSE_ENOUGH = (25.0f);

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

static Bool hasAttackedMeAndICanReturnFire( State *thisState, void* /*userData*/ )
{
	Object *obj = thisState->getMachineOwner();
	BodyModuleInterface *bmi = obj ? obj->getBodyModule() : NULL;

	if (!(obj && bmi)) {
		return FALSE;
	}

	if (bmi->getClearableLastAttacker() == INVALID_ID) {
		return FALSE;
	}

	// K. It appears we have a valid aggressor. Find it, and determine if we can attack it, etc.
	Object *target = TheGameLogic->findObjectByID(bmi->getClearableLastAttacker());
	bmi->clearLastAttacker();

	// We use the clearable last attacker because we should continue attacking the guy. But if he 
	// stops attacking us, then we want our timer to kick us off of him and make us go attack 
	// other units instead.
	

	if (!target) {
		return FALSE;
	}

	if (obj->getRelationship(target) != ENEMIES) {
		return FALSE;
	}

	// This is a quick test on the target. It will be duplicated in getAbleToAttackSpecificObject, 
	// but the payoff is worth the duplication.
	if (target->isEffectivelyDead()) {
		return FALSE;
	}

	//@todo: Get this out of here. Move it into the declaration of calling this function, or figure
	// out some way to call it less often.

	if (!obj->isAbleToAttack()) {
		return FALSE;
	}

	CanAttackResult result = obj->getAbleToAttackSpecificObject(ATTACK_NEW_TARGET, target, CMD_FROM_AI);
	if( result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING )
	{
		return TRUE;
	}
	return FALSE;
}

//-- ExitConditions -------------------------------------------------------------------------------
/**
 * This returns true if the conditions specified have been met, false otherwise.
 */
// ?shouldExit@ExitConditions@@ present-unmatched
Bool ExitConditions::shouldExit(const StateMachine* machine) const
{
	if (!machine->getGoalObject()) 
	{
		if (m_conditionsToConsider & ATTACK_ExitIfNoUnitFound) 
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (m_conditionsToConsider & ATTACK_ExitIfExpiredDuration) 
	{
		if (TheGameLogic->getFrame() >= m_attackGiveUpFrame)
		{
			return true;
		} 
	}
	
	if (m_conditionsToConsider & ATTACK_ExitIfOutsideRadius) 
	{
		Coord3D deltaAggressor;
		Coord3D objPos = *machine->getGoalObject()->getPosition();
		deltaAggressor.x = objPos.x - m_center.x;
		deltaAggressor.y = objPos.y - m_center.y;
	//	deltaAggressor.z = objPos.z - m_center.z;
		deltaAggressor.z = 0; // BGC - when we search for a target we don't account for Z, so why should we here?
													// changing this fixed a crash where a GLARebelInfantry would be in GuardReturnState, find
													// a target that is within range, then not be able to attack because its actually out of range.
													// then it would look for a new target, get the same one, and proceed in an infinite recursive
													// loop that eventually blew the stack.

		if (deltaAggressor.lengthSqr() > m_radiusSqr) 
		{
			return true;
		} 
	}

	return false;
}


//-- AIGuardMachine -------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// ??0AIGuardMachine@@QAE@PAVObject@@@Z
// Body in Code/masm_dumps/_sa___0AIGuardMachine___15D1D0.asm (exact 691B retail @ 0x15D1D0).
//--------------------------------------------------------------------------------------
// Lifting that constructor out took every newInstance() call in this file with
// it, and with them the pool operator new and operator delete these six state
// classes emit. Twelve claims still name this file for those two folded bodies
// at 0x3FD696 and 0x7EFFF0, and no other object in the tree defines them, so
// the calls have to stay here. Nothing calls this, and the linker drops it.
//--------------------------------------------------------------------------------------
void AIGuardStatePoolGlue( AIGuardMachine *machine )
{
	newInstance(AIGuardInnerState)( machine );
	newInstance(AIGuardReturnState)( machine );
	newInstance(AIGuardIdleState)( machine );
	newInstance(AIGuardOuterState)( machine );
	newInstance(AIGuardPickUpCrateState)( machine );
	newInstance(AIGuardAttackAggressorState)( machine );
}
//--------------------------------------------------------------------------------------
// ??1AIGuardMachine@@ present-unmatched
AIGuardMachine::~AIGuardMachine()
{
}

//--------------------------------------------------------------------------------------
/*static*/ Real AIGuardMachine::getStdGuardRange(const Object* obj)
{
	Real visionRange = TheAI->getAdjustedVisionRangeForObject(obj, 
		AI_VISIONFACTOR_OWNERTYPE | AI_VISIONFACTOR_MOOD | AI_VISIONFACTOR_GUARDINNER);

	return visionRange;
}

//--------------------------------------------------------------------------------------
// ?lookForInnerTarget@AIGuardMachine@@ present-unmatched
Bool AIGuardMachine::lookForInnerTarget(void)
{
	Object* owner = getOwner();
	if (!owner->isAbleToAttack())
	{
		return false;	// my, that was easy
	}

	// Check if team auto targets same victim.
	Object *teamVictim = NULL;
	if (owner->getTeam()->getPrototype()->getTemplateInfo()->m_attackCommonTarget) 
	{
		teamVictim = owner->getTeam()->getTeamTargetObject();
		if (teamVictim) 
		{
			setNemesisID(teamVictim->getID());
			return true;	// Transitions to AIGuardInnerState.
		}
	}

	Object* targetToGuard = findTargetToGuardByID();
	Coord3D pos = targetToGuard ? *targetToGuard->getPosition() : *getPositionToGuard();

	const PolygonTrigger*								area = getAreaToGuard();
	PartitionFilterRelationship					f1(owner, PartitionFilterRelationship::ALLOW_ENEMIES);
	PartitionFilterPossibleToAttack			f2(ATTACK_NEW_TARGET, owner, CMD_FROM_AI);
	PartitionFilterSameMapStatus				filterMapStatus(owner);
	PartitionFilterPolygonTrigger				f3(area);
	PartitionFilterIsFlying							f4;
	PartitionFilterRelationship					f5(owner, PartitionFilterRelationship::ALLOW_NEUTRAL);
	PartitionFilterPossibleToEnter			f6(owner, CMD_FROM_AI);
	PartitionFilterPossibleToHijack			f7(owner, CMD_FROM_AI);

	PartitionFilter *filters[16];
	Int count = 0;

	// Enter Guard state
	if (owner->getTemplate()->isEnterGuard())
	{
		filters[count++] = &f6;

		// Hijack Guard state
		if (owner->getTemplate()->isHijackGuard())
		{
			filters[count++] = &f1;
			filters[count++] = &f7;
		}
		else
		{
			filters[count++] = &f5;
		}
	}
	// Attack Guard state
	else
	{
		filters[count++] = &f1;
		filters[count++] = &f2;
	}

	filters[count++] = &filterMapStatus;

	Real visionRange = AIGuardMachine::getStdGuardRange(owner);

	if (area) 
	{
		UnsignedInt checkFrame = TheGameLogic->getFrameObjectsChangedTriggerAreas()+TheAI->getAiData()->m_guardEnemyScanRate;
		if (TheGameLogic->getFrame()>checkFrame) {
			return false; 
		}
		filters[count++] = &f3;
		visionRange = area->getRadius();
		area->getCenterPoint(&pos);
	}

	if (getGuardMode() == GUARDMODE_GUARD_FLYING_UNITS_ONLY) 
	{
		// only consider flying targets
		filters[count++] = &f4;
	}

	filters[count++] = NULL;

//	SimpleObjectIterator* iter = ThePartitionManager->iterateObjectsInRange(
//					&pos, visionRange, FROM_CENTER_2D, filters, ITER_SORTED_NEAR_TO_FAR);
//	MemoryPoolObjectHolder hold(iter);
//	Object* target = iter->first();
//
// srj sez: the above code is stupid and slow. since we only want the closest object,
// just ask for that; the above has to find ALL objects in range, but we ignore all 
// but the first (closest).
//
	Object* target = ThePartitionManager->getClosestObject(&pos, visionRange, FROM_CENTER_2D, filters);
	if (target) 
	{
		setNemesisID(target->getID());	
		return true;	// Transitions to AIGuardInnerState.
	}
	else
	{
		return false;
	}
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@AIGuardMachine@@ present-unmatched
void AIGuardMachine::crc( Xfer *xfer )
{
}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ?xfer@AIGuardMachine@@ present-unmatched
void AIGuardMachine::xfer( Xfer *xfer )
{
  // version
  XferVersion currentVersion = 2;
  XferVersion version = currentVersion;
  xfer->xferVersion( &version, currentVersion );

	if (version>=2) {
// ?xfer@StateMachine@@ present-unmatched
		StateMachine::xfer(xfer);	// Forgot this in initial implementation.  jba.
	}

	xfer->xferObjectID(&m_targetToGuard);
	xfer->xferObjectID(&m_nemesisToAttack);
	xfer->xferCoord3D(&m_positionToGuard);

	AsciiString triggerName;
	if (m_areaToGuard) triggerName = m_areaToGuard->getTriggerName();
	xfer->xferAsciiString(&triggerName);
	if (xfer->getXferMode() == XFER_LOAD)
	{
		if (triggerName.isNotEmpty()) {
			m_areaToGuard = TheTerrainLogic->getTriggerAreaByName(triggerName);
		}
	} 

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@AIGuardMachine@@ present-unmatched
void AIGuardMachine::loadPostProcess( void )
{
}  // end loadPostProcess

//-- AIGuardInnerState ----------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@AIGuardInnerState@@ present-unmatched
void AIGuardInnerState::crc( Xfer *xfer )
{
}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ?xfer@AIGuardInnerState@@ present-unmatched
void AIGuardInnerState::xfer( Xfer *xfer )
{
  // version
  XferVersion currentVersion = 1;
  XferVersion version = currentVersion;
  xfer->xferVersion( &version, currentVersion );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@AIGuardInnerState@@ present-unmatched
void AIGuardInnerState::loadPostProcess( void )
{
	onEnter();
}  // end loadPostProcess

//--------------------------------------------------------------------------------------
// ?onEnter@AIGuardInnerState@@ present-unmatched
StateReturnType AIGuardInnerState::onEnter( void )
{
	// See if we try to enter the target
	if (getMachineOwner()->getTemplate()->isEnterGuard())
	{
		Object* nemesis = TheGameLogic->findObjectByID(getGuardMachine()->getNemesisID()) ;
		if (nemesis == NULL) 
		{
			DEBUG_LOG(("Unexpected NULL nemesis in AIGuardInnerState.\n"));
			return STATE_SUCCESS;
		}
		m_enterState = newInstance(AIEnterState)(getMachine());

		m_enterState->getMachine()->setGoalObject(nemesis);

		StateReturnType returnVal = m_enterState->onEnter();
		if (returnVal == STATE_CONTINUE) {
			return STATE_CONTINUE;
		}
	}
	// Or try to destroy the target
	else
	{
		Object* targetToGuard = getGuardMachine()->findTargetToGuardByID();
		Coord3D pos = targetToGuard ? *targetToGuard->getPosition() : *getGuardMachine()->getPositionToGuard();
		Object* nemesis = TheGameLogic->findObjectByID(getGuardMachine()->getNemesisID()) ;
		if (nemesis == NULL) 
		{
			DEBUG_LOG(("Unexpected NULL nemesis in AIGuardInnerState.\n"));
			return STATE_SUCCESS;
		}
		m_exitConditions.m_center = pos;
		m_exitConditions.m_radiusSqr = sqr(AIGuardMachine::getStdGuardRange(getMachineOwner()));
		m_exitConditions.m_conditionsToConsider = (ExitConditions::ATTACK_ExitIfOutsideRadius | 
																								ExitConditions::ATTACK_ExitIfNoUnitFound);

		m_attackState = newInstance(AIAttackState)(getMachine(), false, true, false, &m_exitConditions);

		m_attackState->getMachine()->setGoalObject(nemesis);

		StateReturnType returnVal = m_attackState->onEnter();
		if (returnVal == STATE_CONTINUE) {
			return STATE_CONTINUE;
		}
	}

	// if we had no one to attack, we were successful, so go to the next state.
	return STATE_SUCCESS;
}

//--------------------------------------------------------------------------------------
// ?update@AIGuardInnerState@@ present-unmatched
StateReturnType AIGuardInnerState::update( void )
{
	if (m_attackState)
	{
		// if the position has moved (IE we're guarding an object), move with it.
		Object* targetToGuard = getGuardMachine()->findTargetToGuardByID();
		if (targetToGuard) 
		{
			m_exitConditions.m_center = *targetToGuard->getPosition();
		}
		
		return m_attackState->update();
	}
	else if (m_enterState)
	{
		return m_enterState->update();
	}

	return STATE_SUCCESS;
}

//--------------------------------------------------------------------------------------
// ?onExit@AIGuardInnerState@@ present-unmatched
void AIGuardInnerState::onExit( StateExitType status )
{
	Object *obj = getMachineOwner();
	if (m_attackState) 
	{
		m_attackState->onExit(status);
		m_attackState->deleteInstance();
		m_attackState = NULL;
	}
	else if (m_enterState)
	{
		m_enterState->onExit(status);
		m_enterState->deleteInstance();
		m_enterState = NULL;
	}
	
	if (obj->getTeam()) 
	{
		obj->getTeam()->setTeamTargetObject(NULL); // clear the target.
	}
}

//-- AIGuardOuterState ----------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@AIGuardOuterState@@ present-unmatched
void AIGuardOuterState::crc( Xfer *xfer )
{
}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ?xfer@AIGuardOuterState@@ present-unmatched
void AIGuardOuterState::xfer( Xfer *xfer )
{
  // version
  XferVersion currentVersion = 1;
  XferVersion version = currentVersion;
  xfer->xferVersion( &version, currentVersion );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@AIGuardOuterState@@ present-unmatched
void AIGuardOuterState::loadPostProcess( void )
{						 AIGuardOuterState
	onEnter();
}  // end loadPostProcess

//--------------------------------------------------------------------------------------
// ?onEnter@AIGuardOuterState@@ present-unmatched
StateReturnType AIGuardOuterState::onEnter( void )
{
	if (getGuardMachine()->getGuardMode() == GUARDMODE_GUARD_WITHOUT_PURSUIT)
	{
		// "patrol" mode does not follow targets outside the guard area.
		return STATE_SUCCESS;
	}

	Object* targetToGuard = getGuardMachine()->findTargetToGuardByID();
	Coord3D pos = targetToGuard ? *targetToGuard->getPosition() : *getGuardMachine()->getPositionToGuard();

	Object* nemesis = TheGameLogic->findObjectByID(getGuardMachine()->getNemesisID()) ;
	if (nemesis == NULL) 
	{
		DEBUG_LOG(("Unexpected NULL nemesis in AIGuardInnerState.\n"));
		return STATE_SUCCESS;
	}
	Object *obj = getMachineOwner();

	Real range = TheAI->getAdjustedVisionRangeForObject(obj, AI_VISIONFACTOR_OWNERTYPE | AI_VISIONFACTOR_MOOD);

	const PolygonTrigger *area = getGuardMachine()->getAreaToGuard();
	if (area) 
	{
		if (range < area->getRadius()) 
			range = area->getRadius();
		area->getCenterPoint(&pos);
	}
	m_exitConditions.m_center = pos;
	m_exitConditions.m_radiusSqr = sqr(range);
	m_exitConditions.m_attackGiveUpFrame = TheGameLogic->getFrame() + TheAI->getAiData()->m_guardChaseUnitFrames;
	m_exitConditions.m_conditionsToConsider = (ExitConditions::ATTACK_ExitIfExpiredDuration | 
																								ExitConditions::ATTACK_ExitIfOutsideRadius | 
																								ExitConditions::ATTACK_ExitIfNoUnitFound);

	m_attackState = newInstance(AIAttackState)(getMachine(), false, true, false, &m_exitConditions);
	m_attackState->getMachine()->setGoalObject(nemesis);

	StateReturnType returnVal = m_attackState->onEnter();
	if (returnVal == STATE_CONTINUE) {
		return STATE_CONTINUE;
	}

	// if we had no one to attack, we were successful, so go to the next state.
	return STATE_SUCCESS;
}

//--------------------------------------------------------------------------------------
// ?update@AIGuardOuterState@@ present-unmatched
StateReturnType AIGuardOuterState::update( void )
{
	if (m_attackState==NULL) return STATE_SUCCESS;

	// if the position has moved (IE we're guarding an object), move with it.
	Object* targetToGuard = getGuardMachine()->findTargetToGuardByID();
	if (targetToGuard) 
	{
		m_exitConditions.m_center = *targetToGuard->getPosition();
	}

	Object* goalObj = m_attackState->getMachineGoalObject();
	if (goalObj) 
	{
		Coord3D deltaAggr;
		deltaAggr.x = m_exitConditions.m_center.x - goalObj->getPosition()->x;
		deltaAggr.y = m_exitConditions.m_center.y - goalObj->getPosition()->y;
		deltaAggr.z = m_exitConditions.m_center.z - goalObj->getPosition()->z;
		Real visionSqr = sqr(AIGuardMachine::getStdGuardRange(getMachineOwner()));
		if (deltaAggr.lengthSqr() <= visionSqr) 
		{
			// reset the counter
			m_exitConditions.m_attackGiveUpFrame = TheGameLogic->getFrame() + TheAI->getAiData()->m_guardChaseUnitFrames;
		}
	}
	
	return m_attackState->update();
}

//--------------------------------------------------------------------------------------
// ?onExit@AIGuardOuterState@@ present-unmatched
void AIGuardOuterState::onExit( StateExitType status )
{
	if (m_attackState) 
	{
		m_attackState->onExit(status);
		m_attackState->deleteInstance();
		m_attackState = NULL;
	}
}

//-- AIGuardReturnState ----------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@AIGuardReturnState@@ present-unmatched
void AIGuardReturnState::crc( Xfer *xfer )
{
}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ?xfer@AIGuardReturnState@@ present-unmatched
void AIGuardReturnState::xfer( Xfer *xfer )
{
  // version
  XferVersion currentVersion = 1;
  XferVersion version = currentVersion;
  xfer->xferVersion( &version, currentVersion );
	
	xfer->xferUnsignedInt(&m_nextReturnScanTime);
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@AIGuardReturnState@@ present-unmatched
void AIGuardReturnState::loadPostProcess( void )
{
}  // end loadPostProcess

struct BfmeGuardAIData
{
	unsigned char m_padding00[0x44];
	UnsignedInt m_guardEnemyReturnScanRate;
};

struct BfmeGuardAI
{
	Pathfinder *pathfinder() const
	{
		return m_pathfinder;
	}

	BfmeGuardAIData *getAiData() const
	{
		return m_aiData;
	}

	unsigned char m_padding00[0x0c];
	Pathfinder *m_pathfinder;
	unsigned char m_padding10[4];
	BfmeGuardAIData *m_aiData;
};

template <Int N>
class BfmeGuardVirtualSlots : public BfmeGuardVirtualSlots<N - 1>
{
public:
	virtual void unusedSlot(char (*)[N]);
};

template <>
class BfmeGuardVirtualSlots<0>
{
};

class BfmeGuardAIUpdate : public BfmeGuardVirtualSlots<123>
{
public:
	virtual Bool isDoingGroundMovement() const;

	const LocomotorSet &getLocomotorSet() const
	{
		return *(const LocomotorSet *)((const char *)this + 0x1a8);
	}
};

class BfmeGuardAIUpdateCallTarget
{
public:
	void destroyPath();
};

struct BfmeGuardObject
{
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	BfmeGuardAIUpdate *getAIUpdateInterface() const
	{
		return *(BfmeGuardAIUpdate *const *)((const char *)this + 0x204);
	}
};

class BfmeGuardStateMachine
{
public:
	virtual void unusedSlot();
	unsigned char m_padding04[0x0c];
	BfmeGuardObject *m_owner;
};

class BfmeGuardMachine : public BfmeGuardStateMachine
{
public:
	void getGuardScanPos(Coord3D *out);
};

struct BfmeGuardReturnStateView
{
	unsigned char m_padding00[0x1c];
	BfmeGuardStateMachine *m_machine;
	unsigned char m_padding20[4];
	Coord3D m_goalPosition;
	unsigned char m_padding30[0x1c];
	Bool m_adjustsDestination;
	unsigned char m_padding4d[3];
	UnsignedInt m_nextReturnScanTime;
};

extern GameLogic *TheBfmeGameLogic;
extern Int GetGameLogicRandomValue(Int minimum, Int maximum, char *file, Int line);
extern Real g_bfmeK1266C;
extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0000314d();
extern void j_000065e1();
extern void j_00017099();
extern void j_00036aa2();
extern void j_0003a17a();

//--------------------------------------------------------------------------------------
StateReturnType AIGuardReturnState::onEnter( void )
{
	BfmeGuardReturnStateView *self = (BfmeGuardReturnStateView *)this;
	UnsignedInt now = TheBfmeGameLogic->getFrame();
	self->m_nextReturnScanTime = now + GetGameLogicRandomValue(
		0, ((BfmeGuardAI *)TheAI)->getAiData()->m_guardEnemyReturnScanRate,
		(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIGuard.cpp",
		901);

	{
		Coord3D goalPosition;
		typedef Coord3D *(BfmeGuardMachine::*GetGuardScanPosCall)(Coord3D *);
		union
		{
			void *asVoid;
			GetGuardScanPosCall asMember;
		} getGuardScanPosCast;
		getGuardScanPosCast.asVoid = (void *)j_00017099;
		Coord3D *scanPosition = (((BfmeGuardMachine *)self->m_machine)->*
			getGuardScanPosCast.asMember)(&goalPosition);
		self->m_goalPosition = *scanPosition;
	}

	register BfmeGuardObject *owner = self->m_machine->m_owner;
	Coord3D &goal = self->m_goalPosition;
	if (!owner)
		goto doEnter;
	{
		Coord3D delta;
		delta.x = owner->getPosition()->x;
		delta.y = owner->getPosition()->y;
		delta.z = owner->getPosition()->z;
		delta.x -= goal.x;
		delta.y -= goal.y;
		delta.z -= goal.z;
		typedef Real (Coord3D::*GetLengthEstimateCall)() const;
		union
		{
			void *asVoid;
			GetLengthEstimateCall asMember;
		} getLengthEstimateCast;
		getLengthEstimateCast.asVoid = (void *)j_00036aa2;
		if (!((delta.*getLengthEstimateCast.asMember)() < g_bfmeK1266C))
			goto doEnter;
	}
	goto returnSuccess;

doEnter:
	BfmeGuardAIUpdate *ai = owner->getAIUpdateInterface();
	if (ai)
	{
		if (ai->isDoingGroundMovement())
		{
			((BfmeGuardAI *)TheAI)->pathfinder()->adjustDestination((Object *)self->m_machine->m_owner,
				ai->getLocomotorSet(), &goal, 0);
		}
		typedef void (BfmeGuardAIUpdateCallTarget::*DestroyPathCall)();
		union
		{
			void *asVoid;
			DestroyPathCall asMember;
		} destroyPathCast;
		destroyPathCast.asVoid = (void *)j_000065e1;
		(((BfmeGuardAIUpdateCallTarget *)ai)->*destroyPathCast.asMember)();
	}

	typedef void (BfmeGuardStateMachine::*SetGoalPositionCall)(const Coord3D *);
	union
	{
		void *asVoid;
		SetGoalPositionCall asMember;
	} setGoalPositionCast;
	setGoalPositionCast.asVoid = (void *)j_0000314d;
	(self->m_machine->*setGoalPositionCast.asMember)(&goal);

	if (g_012F0239 && g_012ED4FC)
	{
		typedef void (__cdecl *CritterDesyncLog)(void *, const char *);
		((CritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: setAdjustDestination(TRUE) 3");
	}
	self->m_adjustsDestination = true;
	return AIInternalMoveToState::onEnter();

returnSuccess:
	return STATE_SUCCESS;
}

//--------------------------------------------------------------------------------------
// ?update@AIGuardReturnState@@ present-unmatched
StateReturnType AIGuardReturnState::update( void )
{
	UnsignedInt now = TheGameLogic->getFrame();
	if (now >= m_nextReturnScanTime)
	{
		m_nextReturnScanTime = now + TheAI->getAiData()->m_guardEnemyReturnScanRate;
		AIGuardMachine *retailGuardMachine = *reinterpret_cast<AIGuardMachine **>(reinterpret_cast<char *>(this) + 0x1c);
		if (retailGuardMachine->lookForInnerTarget())
			return STATE_FAILURE; // early termination because we found a target.
	}

	// Just let the return movement finish.
	return AIInternalMoveToState::update();
}

//--------------------------------------------------------------------------------------
// ?onExit@AIGuardReturnState@@ present-unmatched
void AIGuardReturnState::onExit( StateExitType status )
{
	AIInternalMoveToState::onExit( status );
}

//-- AIGuardIdleState ----------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@AIGuardIdleState@@ present-unmatched
void AIGuardIdleState::crc( Xfer *xfer )
{
}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ?xfer@AIGuardIdleState@@ present-unmatched
void AIGuardIdleState::xfer( Xfer *xfer )
{
  // version
  XferVersion currentVersion = 1;
  XferVersion version = currentVersion;
  xfer->xferVersion( &version, currentVersion );
	
	xfer->xferUnsignedInt(&m_nextEnemyScanTime);
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@AIGuardIdleState@@ present-unmatched
void AIGuardIdleState::loadPostProcess( void )
{
}  // end loadPostProcess

//--------------------------------------------------------------------------------------
// ?onEnter@AIGuardIdleState@@ present-unmatched
StateReturnType AIGuardIdleState::onEnter( void )
{
	// first time thru, use a random amount so that everyone doesn't scan on the same frame,
	// to avoid "spikes". 
	UnsignedInt now = TheGameLogic->getFrame();
	m_nextEnemyScanTime = now + GameLogicRandomValue(0, TheAI->getAiData()->m_guardEnemyScanRate);

	return STATE_CONTINUE;
}

//--------------------------------------------------------------------------------------
// ?update@AIGuardIdleState@@ present-unmatched
StateReturnType AIGuardIdleState::update( void )
{
	//DEBUG_LOG(("AIGuardIdleState frame %d: %08lx\n",TheGameLogic->getFrame(),getMachineOwner()));

	UnsignedInt now = TheGameLogic->getFrame();
	if (now < m_nextEnemyScanTime)
		return STATE_SLEEP(m_nextEnemyScanTime - now);

	m_nextEnemyScanTime = now + TheAI->getAiData()->m_guardEnemyScanRate;

#ifdef STATE_MACHINE_DEBUG
	//getMachine()->setDebugOutput(true);
#endif
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAIUpdateInterface();
	// Check to see if we have created a crate we need to pick up.
	if (ai->getCrateID() != INVALID_ID) 
	{
		getMachine()->setState(AI_GUARD_GET_CRATE);
		return STATE_SLEEP(m_nextEnemyScanTime - now);
	}

	// if anyone is in the inner area, return success.
	if (getGuardMachine()->lookForInnerTarget()) 
	{
		return STATE_SUCCESS;	// Transitions to AIGuardInnerState.
	}

	// See if the object we are guarding moved.
	Object* targetToGuard = getGuardMachine()->findTargetToGuardByID();
	if (targetToGuard) 
	{
		Coord3D pos = *targetToGuard->getPosition();
		Real delta = m_guardeePos.x-pos.x;
		if (delta*delta > 4*PATHFIND_CELL_SIZE_F*PATHFIND_CELL_SIZE_F) {
			m_guardeePos = pos;
			return STATE_FAILURE; // goes to AIGuardReturnState.
		}
		delta = m_guardeePos.y-pos.y;
		if (delta*delta > 4*PATHFIND_CELL_SIZE_F*PATHFIND_CELL_SIZE_F) {
			m_guardeePos = pos;
			return STATE_FAILURE; // goes to AIGuardReturnState.
		}
	} 
	return STATE_SLEEP(m_nextEnemyScanTime - now);
}

//--------------------------------------------------------------------------------------
// ?onExit@AIGuardIdleState@@ present-unmatched
void AIGuardIdleState::onExit( StateExitType status )
{
	
}

//-- AIGuardPickUpCrateState ----------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0AIGuardPickUpCrateState@@ present-unmatched
AIGuardPickUpCrateState::AIGuardPickUpCrateState( StateMachine *machine )	: AIPickUpCrateState(machine)
{
#ifdef STATE_MACHINE_DEBUG
		setName("AIGuardPickUpCrateState");
#endif	
}
//--------------------------------------------------------------------------------------
// ?onEnter@AIGuardPickUpCrateState@@ present-unmatched
StateReturnType AIGuardPickUpCrateState::onEnter( void )
{
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAIUpdateInterface();
	
	// Check to see if we have created a crate we need to pick up.
	Object* crate = ai->checkForCrateToPickup();
	if (crate)
	{
		getMachine()->setGoalObject(crate);
		return AIPickUpCrateState::onEnter();
	}

	return STATE_SUCCESS; // no crate, so we're done.
}

//--------------------------------------------------------------------------------------
// ?update@AIGuardPickUpCrateState@@ present-unmatched
StateReturnType AIGuardPickUpCrateState::update( void )
{
	return AIPickUpCrateState::update();
}

//--------------------------------------------------------------------------------------
// ?onExit@AIGuardPickUpCrateState@@ present-unmatched
void AIGuardPickUpCrateState::onExit( StateExitType status )
{
	
}

//-- AIGuardAttackAggressorState ------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/AI/AIGuardStateConstructors.cpp
// ??0AIGuardAttackAggressorState@@ present-unmatched
AIGuardAttackAggressorState::AIGuardAttackAggressorState( StateMachine *machine ) : 
	State( machine, "AIGuardAttackAggressorState" )
{
	m_attackState = NULL;
}

//-------------------------------------------------------------------------------------------------
// ?onEnter@AIGuardAttackAggressorState@@ present-unmatched
StateReturnType AIGuardAttackAggressorState::onEnter( void )
{
	Object *obj = getMachineOwner();
	ObjectID nemID = INVALID_ID;

	if (obj->getBodyModule() && obj->getBodyModule()->getLastDamageInfo()->in.m_sourceID) {
		nemID = obj->getBodyModule()->getLastDamageInfo()->in.m_sourceID;
		getGuardMachine()->setNemesisID(nemID);
	}

	Object *nemesis = TheGameLogic->findObjectByID(getGuardMachine()->getNemesisID());
	if (nemesis == NULL) 
	{
		DEBUG_LOG(("Unexpected NULL nemesis in AIGuardAttackAggressorState.\n"));
		return STATE_SUCCESS;
	}

	Object* targetToGuard = getGuardMachine()->findTargetToGuardByID();
	Coord3D pos = targetToGuard ? *targetToGuard->getPosition() : *getGuardMachine()->getPositionToGuard();
	//Don't allow guarding units to leave their guard radius!
	m_exitConditions.m_center = pos;
	m_exitConditions.m_radiusSqr = sqr(AIGuardMachine::getStdGuardRange(getMachineOwner()));
	m_exitConditions.m_attackGiveUpFrame = TheGameLogic->getFrame() + TheAI->getAiData()->m_guardChaseUnitFrames;
	m_exitConditions.m_conditionsToConsider = (ExitConditions::ATTACK_ExitIfExpiredDuration | 
																						 ExitConditions::ATTACK_ExitIfNoUnitFound |
																						 ExitConditions::ATTACK_ExitIfOutsideRadius );

	m_attackState = newInstance(AIAttackState)(getMachine(), true, true, false, &m_exitConditions);
	m_attackState->getMachine()->setGoalObject(nemesis);

	StateReturnType returnVal = m_attackState->onEnter();
	if (returnVal == STATE_CONTINUE) {
		return STATE_CONTINUE;
	}

	// if we had no one to attack, we were successful, so go to the next state.
	return STATE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------
// ?update@AIGuardAttackAggressorState@@ present-unmatched
StateReturnType AIGuardAttackAggressorState::update( void )
{
	if (m_attackState==NULL) return STATE_SUCCESS;
	// if the position has moved (IE we're guarding an object), move with it.
	Object* targetToGuard = getGuardMachine()->findTargetToGuardByID();
	if (targetToGuard) 
	{
		m_exitConditions.m_center = *targetToGuard->getPosition();
	}
	
	return m_attackState->update();
}

//-------------------------------------------------------------------------------------------------
// ?onExit@AIGuardAttackAggressorState@@ present-unmatched
void AIGuardAttackAggressorState::onExit( StateExitType status )
{
	Object *obj = getMachineOwner();
	if (m_attackState) 
	{
		m_attackState->onExit(status);
		m_attackState->deleteInstance();
		m_attackState = NULL;
	}

	if (obj->getTeam()) 
	{
		obj->getTeam()->setTeamTargetObject(NULL); // clear the target.
	}
}

//-------------------------------------------------------------------------------------------------
// ?crc@AIGuardAttackAggressorState@@ present-unmatched
void AIGuardAttackAggressorState::crc( Xfer *xfer )
{

}

//-------------------------------------------------------------------------------------------------
// ?xfer@AIGuardAttackAggressorState@@ present-unmatched
void AIGuardAttackAggressorState::xfer( Xfer *xfer )
{
  // version
  XferVersion currentVersion = 1;
  XferVersion version = currentVersion;
  xfer->xferVersion( &version, currentVersion );

}

//-------------------------------------------------------------------------------------------------
// ?loadPostProcess@AIGuardAttackAggressorState@@ present-unmatched
void AIGuardAttackAggressorState::loadPostProcess()
{
	onEnter();
}
