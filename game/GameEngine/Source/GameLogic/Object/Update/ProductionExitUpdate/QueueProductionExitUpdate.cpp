// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/queueproductionexitrallypoint /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: QueueProductionExitUpdate.cpp /////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, January, 2002
// Desc:		Hand off produced Units to me so I can Exit them into the world with my specific style
//					This instance refuses to spit a second out until the first is clear
///////////////////////////////////////////////////////////////////////////////////////////////////

// Zero Hour's Object.h defines getAI inline at its own m_ai offset (0x19C) and this
// unit emits that COMDAT copy; rename it so only retail's 0x000E59A0 (BFME reads
// 0x204) is ?getAI@Object@@QAEPAVAIUpdateInterface@@XZ. Inlined calls are unchanged.
#define getAI getAI_ZHLayout
// The Zero Hour AI.h inline AICommandInterface::aiMoveToPosition compiles to a
// non-retail 142-byte COMDAT here (Zero Hour AICommandParms); this macro turns it
// into a declaration so calls bind to the retail body 0x000D86C0.
#define aiMoveToPosition(a, b) aiMoveToPosition(a, b); void zhInlineAiMoveToPosition(a, b)
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/RandomValue.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "Lib/BaseType.h"
#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/QueueProductionExitUpdate.h"
#undef aiMoveToPosition

//-------------------------------------------------------------------------------------------------
// Retail module registration places this constructor at RVA 0x002D0620.
// The former alias at 0x001F8B80 belongs to DynamicPortalBehaviour.

//-------------------------------------------------------------------------------------------------
// ??1QueueProductionExitUpdate@@MAE@XZ present-unmatched
QueueProductionExitUpdate::~QueueProductionExitUpdate()
{
}

//-------------------------------------------------------------------------------------------------
// ?exitObjectViaDoor@QueueProductionExitUpdate@@UAEXPAVObject@@W4ExitDoorType@@@Z: retail body is in QueueProductionExitUpdateExitObjectViaDoor.cpp


// ?getExitPosition@QueueProductionExitUpdate@@UBE_NAAUCoord3D@@@Z present-unmatched
Bool QueueProductionExitUpdate::getExitPosition( Coord3D& exitPosition ) const
{
	const Object *obj = getObject();
	if (!obj)
		return FALSE;

	const Matrix3D *transform = obj->getTransformMatrix();

	const QueueProductionExitUpdateModuleData *md = getQueueProductionExitUpdateModuleData();

	Vector3 loc;
	loc.Set( md->m_unitCreatePoint.x, md->m_unitCreatePoint.y, md->m_unitCreatePoint.z );
	transform->Transform_Vector( *transform, loc, &loc );

	exitPosition.x = loc.X;
	exitPosition.y = loc.Y;
	exitPosition.z = loc.Z;
	
	return TRUE;

}


//-------------------------------------------------------------------------------------------------
ExitDoorType QueueProductionExitUpdate::reserveDoorForExit( const ThingTemplate* objType, Object *specificObject )
{
	return isFreeToExit() ? DOOR_1 : DOOR_NONE_AVAILABLE;
}

//-------------------------------------------------------------------------------------------------
// ?unreserveDoorForExit@QueueProductionExitUpdate@@UAEXW4ExitDoorType@@@Z present-unmatched
void QueueProductionExitUpdate::unreserveDoorForExit( ExitDoorType exitDoor )
{
	/* nothing */
}

//-------------------------------------------------------------------------------------------------
Bool QueueProductionExitUpdate::isFreeToExit() const
{
	Bool stillBursting = (m_currentBurstCount > 0);
	Bool stillDelaying = (m_currentDelay != 0);

	if ( stillBursting )
	{
		return TRUE;
	}

	return ( ! stillDelaying );
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?exitObjectByBudding@QueueProductionExitUpdate@@UAEXPAVObject@@0@Z: retail body is in QueueProductionExitInterface.cpp





// The retail-proven definition is in QueueProductionExitUpdateGetNaturalRallyPoint.cpp.

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@QueueProductionExitUpdate@@MAEXPAVXfer@@@Z present-unmatched
void QueueProductionExitUpdate::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@QueueProductionExitUpdate@@MAEXPAVXfer@@@Z present-unmatched
void QueueProductionExitUpdate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpdateModule::xfer( xfer );

	// current delay
	xfer->xferUnsignedInt( &m_currentDelay );

	// rally point
	xfer->xferCoord3D( &m_rallyPoint );

	// rally point exists
	xfer->xferBool( &m_rallyPointExists );

	// creation clear distance
	xfer->xferReal( &m_creationClearDistance );

	// current burst count
	xfer->xferUnsignedInt( &m_currentBurstCount );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@QueueProductionExitUpdate@@MAEXXZ present-unmatched
void QueueProductionExitUpdate::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
