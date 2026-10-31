// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/moduledata /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: PoisonedBehavior.cpp /////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, July 2002
// Desc:   Behavior that reacts to poison Damage by continuously damaging us further in an Update
///////////////////////////////////////////////////////////////////////////////////////////////////


// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameLogic/Module/PoisonedBehavior.h"
#include "GameLogic/Damage.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// tinting is all handled in drawable, now, Graham look near the bottom of Drawable::UpdateDrawable()
//static const RGBColor poisonedTint = {0.0f, 1.0f, 0.0f};

//-------------------------------------------------------------------------------------------------
PoisonedBehaviorModuleData::PoisonedBehaviorModuleData()
{
	m_poisonDamageIntervalData = 0; // How often I retake poison damage dealt me
	m_poisonDurationData = 0;				// And how long after the last poison dose I am poisoned
}

//-------------------------------------------------------------------------------------------------
/*static*/ void PoisonedBehaviorModuleData::buildFieldParse(MultiIniFieldParse& p) 
{

	static const FieldParse dataFieldParse[] = 
	{
		{ "PoisonDamageInterval", INI::parseDurationUnsignedInt, NULL, offsetof(PoisonedBehaviorModuleData, m_poisonDamageIntervalData) },
		{ "PoisonDuration", INI::parseDurationUnsignedInt, NULL, offsetof(PoisonedBehaviorModuleData, m_poisonDurationData) },
		{ 0, 0, 0, 0 }
	};

  UpdateModuleData::buildFieldParse(p);
  p.add(dataFieldParse);
}

// The constructor is not placed (targets/game/reverse/identity_evidence/caller-decided-1.md).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1PoisonedBehavior@@MAE@XZ present-unmatched
PoisonedBehavior::~PoisonedBehavior( void )
{
}

//-------------------------------------------------------------------------------------------------
/** Damage has been dealt, this is an opportunity to react to that damage */
//-------------------------------------------------------------------------------------------------
// ?onDamage@PoisonedBehavior@@UAEXPAVDamageInfo@@@Z present-unmatched
void PoisonedBehavior::onDamage( DamageInfo *damageInfo )
{
	if( damageInfo->in.m_damageType == DAMAGE_POISON )
		startPoisonedEffects( damageInfo );
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?onHealing@PoisonedBehavior@@UAEXPAVDamageInfo@@@Z present-unmatched
void PoisonedBehavior::onHealing( DamageInfo *damageInfo )
{
	stopPoisonedEffects();

	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?update@PoisonedBehavior@@UAE?AW4UpdateSleepTime@@XZ: retail body is in PoisonedBehavior_update.cpp

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
UpdateSleepTime PoisonedBehavior::calcSleepTime()
{
	// UPDATE_SLEEP requires a count-of-frames, not an absolute-frame, so subtract 'now' 
	UnsignedInt now = TheGameLogic->getFrame();
	if (m_poisonOverallStopFrame == 0 || m_poisonOverallStopFrame == now)
		return UPDATE_SLEEP_FOREVER;
	return frameToSleepTime(m_poisonDamageFrame, m_poisonOverallStopFrame);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// PoisonedBehavior::startPoisonedEffects (retail 0x00202C10) lives in
// PoisonedBehavior_startPoisonedEffects.cpp.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?stopPoisonedEffects@PoisonedBehavior@@IAEXXZ present-unmatched
void PoisonedBehavior::stopPoisonedEffects()
{
	m_poisonDamageFrame = 0;
	m_poisonOverallStopFrame = 0;
	m_poisonDamageAmount = 0.0f;

	Drawable *myDrawable = getObject()->getDrawable();
	if( myDrawable )
		myDrawable->clearTintStatus( TINT_STATUS_POISONED );// Graham, It has changed, see UpdateDrawable()
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@PoisonedBehavior@@MAEXPAVXfer@@@Z present-unmatched
void PoisonedBehavior::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@PoisonedBehavior@@MAEXPAVXfer@@@Z present-unmatched
void PoisonedBehavior::xfer( Xfer *xfer )
{

	// version 
	const XferVersion currentVersion = 2;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpdateModule::xfer( xfer );

	// poisoned damage frame
	xfer->xferUnsignedInt( &m_poisonDamageFrame );

	// poison overall stop frame
	xfer->xferUnsignedInt( &m_poisonOverallStopFrame );

	// poison damage amount
	xfer->xferReal( &m_poisonDamageAmount );

	if (version >= 2)
	{
		xfer->xferUser(&m_deathType, sizeof(m_deathType));
	}

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@PoisonedBehavior@@MAEXXZ present-unmatched
void PoisonedBehavior::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
