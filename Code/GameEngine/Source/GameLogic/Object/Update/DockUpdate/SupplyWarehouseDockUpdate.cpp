// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: SupplyWarehouseDockUpdate.h /////////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood Feb 2002
// Desc:   The action of this dock update is identifying who is docking and either taking Boxes away or giving them
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GlobalData.h"
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameLogic/Module/SupplyWarehouseDockUpdate.h"
#include "GameLogic/Module/SupplyTruckAIUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/AIPathfind.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
SupplyWarehouseDockUpdateModuleData::SupplyWarehouseDockUpdateModuleData( void )
{
	m_startingBoxesData = 1;
	m_deleteWhenEmpty = FALSE;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/*static*/ void SupplyWarehouseDockUpdateModuleData::buildFieldParse(MultiIniFieldParse& p)
{

	DockUpdateModuleData::buildFieldParse( p );

	static const FieldParse dataFieldParse[] = 
	{
		{ "StartingBoxes",	INI::parseInt,	NULL, offsetof( SupplyWarehouseDockUpdateModuleData, m_startingBoxesData ) },
		{ "DeleteWhenEmpty",	INI::parseBool,	NULL, offsetof( SupplyWarehouseDockUpdateModuleData, m_deleteWhenEmpty ) },
		{ 0, 0, 0, 0 }
	};

  p.add(dataFieldParse);

}  // end buildFieldParse


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdateConstructor.cpp
// ??0SupplyWarehouseDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z present-unmatched
SupplyWarehouseDockUpdate::SupplyWarehouseDockUpdate( Thing *thing, const ModuleData* moduleData ) : DockUpdate( thing, moduleData )
{
	m_boxesStored = getSupplyWarehouseDockUpdateModuleData()->m_startingBoxesData;
}

// ??1SupplyWarehouseDockUpdate@@MAE@XZ present-unmatched
SupplyWarehouseDockUpdate::~SupplyWarehouseDockUpdate()
{
}

class SupplyWarehouseCreatedObject
{
public:
	virtual void unused00();
	virtual void unused04();
	virtual void unused08();
	virtual void unused0c();
	virtual void unused10();
	virtual void unused14();
	virtual void unused18();
	virtual void unused1c();
	virtual void unused20();
	virtual void unused24();
	virtual Drawable *getDrawable();
};

class SupplyWarehouseCreatedModuleData
{
public:
	unsigned char m_unmodelled00[ 0x10 ];
	Int m_startingBoxes;
};

void SupplyWarehouseDockUpdate::onObjectCreated()
{
	char *rawThis = reinterpret_cast<char *>( this );
	SupplyWarehouseCreatedObject *object =
		*reinterpret_cast<SupplyWarehouseCreatedObject **>( rawThis + 8 );
	Drawable *draw = object->getDrawable();
	if( draw )
	{
		SupplyWarehouseCreatedModuleData *moduleData =
			*reinterpret_cast<SupplyWarehouseCreatedModuleData **>( rawThis + 4 );
		draw->updateDrawableSupplyStatus( moduleData->m_startingBoxes,
			*reinterpret_cast<Int *>( rawThis + 0x88 ) );
	}
}

class SupplyWarehouseActionTruckAI
{
public:
	virtual void unused00();
	virtual void unused04();
	virtual void unused08();
	virtual Bool gainOneBox( Int boxesRemaining );
};

class SupplyWarehouseActionAI
{
public:
	virtual void unused000();
	virtual void unused004();
	virtual void unused008();
	virtual void unused00c();
	virtual void unused010();
	virtual void unused014();
	virtual void unused018();
	virtual void unused01c();
	virtual void unused020();
	virtual void unused024();
	virtual void unused028();
	virtual void unused02c();
	virtual void unused030();
	virtual void unused034();
	virtual void unused038();
	virtual void unused03c();
	virtual void unused040();
	virtual void unused044();
	virtual void unused048();
	virtual void unused04c();
	virtual void unused050();
	virtual void unused054();
	virtual void unused058();
	virtual void unused05c();
	virtual void unused060();
	virtual void unused064();
	virtual void unused068();
	virtual void unused06c();
	virtual void unused070();
	virtual void unused074();
	virtual void unused078();
	virtual void unused07c();
	virtual void unused080();
	virtual void unused084();
	virtual void unused088();
	virtual void unused08c();
	virtual void unused090();
	virtual void unused094();
	virtual void unused098();
	virtual void unused09c();
	virtual void unused0a0();
	virtual void unused0a4();
	virtual void unused0a8();
	virtual void unused0ac();
	virtual void unused0b0();
	virtual void unused0b4();
	virtual void unused0b8();
	virtual void unused0bc();
	virtual void unused0c0();
	virtual void unused0c4();
	virtual void unused0c8();
	virtual void unused0cc();
	virtual void unused0d0();
	virtual void unused0d4();
	virtual void unused0d8();
	virtual void unused0dc();
	virtual void unused0e0();
	virtual void unused0e4();
	virtual void unused0e8();
	virtual void unused0ec();
	virtual void unused0f0();
	virtual void unused0f4();
	virtual void unused0f8();
	virtual void unused0fc();
	virtual void unused100();
	virtual void unused104();
	virtual void unused108();
	virtual void unused10c();
	virtual void unused110();
	virtual void unused114();
	virtual void unused118();
	virtual void unused11c();
	virtual void unused120();
	virtual void unused124();
	virtual void unused128();
	virtual void unused12c();
	virtual void unused130();
	virtual void unused134();
	virtual void unused138();
	virtual void unused13c();
	virtual void unused140();
	virtual SupplyWarehouseActionTruckAI *getSupplyTruckAIInterface();
};

class SupplyWarehouseActionObject
{
public:
	virtual void unused00();
	virtual void unused04();
	virtual void unused08();
	virtual void unused0c();
	virtual void unused10();
	virtual void unused14();
	virtual void unused18();
	virtual void unused1c();
	virtual void unused20();
	virtual void unused24();
	virtual Drawable *getDrawable();

	Real getDistanceSquared( const SupplyWarehouseActionObject *other ) const;

	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }
	SupplyWarehouseActionAI *getAI() const { return m_ai; }

public:
	unsigned char m_unmodelled04[ 0x38 - 4 ];
	Coord3D m_position;

private:
	unsigned char m_unmodelled44[ 0xBC - 0x44 ];
	Real m_boundingCircleRadius;
	unsigned char m_unmodelledC0[ 0x204 - 0xC0 ];
	SupplyWarehouseActionAI *m_ai;
};

class SupplyWarehouseActionModuleData
{
public:
	unsigned char m_unmodelled00[ 0x10 ];
	Int m_startingBoxes;
	Bool m_deleteWhenEmpty;
};

Bool SupplyWarehouseDockUpdate::action( Object* docker, Object *drone )
{
	char *rawThis = reinterpret_cast<char *>( this );
	Int &boxesStored = *reinterpret_cast<Int *>( rawThis + 0x88 );
	Int boxes = boxesStored;
	SupplyWarehouseActionObject *retailDocker = reinterpret_cast<SupplyWarehouseActionObject *>( docker );

	if( boxes == 0 )
		return FALSE;

	Real closeEnoughSqr = sqr(retailDocker->getBoundingCircleRadius() * 2);
	Real curDistSqr = retailDocker->getDistanceSquared(
		*reinterpret_cast<SupplyWarehouseActionObject **>( rawThis + 8 ) );
	if (curDistSqr > closeEnoughSqr) {
		DEBUG_LOG(("Failing dock, dist %f, not close enough(%f).\n", sqrt(curDistSqr), sqrt(closeEnoughSqr)));
		Coord3D newPos;
		newPos.x = retailDocker->m_position.x;
		newPos.y = retailDocker->m_position.y;
		newPos.z = retailDocker->m_position.z;
		Real range = 0.4*PATHFIND_CELL_SIZE_F;
		#line 87 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\DockUpdate\\SupplyWarehouseDockUpdate.cpp"
		newPos.x += GameLogicRandomValue(-range, range);
		newPos.y += GameLogicRandomValue(-range, range);
		#line 235 "Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdate.cpp"
		docker->setPosition(&newPos);
		return FALSE;
	}
	
	--boxes;
	boxesStored = boxes;

	SupplyWarehouseActionTruckAI *ai = retailDocker->getAI()->getSupplyTruckAIInterface();
	if( ai && ai->gainOneBox( boxesStored ) )
	{
		if( boxesStored == 0 &&
			(*reinterpret_cast<SupplyWarehouseActionModuleData **>( rawThis + 4 ))->m_deleteWhenEmpty )
		{
			TheGameLogic->destroyObject( *reinterpret_cast<Object **>( rawThis + 8 ) );
			return FALSE;
		}
		else
		{
			SupplyWarehouseActionObject *retailObject =
				*reinterpret_cast<SupplyWarehouseActionObject **>( rawThis + 8 );
			Drawable *draw = retailObject->getDrawable();
			if( draw )
			{
				SupplyWarehouseActionModuleData *moduleData =
					*reinterpret_cast<SupplyWarehouseActionModuleData **>( rawThis + 4 );
				draw->updateDrawableSupplyStatus( moduleData->m_startingBoxes, boxesStored );
			}
		}

		return TRUE;
	}
	else 
		++boxesStored;

	return FALSE;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/SupplyWarehouseDockUpdate_setDockCrippledMethodThunk.cpp
// ?setDockCrippled@SupplyWarehouseDockUpdate@@UAEX_N@Z present-unmatched
void SupplyWarehouseDockUpdate::setDockCrippled( Bool setting )
{
	// At this level, Crippling means I kill any activeDocker between enter and exit.
	if( setting )
	{
		if( m_activeDocker != INVALID_ID )
		{
			Object *victim = TheGameLogic->findObjectByID( m_activeDocker );
			if( victim )
			{
				if( m_dockerInside )
				{
					if( !victim->isUsingAirborneLocomotor() )
						victim->kill();
				}
				else
				{
					// Else, he was between Approach and Enter.  Lucky guy.  Tell him to stop, but then
					// remind him that he wants to try again later
					SupplyTruckAIInterface* supplyTruckAI = victim->getAI()->getSupplyTruckAIInterface();
					if( supplyTruckAI )
					{
						victim->getAI()->aiIdle( CMD_FROM_AI );
						supplyTruckAI->setForceWantingState( TRUE );
					}
				}
			}
		}
	}

	DockUpdate::setDockCrippled( setting );
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/promoted__setCashValue_SupplyWarehouseDockUpdate_QAEXH_Z_002CFA50.cpp
// ?setCashValue@SupplyWarehouseDockUpdate@@QAEXH@Z present-unmatched
void SupplyWarehouseDockUpdate::setCashValue( Int cashValue )
{
	// A script can tell us our set value, and we need to figure out the boxes needed to provide that.
	m_boxesStored = ceil(cashValue / (float)TheGlobalData->m_baseValuePerSupplyBox);
	Drawable *draw = getObject()->getDrawable();
	if( draw )
	{
		draw->updateDrawableSupplyStatus( getSupplyWarehouseDockUpdateModuleData()->m_startingBoxesData, m_boxesStored );
	}
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@SupplyWarehouseDockUpdate@@MAEXPAVXfer@@@Z present-unmatched
void SupplyWarehouseDockUpdate::crc( Xfer *xfer )
{

	// extend base class
	DockUpdate::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@SupplyWarehouseDockUpdate@@MAEXPAVXfer@@@Z present-unmatched
void SupplyWarehouseDockUpdate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	DockUpdate::xfer( xfer );

	// boxes stored
	xfer->xferInt( &m_boxesStored );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
class SupplyWarehouseDockUpdateRetailModuleData
{
public:
	unsigned char m_unmodelled00[ 0x10 ];
	Int m_startingBoxesData;
};

class SupplyWarehouseDockUpdateRetailObject
{
public:
	virtual void _pad00( void ) = 0;
	virtual void _pad04( void ) = 0;
	virtual void _pad08( void ) = 0;
	virtual void _pad0c( void ) = 0;
	virtual void _pad10( void ) = 0;
	virtual void _pad14( void ) = 0;
	virtual void _pad18( void ) = 0;
	virtual void _pad1c( void ) = 0;
	virtual void _pad20( void ) = 0;
	virtual void _pad24( void ) = 0;
	virtual Drawable *getDrawable( void ) = 0;
};

void SupplyWarehouseDockUpdate::loadPostProcess( void )
{
	// extend base class
	DockUpdate::loadPostProcess();

	// update the drawable supply status
	char *rawThis = reinterpret_cast<char *>( this );
	const SupplyWarehouseDockUpdateRetailModuleData *modData =
		*reinterpret_cast<const SupplyWarehouseDockUpdateRetailModuleData **>( rawThis + 8 );
	Object *object = *reinterpret_cast<Object **>( rawThis + 12 );
	Drawable *draw = reinterpret_cast<SupplyWarehouseDockUpdateRetailObject *>( object )->getDrawable();
	if( draw )
		draw->updateDrawableSupplyStatus( modData->m_startingBoxesData,
			*reinterpret_cast<Int *>( rawThis + 0x8c ) );
}
