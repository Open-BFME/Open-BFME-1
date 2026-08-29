// cl: /DNDEBUG /DWIN32 /D_WINDOWS /DBFME_MODULE_NO_MPO /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: SupplyWarehouseCreate.cpp ///////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood Feb 2002
// Desc:   When a Supply Center is created, it needs to update all the Resource brains in all players
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ResourceGatheringManager.h"
#include "Common/Xfer.h"
#include "GameLogic/Module/SupplyWarehouseCreate.h"

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// The module hierarchy needs BFME_MODULE_NO_MPO on this file's own cl line:
// retail's Module has no MemoryPoolObject base, so BehaviorModule spans 0x0C
// and the second vtable store lands there, where the wider layout puts a
// fourth vptr at +0x04 and shifts everything after it.
SupplyWarehouseCreate::SupplyWarehouseCreate( Thing *thing, const ModuleData* moduleData ) : CreateModule( thing, moduleData )
{

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1SupplyWarehouseCreate@@MAE@XZ present-unmatched
SupplyWarehouseCreate::~SupplyWarehouseCreate( void )
{

}

//-------------------------------------------------------------------------------------------------
// ?onCreate@SupplyWarehouseCreate@@UAEXXZ
void SupplyWarehouseCreate::onCreate( void )
{
	// Warehouses are never Built.
	if( ThePlayerList == NULL )
		return;

	for( Int playerIndex = ThePlayerList->getPlayerCount() - 1; playerIndex >= 0; playerIndex-- )
	{
		Player *currentPlayer = ThePlayerList->getNthPlayer( playerIndex );
		if( currentPlayer == NULL )
			continue;
		// BFME's Player layout inserts extra members ahead of
		// m_resourceGatheringManager relative to the vendored ZH header (the
		// dominant BFME/ZH layout-drift pattern -- see reference/shims/player).
		// Retail onCreate@SupplyWarehouseCreate proves the field lives at
		// Player+0x228, not the header's natural (or shim-patched) offset, so
		// read it directly rather than through getResourceGatheringManager().
		ResourceGatheringManager *manager =
			*reinterpret_cast<ResourceGatheringManager * const *>(
				reinterpret_cast<const char *>( currentPlayer ) + 0x228 );
		if( manager == NULL )
			continue;
		manager->addSupplyWarehouse( getObject() );
	}
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@SupplyWarehouseCreate@@MAEXPAVXfer@@@Z present-unmatched
void SupplyWarehouseCreate::crc( Xfer *xfer )
{

	// extend base class
	CreateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@SupplyWarehouseCreate@@MAEXPAVXfer@@@Z present-unmatched
void SupplyWarehouseCreate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	CreateModule::xfer( xfer );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@SupplyWarehouseCreate@@MAEXXZ present-unmatched
void SupplyWarehouseCreate::loadPostProcess( void )
{

	// extend base class
	CreateModule::loadPostProcess();

}  // end loadPostProcess
