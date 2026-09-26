// cl: /DBFME_MODULE_NO_MPO /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

// FILE: CreateObjectDie.cpp ///////////////////////////////////////////////////////////////////////////
// Author: Michael S. Booth, January 2002
// Desc:   Create an object upon this object's death
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_OBJECT_STATUS_NAMES
#include "Common/ThingFactory.h"
#include "Common/Xfer.h"
#include "GameLogic/Module/CreateObjectDie.h"
#include "GameLogic/Object.h"
// BFME keeps these helpers out of line; the GeneralsMD headers inline the
// lookup and give createInternal a different return type.
class GameLogic
{
public:
	Object *findObjectByID( int id );
};
extern GameLogic *TheGameLogic;

class ObjectCreationList
{
public:
	void createInternal( const Object *primary, const Object *secondary, UnsignedInt lifetimeFrames ) const;
};

// BFME's CreateObjectDie module data stores its OCL at +0x34.
struct BfmeCreateObjectDieModuleDataView
{
	unsigned char m_unreconstructed[0x34];
	const ObjectCreationList *m_ocl;
};


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/AI/CreateObjectDieModuleDataCtorThunk.cpp
// ??0CreateObjectDieModuleData@@ present-unmatched
CreateObjectDieModuleData::CreateObjectDieModuleData()
{

	m_ocl = NULL;
	m_transferPreviousHealth = FALSE;

}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/*static*/ void CreateObjectDieModuleData::buildFieldParse(MultiIniFieldParse& p)
{
	DieModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] = 
	{
		{ "CreationList",	INI::parseObjectCreationList,		NULL,											offsetof( CreateObjectDieModuleData, m_ocl ) },
		{ "TransferPreviousHealth", INI::parseBool, NULL	,offsetof( CreateObjectDieModuleData, m_transferPreviousHealth ) },
		{ 0, 0, 0, 0 }
	};
	p.add(dataFieldParse);

}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// /DBFME_MODULE_NO_MPO on the cl line above is what makes this byte-exact:
// BFME's Module derives from Snapshot alone, so the vptr MemoryPoolObject would
// contribute is absent and every base offset below it shifts down four bytes.
// Screen it per file, never per family -- InstantDeathBehavior.cpp and
// BridgeTowerBehavior.cpp go RED under the same define, because their
// this-adjusting interface getters are matched against the two-vptr layout.
CreateObjectDie::CreateObjectDie( Thing *thing, const ModuleData* moduleData ) : DieModule( thing, moduleData )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1CreateObjectDie@@ present-unmatched
CreateObjectDie::~CreateObjectDie( void )
{

}

//-------------------------------------------------------------------------------------------------
// Retail RVA 0x00254900 is CreateObjectDie's DieModuleInterface slot 0
// (table 0x010B2A60). BFME checks m_ocl at moduleData+0x34 before looking up
// the damage dealer; its body has no TransferPreviousHealth extension.
//-------------------------------------------------------------------------------------------------
void CreateObjectDie::onDie( const DamageInfo * damageInfo )
{
	if (!isDieApplicable(damageInfo))
		return;

	const BfmeCreateObjectDieModuleDataView *data =
		(const BfmeCreateObjectDieModuleDataView *)getModuleData();
	const ObjectCreationList *ocl = data->m_ocl;
	if (ocl == NULL)
		return;

	// This interface override's this+8 is the ObjectModule object slot
	// ([entry this-8]); volatile preserves retail's reload after the lookup.
	ocl->createInternal(
		*(Object * volatile *)((char *)this + 8),
		TheGameLogic->findObjectByID( damageInfo->in.m_sourceID ),
		0 );
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@CreateObjectDie@@ present-unmatched
void CreateObjectDie::crc( Xfer *xfer )
{

	// extend base class
	DieModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@CreateObjectDie@@ present-unmatched
void CreateObjectDie::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	DieModule::xfer( xfer );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@CreateObjectDie@@ present-unmatched
void CreateObjectDie::loadPostProcess( void )
{

	// extend base class
	DieModule::loadPostProcess();

}  // end loadPostProcess
