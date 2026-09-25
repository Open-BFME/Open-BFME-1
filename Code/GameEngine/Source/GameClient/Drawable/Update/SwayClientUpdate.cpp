// cl: /DNDEBUG /MD /EHsc /DBFME_MODULE_NO_MPO /Ireference/shims/swayclientupdate /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
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

// FILE: SwayClientUpdate.cpp //////////////////////////////////////////////////////////////////
// Author: Matthew D. Campbell, May 2002
// Desc:   Tree sway client update module
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameClient/Drawable.h"
#include "GameClient/Module/SwayClientUpdate.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/RandomValue.h"
#include "Common/PerfTimer.h"
#include "Common/Xfer.h"
#include "Common/GameEngine.h"
#include "GameLogic/Object.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/GameLogic.h"

extern const Real BfmeZeroRange;

class BfmeCalc919G
{
public:
	Int bfmeCalc919G();
};

struct Rva00604840StatusWord
{
	UnsignedInt m_word;

	Bool test( Int bit ) const
	{
		return (m_word & (1UL << bit)) != 0;
	}
};

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
SwayClientUpdate::SwayClientUpdate( Thing *thing, const ModuleData* moduleData ) :
	ClientUpdateModule( thing, moduleData ),
	m_curDelta(0),
	m_curValue(0),
	m_curAngle(0),
	m_curAngleLimit(0),
	m_leanAngle(0),
	m_swaying(true),
	m_unused(false),
	_bfme_hole_a(0),
	_bfme_hole_b(0),
	m_curVersion(-1)	// so that we never match the first time
{

	// don't do updateSway here; wait till the first time we go thru our update loop.
	//updateSway();

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1SwayClientUpdate@@MAE@XZ present-unmatched
SwayClientUpdate::~SwayClientUpdate( void )
{

}

//-------------------------------------------------------------------------------------------------
// Update the sway parameters.
//-------------------------------------------------------------------------------------------------
void SwayClientUpdate::updateSway()
{
	const BreezeInfo& info = TheScriptEngine->getBreezeInfo();
	if (info.m_randomness == BfmeZeroRange)
	{
		m_curValue = 0;
	} 
	Real delta = info.m_randomness * 0.5f;
	m_curAngleLimit = info.m_intensity * GetGameClientRandomValueReal(1.0f - delta, 1.0f + delta, const_cast<char *>("F:\\bfme\\Code\\gameengine\\Source\\GameClient\\Drawable\\Update\\SwayClientUpdate.cpp"), 73);
	m_curDelta = 2 * PI / ((Real)*(const Int *)((const char *)TheGameEngine + 0x34) * info.m_breezePeriod) * GetGameClientRandomValueReal(1.0f - delta, 1.0f + delta, const_cast<char *>("F:\\bfme\\Code\\gameengine\\Source\\GameClient\\Drawable\\Update\\SwayClientUpdate.cpp"), 74);
	m_leanAngle = info.m_lean * GetGameClientRandomValueReal(1.0f - delta, 1.0f + delta, const_cast<char *>("F:\\bfme\\Code\\gameengine\\Source\\GameClient\\Drawable\\Update\\SwayClientUpdate.cpp"), 75);
	m_curVersion			= info.m_breezeVersion;
	Drawable *draw = getDrawable();
	if (draw)
	{
		const Matrix3D *matrix = reinterpret_cast<const Matrix3D *>(reinterpret_cast<BfmeCalc919G *>(draw)->bfmeCalc919G());
		Real angle = info.m_direction - matrix->Get_Z_Rotation();
		_bfme_hole_a = Sin(angle);
		_bfme_hole_b = Cos(angle);
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** The client update callback. */
//-------------------------------------------------------------------------------------------------
void SwayClientUpdate::clientUpdate( void )
{
	if( !m_swaying )
		return;

	Drawable *draw = getDrawable();

	// if breeze changes, always process the full update, even if not visible, 
	// so that things offscreen won't 'pop' when first viewed
	if (TheScriptEngine->getBreezeInfo().m_breezeVersion != m_curVersion)
	{
		updateSway();
	}
	else
	{
		// Otherwise, only update visible drawables
		if (!draw || !draw->isVisible())
			return;
	}

	m_curValue += m_curDelta;
	if (m_curValue > 2*PI) 
		m_curValue -= 2*PI;
	Real cosine = Sin(m_curValue);

	Real targetAngle = cosine * m_curAngleLimit + m_leanAngle;
	Real deltaAngle = targetAngle - m_curAngle;

	Matrix3D xfrm = *draw->getInstanceMatrix();
	xfrm.In_Place_Pre_Rotate_X(-deltaAngle * _bfme_hole_a);
	xfrm.In_Place_Pre_Rotate_Y(deltaAngle * _bfme_hole_b);
	draw->setInstanceMatrix(&xfrm, false);

	m_curAngle = targetAngle;
	
	// burned things don't sway.
	Object* obj = draw->getObject();
	if( obj && (reinterpret_cast<const Rva00604840StatusWord *>(reinterpret_cast<const char *>(obj) + 0x90)->test( 11 ) ||
				*(reinterpret_cast<const UnsignedByte *>(reinterpret_cast<const char *>(obj) + 0x344)) & 1) )
		stopSway();

}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@SwayClientUpdate@@MAEXPAVXfer@@@Z present-unmatched
void SwayClientUpdate::crc( Xfer *xfer )
{

	// extend base class
	ClientUpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@SwayClientUpdate@@MAEXPAVXfer@@@Z present-unmatched
void SwayClientUpdate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	ClientUpdateModule::xfer( xfer );

	// cur value
	xfer->xferReal( &m_curValue );

	// cur angle
	xfer->xferReal( &m_curAngle );

	// cur delta
	xfer->xferReal( &m_curDelta );

	// cur angle limit
	xfer->xferReal( &m_curAngleLimit );

	// lean angle
	xfer->xferReal( &m_leanAngle );

	// cur version
	xfer->xferShort( &m_curVersion );

	// swaying
	xfer->xferBool( &m_swaying );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@SwayClientUpdate@@MAEXXZ present-unmatched
void SwayClientUpdate::loadPostProcess( void )
{

	// extend base class
	ClientUpdateModule::loadPostProcess();

	updateSway();

}  // end loadPostProcess
