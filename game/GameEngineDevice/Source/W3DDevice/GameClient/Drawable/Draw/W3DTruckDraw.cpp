// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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

// FILE: W3DTruckDraw.cpp 
// Draw Trucks.  Actually, this draws rocket buggies.
// Author: John Ahlquist, March 2002

#include <stdlib.h>
#include <math.h>

#include "Common/Thing.h"
#include "Common/ThingFactory.h"
#include "Common/GameAudio.h"
#include "Common/GlobalData.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameClient/ParticleSys.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/GameLogic.h"		// for logic frame count
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/ScriptEngine.h"
#include "W3DDevice/GameClient/W3DGameClient.h"
#include "W3DDevice/GameClient/Module/W3DTruckDraw.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// Retail W3DTruckDrawModuleData constructor (0x0077F830) is implemented in W3DTruckDrawModuleDataConstructor.cpp.

// Retail W3DTruckDrawModuleData destructor (0x0077F920) is implemented in W3DTruckDrawModuleDataDestructor.cpp.

//-------------------------------------------------------------------------------------------------
// ?buildFieldParse@W3DTruckDrawModuleData@@ present-unmatched
void W3DTruckDrawModuleData::buildFieldParse(MultiIniFieldParse& p) 
{
  W3DModelDrawModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] = 
	{
		{ "Dust", INI::parseAsciiString, NULL, offsetof(W3DTruckDrawModuleData, m_dustEffectName) },
		{ "DirtSpray", INI::parseAsciiString, NULL, offsetof(W3DTruckDrawModuleData, m_dirtEffectName) },
		{ "PowerslideSpray", INI::parseAsciiString, NULL, offsetof(W3DTruckDrawModuleData, m_powerslideEffectName) },

		{ "LeftFrontTireBone", INI::parseAsciiString, NULL, offsetof(W3DTruckDrawModuleData, m_frontLeftTireBoneName) },
		{ "RightFrontTireBone", INI::parseAsciiString, NULL, offsetof(W3DTruckDrawModuleData, m_frontRightTireBoneName) },
		{ "LeftRearTireBone", INI::parseAsciiString, NULL, offsetof(W3DTruckDrawModuleData, m_rearLeftTireBoneName) },
		{ "RightRearTireBone", INI::parseAsciiString, NULL, offsetof(W3DTruckDrawModuleData, m_rearRightTireBoneName) },
		{ "MidLeftFrontTireBone", INI::parseAsciiString, NULL, offsetof(W3DTruckDrawModuleData, m_midFrontLeftTireBoneName) },
		{ "MidRightFrontTireBone", INI::parseAsciiString, NULL, offsetof(W3DTruckDrawModuleData, m_midFrontRightTireBoneName) },
		{ "MidLeftRearTireBone", INI::parseAsciiString, NULL, offsetof(W3DTruckDrawModuleData, m_midRearLeftTireBoneName) },
		{ "MidRightRearTireBone", INI::parseAsciiString, NULL, offsetof(W3DTruckDrawModuleData, m_midRearRightTireBoneName) },
		{ "MidLeftMidTireBone", INI::parseAsciiString, NULL, offsetof(W3DTruckDrawModuleData, m_midMidLeftTireBoneName) },
		{ "MidRightMidTireBone", INI::parseAsciiString, NULL, offsetof(W3DTruckDrawModuleData, m_midMidRightTireBoneName) },

		{ "TireRotationMultiplier", INI::parseReal, NULL, offsetof(W3DTruckDrawModuleData, m_rotationSpeedMultiplier) },
		{ "PowerslideRotationAddition", INI::parseReal, NULL, offsetof(W3DTruckDrawModuleData, m_powerslideRotationAddition) },
		{ "CabBone", INI::parseAsciiString, NULL, offsetof(W3DTruckDrawModuleData, m_cabBoneName) },
		{ "TrailerBone", INI::parseAsciiString, NULL, offsetof(W3DTruckDrawModuleData, m_trailerBoneName) },
		{ "CabRotationMultiplier", INI::parseReal, NULL, offsetof(W3DTruckDrawModuleData, m_cabRotationFactor) },
		{ "TrailerRotationMultiplier", INI::parseReal, NULL, offsetof(W3DTruckDrawModuleData, m_trailerRotationFactor) },
		{ "RotationDamping", INI::parseReal, NULL, offsetof(W3DTruckDrawModuleData, m_rotationDampingFactor) },

		{ 0, 0, 0, 0 }
	};
  p.add(dataFieldParse);
}

// Retail W3DTruckDraw constructor (0x0077FB20) is implemented in W3DTruckDrawConstructor.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1W3DTruckDraw@@MAE@XZ present-unmatched
W3DTruckDraw::~W3DTruckDraw()
{
	tossEmitters();
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?tossEmitters@W3DTruckDraw@@IAEXXZ present-unmatched
void W3DTruckDraw::tossEmitters()
{
	if (m_dustEffect)
	{
		m_dustEffect->attachToObject(NULL);
		m_dustEffect->destroy();
		m_dustEffect = NULL;
	}
	if (m_dirtEffect)
	{
		m_dirtEffect->attachToObject(NULL);
		m_dirtEffect->destroy();
		m_dirtEffect = NULL;
	}
	if (m_powerslideEffect)
	{
		m_powerslideEffect->attachToObject(NULL);
		m_powerslideEffect->destroy();
		m_powerslideEffect = NULL;
	}
}

//-------------------------------------------------------------------------------------------------
// ?setFullyObscuredByShroud@W3DTruckDraw@@UAEX_N@Z present-unmatched
void W3DTruckDraw::setFullyObscuredByShroud(Bool fullyObscured)
{
	if (fullyObscured != getFullyObscuredByShroud())
	{
		if (fullyObscured)
			tossEmitters();
		else
			createEmitters();
	}
	W3DModelDraw::setFullyObscuredByShroud(fullyObscured);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/**

 * Start creating debris from the tank treads
 */
// ?createEmitters@W3DTruckDraw@@IAEXXZ present-unmatched
void W3DTruckDraw::createEmitters( void )
{
	if (getDrawable()->isDrawableEffectivelyHidden())
		return;
	if (getW3DTruckDrawModuleData())
	{
		const ParticleSystemTemplate *sysTemplate;

		if (!m_dustEffect) {

			sysTemplate = TheParticleSystemManager->findTemplate(getW3DTruckDrawModuleData()->m_dustEffectName);
			if (sysTemplate)
			{
				m_dustEffect = TheParticleSystemManager->createParticleSystem( sysTemplate );
				m_dustEffect->attachToObject(getDrawable()->getObject());
				// important: mark it as do-not-save, since we'll just re-create it when we reload.
				m_dustEffect->setSaveable(FALSE);
			}	else {
				if (!getW3DTruckDrawModuleData()->m_dustEffectName.isEmpty()) {
					DEBUG_LOG(("*** ERROR - Missing particle system '%s' in thing '%s'\n", 
						getW3DTruckDrawModuleData()->m_dustEffectName.str(), getDrawable()->getObject()->getTemplate()->getName().str()));
				}
			}

		}	 
		if (!m_dirtEffect) {
			sysTemplate = TheParticleSystemManager->findTemplate(getW3DTruckDrawModuleData()->m_dirtEffectName);
			if (sysTemplate)
			{
				m_dirtEffect = TheParticleSystemManager->createParticleSystem( sysTemplate );
				m_dirtEffect->attachToObject(getDrawable()->getObject());
				// important: mark it as do-not-save, since we'll just re-create it when we reload.
				m_dirtEffect->setSaveable(FALSE);
			}	else {
				if (!getW3DTruckDrawModuleData()->m_dirtEffectName.isEmpty()) {
					DEBUG_LOG(("*** ERROR - Missing particle system '%s' in thing '%s'\n", 
						getW3DTruckDrawModuleData()->m_dirtEffectName.str(), getDrawable()->getObject()->getTemplate()->getName().str()));
				}
			}
		}
		if (!m_powerslideEffect) {
			sysTemplate = TheParticleSystemManager->findTemplate(getW3DTruckDrawModuleData()->m_powerslideEffectName);
			if (sysTemplate)
			{
				m_powerslideEffect = TheParticleSystemManager->createParticleSystem( sysTemplate );
				m_powerslideEffect->attachToObject(getDrawable()->getObject());
				// important: mark it as do-not-save, since we'll just re-create it when we reload.
				m_powerslideEffect->setSaveable(FALSE);
			}	else {
				if (!getW3DTruckDrawModuleData()->m_powerslideEffectName.isEmpty()) {
					DEBUG_LOG(("*** ERROR - Missing particle system '%s' in thing '%s'\n", 
						getW3DTruckDrawModuleData()->m_powerslideEffectName.str(), getDrawable()->getObject()->getTemplate()->getName().str()));
				}
			}
		}
	}
	
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/**
 * Stop creating debris from the tank treads
 */
// ?enableEmitters@W3DTruckDraw@@IAEX_N@Z present-unmatched
void W3DTruckDraw::enableEmitters( Bool enable  )
{
	// don't check... if we are hidden the first time thru, then we'll never create the emitters.
	// eg, if we are loading a game and the unit is in a tunnel, he'll never get emitteres even when he exits.
	//if (!m_effectsInitialized) 
	{
		createEmitters();
		m_effectsInitialized=true;
	}
	if (m_dustEffect)
	{
		if (enable) 
			m_dustEffect->start();
		else
			m_dustEffect->stop();
	}
	if (m_dirtEffect)
	{
		if (enable) 
			m_dirtEffect->start();
		else
			m_dirtEffect->stop();
	}
	if (m_powerslideEffect)
	{
		if (!enable) 
			m_powerslideEffect->stop();
	}
}
// Retail W3DTruckDraw::updateBones (0x00780170) is implemented in W3DTruckDrawUpdateBones.cpp.

//-------------------------------------------------------------------------------------------------
// ?setHidden@W3DTruckDraw@@UAEX_N@Z present-unmatched
void W3DTruckDraw::setHidden(Bool h)
{
	W3DModelDraw::setHidden(h);
	if (h)
	{
		enableEmitters(false);
	}
}

// Retail W3DTruckDraw::onRenderObjRecreated (0x00781440) is implemented in W3DTruckDrawUpdateBones.cpp.

// Retail W3DTruckDraw::doDrawModule at RVA 0x00781660 is implemented in W3DTruckDrawDoDrawModule.cpp.

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@W3DTruckDraw@@MAEXPAVXfer@@@Z present-unmatched
void W3DTruckDraw::crc( Xfer *xfer )
{

	// extend base class
	W3DModelDraw::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@W3DTruckDraw@@MAEXPAVXfer@@@Z present-unmatched
void W3DTruckDraw::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	W3DModelDraw::xfer( xfer );

	// John A and Mark W say there is no data to save here

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@W3DTruckDraw@@MAEXXZ present-unmatched
void W3DTruckDraw::loadPostProcess( void )
{

	// extend base class
	W3DModelDraw::loadPostProcess();

	// toss any existing ones (no need to re-create; we'll do that on demand)
	tossEmitters();

}  // end loadPostProcess
