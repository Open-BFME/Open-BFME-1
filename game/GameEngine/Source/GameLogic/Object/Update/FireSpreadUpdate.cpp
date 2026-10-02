// cl: /DBFME_MODULE_NO_MPO /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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
// BFME evidence: targets/game/reverse/identity_evidence/FireSpreadUpdate_update_00292900.md
// The ZH headers own the engine classes. Address-derived views describe only
// BFME additions that those headers do not expose.
class AI;
extern AI *TheAI;
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

struct Rva00292900AIData
{
	char pad_00[0xb8];
	bool slot_b8;
};

struct Rva00292900AI
{
	char pad_00[0x14];
	Rva00292900AIData *slot_14;
	const Rva00292900AIData *data() const { return slot_14; }
};

// The filter is a BFME linked node, not the ZH array of filter pointers.
// Its lifetime ends before the terrain fallback. Both table symbols already
// exist in this TU through the native filter declarations.
struct Rva00292900Filter
{
	const void *slot_00;
	Rva00292900Filter *slot_04;

	Rva00292900Filter() : slot_04(0)
	{
		slot_00 = __identifier("??_7PartitionFilterFlammable@@6B@");
	}
	~Rva00292900Filter()
	{
		slot_00 = __identifier("??_7PartitionFilter@@6B@");
	}
};

// Existing pinned four-argument wrappers at 0x009F26A0 and 0x001A62D0.
// Their integer ABI slots carry position/filter pointers and radius bits.
class BfmeC1050 { public: void *bfmeGo1050D(int, int, int, int); };
class BfmeA1275 { public: int bfmeGo1275(int, int, int, int); };
class Rva001AA5B0Receiver { public: Object *invoke(const Coord3D *); };

// BFME createInternal returns void; the ZH header returns Object*. Bind its
// existing ILT through the independently decoded single-inheritance thiscall
// ABI without redeclaring ObjectCreationList or adding a second callee pin.
void j_000160d1();
class Rva001D6810Receiver {};
static void rva001D6810Call(const ObjectCreationList *ocl,
	const Object *a, const Object *b, unsigned n)
{
	typedef void (Rva001D6810Receiver::*Call)(const Object *, const Object *, unsigned);
	union { void (*symbol)(); Call member; } call;
	call.symbol = j_000160d1;
	(((Rva001D6810Receiver *)ocl)->*call.member)(a, b, n);
}

UpdateSleepTime FireSpreadUpdate::update(void)
{
	Object *me = getObject();
	const FireSpreadUpdateModuleData *d = getFireSpreadUpdateModuleData();
	if ((*(const unsigned *)((const char *)me + 0x90) & 0x400) == 0)
		return UPDATE_SLEEP_FOREVER;

	if (d->m_oclEmbers)
		rva001D6810Call(d->m_oclEmbers, me, 0, 0);

	if (d->m_spreadTryRange != 0)
	{
		Object *objectToLight;
		{
			Rva00292900Filter filter;
			objectToLight = (Object *)((BfmeC1050 *)ThePartitionManager)->bfmeGo1050D(
				(int)((char *)getObject() + 0x38), *(const int *)&d->m_spreadTryRange,
				2, (int)&filter);
		}

		// objectToLight is zero on this arm and supplies the final false argument.
		if (!objectToLight && ((Rva00292900AI *)TheAI)->data()->slot_b8)
		{
			const Coord3D *point = (const Coord3D *)((BfmeA1275 *)TheTerrainLogic)->bfmeGo1275(
				(int)((char *)me + 0x38), *(const int *)&d->m_spreadTryRange,
				1, (int)objectToLight);
			if (point)
				objectToLight = ((Rva001AA5B0Receiver *)TheTerrainLogic)->invoke(point);
		}

		if (objectToLight)
		{
			static NameKeyType key_FlammableUpdate = NAMEKEY("FlammableUpdate");
			FlammableUpdate *fu = (FlammableUpdate *)objectToLight->findUpdateModule(key_FlammableUpdate);
			if (fu)
				fu->tryToIgnite();
		}
	}
	return UPDATE_SLEEP(calcNextSpreadDelay());
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void FireSpreadUpdate::startFireSpreading()
{
	if( (*reinterpret_cast<const UnsignedInt *>(reinterpret_cast<const char *>(getObject()) + 0x90) & 0x400) == 0 )
		return;	// sorry, must be on fire

	const char *moduleData = *reinterpret_cast<const char * const *>(reinterpret_cast<const char *>(this) + 0x04);
#line 152 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\FireSpreadUpdate.cpp"
	UnsignedInt delay = GameLogicRandomValue(*reinterpret_cast<const Int *>(moduleData + 0x0c), *reinterpret_cast<const Int *>(moduleData + 0x10));
#line 186
	if (delay < 1)
		delay = 1;
	setWakeFrame(getObject(), UPDATE_SLEEP(delay));
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
