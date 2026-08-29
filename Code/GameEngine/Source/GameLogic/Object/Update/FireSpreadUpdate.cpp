// cl: /DBFME_MODULE_NO_MPO /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: FireSpreadUpdate.cpp /////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, April 2002
// Desc:   Update looks for ::Aflame and explicitly ignites someone nearby if set
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/RandomValue.h"
#include "Common/Xfer.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/UpdateModule.h"
#include "GameLogic/Module/FlammableUpdate.h"

// BFME adds the update-list sentinel immediately after the two reference
// UpdateModule state words.  Keep that proven layout local to this TU because
// the vendored UpdateModule header is shared by the reference-era sources.
class FireSpreadUpdateBFMELayout : public UpdateModule
{
	public:
	FireSpreadUpdateBFMELayout( Thing *thing, const ModuleData *moduleData ) :
		UpdateModule( thing, moduleData ),
		m_pad(-1)
	{
	}

	protected:
	Int m_pad;
};

#define UpdateModule FireSpreadUpdateBFMELayout
#include "GameLogic/Module/FireSpreadUpdate.h"
#undef UpdateModule

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// This is a one sided query, as in I am not checking for "Flammable By Me", I'm simply testing for a property
class PartitionFilterFlammable : public PartitionFilter
{
public:

	PartitionFilterFlammable(){ }
	
	virtual Bool allow(Object *objOther);
#if defined(_DEBUG) || defined(_INTERNAL)
	virtual const char* debugGetName() { return "PartitionFilterFlammable"; }
#endif
};

//-------------------------------------------------------------------------------------------------
Bool PartitionFilterFlammable::allow(Object *objOther)
{
	// It must be burnable in general, and burnable now
	static NameKeyType key_FlammableUpdate = NAMEKEY("FlammableUpdate");
	FlammableUpdate* fu = (FlammableUpdate*)objOther->findUpdateModule(key_FlammableUpdate);
	if (fu == NULL)
		return FALSE;

	if( ! fu->wouldIgnite() )
		return FALSE;

	return TRUE;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/*static*/ void FireSpreadUpdateModuleData::buildFieldParse(MultiIniFieldParse& p) 
{
  UpdateModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] = 
	{
		{ "OCLEmbers",				INI::parseObjectCreationList,		NULL, offsetof( FireSpreadUpdateModuleData, m_oclEmbers ) },
		{ "MinSpreadDelay",		INI::parseDurationUnsignedInt,	NULL, offsetof( FireSpreadUpdateModuleData, m_minSpreadTryDelayData ) },
		{ "MaxSpreadDelay",		INI::parseDurationUnsignedInt,	NULL, offsetof( FireSpreadUpdateModuleData, m_maxSpreadTryDelayData ) },
		{ "SpreadTryRange",		INI::parseReal,									NULL, offsetof( FireSpreadUpdateModuleData, m_spreadTryRange ) },
		{ 0, 0, 0, 0 }
	};
  p.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
FireSpreadUpdate::FireSpreadUpdate( Thing *thing, const ModuleData* moduleData ) : FireSpreadUpdateBFMELayout( thing, moduleData )
{
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1FireSpreadUpdate@@UAE@XZ present-unmatched
FireSpreadUpdate::~FireSpreadUpdate( void )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
UpdateSleepTime FireSpreadUpdate::update( void )
{
	const FireSpreadUpdateModuleData* d = getFireSpreadUpdateModuleData();
	Object* me = getObject();

	if( !me->getStatusBits().test( OBJECT_STATUS_AFLAME ) )
		return UPDATE_SLEEP_FOREVER;		// not on fire -- sleep forever
	{
		ObjectCreationList::create( d->m_oclEmbers, getObject(), NULL );

		if( d->m_spreadTryRange != 0 )
		{
			// This will spread fire explicitly
			PartitionFilterFlammable fFilter;
			PartitionFilter *filters[] = { &fFilter, NULL };

//			SimpleObjectIterator *iter = NULL;
//			iter = ThePartitionManager->iterateObjectsInRange(getObject(), 
//																									d->m_spreadTryRange, 
//																									FROM_CENTER_3D, 
//																									filters, 
//																									ITER_SORTED_NEAR_TO_FAR
//																									);
//			MemoryPoolObjectHolder hold(iter);
//			Object *objectToLight = iter->first();
//
// srj sez: the above code is stupid and slow. since we only want the closest object,
// just ask for that; the above has to find ALL objects in range, but we ignore all 
// but the first (closest).
//
			Object* objectToLight = ThePartitionManager->getClosestObject(getObject(), d->m_spreadTryRange, FROM_CENTER_3D, filters);
			if( objectToLight )
			{
				static NameKeyType key_FlammableUpdate = NAMEKEY("FlammableUpdate");
				FlammableUpdate* fu = (FlammableUpdate*)objectToLight->findUpdateModule(key_FlammableUpdate);
				if( fu )
					fu->tryToIgnite();
			}
		}

		return UPDATE_SLEEP(calcNextSpreadDelay());
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?startFireSpreading@FireSpreadUpdate@@QAEXXZ present-unmatched
void FireSpreadUpdate::startFireSpreading()
{
	if( !getObject()->getStatusBits().test( OBJECT_STATUS_AFLAME ) )
		return;	// sorry, must be on fire

	setWakeFrame(getObject(), UPDATE_SLEEP(calcNextSpreadDelay()));
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?calcNextSpreadDelay@FireSpreadUpdate@@QAEIXZ present-unmatched
UnsignedInt FireSpreadUpdate::calcNextSpreadDelay()
{
	const FireSpreadUpdateModuleData* d = getFireSpreadUpdateModuleData();
	// GameLogicRandomValue bakes __FILE__ and __LINE__ into the call as
	// immediates, so retail's own path and line are part of the body: it pushes
	// 0x98 and the literal at 0x010BEC08. This reconstruction sits at a
	// different line than BFME's did, so restore both here.
#line 152 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\FireSpreadUpdate.cpp"
	UnsignedInt delay = GameLogicRandomValue( d->m_minSpreadTryDelayData, d->m_maxSpreadTryDelayData );
	if (delay < 1)
		delay = 1;
	return delay;
}
#line 204

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@FireSpreadUpdate@@QAEXPAVXfer@@@Z present-unmatched
void FireSpreadUpdate::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@FireSpreadUpdate@@QAEXPAVXfer@@@Z present-unmatched
void FireSpreadUpdate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpdateModule::xfer( xfer );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@FireSpreadUpdate@@UAEXXZ present-unmatched
void FireSpreadUpdate::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
