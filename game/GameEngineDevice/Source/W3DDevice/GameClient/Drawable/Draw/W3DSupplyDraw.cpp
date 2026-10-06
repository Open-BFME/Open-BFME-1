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

// FILE: W3DSupplyDraw.cpp ////////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, September 2002
// Desc: Draw module reacts to SupplyStatus setting by hiding an equal number of the specified bone array.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "W3DDevice/GameClient/Module/W3DSupplyDraw.h"

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DSupplyDrawConstructors.cpp
// ??0W3DSupplyDrawModuleData@@QAE@XZ present-unmatched
W3DSupplyDrawModuleData::W3DSupplyDrawModuleData() 
{
}

//-------------------------------------------------------------------------------------------------
// ??1W3DSupplyDrawModuleData@@UAE@XZ present-unmatched
W3DSupplyDrawModuleData::~W3DSupplyDrawModuleData()
{
}

//-------------------------------------------------------------------------------------------------
// ?buildFieldParse@W3DSupplyDrawModuleData@@ present-unmatched
void W3DSupplyDrawModuleData::buildFieldParse(MultiIniFieldParse& p) 
{
  W3DModelDrawModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] = 
	{
		{ "SupplyBonePrefix", INI::parseAsciiString, NULL, offsetof(W3DSupplyDrawModuleData, m_supplyBonePrefix) },

		{ 0, 0, 0, 0 }
	};
  p.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DSupplyDrawConstructors.cpp
// ??0W3DSupplyDraw@@QAE@PAVThing@@PBVModuleData@@@Z present-unmatched
W3DSupplyDraw::W3DSupplyDraw( Thing *thing, const ModuleData* moduleData ) : W3DModelDraw( thing, moduleData )
{	 
	m_totalBones = -1;
	m_lastNumberShown = 0;
}

//-------------------------------------------------------------------------------------------------
// ??1W3DSupplyDraw@@MAE@XZ present-unmatched
W3DSupplyDraw::~W3DSupplyDraw()
{
}

// W3DSupplyDraw::updateDrawModuleSupplyStatus: retail's body (0x0077DDF0) is
// W3DSupplyDrawUpdate.cpp; Zero Hour's version is not defined here.

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@W3DSupplyDraw@@MAEXPAVXfer@@@Z present-unmatched
void W3DSupplyDraw::crc( Xfer *xfer )
{

	// extend base class
	W3DModelDraw::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@W3DSupplyDraw@@MAEXPAVXfer@@@Z present-unmatched
void W3DSupplyDraw::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	W3DModelDraw::xfer( xfer );

	// Graham says there's no data to save here

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@W3DSupplyDraw@@MAEXXZ present-unmatched
void W3DSupplyDraw::loadPostProcess( void )
{

	// extend base class
	W3DModelDraw::loadPostProcess();

}  // end loadPostProcess


