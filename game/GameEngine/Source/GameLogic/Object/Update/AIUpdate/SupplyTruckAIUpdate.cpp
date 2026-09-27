// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

// SupplyTruckAIUpdate.cpp ////////////
// Author: Graham Smallwood, February 2002
// Desc:   State machine that controls when and with who a Truck docks

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:

#include "Common/Player.h"
#include "Common/ResourceGatheringManager.h"
#include "Common/ThingTemplate.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/SupplyTruckAIUpdate.h"
#include "GameLogic/Module/SupplyCenterDockUpdate.h"
#include "GameLogic/Module/SupplyWarehouseDockUpdate.h"
#include "GameLogic/Module/WorkerAIUpdate.h"

#include "GameClient/Drawable.h"
#include "GameClient/InGameUI.h"

bool findPositionAround(const Coord3D *, const FindPositionOptions *, Coord3D *);

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#if defined(_DEBUG) || defined(_INTERNAL)
#define NO_DEBUG_SUPPLY_STATE
#endif

#ifdef DEBUG_SUPPLY_STATE
static const char* statenames[] =
{
	"ST_IDLE",						///< Not doing anything.  Should I autopilot?
	"ST_BUSY",						///< Direct player involvement (move) has taken me off autopilot
	"ST_WANTING",					///< Search for warehouse or center and dock with it
	"ST_REGROUPING",			///< Wanting failed, so hang out at base until something changes.  Still on autopilot, but resting.
	"ST_DOCKING"					///< Docking substates are running, wait for them to finish
};
#endif

enum {
	REGROUP_SUCCESS_DISTANCE_SQUARED = 225
};

// The BFME object routes the player-stop setter through the secondary
// subobject at this+0x340.  Its retail vtable places setForceBusyState at
// slot 13 (+0x34), five slots after the Zero Hour interface declaration.  This
// carrier models only that proven call site; it does not rename the other
// unresolved secondary slots.
#define SUPPLY_TRUCK_BUSY_SLOT(n) virtual void supplyTruckBusySlot##n() = 0;
class SupplyTruckAIUpdateRetailBusyInterface
{
public:
	SUPPLY_TRUCK_BUSY_SLOT(00)
	SUPPLY_TRUCK_BUSY_SLOT(01)
	SUPPLY_TRUCK_BUSY_SLOT(02)
	SUPPLY_TRUCK_BUSY_SLOT(03)
	SUPPLY_TRUCK_BUSY_SLOT(04)
	SUPPLY_TRUCK_BUSY_SLOT(05)
	SUPPLY_TRUCK_BUSY_SLOT(06)
	SUPPLY_TRUCK_BUSY_SLOT(07)
	SUPPLY_TRUCK_BUSY_SLOT(08)
	SUPPLY_TRUCK_BUSY_SLOT(09)
	SUPPLY_TRUCK_BUSY_SLOT(10)
	SUPPLY_TRUCK_BUSY_SLOT(11)
	SUPPLY_TRUCK_BUSY_SLOT(12)
	virtual void setForceBusyState(Bool value) = 0;
};
#undef SUPPLY_TRUCK_BUSY_SLOT

#pragma comment(linker, "/alternatename:?privateIdle@AIUpdateInterface@@MAEXW4CommandSourceType@@@Z=?j_0002270f@@YAXXZ")
#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?findBestSupplyCenter@ResourceGatheringManager@@QAEPAVObject@@PAV2@@Z=?j_00045df4@@YAXXZ")
#pragma comment(linker, "/alternatename:?findBestSupplyWarehouse@ResourceGatheringManager@@QAEPAVObject@@PAV2@@Z=?j_00015960@@YAXXZ")
#pragma comment(linker, "/alternatename:?aiDock@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z=?j_0002221e@@YAXXZ")
#pragma comment(linker, "/alternatename:?aiBfmeCommand19@AICommandInterface@@QAEXPBVCoord3D@@W4CommandSourceType@@@Z=?j_00012774@@YAXXZ")

class Rva002C6CC0AIUpdateView
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00c() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01c() = 0;
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02c() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038() = 0;
	virtual void slot03c() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual void slot04c() = 0;
	virtual void slot050() = 0;
	virtual void slot054() = 0;
	virtual void slot058() = 0;
	virtual void slot05c() = 0;
	virtual void slot060() = 0;
	virtual void slot064() = 0;
	virtual void slot068() = 0;
	virtual void slot06c() = 0;
	virtual void slot070() = 0;
	virtual void slot074() = 0;
	virtual void slot078() = 0;
	virtual void slot07c() = 0;
	virtual void slot080() = 0;
	virtual void slot084() = 0;
	virtual void slot088() = 0;
	virtual void slot08c() = 0;
	virtual void slot090() = 0;
	virtual void slot094() = 0;
	virtual void slot098() = 0;
	virtual void slot09c() = 0;
	virtual void slot0a0() = 0;
	virtual void slot0a4() = 0;
	virtual void slot0a8() = 0;
	virtual void slot0ac() = 0;
	virtual void slot0b0() = 0;
	virtual void slot0b4() = 0;
	virtual void slot0b8() = 0;
	virtual void slot0bc() = 0;
	virtual void slot0c0() = 0;
	virtual void slot0c4() = 0;
	virtual void slot0c8() = 0;
	virtual void slot0cc() = 0;
	virtual void slot0d0() = 0;
	virtual void slot0d4() = 0;
	virtual void slot0d8() = 0;
	virtual void slot0dc() = 0;
	virtual void slot0e0() = 0;
	virtual void slot0e4() = 0;
	virtual void slot0e8() = 0;
	virtual void slot0ec() = 0;
	virtual void slot0f0() = 0;
	virtual void slot0f4() = 0;
	virtual void slot0f8() = 0;
	virtual void slot0fc() = 0;
	virtual void slot100() = 0;
	virtual void slot104() = 0;
	virtual void slot108() = 0;
	virtual void slot10c() = 0;
	virtual void slot110() = 0;
	virtual void slot114() = 0;
	virtual void slot118() = 0;
	virtual void slot11c() = 0;
	virtual void slot120() = 0;
	virtual void slot124() = 0;
	virtual void slot128() = 0;
	virtual void slot12c() = 0;
	virtual void slot130() = 0;
	virtual void slot134() = 0;
	virtual void slot138() = 0;
	virtual void slot13c() = 0;
	virtual void slot140() = 0;
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface() = 0;
};

class Rva002C6CC0SupplyInterfaceView
{
public:
	virtual Int getNumberBoxes() const = 0;
	virtual void slot004() const = 0;
	virtual void slot008() const = 0;
	virtual void slot00c() const = 0;
	virtual Bool isAvailableForSupplying() const = 0;
	virtual void slot014() const = 0;
	virtual Bool slot018() const = 0;
};

class Rva002C6DD0SupplyInterfaceView
{
public:
	virtual Int getNumberBoxes() const = 0;
	virtual void slot004() const = 0;
	virtual void slot008() const = 0;
	virtual void slot00c() const = 0;
	virtual void slot010() const = 0;
	virtual void slot014() const = 0;
	virtual void slot018() const = 0;
	virtual void slot01c() const = 0;
	virtual void slot020() const = 0;
	virtual void slot024() const = 0;
	virtual void slot028() const = 0;
	virtual void slot02c(Bool hasBoxes) const = 0;
};

class Rva002C6DD0PlayerView
{
public:
	Object *findClosestByKindOf(Object *queryObject, BitFlags<0xC0> setMask, BitFlags<0xC0> clearMask);
};

#pragma comment(linker, "/alternatename:?findClosestByKindOf@Rva002C6DD0PlayerView@@QAEPAVObject@@PAV2@V?$BitFlags@$0MA@@@1@Z=?j_00003909@@YAXXZ")

class Rva001565D0Sub
{
public:
	void notify(const Coord3D *destination, CommandSourceType commandSource);
};

#pragma comment(linker, "/alternatename:?notify@Rva001565D0Sub@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z=?j_00012774@@YAXXZ")

class Rva000E5B30Fallback
{
public:
	Bool invoke(Object *owner, Coord3D *destination);
};

#pragma comment(linker, "/alternatename:?invoke@Rva000E5B30Fallback@@QAE_NPAVObject@@PAUCoord3D@@@Z=?j_0001ab8b@@YAXXZ")

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/SupplyTruckAIUpdateMakeStateMachineThunk.cpp
// ?makeStateMachine@SupplyTruckAIUpdate@@ present-unmatched
AIStateMachine* SupplyTruckAIUpdate::makeStateMachine()
{
	return newInstance(AIStateMachine)( getObject(), "SupplyTruckAIUpdateMachine");
}

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/AI/SupplyTruckAIUpdateCtorThunk.cpp
// ??0SupplyTruckAIUpdate@@ present-unmatched
SupplyTruckAIUpdate::SupplyTruckAIUpdate( Thing *thing, const ModuleData* moduleData ) : AIUpdateInterface( thing, moduleData )
{
	m_supplyTruckStateMachine = NULL;
	m_preferredDock = INVALID_ID;
	m_numberBoxes = 0;
	m_forcePending = FALSE;
	m_forcedBusyPending = FALSE;
	m_supplyTruckStateMachine = newInstance(SupplyTruckStateMachine)( getObject() );
	m_supplyTruckStateMachine->initDefaultState();
	
	m_suppliesDepletedVoice = getSupplyTruckAIUpdateModuleData()->m_suppliesDepletedVoice;

} 

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/Common/SupplyTruckAIUpdateDestructorThunk.cpp
// ??1SupplyTruckAIUpdate@@ present-unmatched
SupplyTruckAIUpdate::~SupplyTruckAIUpdate( void )
{
	m_supplyTruckStateMachine->deleteInstance();
} 


//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/AI/SupplyTruckAIUpdate_updateAndPrivateDock_Thunk.cpp
// ?update@SupplyTruckAIUpdate@@ present-unmatched
UpdateSleepTime SupplyTruckAIUpdate::update( void )
{

	StateReturnType stRet = m_supplyTruckStateMachine->updateStateMachine();

	UpdateSleepTime mine = IS_STATE_SLEEP(stRet) ? UPDATE_SLEEP(GET_STATE_SLEEP_FRAMES(stRet)) : UPDATE_SLEEP_NONE;

	// extend
	UpdateSleepTime ret = AIUpdateInterface::update();
	return (mine < ret) ? mine : ret;
}

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/AI/SupplyTruckAIUpdate_updateAndPrivateDock_Thunk.cpp
// ?isCurrentlyFerryingSupplies@SupplyTruckAIUpdate@@ present-unmatched
Bool SupplyTruckAIUpdate::isCurrentlyFerryingSupplies() const
{
	if (m_supplyTruckStateMachine)
	{
		switch (m_supplyTruckStateMachine->getCurrentStateID())
		{
			case ST_IDLE:
			case ST_BUSY:
			case ST_REGROUPING:
				return false;
			case ST_WANTING:
			case ST_DOCKING:
				return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
// ?isAvailableForSupplying@SupplyTruckAIUpdate@@ present-unmatched
Bool SupplyTruckAIUpdate::isAvailableForSupplying() const 
{ 
	return true;
}

//-------------------------------------------------------------------------------------------------
// ?loseOneBox@SupplyTruckAIUpdate@@ present-unmatched
Bool SupplyTruckAIUpdate::loseOneBox()
{
	if( m_numberBoxes == 0 )
		return FALSE;
	--m_numberBoxes;

	Drawable *draw = getObject()->getDrawable();
	if( draw )
	{
		draw->updateDrawableSupplyStatus( getSupplyTruckAIUpdateModuleData()->m_maxBoxesData, m_numberBoxes );
	}

	return TRUE;
}

//-------------------------------------------------------------------------------------------------
// ?gainOneBox@SupplyTruckAIUpdate@@ present-unmatched
Bool SupplyTruckAIUpdate::gainOneBox( Int remainingStock )
{
	if( getSupplyTruckAIUpdateModuleData() && m_numberBoxes >= getSupplyTruckAIUpdateModuleData()->m_maxBoxesData )
		return FALSE;
	++m_numberBoxes;


	//if I just took the last box, 
	//i will announce that this supply source is now empty
	if (remainingStock == 0)
	{
		Object* bestWarehouse = getObject()->getControllingPlayer()->getResourceGatheringManager()->findBestSupplyWarehouse( getObject() );
		
		Bool playDepleted = FALSE;
		if ( bestWarehouse )
		{
			//figure out whether the best one is considerably far from the previous one (current position)
			Coord3D delta = *getObject()->getPosition();
			delta.sub( bestWarehouse->getPosition() ); 
			if ( delta.length() > getWarehouseScanDistance()/4)
			playDepleted = TRUE;
		}
		else
			playDepleted = TRUE;

		if (playDepleted && m_suppliesDepletedVoice.getEventName().isEmpty() == false)
		{
			m_suppliesDepletedVoice.setObjectID(getObject()->getID());
			m_suppliesDepletedVoice.setPlayingHandle(TheAudio->addAudioEvent(&m_suppliesDepletedVoice));
		}
	}

	Drawable *draw = getObject()->getDrawable();
	if( draw )
	{
		draw->updateDrawableSupplyStatus( getSupplyTruckAIUpdateModuleData()->m_maxBoxesData, m_numberBoxes );
	}

	return TRUE;
}

//----------------------------------------------------------------------------------------
// The reference SupplyTruck implementation keeps a player-issued idle command
// from re-entering the automatic supply state, then delegates the common idle
// handling to AIUpdateInterface.
void SupplyTruckAIUpdate::privateIdle(CommandSourceType cmdSource)
{
	if( cmdSource == CMD_FROM_PLAYER )
		reinterpret_cast<SupplyTruckAIUpdateRetailBusyInterface *>(
			reinterpret_cast<unsigned char *>(this) + 0x340)->setForceBusyState(TRUE);

	AIUpdateInterface::privateIdle(cmdSource);
}

//----------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/AI/SupplyTruckAIUpdate_updateAndPrivateDock_Thunk.cpp
// ?privateDock@SupplyTruckAIUpdate@@ present-unmatched
void SupplyTruckAIUpdate::privateDock( Object *dock, CommandSourceType cmdSource )
{
	AIUpdateInterface::privateDock( dock, cmdSource );

	// If this is a command from a player, I will remember this as my favorite dock to override
	// ResourceManager searches.
	if ((cmdSource == CMD_FROM_PLAYER) && dock)
	{
		// Please note, there is not a separate Warehouse and Center memory by Design.  Because
		// we lack a UI way to click Warehouse and drag to center to set up a specific path, the
		// practical realization has been made that you do not want separate memory.
		m_preferredDock = dock->getID();
	}
}

//----------------------------------------------------------------------------------------
UnsignedInt SupplyTruckAIUpdate::getActionDelayForDock( Object *dock )
{
	// BFME's AIUpdate module-data pointer is at retail this-0x33c (SupplyTruckAIUpdate
	// carries one fewer interface vptr than WorkerAIUpdate, whose analogous fix uses
	// this-0x340). The ZH-shaped module header exposes the same fields through a
	// shorter base; this source-level displacement emits the retail slot unchanged.
	// Decide whether to use my Center or Warehouse delay time
	static const NameKeyType key_warehouseUpdate = NAMEKEY("SupplyWarehouseDockUpdate");
	SupplyWarehouseDockUpdate *warehouseModule = (SupplyWarehouseDockUpdate*) dock->findUpdateModule( key_warehouseUpdate );
	if (warehouseModule) {
		// SupplyTruckAIUpdateModuleData lacks WorkerAIUpdateModuleData's three extra
		// Real fields, so its delay fields sit 0xC lower: this -0x13c, +0x6c.
		const char *moduleData = *reinterpret_cast<const char * const *>(reinterpret_cast<const char *>(this) - 0x13c);
		return *reinterpret_cast<const UnsignedInt *>(moduleData + 0x6c);
	}
	static const NameKeyType key_centerUpdate = NAMEKEY("SupplyCenterDockUpdate");
	SupplyCenterDockUpdate *centerModule = (SupplyCenterDockUpdate*) dock->findUpdateModule( key_centerUpdate );
	if (centerModule) {
		const char *moduleData = *reinterpret_cast<const char * const *>(reinterpret_cast<const char *>(this) - 0x13c);
		return *reinterpret_cast<const UnsignedInt *>(moduleData + 0x68);
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?getWarehouseScanDistance@SupplyTruckAIUpdate@@ present-unmatched
Real SupplyTruckAIUpdate::getWarehouseScanDistance() const
{
	// Ai players get larger scan range.  jba.
	if (getObject()->getControllingPlayer()->getPlayerType() == PLAYER_COMPUTER) {
		return 2 * getSupplyTruckAIUpdateModuleData()->m_warehouseScanDistance;
	}
	return getSupplyTruckAIUpdateModuleData()->m_warehouseScanDistance;
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@SupplyTruckAIUpdate@@ present-unmatched
void SupplyTruckAIUpdate::crc( Xfer *xfer )
{
	// extend base class
	AIUpdateInterface::crc(xfer);
}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@SupplyTruckAIUpdate@@ present-unmatched
void SupplyTruckAIUpdate::xfer( Xfer *xfer )
{
  XferVersion currentVersion = 1;
  XferVersion version = currentVersion;
  xfer->xferVersion( &version, currentVersion );
 
 // extend base class
	AIUpdateInterface::xfer(xfer);

	xfer->xferSnapshot(m_supplyTruckStateMachine);
	xfer->xferObjectID(&m_preferredDock);
	xfer->xferInt(&m_numberBoxes);
	xfer->xferBool(&m_forcePending);

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@SupplyTruckAIUpdate@@ present-unmatched
void SupplyTruckAIUpdate::loadPostProcess( void )
{
 // extend base class
	AIUpdateInterface::loadPostProcess();
}  // end loadPostProcess

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

class SupplyTruckBusyState :  public State
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(SupplyTruckBusyState, "SupplyTruckBusyState")		
protected:
	// snapshot interface STUBBED.
	virtual void crc( Xfer *xfer ){};
	virtual void xfer( Xfer *xfer ){};
	virtual void loadPostProcess(){};

public:
	SupplyTruckBusyState( StateMachine *machine ) : State( machine, "SupplyTruckBusyState" ) { }
	virtual StateReturnType onEnter() 
	{ 
		if( getMachineOwner() && getMachineOwner()->getAI() )
		{
			// Have to check, since constructor sets a state.  Phhbbt. Constructor = set up, init = do first thing.
			SupplyTruckAIInterface *update = getMachineOwner()->getAI()->getSupplyTruckAIInterface();
			if( update )
			{
				// Turn off the Busy latch when we make it to Busy
				update->setForceBusyState( FALSE );
			}
		}

#ifdef DEBUG_SUPPLY_STATE
TheInGameUI->DEBUG_addFloatingText("entering busy state", getMachineOwner()->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
		return STATE_CONTINUE; 
	}	
	virtual StateReturnType update() 
	{ 
		return STATE_CONTINUE; 
	}
	virtual void onExit(StateExitType status)
	{
#ifdef DEBUG_SUPPLY_STATE
TheInGameUI->DEBUG_addFloatingText("exiting busy state", getMachineOwner()->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
	}

};
EMPTY_DTOR(SupplyTruckBusyState)

//-----------------------------------------------------------------------------------------------------------
class SupplyTruckIdleState :  public State
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(SupplyTruckIdleState, "SupplyTruckIdleState")		
protected:
	// snapshot interface STUBBED.
	virtual void crc( Xfer *xfer ){};
	virtual void xfer( Xfer *xfer ){};
	virtual void loadPostProcess(){};

public:
	SupplyTruckIdleState( StateMachine *machine ) : State( machine, "SupplyTruckIdleState" ) { }
	virtual StateReturnType onEnter();
	virtual StateReturnType update() 
	{ 
		return STATE_CONTINUE; 
	}
	virtual void onExit(StateExitType status)
	{
#ifdef DEBUG_SUPPLY_STATE
TheInGameUI->DEBUG_addFloatingText("exiting idle state", getMachineOwner()->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
	}

};
EMPTY_DTOR(SupplyTruckIdleState)

// ?onEnter@SupplyTruckIdleState@@ present-unmatched
StateReturnType SupplyTruckIdleState::onEnter() 
{ 
#ifdef DEBUG_SUPPLY_STATE
TheInGameUI->DEBUG_addFloatingText("entering idle state", getMachineOwner()->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
 
 	Object *owner = getMachineOwner();
 	if (owner != NULL) {
 		AIUpdateInterface * ownerAI = owner->getAIUpdateInterface();
 		if (ownerAI != NULL) {
 			// This is to get idle workers to always show up on the
 			// "idle worker button."
 			// Basically if you have a worker interface, and we are entering
 			// the idle state for the supply truck, we let the worker interface
 			// know so it can decide which idle state it wants us to actually
 			// be in from its perspective.
 			WorkerAIInterface *workerAI = ownerAI->getWorkerAIInterface();
 			if (workerAI != NULL) {
 				workerAI->exitingSupplyTruckState();
 			}
 		}
 	}

	return STATE_CONTINUE; 
}	


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/SupplyTruckStateMachineConstructorThunk.cpp
// ??0SupplyTruckStateMachine@@ present-unmatched
SupplyTruckStateMachine::SupplyTruckStateMachine( Object *owner ) : StateMachine( owner, "SupplyTruckStateMachine" )
{
	static const StateConditionInfo busyConditions[] = 
	{
		StateConditionInfo(ownerIdle, ST_IDLE, NULL),
		StateConditionInfo(ownerDocking, ST_DOCKING, NULL),
		StateConditionInfo(NULL, NULL, NULL)	// keep last
	};

	static const StateConditionInfo idleConditions[] = 
	{
		StateConditionInfo(isForcedIntoBusyState, ST_BUSY, NULL),
		StateConditionInfo(isForcedIntoWantingState, ST_WANTING, NULL),
		StateConditionInfo(ownerDocking, ST_DOCKING, NULL),
		StateConditionInfo(ownerNotDockingOrIdle, ST_BUSY, NULL),
		StateConditionInfo(NULL, NULL, NULL)	// keep last
	};

	static const StateConditionInfo wantingConditions[] = 
	{
		StateConditionInfo(ownerDocking, ST_DOCKING, NULL),
		StateConditionInfo(ownerNotDockingOrIdle, ST_BUSY, NULL),
		StateConditionInfo(NULL, NULL, NULL)	// keep last
	};

	static const StateConditionInfo regroupingConditions[] = 
	{
		StateConditionInfo(ownerPlayerCommanded, ST_BUSY, NULL),
		StateConditionInfo(NULL, NULL, NULL)	// keep last
	};

	static const StateConditionInfo dockingConditions[] = 
	{
		StateConditionInfo(isForcedIntoBusyState, ST_BUSY, NULL),
		StateConditionInfo(ownerAvailableForSupplying, ST_WANTING, NULL),
		StateConditionInfo(ownerNotDockingOrIdle, ST_BUSY, NULL),
		StateConditionInfo(NULL, NULL, NULL)	// keep last
	};

	// order matters: first state is the default state.
	defineState( ST_BUSY,							newInstance(SupplyTruckBusyState)( this ),												ST_BUSY,		ST_BUSY,					busyConditions );
	defineState( ST_IDLE,							newInstance(SupplyTruckIdleState)( this ),												ST_BUSY,		ST_BUSY,					idleConditions );
	defineState( ST_WANTING,					newInstance(SupplyTruckWantsToPickUpOrDeliverBoxesState)( this ),	ST_BUSY,		ST_REGROUPING,		wantingConditions );
	defineState( ST_REGROUPING,				newInstance(RegroupingState)( this ),															ST_WANTING, ST_BUSY,					regroupingConditions );
	defineState( ST_DOCKING,					newInstance(DockingState)( this ),																ST_BUSY,		ST_BUSY,					dockingConditions );
}

//-------------------------------------------------------------------------------------------------
// ??1SupplyTruckStateMachine@@ present-unmatched
SupplyTruckStateMachine::~SupplyTruckStateMachine()
{
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@SupplyTruckStateMachine@@ present-unmatched
void SupplyTruckStateMachine::crc( Xfer *xfer )
{
	StateMachine::crc(xfer);
}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ?xfer@SupplyTruckStateMachine@@ present-unmatched
void SupplyTruckStateMachine::xfer( Xfer *xfer )
{
	XferVersion cv = 1;	
	XferVersion v = cv; 
	xfer->xferVersion( &v, cv );

	StateMachine::xfer(xfer);
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@SupplyTruckStateMachine@@ present-unmatched
void SupplyTruckStateMachine::loadPostProcess( void )
{
	StateMachine::loadPostProcess();
}  // end loadPostProcess

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// ?onEnter@SupplyTruckWantsToPickUpOrDeliverBoxesState@@ present-unmatched
StateReturnType SupplyTruckWantsToPickUpOrDeliverBoxesState::onEnter()
{
#ifdef DEBUG_SUPPLY_STATE
TheInGameUI->DEBUG_addFloatingText("entering wanting state", getMachineOwner()->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
	Object *owner = getMachineOwner();
	SupplyTruckAIInterface *update = owner->getAIUpdateInterface()->getSupplyTruckAIInterface();
	if( !update )
	{
		return STATE_FAILURE;
	}

	// We can only force Wanting for one go at Wanting.  It could fail and we would be stuck forever.
	// So a force means one try at the wanting state, then back to normal.
	update->setForceWantingState(false);

	return STATE_CONTINUE;
}

//-------------------------------------------------------------------------------------------------
void SupplyTruckWantsToPickUpOrDeliverBoxesState::onExit(StateExitType status)
{
#ifdef DEBUG_SUPPLY_STATE
TheInGameUI->DEBUG_addFloatingText("exiting wanting state", getMachineOwner()->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
}

//-------------------------------------------------------------------------------------------------
StateReturnType SupplyTruckWantsToPickUpOrDeliverBoxesState::update()
{
	Coord3D destination;
	void *machine = *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(this) + 0x1c);
	Object *owner = *reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(machine) + 0x10);
	AIUpdateInterface *ownerAI = *reinterpret_cast<AIUpdateInterface **>(reinterpret_cast<unsigned char *>(owner) + 0x204);
	if (!ownerAI)
		return STATE_FAILURE;

	Player* ownerPlayer = owner->getControllingPlayer();
	ResourceGatheringManager *manager = *reinterpret_cast<ResourceGatheringManager **>(reinterpret_cast<unsigned char *>(ownerPlayer) + 0x228);
	if (!manager)
		return STATE_FAILURE;

	Rva002C6CC0AIUpdateView *ownerAIView = reinterpret_cast<Rva002C6CC0AIUpdateView *>(ownerAI);
	Rva002C6CC0SupplyInterfaceView *update = reinterpret_cast<Rva002C6CC0SupplyInterfaceView *>(ownerAIView->getSupplyTruckAIInterface());
	if (update && update->isAvailableForSupplying())
	{
		Int numBoxes = update->getNumberBoxes();
		if (numBoxes > 0)
		{
			// want a center.
			Object *destinationObject = manager->findBestSupplyCenter( owner );
			if (!destinationObject)
				return STATE_FAILURE;
			reinterpret_cast<AICommandInterface *>(reinterpret_cast<unsigned char *>(ownerAI) + 0x20)->aiDock( destinationObject, CMD_FROM_AI );
			return STATE_SUCCESS;
		}
		else
		{
			// want a warehouse.
			Object *destinationObject = manager->findBestSupplyWarehouse( owner );
			if( destinationObject )
			{
				reinterpret_cast<AICommandInterface *>(reinterpret_cast<unsigned char *>(ownerAI) + 0x20)->aiDock( destinationObject, CMD_FROM_AI );
				return STATE_SUCCESS;
			}
		}
		if (update->slot018() && reinterpret_cast<Rva000E5B30Fallback *>(manager)->invoke(owner, &destination))
		{
			reinterpret_cast<Rva001565D0Sub *>(reinterpret_cast<unsigned char *>(ownerAI) + 0x20)->notify(&destination, CMD_FROM_AI);
			return STATE_SUCCESS;
		}
	}
	return STATE_FAILURE;
}

//-------------------------------------------------------------------------------------------------
StateReturnType RegroupingState::onEnter()
{
#ifdef DEBUG_SUPPLY_STATE
TheInGameUI->DEBUG_addFloatingText("entering regrouping state", getMachineOwner()->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
	// I have failed to find a dock, so my first choice is to go hang out at a Supply Center (I may have
	// failed to find a Warehouse).  My second choices is to go to a ConYard.  My last choice is just to 
	// go to a friendly building.

	void *machine = *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(this) + 0x1c);
	Object *owner = *reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(machine) + 0x10);
	Coord3D destination;
	AIUpdateInterface *ownerAI = *reinterpret_cast<AIUpdateInterface **>(reinterpret_cast<unsigned char *>(owner) + 0x204);
	Player* ownerPlayer = owner->getControllingPlayer();
	if( !ownerPlayer || !ownerAI )
		return STATE_FAILURE;

	ownerAI->ignoreObstacle( NULL );
	Rva002C6CC0AIUpdateView *ownerAIView = reinterpret_cast<Rva002C6CC0AIUpdateView *>(
		*reinterpret_cast<AIUpdateInterface **>(reinterpret_cast<unsigned char *>(owner) + 0x204));
	Rva002C6DD0SupplyInterfaceView *update = reinterpret_cast<Rva002C6DD0SupplyInterfaceView *>(ownerAIView->getSupplyTruckAIInterface());
	if( !update )
	{
		return STATE_FAILURE;
	}
	Bool hasBoxes = update->getNumberBoxes() > 0;
	update->slot02c(hasBoxes);

	Object *destinationObject;

	BitFlags<0xC0> kindof;
	BitFlags<0xC0> kindofnot;
	kindof.set(34);
	kindofnot.clear();
	// can't do best supply center of the player's resource brain, because that adds canTransfer checks.
	destinationObject = reinterpret_cast<Rva002C6DD0PlayerView *>(ownerPlayer)->findClosestByKindOf( owner, kindof, kindofnot );
	if (destinationObject)
		goto found_destination;

	kindof.clear();
	kindof.set(17);
	kindofnot.clear();
	destinationObject = reinterpret_cast<Rva002C6DD0PlayerView *>(ownerPlayer)->findClosestByKindOf( owner, kindof, kindofnot );
	if (destinationObject)
		goto found_destination;

	kindof.clear();
	kindof.set(7);
	kindofnot.clear();
	destinationObject = reinterpret_cast<Rva002C6DD0PlayerView *>(ownerPlayer)->findClosestByKindOf( owner, kindof, kindofnot );
	if( !destinationObject )
		return STATE_FAILURE;

found_destination:
	
	FindPositionOptions fpOptions;
	fpOptions.minRadius = 0.0f;
	fpOptions.maxRadius = 100.0f;

	if( ! findPositionAround(
		reinterpret_cast<const Coord3D *>(reinterpret_cast<const unsigned char *>(destinationObject) + 0x38),
		&fpOptions, &destination ) )
		return STATE_FAILURE;

	ownerAI->aiMoveToPosition( &destination, CMD_FROM_AI );
	return STATE_CONTINUE;// Remember to say continue when you change ai command inside a state
}

//-------------------------------------------------------------------------------------------------
// ?update@RegroupingState@@ present-unmatched
StateReturnType RegroupingState::update()
{
	Object *owner = getMachineOwner();

	if( owner->getAI()->isIdle() )
		return STATE_SUCCESS; // Once we have regrouped, chill with the regrouping.  We will succeed to Wanting, which can handle Busy.

	return STATE_CONTINUE;
}

//-------------------------------------------------------------------------------------------------
// ?onExit@RegroupingState@@ present-unmatched
void RegroupingState::onExit(StateExitType status)
{
#ifdef DEBUG_SUPPLY_STATE
	TheInGameUI->DEBUG_addFloatingText("exiting regroup state", getMachineOwner()->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
}


//-------------------------------------------------------------------------------------------------
// ?onEnter@DockingState@@ present-unmatched
StateReturnType DockingState::onEnter()
{
#ifdef DEBUG_SUPPLY_STATE
TheInGameUI->DEBUG_addFloatingText("entering docking state", getMachineOwner()->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
	Object *owner = getMachineOwner();
	SupplyTruckAIInterface *update = owner->getAIUpdateInterface()->getSupplyTruckAIInterface();
	if( !update )
	{
		return STATE_FAILURE;
	}

	// after we dock the first time, we clear this, and then follow our normal state machine path
	update->setForceWantingState(false);

	return STATE_CONTINUE;
}

//-------------------------------------------------------------------------------------------------
StateReturnType DockingState::update()
{
	return STATE_CONTINUE;
}

//-------------------------------------------------------------------------------------------------
// ?onExit@DockingState@@ present-unmatched
void DockingState::onExit(StateExitType status)
{
#ifdef DEBUG_SUPPLY_STATE
TheInGameUI->DEBUG_addFloatingText("exiting docking state", getMachineOwner()->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/* static */ Bool SupplyTruckStateMachine::isForcedIntoWantingState( State *thisState, void* userData )
{
	Object *owner = thisState->getMachineOwner();
	AIUpdateInterface *ai = owner->getAIUpdateInterface();
	if( !ai )
		return false;
	SupplyTruckAIInterface *update = ai->getSupplyTruckAIInterface();
	if( !update )
		return false;

	if (update->isForcedIntoWantingState())
	{
#ifdef DEBUG_SUPPLY_STATE
AsciiString tmp;
tmp.format("isForcedIntoWantingState returns true (%s)",statenames[thisState->getID()]);
TheInGameUI->DEBUG_addFloatingText(tmp, owner->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------
/* static */ Bool SupplyTruckStateMachine::isForcedIntoBusyState( State *thisState, void* userData )
{
	Object *owner = thisState->getMachineOwner();
	AIUpdateInterface *ai = owner->getAIUpdateInterface();
	if( !ai )
		return false;
	SupplyTruckAIInterface *update = ai->getSupplyTruckAIInterface();
	if( !update )
		return false;

	if (update->isForcedIntoBusyState())
	{
#ifdef DEBUG_SUPPLY_STATE
AsciiString tmp;
tmp.format("isForcedIntoBusytate returns true (%s)",statenames[thisState->getID()]);
TheInGameUI->DEBUG_addFloatingText(tmp, owner->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------
/* static */ Bool SupplyTruckStateMachine::ownerDocking( State *thisState, void* userData )
{
	// Three offsets are BFME's: State::m_machine at +0x1c (this tree +0x20),
	// StateMachine::m_owner at +0x10 (+0x14), and Object::m_ai at +0x204
	// (+0x19c). The first and last are the same two
	// AIMoveAndEvacuateState::onExit and TurretAI::loadPostProcess pin.
	char *machine = *(char **)((char *)thisState + 0x1c);
	Object *owner = *(Object **)(machine + 0x10);
	AIUpdateInterface *ai = *(AIUpdateInterface **)((char *)owner + 0x204);
	if( !ai )
		return false;

	AIStateType masterState = ai->getAIStateType();

	if (masterState == AI_DOCK)
	{
#ifdef DEBUG_SUPPLY_STATE
AsciiString tmp;
tmp.format("ownerDocking returns true (%s)",statenames[thisState->getID()]);
TheInGameUI->DEBUG_addFloatingText(tmp, owner->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------
/* static */ Bool SupplyTruckStateMachine::ownerPlayerCommanded( State *thisState, void* userData )
{
	Object *owner = thisState->getMachineOwner();
	AIUpdateInterface *ai = owner->getAIUpdateInterface();
	if( !ai )
		return false;

	if( ai->getLastCommandSource() == CMD_FROM_PLAYER )
	{
#ifdef DEBUG_SUPPLY_STATE
AsciiString tmp;
tmp.format("ownerPlayerCommanded returns true (%s)",statenames[thisState->getID()]);
TheInGameUI->DEBUG_addFloatingText(tmp, owner->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------
/* static */ Bool SupplyTruckStateMachine::ownerIdle( State *thisState, void* userData )
{
	Object *owner = thisState->getMachineOwner();
	AIUpdateInterface *ai = owner->getAIUpdateInterface();
	if( !ai )
		return false;

	if (ai->isIdle())
	{
#ifdef DEBUG_SUPPLY_STATE
AsciiString tmp;
tmp.format("ownerIdle returns true (%s)",statenames[thisState->getID()]);
TheInGameUI->DEBUG_addFloatingText(tmp, owner->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------
/* static */ Bool SupplyTruckStateMachine::ownerAvailableForSupplying( State *thisState, void* userData )
{
	Object *owner = thisState->getMachineOwner();
	AIUpdateInterface *ai = owner->getAIUpdateInterface();
	if( !ai )
		return false;
	SupplyTruckAIInterface *update = ai->getSupplyTruckAIInterface();
	if( !update )
		return false;

	if (update->isAvailableForSupplying() && ai->isIdle())
	{
#ifdef DEBUG_SUPPLY_STATE
AsciiString tmp;
tmp.format("ownerAvailableForSupplying returns true (%s)",statenames[thisState->getID()]);
TheInGameUI->DEBUG_addFloatingText(tmp, owner->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------
/* static */ Bool SupplyTruckStateMachine::ownerNotDockingOrIdle( State *thisState, void* userData )
{
	Object *owner = thisState->getMachineOwner();
	AIUpdateInterface *ai = owner->getAIUpdateInterface();
	if( !ai )
		return false;

	if (!ai->isIdle() && ai->getAIStateType() != AI_DOCK)
	{
#ifdef DEBUG_SUPPLY_STATE
AsciiString tmp;
tmp.format("ownerNotDockingOrIdle returns true (%s)",statenames[thisState->getID()]);
TheInGameUI->DEBUG_addFloatingText(tmp, owner->getPosition(), GameMakeColor(255, 0, 0, 255));
#endif
		return true;
	}

	return false;
}
