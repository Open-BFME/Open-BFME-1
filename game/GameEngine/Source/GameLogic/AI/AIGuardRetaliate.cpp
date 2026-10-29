// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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


// FILE: AIGuardRetaliate.h 
/*---------------------------------------------------------------------------*/
/* Electronic Arts Los Angeles                                               */
/* Confidential Information	                                                 */
/* Copyright (C) 2003 - All Rights Reserved                                  */
/* DO NOT DISTRIBUTE                                                         */
/*---------------------------------------------------------------------------*/
/* Project:    RTS3                                                          */
/* File name:  AIGuardRetaliate.h                                            */
/* Created:    Kris Morness July 2003                                        */
/* Desc:       // Define Guard Retaliation states for AI                     */
/*---------------------------------------------------------------------------*/

#define KindOfMaskType ZHKindOfMaskType
#define KINDOFMASK_NONE ZHKINDOFMASK_NONE
#define PartitionFilter ZHPartitionFilter
#define PartitionFilterRelationship ZHPartitionFilterRelationship
#define PartitionFilterPossibleToAttack ZHPartitionFilterPossibleToAttack
#define PartitionFilterSameMapStatus ZHPartitionFilterSameMapStatus
#define PartitionFilterPossibleToEnter ZHPartitionFilterPossibleToEnter
#define PartitionFilterPossibleToHijack ZHPartitionFilterPossibleToHijack
#define PartitionFilterRejectBuildings ZHPartitionFilterRejectBuildings
#define PartitionFilterAcceptByKindOf ZHPartitionFilterAcceptByKindOf
#define PartitionManager ZHPartitionManager
#define ThePartitionManager ZHThePartitionManager

// This unit's State view defines getMachine inline at another offset than
// retail's 0x0009FEE0 (+0x1C) and emits that COMDAT copy; rename it so only
// retail-equal copies carry the name. Inlined calls are unchanged.
#define getMachine getMachine_LocalView
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/PerfTimer.h"
#include "Common/Team.h"
#include "Common/Xfer.h"
#include "Common/ThingTemplate.h"
#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/AIGuardRetaliate.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/CollideModule.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/PolygonTrigger.h"

#undef KindOfMaskType
#undef KINDOFMASK_NONE
typedef BitFlags<192> GuardKindMaskType;
extern const GuardKindMaskType KINDOFMASK_NONE;

#undef PartitionFilterAcceptByKindOf
#undef PartitionFilterRejectBuildings
#undef PartitionFilterPossibleToHijack
#undef PartitionFilterPossibleToEnter
#undef PartitionFilterSameMapStatus
#undef PartitionFilterPossibleToAttack
#undef PartitionFilterRelationship
#undef ThePartitionManager
#undef PartitionManager
#undef PartitionFilter

class __declspec(novtable) PartitionFilter : public ZHPartitionFilter
{
public:
	PartitionFilter() : m_next(NULL) {}
	PartitionFilter(UnsignedInt vptr) : m_next(NULL)
	{
		*reinterpret_cast<UnsignedInt *>(this) = vptr;
	}
	virtual ~PartitionFilter()
	{
		*reinterpret_cast<volatile UnsignedInt *>(this) = 0x01083B5C;
	}
	virtual Bool allow(Object *) { return TRUE; }
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		Int distanceCalculation, PartitionFilter *filter);
};

extern PartitionManager *ThePartitionManager;
extern const double g_Va010965B8;

static __forceinline void setGuardFilterVptr(void *filter, UnsignedInt value)
{
	*reinterpret_cast<UnsignedInt *>(filter) = value;
}

class __declspec(novtable) PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int flags, Bool allow)
	{
		setGuardFilterVptr(this, 0x01085DC0);
		m_object = object;
		m_flags = flags;
		m_allow = allow;
	}
	virtual ~PartitionFilterRelationship() {}

private:
	Object *m_object;
	Int m_flags;
	Bool m_allow;
};

class __declspec(novtable) PartitionFilterPossibleToAttack : public PartitionFilter
{
public:
	PartitionFilterPossibleToAttack(Object *object, Int attackType, Int commandSource)
	{
		setGuardFilterVptr(this, 0x010956C4);
		m_object = object;
		m_commandSource = commandSource;
		m_attackType = attackType;
	}
	virtual ~PartitionFilterPossibleToAttack() {}

private:
	Object *m_object;
	Int m_commandSource;
	Int m_attackType;
};

class __declspec(novtable) PartitionFilterRejectBuildings : public PartitionFilter
{
public:
	PartitionFilterRejectBuildings(const Object *object);
	virtual ~PartitionFilterRejectBuildings() {}

private:
	const Object *m_self;
	Bool m_acquireEnemies;
};

class __declspec(novtable) PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(
		const GuardKindMaskType &mustBeClear,
		const GuardKindMaskType &mustBeSet) throw();
	virtual ~PartitionFilterAcceptByKindOf() {}

private:
	GuardKindMaskType m_mustBeClear;
	GuardKindMaskType m_mustBeSet;
};

__declspec(noinline) PartitionFilterAcceptByKindOf::PartitionFilterAcceptByKindOf(
	const GuardKindMaskType &mustBeClear,
	const GuardKindMaskType &mustBeSet) throw()
	: PartitionFilter(0x01083B70), m_mustBeClear(mustBeClear),
	  m_mustBeSet(mustBeSet)
{}

class __declspec(novtable) PartitionFilterSameMapStatus : public PartitionFilter
{
public:
	PartitionFilterSameMapStatus(const Object *object)
	{
		setGuardFilterVptr(this, 0x01085DD0);
		m_object = object;
	}
	virtual ~PartitionFilterSameMapStatus() {}

private:
	const Object *m_object;
};

class __declspec(novtable) Rva0015B910Filter : public PartitionFilter
{
public:
	Rva0015B910Filter()
	{
		setGuardFilterVptr(this, 0x01095FBC);
	}
	virtual ~Rva0015B910Filter() {}
};

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
//-- AIGuardRetaliateMachine -------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Zero Hour-layout source; the BFME byte-exact constructor is in
// game/GameEngine/Source/GameLogic/AI/AIGuardRetaliateMachineCtor.cpp.
// ??0AIGuardRetaliateMachine@@ present-unmatched
AIGuardRetaliateMachine::AIGuardRetaliateMachine( Object *owner ) : 
	StateMachine(owner, "AIGuardRetaliateMachine"),
	m_nemesisToAttack(INVALID_ID)
{
	m_positionToGuard.zero();
	
	static const StateConditionInfo attackAggressors[] =
	{
		StateConditionInfo(hasAttackedMeAndICanReturnFire, AI_GUARD_RETALIATE_ATTACK_AGGRESSOR, NULL),
		StateConditionInfo(NULL, NULL, NULL)	// keep last
	};

	// order matters: first state is the default state.
// srj sez: I made "return" the start state, so that if ordered to guard a position
// that isn't the unit's current position, it moves to that position first.
	defineState( AI_GUARD_RETALIATE_ATTACK_AGGRESSOR, newInstance(AIGuardRetaliateAttackAggressorState)( this ), AI_GUARD_RETALIATE_RETURN, AI_GUARD_RETALIATE_RETURN );
	defineState( AI_GUARD_RETALIATE_RETURN,						newInstance(AIGuardRetaliateReturnState)( this ), AI_GUARD_RETALIATE_IDLE, AI_GUARD_RETALIATE_INNER, attackAggressors );
	defineState( AI_GUARD_RETALIATE_IDLE,							newInstance(AIGuardRetaliateIdleState)( this ), AI_GUARD_RETALIATE_INNER, EXIT_MACHINE_WITH_SUCCESS, attackAggressors );
	defineState( AI_GUARD_RETALIATE_INNER,						newInstance(AIGuardRetaliateInnerState)( this ), AI_GUARD_RETALIATE_OUTER, AI_GUARD_RETALIATE_OUTER );
	defineState( AI_GUARD_RETALIATE_OUTER,						newInstance(AIGuardRetaliateOuterState)( this ), AI_GUARD_RETALIATE_GET_CRATE, AI_GUARD_RETALIATE_GET_CRATE );
	defineState( AI_GUARD_RETALIATE_GET_CRATE,				newInstance(AIGuardRetaliatePickUpCrateState)( this ), AI_GUARD_RETALIATE_RETURN, AI_GUARD_RETALIATE_RETURN );
}

//--------------------------------------------------------------------------------------
// ??1AIGuardRetaliateMachine@@ present-unmatched
AIGuardRetaliateMachine::~AIGuardRetaliateMachine()
{
}

// ?isIdle@AIGuardRetaliateMachine@@ present-unmatched
Bool AIGuardRetaliateMachine::isIdle() const
{
	if( getCurrentStateID() == AI_IDLE )
	{
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------
/*static*/ Real AIGuardRetaliateMachine::getStdGuardRange(const Object* object)
{
	Real visionRange = TheAI->getAdjustedVisionRangeForObject(object,
		AI_VISIONFACTOR_OWNERTYPE | AI_VISIONFACTOR_MOOD | AI_VISIONFACTOR_GUARDINNER);

	return visionRange;
}

//--------------------------------------------------------------------------------------
Bool AIGuardRetaliateMachine::lookForInnerTarget(void)
{
	Object *owner = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) + 0x10);
	if (!owner->isAbleToAttack())
	{
		return false;	// my, that was easy
	}

	// Check if team auto targets same victim.
	Team *team = *reinterpret_cast<Team **>(reinterpret_cast<char *>(owner) + 0x23C);
	const char *teamTemplate = *reinterpret_cast<const char **>(reinterpret_cast<char *>(team) + 4);
	if (*reinterpret_cast<const Bool *>(teamTemplate + 0x1C2))
	{
		Object *teamVictim = team->getTeamTargetObject();
		if (teamVictim)
		{
			*reinterpret_cast<ObjectID *>(reinterpret_cast<char *>(this) + 0x50) = teamVictim->getID();
			return true;	// Transitions to AIGuardRetaliateInnerState.
		}
	}

	PartitionFilterRelationship relationship(owner, 1, false);
	PartitionFilterPossibleToAttack attack(owner, ATTACK_NEW_TARGET, CMD_FROM_AI);
	PartitionFilterRejectBuildings buildings(owner);

	GuardKindMaskType kindMask(GuardKindMaskType::kInit, 129);
	PartitionFilterAcceptByKindOf kindFilter(KINDOFMASK_NONE, kindMask);

	PartitionFilterSameMapStatus mapStatus(owner);
	Rva0015B910Filter trailingFilter;

	relationship.link(attack.link(&mapStatus));
	relationship.link(&buildings);
	relationship.link(&kindFilter);

	struct GuardRangeData
	{
		char pad[0xC4];
		Real m_guardInnerRange;
	};
	struct GuardRangeAI
	{
		char pad[0x14];
		GuardRangeData *m_aiData;
	};
	const GuardRangeAI *ai = reinterpret_cast<const GuardRangeAI *>(TheAI);
	Real visionRange = ai->m_aiData->m_guardInnerRange * g_Va010965B8;

	struct GuardOwnerPosition
	{
		char pad[0x38];
		Coord3D position;
	};
	Coord3D pos;
	pos.set(reinterpret_cast<const Coord3D *>(
		reinterpret_cast<const char *>(owner) + 0x38));
	Object *target = reinterpret_cast<PartitionManager *>(ThePartitionManager)->getClosestObject(
		&pos, visionRange, FROM_CENTER_3D, &relationship);
	if (target)
	{
		*reinterpret_cast<ObjectID *>(reinterpret_cast<char *>(this) + 0x50) = target->getID();
		return true;	// Transitions to AIGuardRetaliateInnerState.
	}
	else
	{
		return false;
	}
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@AIGuardRetaliateMachine@@ present-unmatched
void AIGuardRetaliateMachine::crc( Xfer *xfer )
{
}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ?xfer@AIGuardRetaliateMachine@@ present-unmatched
void AIGuardRetaliateMachine::xfer( Xfer *xfer )
{
  // version
  XferVersion currentVersion = 2;
  XferVersion version = currentVersion;
  xfer->xferVersion( &version, currentVersion );

	if (version>=2) {
// ?xfer@StateMachine@@ present-unmatched
		StateMachine::xfer(xfer);	// Forgot this in initial implementation.  jba.
	}

	xfer->xferObjectID(&m_nemesisToAttack);
	xfer->xferCoord3D(&m_positionToGuard);

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
void AIGuardRetaliateMachine::loadPostProcess( void )
{
}  // end loadPostProcess

//-- AIGuardRetaliateInnerState ----------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@AIGuardRetaliateInnerState@@ present-unmatched
void AIGuardRetaliateInnerState::crc( Xfer *xfer )
{
}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ?xfer@AIGuardRetaliateInnerState@@ present-unmatched
void AIGuardRetaliateInnerState::xfer( Xfer *xfer )
{
  // version
  XferVersion currentVersion = 1;
  XferVersion version = currentVersion;
  xfer->xferVersion( &version, currentVersion );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@AIGuardRetaliateInnerState@@ present-unmatched
void AIGuardRetaliateInnerState::loadPostProcess( void )
{
	onEnter();
}  // end loadPostProcess

//--------------------------------------------------------------------------------------
// ?onEnter@AIGuardRetaliateInnerState@@ present-unmatched
StateReturnType AIGuardRetaliateInnerState::onEnter( void )
{
	// See if we try to enter the target
	if (getMachineOwner()->getTemplate()->isEnterGuard())
	{
		Object* nemesis = TheGameLogic->findObjectByID(getGuardMachine()->getNemesisID()) ;
		if (nemesis == NULL) 
		{
			DEBUG_LOG(("Unexpected NULL nemesis in AIGuardRetaliateInnerState.\n"));
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
		Coord3D pos = *getGuardMachine()->getPositionToGuard();
		Object* nemesis = TheGameLogic->findObjectByID(getGuardMachine()->getNemesisID()) ;
		if (nemesis == NULL) 
		{
			DEBUG_LOG(("Unexpected NULL nemesis in AIGuardRetaliateInnerState.\n"));
			return STATE_SUCCESS;
		}
		m_exitConditions.m_center = pos;
		m_exitConditions.m_radiusSqr = sqr( 1.5f * AIGuardRetaliateMachine::getStdGuardRange( getMachineOwner() ) );
		m_exitConditions.m_conditionsToConsider = (GuardRetaliateExitConditions::ATTACK_ExitIfOutsideRadius | 
																								GuardRetaliateExitConditions::ATTACK_ExitIfNoUnitFound);

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
// ?update@AIGuardRetaliateInnerState@@ present-unmatched
StateReturnType AIGuardRetaliateInnerState::update( void )
{
	if (m_attackState)
	{
		return m_attackState->update();
	}
	else if (m_enterState)
	{
		return m_enterState->update();
	}

	return STATE_SUCCESS;
}

//--------------------------------------------------------------------------------------
// ?onExit@AIGuardRetaliateInnerState@@ present-unmatched
void AIGuardRetaliateInnerState::onExit( StateExitType status )
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

//-- AIGuardRetaliateOuterState ----------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@AIGuardRetaliateOuterState@@ present-unmatched
void AIGuardRetaliateOuterState::crc( Xfer *xfer )
{
}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ?xfer@AIGuardRetaliateOuterState@@ present-unmatched
void AIGuardRetaliateOuterState::xfer( Xfer *xfer )
{
  // version
  XferVersion currentVersion = 1;
  XferVersion version = currentVersion;
  xfer->xferVersion( &version, currentVersion );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@AIGuardRetaliateOuterState@@ present-unmatched
void AIGuardRetaliateOuterState::loadPostProcess( void )
{						 AIGuardRetaliateOuterState
	onEnter();
}  // end loadPostProcess

//--------------------------------------------------------------------------------------
// ?onEnter@AIGuardRetaliateOuterState@@ present-unmatched
StateReturnType AIGuardRetaliateOuterState::onEnter( void )
{
	//if (getGuardMachine()->getGuardMode() == GUARDMODE_GUARD_WITHOUT_PURSUIT)
	//{
	//	// "patrol" mode does not follow targets outside the guard area.
	//	return STATE_SUCCESS;
	//}

	Coord3D pos = *getGuardMachine()->getPositionToGuard();

	Object* nemesis = TheGameLogic->findObjectByID(getGuardMachine()->getNemesisID()) ;
	if (nemesis == NULL) 
	{
		DEBUG_LOG(("Unexpected NULL nemesis in AIGuardRetaliateOuterState.\n"));
		return STATE_SUCCESS;
	}
	Object *obj = getMachineOwner();

	Real range = TheAI->getAdjustedVisionRangeForObject(obj, AI_VISIONFACTOR_OWNERTYPE | AI_VISIONFACTOR_MOOD);

	m_exitConditions.m_center = pos;
	m_exitConditions.m_radiusSqr = sqr( 0.67f * (range + AIGuardRetaliateMachine::getStdGuardRange( getMachineOwner() )) );
	m_exitConditions.m_attackGiveUpFrame = TheGameLogic->getFrame() + TheAI->getAiData()->m_guardChaseUnitFrames;
	m_exitConditions.m_conditionsToConsider = (GuardRetaliateExitConditions::ATTACK_ExitIfExpiredDuration | 
																								GuardRetaliateExitConditions::ATTACK_ExitIfOutsideRadius | 
																								GuardRetaliateExitConditions::ATTACK_ExitIfNoUnitFound);

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
// ?update@AIGuardRetaliateOuterState@@ present-unmatched
StateReturnType AIGuardRetaliateOuterState::update( void )
{
	if (m_attackState==NULL) return STATE_SUCCESS;

	Object* goalObj = m_attackState->getMachineGoalObject();
	if (goalObj) 
	{
		Coord3D deltaAggr;
		deltaAggr.x = m_exitConditions.m_center.x - goalObj->getPosition()->x;
		deltaAggr.y = m_exitConditions.m_center.y - goalObj->getPosition()->y;
		deltaAggr.z = m_exitConditions.m_center.z - goalObj->getPosition()->z;
		Real visionSqr = sqr(AIGuardRetaliateMachine::getStdGuardRange(getMachineOwner()));
		if (deltaAggr.lengthSqr() <= visionSqr) 
		{
			// reset the counter
			m_exitConditions.m_attackGiveUpFrame = TheGameLogic->getFrame() + TheAI->getAiData()->m_guardChaseUnitFrames;
		}
	}
	
	return m_attackState->update();
}

//--------------------------------------------------------------------------------------
// ?onExit@AIGuardRetaliateOuterState@@ present-unmatched
void AIGuardRetaliateOuterState::onExit( StateExitType status )
{
	if (m_attackState) 
	{
		m_attackState->onExit(status);
		m_attackState->deleteInstance();
		m_attackState = NULL;
	}
}

//-- AIGuardRetaliateReturnState ----------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@AIGuardRetaliateReturnState@@ present-unmatched
void AIGuardRetaliateReturnState::crc( Xfer *xfer )
{
}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ?xfer@AIGuardRetaliateReturnState@@ present-unmatched
void AIGuardRetaliateReturnState::xfer( Xfer *xfer )
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
void AIGuardRetaliateReturnState::loadPostProcess( void )
{
}  // end loadPostProcess

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
void AIGuardRetaliateReturnState::onExit( StateExitType status )
{
	AIInternalMoveToState::onExit( status );
}

//-- AIGuardRetaliateIdleState ----------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@AIGuardRetaliateIdleState@@ present-unmatched
void AIGuardRetaliateIdleState::crc( Xfer *xfer )
{
}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ?xfer@AIGuardRetaliateIdleState@@ present-unmatched
void AIGuardRetaliateIdleState::xfer( Xfer *xfer )
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
// ?loadPostProcess@AIGuardRetaliateIdleState@@ present-unmatched
void AIGuardRetaliateIdleState::loadPostProcess( void )
{
}  // end loadPostProcess

//--------------------------------------------------------------------------------------
// ?onEnter@AIGuardRetaliateIdleState@@ present-unmatched
StateReturnType AIGuardRetaliateIdleState::onEnter( void )
{
	// first time thru, use a random amount so that everyone doesn't scan on the same frame,
	// to avoid "spikes". 
	UnsignedInt now = TheGameLogic->getFrame();
	m_nextEnemyScanTime = now + GameLogicRandomValue(0, TheAI->getAiData()->m_guardEnemyScanRate);

	return STATE_CONTINUE;
}

//--------------------------------------------------------------------------------------
// ?update@AIGuardRetaliateIdleState@@ present-unmatched
StateReturnType AIGuardRetaliateIdleState::update( void )
{
	//DEBUG_LOG(("AIGuardRetaliateIdleState frame %d: %08lx\n",TheGameLogic->getFrame(),getMachineOwner()));

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
		getMachine()->setState(AI_GUARD_RETALIATE_GET_CRATE);
		return STATE_SLEEP(m_nextEnemyScanTime - now);
	}

	// if anyone is in the inner area, return success.
	if (getGuardMachine()->lookForInnerTarget()) 
	{
		return STATE_SUCCESS;	// Transitions to AIGuardRetaliateInnerState.
	}
	else
	{
		return STATE_FAILURE;
	}

	return STATE_SLEEP(m_nextEnemyScanTime - now);
}

//--------------------------------------------------------------------------------------
// ?onExit@AIGuardRetaliateIdleState@@ present-unmatched
void AIGuardRetaliateIdleState::onExit( StateExitType status )
{
	
}

//-- AIGuardRetaliatePickUpCrateState ----------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0AIGuardRetaliatePickUpCrateState@@ present-unmatched
AIGuardRetaliatePickUpCrateState::AIGuardRetaliatePickUpCrateState( StateMachine *machine )	: AIPickUpCrateState(machine)
{
#ifdef STATE_MACHINE_DEBUG
		setName("AIGuardRetaliatePickUpCrateState");
#endif	
}
//--------------------------------------------------------------------------------------
// ?onEnter@AIGuardRetaliatePickUpCrateState@@ present-unmatched
StateReturnType AIGuardRetaliatePickUpCrateState::onEnter( void )
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
// ?update@AIGuardRetaliatePickUpCrateState@@ present-unmatched
StateReturnType AIGuardRetaliatePickUpCrateState::update( void )
{
	return AIPickUpCrateState::update();
}

//--------------------------------------------------------------------------------------
// ?onExit@AIGuardRetaliatePickUpCrateState@@ present-unmatched
void AIGuardRetaliatePickUpCrateState::onExit( StateExitType status )
{
	
}

//-- AIGuardRetaliateAttackAggressorState ------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0AIGuardRetaliateAttackAggressorState@@ present-unmatched
AIGuardRetaliateAttackAggressorState::AIGuardRetaliateAttackAggressorState( StateMachine *machine ) : 
	State( machine, "AIGuardRetaliateAttackAggressorState" )
{
	m_attackState = NULL;
}
#ifdef STATE_MACHINE_DEBUG
//----------------------------------------------------------------------------------------------------------
// ?getName@AIGuardRetaliateAttackAggressorState@@ present-unmatched
AsciiString AIGuardRetaliateAttackAggressorState::getName(  ) const
{
	AsciiString name = m_name;
	name.concat("/ ");
	if (m_attackState) name.concat(m_attackState->getName());
	else name.concat("*NULL m_attackState");
	return name;
}
#endif

//-------------------------------------------------------------------------------------------------
// ?onEnter@AIGuardRetaliateAttackAggressorState@@ present-unmatched
StateReturnType AIGuardRetaliateAttackAggressorState::onEnter( void )
{
	Object *obj = getMachineOwner();
	ObjectID nemID = INVALID_ID;

	//Get the specified nemesis. If he doesn't exist... look at the object that damaged
	//us last.
	Object *nemesis = TheGameLogic->findObjectByID( getGuardMachine()->getNemesisID() );

	BodyModuleInterface *body = obj->getBodyModule();
	if( !nemesis && body && body->getLastDamageInfo()->in.m_sourceID && body->getLastDamageInfo()->in.m_damageType != DAMAGE_HEALING ) 
	{
		nemID = obj->getBodyModule()->getLastDamageInfo()->in.m_sourceID;
		nemesis = TheGameLogic->findObjectByID( nemID );
		if( nemesis && obj->getRelationship( nemesis ) == ENEMIES )
		{
			getGuardMachine()->setNemesisID(nemID);
		}
	}

	if( !nemesis )
	{
		DEBUG_LOG(("Unexpected NULL nemesis in AIGuardRetaliateAttackAggressorState.\n"));
		return STATE_SUCCESS;
	}

	Coord3D pos = *getGuardMachine()->getPositionToGuard();

	Real range = TheAI->getAdjustedVisionRangeForObject(obj, AI_VISIONFACTOR_OWNERTYPE | AI_VISIONFACTOR_MOOD);

	m_exitConditions.m_center = pos;
	m_exitConditions.m_attackGiveUpFrame = TheGameLogic->getFrame() + TheAI->getAiData()->m_guardChaseUnitFrames;
	m_exitConditions.m_radiusSqr = sqr( range + AIGuardRetaliateMachine::getStdGuardRange( obj ) );
	m_exitConditions.m_conditionsToConsider = ( GuardRetaliateExitConditions::ATTACK_ExitIfExpiredDuration | 
																						  GuardRetaliateExitConditions::ATTACK_ExitIfOutsideRadius |
																						  GuardRetaliateExitConditions::ATTACK_ExitIfNoUnitFound );

	m_attackState = newInstance(AIAttackState)(getMachine(), false, true, false, &m_exitConditions);
	m_attackState->getMachine()->setGoalObject(nemesis);

	StateReturnType returnVal = m_attackState->onEnter();
	if (returnVal == STATE_CONTINUE) {
		return STATE_CONTINUE;
	}

	// if we had no one to attack, we were successful, so go to the next state.
	return STATE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?onExit@AIGuardRetaliateAttackAggressorState@@ present-unmatched
void AIGuardRetaliateAttackAggressorState::onExit( StateExitType status )
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
// ?crc@AIGuardRetaliateAttackAggressorState@@ present-unmatched
void AIGuardRetaliateAttackAggressorState::crc( Xfer *xfer )
{

}

//-------------------------------------------------------------------------------------------------
// ?xfer@AIGuardRetaliateAttackAggressorState@@ present-unmatched
void AIGuardRetaliateAttackAggressorState::xfer( Xfer *xfer )
{
  // version
  XferVersion currentVersion = 1;
  XferVersion version = currentVersion;
  xfer->xferVersion( &version, currentVersion );

}

//-------------------------------------------------------------------------------------------------
// ?loadPostProcess@AIGuardRetaliateAttackAggressorState@@ present-unmatched
void AIGuardRetaliateAttackAggressorState::loadPostProcess()
{
	onEnter();
}

// Native BFME 1 lookup visible for the donor-based state update below.
// Its hash-map storage and complete 82-byte body are independently matched.
#include <hash_map>
struct Rva0015F0F0Lookup
{
    char m_at00[0xb0];
    _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> > m_atB0;
};
inline __declspec(noinline) Object *GameLogic::findObjectByID(ObjectID id)
{
    if (id == INVALID_ID) return 0;
    Rva0015F0F0Lookup *view = reinterpret_cast<Rva0015F0F0Lookup *>(this);
    _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> >::iterator it = view->m_atB0.find((int)id);
    if (it == view->m_atB0.end()) return 0;
    return (*it).second;
}

// BFME 2 donor AIGuardRetaliateStates.cpp update at 0x00545A46.
class Rva0015EBE0State { public: int queryGuardContain(); };
extern GameLogic *TheGameLogic;

struct Rva0015F0F0Horde;
struct Rva0015F0F0Contain;
struct Rva0015F0F0Machine;
struct Rva0015F0F0Substate;
struct Rva0015F0F0Condition;

struct Rva0015F0F0Horde {
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7C();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8C();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9C();
    virtual void slotA0();
    virtual void slotA4();
    virtual void slotA8();
    virtual void slotAC();
    virtual void slotB0();
    virtual void slotB4();
    virtual void slotB8();
    virtual void slotBC();
    virtual void slotC0();
    virtual void slotC4();
    virtual void slotC8();
    virtual void slotCC();
    virtual void slotD0();
    virtual void slotD4();
    virtual void slotD8();
    virtual void slotDC();
    virtual void slotE0();
    virtual void slotE4();
    virtual void slotE8();
    virtual void slotEC();
    virtual void slotF0();
    virtual void slotF4();
    virtual void slotF8();
    virtual void slotFC();
    virtual void slot100();
    virtual void slot104();
    virtual void slot108();
    virtual void slot10C();
    virtual void slot110();
    virtual void slot114();
    virtual void slot118();
    virtual void slot11C();
    virtual void slot120();
    virtual void slot124();
    virtual void slot128();
    virtual void slot12C();
    virtual bool slot130(Object *);
    virtual void slot134();
    virtual void slot138();
    virtual void slot13C();
    virtual void slot140();
    virtual void slot144();
    virtual void slot148();
    virtual void slot14C();
    virtual void slot150();
    virtual void slot154();
    virtual void slot158();
    virtual void slot15C();
    virtual void slot160();
    virtual void slot164();
    virtual void slot168();
    virtual void slot16C();
    virtual void slot170();
    virtual void slot174();
    virtual void slot178();
    virtual void slot17C();
    virtual void slot180();
    virtual void slot184();
    virtual void slot188();
    virtual void slot18C();
    virtual void slot190();
    virtual void slot194();
    virtual void slot198();
    virtual void slot19C();
    virtual void slot1A0();
    virtual void slot1A4();
    virtual void slot1A8();
    virtual void slot1AC();
    virtual void slot1B0();
    virtual void slot1B4();
    virtual void slot1B8();
    virtual void slot1BC();
    virtual void slot1C0();
    virtual void slot1C4();
    virtual void slot1C8();
    virtual void slot1CC();
    virtual void slot1D0();
    virtual void slot1D4();
    virtual void slot1D8();
    virtual void slot1DC();
    virtual void slot1E0();
    virtual void slot1E4();
    virtual void slot1E8();
    virtual void slot1EC();
    virtual void slot1F0();
    virtual void slot1F4();
    virtual void slot1F8();
    virtual int slot1FC(int);
};
struct Rva0015F0F0Contain {
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual Rva0015F0F0Horde *slot68();
};
struct Rva0015F0F0Object {
    char m_at00[0x74]; int m_at74;
    char m_at78[0x90 - 0x78]; unsigned int m_at90;
    char m_at94[0x1fc - 0x94]; Rva0015F0F0Contain *m_at1fc;
    char m_at200[4]; AIUpdateInterface *m_at204;
    char m_at208[0x344 - 0x208]; unsigned char m_at344;
    int getID() const { return m_at74; }
    bool testDead() const { return (m_at344 & 1) != 0; }
};
struct Rva0015F0F0Machine {
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38(Object *);
    char m_at04[12]; Rva0015F0F0Object *m_at10;
    char m_at14[0x50 - 0x14]; int m_at50;
    int getNemesisID() const { return m_at50; }
    void setNemesisID(int id) { m_at50 = id; }
    Rva0015F0F0Object *getOwner() const { return m_at10; }
};
struct Rva0015F0F0Condition {
    virtual bool slot00(StateMachine *);
    char m_at04[0x18];
};
struct Rva0015F0F0Substate {
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual int slot18();
};
class Rva0015F0F0 {
public:
    int method();
    Rva0015F0F0Machine *getMachine() const { return m_at1c; }
    Rva0015F0F0Machine *getGuardMachine() const { return getMachine(); }
    Rva0015F0F0Object *getMachineOwner() const { return getMachine()->getOwner(); }
    char m_at00[0x1c]; Rva0015F0F0Machine *m_at1c;
    char m_at20[4]; Rva0015F0F0Condition m_at24;
    Rva0015F0F0Substate *m_at40;
};

StateReturnType AIGuardRetaliateAttackAggressorState::update()
{
    Rva0015F0F0 *view = reinterpret_cast<Rva0015F0F0 *>(this);
    Rva0015F0F0Machine *machine = view->getGuardMachine();
    Rva0015F0F0Object *target = (Rva0015F0F0Object *)TheGameLogic->findObjectByID((ObjectID)machine->getNemesisID());
    if (target && (target->testDead())) target = 0;
    Rva0015F0F0Object *goal = (Rva0015F0F0Object *)((StateMachine *)machine)->getGoalObject();
    if (goal && (goal->testDead())) goal = 0;
    Rva0015F0F0Object *owner = view->getMachineOwner();
    if (!goal)
    {
        if (!target) {
            target = (Rva0015F0F0Object *)((Rva0015EBE0State *)this)->queryGuardContain();
            if (!target) return STATE_SUCCESS;
        }
        owner->m_at204->friend_setGoalObject((Object *)target);
        view->getGuardMachine()->setNemesisID(target->getID());
        view->getMachine()->slot38((Object *)target);
    }
    Rva0015F0F0Condition *conditions = &view->m_at24;
    if (conditions->slot00((StateMachine *)view->getMachine())) return STATE_SUCCESS;
    if (!view->m_at40) return STATE_SUCCESS;
    bool flag = ((owner->m_at90 >> 28) & 1) != 0;
    Rva0015F0F0Contain *contain = owner->m_at1fc;
    if (contain)
    {
        Rva0015F0F0Horde *horde = contain->slot68();
        if (horde && target)
        {
            if (horde->slot130((Object *)target)) flag = true;
            int reportedID = horde->slot1FC(target->getID());
            if (reportedID == target->getID()) flag = true;
        }
    }
    if (flag)
    {
        unsigned int frame = *(unsigned int *)((char *)TheGameLogic + 0x3c) + 20;
        unsigned int &deadline = *(unsigned int *)((char *)this + 0x3c);
        if (deadline < frame) deadline = frame;
    }
    return (StateReturnType)view->m_at40->slot18();
}
