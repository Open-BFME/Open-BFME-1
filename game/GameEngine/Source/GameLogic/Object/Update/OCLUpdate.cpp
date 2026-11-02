// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: OCLUpdate.cpp /////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, August2002
// Desc:   Update Spits out an OCL on a timer
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#include "Common/RandomValue.h"
#include "Common/Xfer.h"
#include "Common/Player.h"
#include "Common/PlayerTemplate.h"
#include "Common/UnicodeString.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/OCLUpdate.h"
#include "GameLogic/TerrainLogic.h"

//-------------------------------------------------------------------------------------------------
void parseFactionObjectCreationList( INI *ini, void *instance, void *store, const void *userData )
{
	OCLUpdateModuleData::FactionOCLInfo info;
	info.m_factionName = "";
	info.m_ocl = 0;

	const char *token = ini->getNextToken( ini->getSepsColon() );

	if ( stricmp(token, "Faction") == 0 )
	{
		token = ini->getNextTokenOrNull( ini->getSepsColon() );
		if (!token)	throw INI_INVALID_DATA;

		info.m_factionName = token;
	}
	else
		throw INI_INVALID_DATA;


	token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( stricmp(token, "OCL") == 0 )
		ini->parseObjectCreationList( ini, instance, &info.m_ocl, NULL );
	else
		throw INI_INVALID_DATA;

	// Insert the info into the ocl hashmap
	OCLUpdateModuleData::FactionOCLList * theList = (OCLUpdateModuleData::FactionOCLList*)store;
	theList->push_back(info);
	
}  // end parseFactionObjectCreationList

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/Object/Update/OCLUpdateModuleData.cpp
// ??0OCLUpdateModuleData@@QAE@XZ present-unmatched
OCLUpdateModuleData::OCLUpdateModuleData()
{
	m_minDelay = 0;
	m_maxDelay = 0;
	m_ocl = NULL;
	m_factionOCL.clear();
	m_isCreateAtEdge = FALSE;
	m_isFactionTriggered = FALSE;
}

//-------------------------------------------------------------------------------------------------
/*static*/ void OCLUpdateModuleData::buildFieldParse(MultiIniFieldParse& p) 
{
  UpdateModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] = 
	{
		{ "OCL",					INI::parseObjectCreationList,		NULL, offsetof( OCLUpdateModuleData, m_ocl ) },
		{ "FactionOCL",		parseFactionObjectCreationList,	NULL, offsetof( OCLUpdateModuleData, m_factionOCL ) },
		{ "MinDelay",			INI::parseDurationUnsignedInt,	NULL, offsetof( OCLUpdateModuleData, m_minDelay ) },
		{ "MaxDelay",			INI::parseDurationUnsignedInt,	NULL, offsetof( OCLUpdateModuleData, m_maxDelay ) },
		{ "CreateAtEdge",	INI::parseBool,									NULL, offsetof( OCLUpdateModuleData, m_isCreateAtEdge ) },
		{ "FactionTriggered",	INI::parseBool,							NULL, offsetof( OCLUpdateModuleData, m_isFactionTriggered ) },
		{ 0, 0, 0, 0 }
	};
  p.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/Object/Update/OCLUpdateConstructor.cpp
// ??0OCLUpdate@@QAE@PAVThing@@PBVModuleData@@@Z present-unmatched
OCLUpdate::OCLUpdate( Thing *thing, const ModuleData* moduleData ) : UpdateModule( thing, moduleData )
{
	m_nextCreationFrame = 0;
	m_timerStartedFrame = 0;
	m_isFactionNeutral = TRUE;
	m_currentPlayerColor = 0;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1OCLUpdate@@MAE@XZ present-unmatched

// Retail OCLUpdate::update (0x00298BB0) is implemented in OCLUpdateUpdate.cpp.
// Preserve the existing native string equality body at 0x00832760 in this TU.
template bool _STL::operator==<char, _STL::char_traits<char>, _STL::allocator<char> >(
    const _STL::string &, const _STL::string &);
// Keep the unique native const-iterator helpers when removing their old caller.
template OCLUpdateModuleData::FactionOCLList::const_iterator
    OCLUpdateModuleData::FactionOCLList::begin() const;
template OCLUpdateModuleData::FactionOCLList::const_iterator
    OCLUpdateModuleData::FactionOCLList::end() const;
template const OCLUpdateModuleData::FactionOCLInfo &
    OCLUpdateModuleData::FactionOCLList::const_iterator::operator*() const;
template OCLUpdateModuleData::FactionOCLList::const_iterator &
    OCLUpdateModuleData::FactionOCLList::const_iterator::operator++();

//-------------------------------------------------------------------------------------------------
// ?resetTimer@OCLUpdate@@QAEXXZ present-unmatched
void OCLUpdate::resetTimer()
{
	setNextCreationFrame();
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?shouldCreate@OCLUpdate@@IAE_NXZ present-unmatched
Bool OCLUpdate::shouldCreate()
{
	if( TheGameLogic->getFrame() < m_nextCreationFrame )
		return FALSE;//too soon

	if( getObject()->getStatusBits().test( OBJECT_STATUS_UNDER_CONSTRUCTION ) )
		return FALSE;// not built yet

	return TRUE;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?setNextCreationFrame@OCLUpdate@@IAEXXZ present-unmatched
void OCLUpdate::setNextCreationFrame()
{
	UnsignedInt delay = GameLogicRandomValue( getOCLUpdateModuleData()->m_minDelay, 
																						getOCLUpdateModuleData()->m_maxDelay );
	m_timerStartedFrame = TheGameLogic->getFrame();
	m_nextCreationFrame = m_timerStartedFrame + delay;

}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
Real OCLUpdate::getCountdownPercent() const
{
	UnsignedInt now = TheGameLogic->getFrame();

	return 1.0f - (( m_nextCreationFrame - now ) / (float)( m_nextCreationFrame - m_timerStartedFrame ));
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?getRemainingFrames@OCLUpdate@@QBEIXZ present-unmatched
UnsignedInt OCLUpdate::getRemainingFrames() const
{
	UnsignedInt now = TheGameLogic->getFrame();

	return ( m_nextCreationFrame - now );
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@OCLUpdate@@MAEXPAVXfer@@@Z present-unmatched
void OCLUpdate::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@OCLUpdate@@MAEXPAVXfer@@@Z present-unmatched
void OCLUpdate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpdateModule::xfer( xfer );

	// next creation frame
	xfer->xferUnsignedInt( &m_nextCreationFrame );

	// timer stated frame
	xfer->xferUnsignedInt( &m_timerStartedFrame );

	// faction status
	xfer->xferBool( &m_isFactionNeutral );
	
	// current owning player color
	xfer->xferInt( &m_currentPlayerColor );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@OCLUpdate@@MAEXXZ present-unmatched
void OCLUpdate::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
