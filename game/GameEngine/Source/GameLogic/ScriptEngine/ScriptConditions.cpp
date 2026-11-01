// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Retail's containers use STLport's node allocator (see inputs/reference/shims/stlp_nodealloc), so the vector COMDATs this TU emits match the retail-shaped copies.
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

// FILE: ScriptConditions.cpp /////////////////////////////////////////////////////////////////////////
// The game scripting conditions.  Evaluates conditions.
// Author: John Ahlquist, Nov. 2001
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <bitset>
extern "C" void __cdecl _WriteBarrier(void);
extern "C" void __cdecl _ReadWriteBarrier(void);
#pragma intrinsic(_WriteBarrier)
#pragma intrinsic(_ReadWriteBarrier)

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

#include "Common/GameEngine.h"
#include "Common/MapObject.h"
#include "Common/PlayerList.h"
#include "Common/Player.h"
#include "Common/SpecialPower.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/Team.h"
#include "Common/Player.h"
#include "Common/ObjectStatusTypes.h"

#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameClient.h"
#include "GameClient/InGameUI.h"
#include "GameClient/View.h"

#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/SupplyWarehouseDockUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectTypes.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/PolygonTrigger.h"
#define evaluatePlayerHasComparisonValueExcessPower evaluateRva003231E0
#define evaluateSkirmishSupplySourceSafe evaluateRva00323650
#include "GameLogic/ScriptConditions.h"
#undef evaluatePlayerHasComparisonValueExcessPower
#undef evaluateSkirmishSupplySourceSafe
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Scripts.h"
#include "GameLogic/VictoryConditions.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

class ScriptConditionsObjectTypesTemp
{
public:
	ObjectTypes* m_types;

	ScriptConditionsObjectTypesTemp() : m_types(NULL)
	{
		m_types = newInstance(ObjectTypes);
	}

	~ScriptConditionsObjectTypesTemp()
	{
		if (m_types)
			m_types->deleteInstance();
	}
};

// STATICS ////////////////////////////////////////////////////////////////////////////////////////
namespace rts
{
	template<typename T> 
		T sum(std::vector<T>& vecOfValues )
	{
		T retVal = 0;
		std::vector<T>::iterator it;
		for (it = vecOfValues.begin(); it != vecOfValues.end(); ++it) {
			retVal += (*it);
		}
		return retVal;
	}
};

// GLOBALS ////////////////////////////////////////////////////////////////////////////////////////
ScriptConditionsInterface *TheScriptConditions = NULL;

class TransportStatus : public MemoryPoolObject
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(TransportStatus, "TransportStatus")		
public:
	TransportStatus *	m_nextStatus;
	ObjectID					m_objID;
	UnsignedInt				m_frameNumber;
	Int								m_unitCount;

public:
	TransportStatus() : m_objID(INVALID_ID), m_frameNumber(0), m_unitCount(0), m_nextStatus(NULL) {}
	//~TransportStatus();
};

//-------------------------------------------------------------------------------------------------
// ??1TransportStatus@@MAE@XZ present-unmatched
TransportStatus::~TransportStatus() 
{ 
	if (m_nextStatus) 
		m_nextStatus->deleteInstance(); 
}

//-------------------------------------------------------------------------------------------------
static TransportStatus *s_transportStatuses;

//-------------------------------------------------------------------------------------------------
#define BFME_SCRIPT_CONDITION_SLOT(N) virtual void slot##N() = 0

class BfmeScriptConditionEngine
{
public:
	BFME_SCRIPT_CONDITION_SLOT(00); BFME_SCRIPT_CONDITION_SLOT(01); BFME_SCRIPT_CONDITION_SLOT(02);
	BFME_SCRIPT_CONDITION_SLOT(03); BFME_SCRIPT_CONDITION_SLOT(04); BFME_SCRIPT_CONDITION_SLOT(05);
	BFME_SCRIPT_CONDITION_SLOT(06); BFME_SCRIPT_CONDITION_SLOT(07); BFME_SCRIPT_CONDITION_SLOT(08);
	BFME_SCRIPT_CONDITION_SLOT(09); BFME_SCRIPT_CONDITION_SLOT(10); BFME_SCRIPT_CONDITION_SLOT(11);
	BFME_SCRIPT_CONDITION_SLOT(12); BFME_SCRIPT_CONDITION_SLOT(13); BFME_SCRIPT_CONDITION_SLOT(14);
	BFME_SCRIPT_CONDITION_SLOT(15); BFME_SCRIPT_CONDITION_SLOT(16); BFME_SCRIPT_CONDITION_SLOT(17);
	BFME_SCRIPT_CONDITION_SLOT(18); BFME_SCRIPT_CONDITION_SLOT(19); BFME_SCRIPT_CONDITION_SLOT(20);
	BFME_SCRIPT_CONDITION_SLOT(21); BFME_SCRIPT_CONDITION_SLOT(22); BFME_SCRIPT_CONDITION_SLOT(23);
	BFME_SCRIPT_CONDITION_SLOT(24); BFME_SCRIPT_CONDITION_SLOT(25);
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
	virtual void slot27() = 0;
	virtual Bool didUnitExist(const AsciiString &name) = 0;
	BFME_SCRIPT_CONDITION_SLOT(29); BFME_SCRIPT_CONDITION_SLOT(30); BFME_SCRIPT_CONDITION_SLOT(31);
	BFME_SCRIPT_CONDITION_SLOT(32); BFME_SCRIPT_CONDITION_SLOT(33); BFME_SCRIPT_CONDITION_SLOT(34);
	BFME_SCRIPT_CONDITION_SLOT(35); BFME_SCRIPT_CONDITION_SLOT(36); BFME_SCRIPT_CONDITION_SLOT(37);
	BFME_SCRIPT_CONDITION_SLOT(38); BFME_SCRIPT_CONDITION_SLOT(39); BFME_SCRIPT_CONDITION_SLOT(40);
	BFME_SCRIPT_CONDITION_SLOT(41);
	// Retail folded evaluateVideoHasCompleted, evaluateSpeechHasCompleted and
	// evaluateAudioHasCompleted onto one body, so which of isVideoComplete,
	// isSpeechComplete and isAudioComplete sits here cannot be told apart from
	// the call site. The slot is what the bytes prove; the name is not.
	virtual Bool unidentifiedIsComplete(const AsciiString &name, Bool value) = 0;	///< vtable +0xA8
};

#undef BFME_SCRIPT_CONDITION_SLOT

class BfmeScriptConditionParameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

// The excess-power predicate calls the reviewed BFME player-mask thunk rather
// than the Zero Hour ScriptEngine member used by the surrounding source.  Its
// decorated ABI and global are already pinned at 0x000230B5/0x00EF076C.
class BfmeP1087
{
public:
	PlayerMaskType bfmeNext1087(Parameter *parameter);
};

// Retail spells the singleton at 0x012F076C TheScriptEngine; BfmeP1087 is this
// TU's view of the reviewed player-mask thunk, so the global carries its real
// name and the view is cast at each use.

// BFME keeps Parameter::m_int at +0x08 and embeds the energy counters in the
// player at +0xA8/+0xAC.  These views keep this predicate from selecting the
// incompatible Zero Hour accessors declared by the common headers.
class BfmeScriptConditionIntParameter
{
public:
	unsigned char m_beforeInt[0x08];
	Int m_int;
};

class BfmeScriptConditionEnergyPlayer
{
public:
	unsigned char m_beforeProduction[0xA8];
	Int m_production;
	Int m_consumption;
};

// BFME's supply-source predicate reads these two Condition cache
// fields directly and uses the game-logic frame at +0x3c.  The upstream
// accessors select a different layout and do not produce the retail shape.
class BfmeScriptConditionCache
{
public:
	unsigned char m_beforeCustomData[0x44];
	Int m_customData;
	UnsignedInt m_customFrame;
};

class BfmeScriptConditionGameLogic
{
public:
	unsigned char m_beforeFrame[0x3c];
	Int m_frame;
};

class BfmeEvaluateContainModule
{
public:
#define BFME_EVALUATE_CONTAIN_SLOT(N) virtual void slot##N() = 0
	BFME_EVALUATE_CONTAIN_SLOT(00); BFME_EVALUATE_CONTAIN_SLOT(01); BFME_EVALUATE_CONTAIN_SLOT(02);
	BFME_EVALUATE_CONTAIN_SLOT(03); BFME_EVALUATE_CONTAIN_SLOT(04); BFME_EVALUATE_CONTAIN_SLOT(05);
	BFME_EVALUATE_CONTAIN_SLOT(06); BFME_EVALUATE_CONTAIN_SLOT(07); BFME_EVALUATE_CONTAIN_SLOT(08);
	BFME_EVALUATE_CONTAIN_SLOT(09); BFME_EVALUATE_CONTAIN_SLOT(10); BFME_EVALUATE_CONTAIN_SLOT(11);
	BFME_EVALUATE_CONTAIN_SLOT(12); BFME_EVALUATE_CONTAIN_SLOT(13); BFME_EVALUATE_CONTAIN_SLOT(14);
	BFME_EVALUATE_CONTAIN_SLOT(15); BFME_EVALUATE_CONTAIN_SLOT(16); BFME_EVALUATE_CONTAIN_SLOT(17);
	BFME_EVALUATE_CONTAIN_SLOT(18); BFME_EVALUATE_CONTAIN_SLOT(19); BFME_EVALUATE_CONTAIN_SLOT(20);
	BFME_EVALUATE_CONTAIN_SLOT(21); BFME_EVALUATE_CONTAIN_SLOT(22); BFME_EVALUATE_CONTAIN_SLOT(23);
	BFME_EVALUATE_CONTAIN_SLOT(24); BFME_EVALUATE_CONTAIN_SLOT(25); BFME_EVALUATE_CONTAIN_SLOT(26);
	BFME_EVALUATE_CONTAIN_SLOT(27); BFME_EVALUATE_CONTAIN_SLOT(28); BFME_EVALUATE_CONTAIN_SLOT(29);
	BFME_EVALUATE_CONTAIN_SLOT(30); BFME_EVALUATE_CONTAIN_SLOT(31); BFME_EVALUATE_CONTAIN_SLOT(32);
	BFME_EVALUATE_CONTAIN_SLOT(33); BFME_EVALUATE_CONTAIN_SLOT(34); BFME_EVALUATE_CONTAIN_SLOT(35);
	BFME_EVALUATE_CONTAIN_SLOT(36); BFME_EVALUATE_CONTAIN_SLOT(37); BFME_EVALUATE_CONTAIN_SLOT(38);
	BFME_EVALUATE_CONTAIN_SLOT(39); BFME_EVALUATE_CONTAIN_SLOT(40); BFME_EVALUATE_CONTAIN_SLOT(41);
	BFME_EVALUATE_CONTAIN_SLOT(42); BFME_EVALUATE_CONTAIN_SLOT(43); BFME_EVALUATE_CONTAIN_SLOT(44);
	BFME_EVALUATE_CONTAIN_SLOT(45); BFME_EVALUATE_CONTAIN_SLOT(46); BFME_EVALUATE_CONTAIN_SLOT(47);
	BFME_EVALUATE_CONTAIN_SLOT(48); BFME_EVALUATE_CONTAIN_SLOT(49); BFME_EVALUATE_CONTAIN_SLOT(50);
	BFME_EVALUATE_CONTAIN_SLOT(51); BFME_EVALUATE_CONTAIN_SLOT(52); BFME_EVALUATE_CONTAIN_SLOT(53);
	BFME_EVALUATE_CONTAIN_SLOT(54); BFME_EVALUATE_CONTAIN_SLOT(55); BFME_EVALUATE_CONTAIN_SLOT(56);
	BFME_EVALUATE_CONTAIN_SLOT(57); BFME_EVALUATE_CONTAIN_SLOT(58); BFME_EVALUATE_CONTAIN_SLOT(59);
	BFME_EVALUATE_CONTAIN_SLOT(60); BFME_EVALUATE_CONTAIN_SLOT(61); BFME_EVALUATE_CONTAIN_SLOT(62);
	BFME_EVALUATE_CONTAIN_SLOT(63);
#undef BFME_EVALUATE_CONTAIN_SLOT
	virtual Int getContainCount(Int) const = 0;
};

class BfmeEvaluateUnitObject
{
public:
	unsigned char m_beforeObjectID[0x74];
	ObjectID m_objectID;
	unsigned char m_beforeContain[0x184];
	BfmeEvaluateContainModule *m_contain;

	ObjectID getID() const { return m_objectID; }
	BfmeEvaluateContainModule *getContain() const { return m_contain; }
};

class BfmeScriptConditionTerrainLogic
{
public:
	unsigned char m_unreconstructed[0x38];
	unsigned char m_bridgesChanged;
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0ScriptConditions@@QAE@XZ present-unmatched
ScriptConditions::ScriptConditions()
{

}  // end ScriptConditions

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Matched via game/masm_dumps/ScriptConditions_dtor.asm @ 0x003244B0 (106B).
// C++ kept for TU completeness; retail body is scalar-delete of s_transportStatuses
// (not MemoryPool deleteInstance) then SubsystemInterface dtor — not emittable as ZH.
ScriptConditions::~ScriptConditions()
{
	reset(); // just in case.
}  // end ~ScriptConditions

//-------------------------------------------------------------------------------------------------
/** Init */
//-------------------------------------------------------------------------------------------------
// ?init@ScriptConditions@@UAEXXZ present-unmatched
void ScriptConditions::init( void )
{

	reset();

}  // end init

//-------------------------------------------------------------------------------------------------
/** Reset */
//-------------------------------------------------------------------------------------------------
// ?reset@ScriptConditions@@UAEXXZ present-unmatched
void ScriptConditions::reset( void )
{

	s_transportStatuses->deleteInstance();
	s_transportStatuses = NULL;
	// Empty for now.  jba.
}  // end reset

//-------------------------------------------------------------------------------------------------
/** Update */
//-------------------------------------------------------------------------------------------------
// ?update@ScriptConditions@@UAEXXZ present-unmatched
void ScriptConditions::update( void )
{

	// Empty for now. jba
}  // end update


//-------------------------------------------------------------------------------------------------
/** Finds the player by the name in the parameter, and if found caches the player mask in the
parameter so we don't have to do a name search.  May return null if the player doesn't exist.*/
//-------------------------------------------------------------------------------------------------
// ?playerFromParam@ScriptConditions@@IAEPAVPlayer@@PAVParameter@@@Z present-unmatched
Player *ScriptConditions::playerFromParam(Parameter *pSideParm)
{
	DEBUG_ASSERTCRASH(Parameter::SIDE == pSideParm->getParameterType(), ("Wrong parameter type."));
	Player *pPlayer=NULL;
	UnsignedInt mask = (UnsignedInt)pSideParm->getInt();
	if (mask) {
		pPlayer = ThePlayerList->getPlayerFromMask(mask);
	} else {
		pPlayer = TheScriptEngine->getPlayerFromAsciiString(pSideParm->getString());
		if (pPlayer) {
			// Enemy player can change dynamically, so don't cache the player mask.  jba.
			if (pSideParm->getString()!=THIS_PLAYER_ENEMY) {
				mask = pPlayer->getPlayerMask();
			}
		} else {
			mask = 0xFFFF0000;
		}
		pSideParm->friend_setInt((Int)mask);
	}
	DEBUG_ASSERTCRASH(pPlayer, ("Couldn't find player %s", pSideParm->getString().str()));
	return pPlayer;
}

//-------------------------------------------------------------------------------------------------
/** objectTypesFromParam */
//-------------------------------------------------------------------------------------------------
// ?objectTypesFromParam@ScriptConditions@@IAEXPAVParameter@@PAVObjectTypes@@@Z present-unmatched
void ScriptConditions::objectTypesFromParam(Parameter *pTypeParm, ObjectTypes *outObjectTypes)
{
	if (!(pTypeParm && outObjectTypes)) {
		return;
	}

	AsciiString str = pTypeParm->getString();

	if (str.isEmpty()) {
		return;
	}

	ObjectTypes *types = TheScriptEngine->getObjectTypes(str);
	if (!types) {
		(*outObjectTypes).addObjectType(str);
	} else {
		(*outObjectTypes) = (*types);
	}
}


//-------------------------------------------------------------------------------------------------
/** evaluateAllDestroyed */
//-------------------------------------------------------------------------------------------------
// ?evaluateAllDestroyed@ScriptConditions@@IAE_NPAVParameter@@@Z present-unmatched
Bool ScriptConditions::evaluateAllDestroyed(Parameter *pSideParm )
{
	Player *pPlayer = playerFromParam(pSideParm);
	if (pPlayer) {
		return (!pPlayer->hasAnyObjects());
	}
	return true; // Non existent player is all destroyed. :)
}  

//-------------------------------------------------------------------------------------------------
/** evaluateAllBuildFacilitiesDestroyed */
//-------------------------------------------------------------------------------------------------
// ?evaluateAllBuildFacilitiesDestroyed@ScriptConditions@@IAE_NPAVParameter@@@Z present-unmatched
Bool ScriptConditions::evaluateAllBuildFacilitiesDestroyed(Parameter *pSideParm )
{
	Player *pPlayer = playerFromParam(pSideParm);
	if (pPlayer) {
		return (!pPlayer->hasAnyBuildFacility());
	}
	return true; // Non existent player is all destroyed. :)
}  

//-------------------------------------------------------------------------------------------------
/** evaluateIsDestroyed */
//-------------------------------------------------------------------------------------------------
// ?evaluateIsDestroyed@ScriptConditions@@IAE_NPAVParameter@@@Z: retail body is in ScriptConditionsTeamState.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateBridgeBroken */
//-------------------------------------------------------------------------------------------------
Bool ScriptConditions::evaluateBridgeBroken(Parameter *pBridgeParm)
{
	if (!reinterpret_cast<BfmeScriptConditionTerrainLogic *>(TheTerrainLogic)->m_bridgesChanged) {
		// Don't bother checking if no bridges changed damage states.
		return false;
	}
	BfmeScriptConditionEngine *engine = reinterpret_cast<BfmeScriptConditionEngine *>(TheScriptEngine);
	Object *theBridge = engine->getUnitNamed(*reinterpret_cast<const AsciiString *>(pBridgeParm));
	if (theBridge) {
		return (TheTerrainLogic->isBridgeBroken(theBridge));
	}
	return false;
}  

//-------------------------------------------------------------------------------------------------
/** evaluateBridgeRepaired */
//-------------------------------------------------------------------------------------------------
Bool ScriptConditions::evaluateBridgeRepaired(Parameter *pBridgeParm)
{
	if (!reinterpret_cast<BfmeScriptConditionTerrainLogic *>(TheTerrainLogic)->m_bridgesChanged) {
		// Don't bother checking if no bridges changed damage states.
		return false;
	}
	BfmeScriptConditionEngine *engine = reinterpret_cast<BfmeScriptConditionEngine *>(TheScriptEngine);
	Object *theBridge = engine->getUnitNamed(*reinterpret_cast<const AsciiString *>(pBridgeParm));
	if (theBridge) {
		return (TheTerrainLogic->isBridgeRepaired(theBridge));
	}
	return false;
}  

//-------------------------------------------------------------------------------------------------
/** evaluateNamedUnitDestroyed */
//-------------------------------------------------------------------------------------------------
class BfmeNamedUnitObject
{
public:
	unsigned char m_unreconstructed[0x344];
	unsigned char m_privateStatus;

	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
};

Bool ScriptConditions::evaluateNamedUnitDestroyed(Parameter *pUnitParm)
{
	BfmeScriptConditionEngine *engine = reinterpret_cast<BfmeScriptConditionEngine *>(TheScriptEngine);
	BfmeNamedUnitObject *theUnit = reinterpret_cast<BfmeNamedUnitObject *>(
		engine->getUnitNamed(*reinterpret_cast<const AsciiString *>(pUnitParm)));
	if (theUnit) 
	{
		return theUnit->isEffectivelyDead();
	}

	BfmeScriptConditionParameter *parameter = reinterpret_cast<BfmeScriptConditionParameter *>(pUnitParm);
	if (reinterpret_cast<BfmeScriptConditionEngine *>(TheScriptEngine)->didUnitExist(parameter->m_string)) {
		return true;
	}
	return false; // Non existent unit is not destroyed. 
}

//-------------------------------------------------------------------------------------------------
/** evaluateNamedUnitExists */
//-------------------------------------------------------------------------------------------------
Bool ScriptConditions::evaluateNamedUnitExists(Parameter *pUnitParm)
{
	BfmeScriptConditionEngine *engine = reinterpret_cast<BfmeScriptConditionEngine *>(TheScriptEngine);
	BfmeNamedUnitObject *theUnit = reinterpret_cast<BfmeNamedUnitObject *>(
		engine->getUnitNamed(*reinterpret_cast<const AsciiString *>(pUnitParm)));
	if (theUnit) 
	{
		return !theUnit->isEffectivelyDead();
	}

	return false; // Doesn't exist. 
}

//-------------------------------------------------------------------------------------------------
/** evaluateNamedUnitDying */
//-------------------------------------------------------------------------------------------------
Bool ScriptConditions::evaluateNamedUnitDying(Parameter *pUnitParm)
{
	BfmeScriptConditionEngine *engine = reinterpret_cast<BfmeScriptConditionEngine *>(TheScriptEngine);
	BfmeNamedUnitObject *theUnit = reinterpret_cast<BfmeNamedUnitObject *>(
		engine->getUnitNamed(*reinterpret_cast<const AsciiString *>(pUnitParm)));
	if (theUnit) 
	{
		return theUnit->isEffectivelyDead();
	}

	BfmeScriptConditionParameter *parameter = reinterpret_cast<BfmeScriptConditionParameter *>(pUnitParm);
	if (reinterpret_cast<BfmeScriptConditionEngine *>(TheScriptEngine)->didUnitExist(parameter->m_string))
	{
		return false; // already totally killed
	}
	return false; // Non existent unit is not dying. 
}

//-------------------------------------------------------------------------------------------------
/** evaluateNamedUnitTotallyDead */
//-------------------------------------------------------------------------------------------------
Bool ScriptConditions::evaluateNamedUnitTotallyDead(Parameter *pUnitParm)
{
	BfmeScriptConditionEngine *engine = reinterpret_cast<BfmeScriptConditionEngine *>(TheScriptEngine);
	Object *theUnit = engine->getUnitNamed(*reinterpret_cast<const AsciiString *>(pUnitParm));
	if (theUnit) {
		return false; // if the unit still exists, it isn't totally dead.
	}

	BfmeScriptConditionParameter *parameter = reinterpret_cast<BfmeScriptConditionParameter *>(pUnitParm);
	if (reinterpret_cast<BfmeScriptConditionEngine *>(TheScriptEngine)->didUnitExist(parameter->m_string)) {
		// Did exist, now it doesnt.  So it is really, really dead.
		return true; // totally killed
	}
	return false; // Non existent unit is not dead. 
}

//-------------------------------------------------------------------------------------------------
/** evaluateHasUnits */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_evaluateHasUnits_Thunk.cpp
// ?evaluateHasUnits@ScriptConditions@@IAE_NPAVParameter@@@Z present-unmatched
Bool ScriptConditions::evaluateHasUnits(Parameter *pTeamParm)
{
	AsciiString desiredTeamName = pTeamParm->getString();
	// If they are calling a <this team> condition, do it.
	if (desiredTeamName == THIS_TEAM) {
		Team *theTeam = TheScriptEngine->getTeamNamed( desiredTeamName );
		// The team is the team based on the name, and the calling team (if any) and the team that
		// is being considered for the condition.  jba. :)
		if (theTeam) {
			return (theTeam->hasAnyUnits());
		}
		return false; // Non existent team has no units. 
	}
	Team *thisTeam = TheScriptEngine->getTeamNamed(THIS_TEAM);
	if (thisTeam && thisTeam->getName()==desiredTeamName)	{
		return thisTeam->hasAnyUnits();
	}

	// It isn't THIS_TEAM, and doesn't match the THIS_TEAM, so check if any team with this name
	// has units.
	TeamPrototype *pProto = NULL;
	pProto = TheTeamFactory->findTeamPrototype(desiredTeamName);

	if (pProto) {
		// We have a team referred to in the conditions.  Iterate over the instances of the team, 
		// applying the script conditions (and possibly actions) to each instance of the team.
		for (DLINK_ITERATOR<Team> iter = pProto->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
			if (iter.cur()->hasAnyUnits()) {
				return true;
			}
		}
	}
	return false; // Non existent team has no units. 
}  

//-------------------------------------------------------------------------------------------------
/** evaluateUnitsEntered */
//-------------------------------------------------------------------------------------------------
// ?evaluateTeamInsideAreaPartially@ScriptConditions@@IAE_NPAVParameter@@00@Z: retail body is in ScriptConditionsTriggerAreas.cpp

//-------------------------------------------------------------------------------------------------
/** evaluatePlayerHasUnitTypeInArea */
//-------------------------------------------------------------------------------------------------
// ?evaluatePlayerHasUnitTypeInArea@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@1111@Z present-unmatched
Bool ScriptConditions::evaluatePlayerHasUnitTypeInArea(Condition *pCondition, Parameter *pPlayerParm, Parameter *pComparisonParm, Parameter *pCountParm, Parameter *pTypeParm, Parameter *pTriggerParm )
{
	AsciiString triggerName = pTriggerParm->getString();
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());
	if (pTrig == NULL) return false;

	Player* pPlayer = playerFromParam(pPlayerParm);
	if (!pPlayer) {
		return false;
	}
	Player::PlayerTeamList::const_iterator it;
	Bool anyChanges = false;


	if (pCondition->getCustomData() == 0) anyChanges = true;

	for (it = pPlayer->getPlayerTeams()->begin(); it != pPlayer->getPlayerTeams()->end(); ++it) {
		if (anyChanges) break;
		for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
			if (anyChanges) break;
			Team *team = iter.cur();
			if (!team) {
				continue;
			}
			if (team->didEnterOrExit()) {
				anyChanges = true; 
			}
		}
	}

	if (TheScriptEngine->getFrameObjectCountChanged() > pCondition->getCustomFrame()) {
		anyChanges = true; // Objects were added/deleted last frame, so count could have changed.  jba.
	}

	if (!anyChanges) {
		if (pCondition->getCustomData()==-1) return false;
		if (pCondition->getCustomData()==1) return true;
	}

	ScriptConditionsObjectTypesTemp types;
	objectTypesFromParam(pTypeParm, types.m_types);

	Int count = 0;
	for (it = pPlayer->getPlayerTeams()->begin(); it != pPlayer->getPlayerTeams()->end(); ++it) {
		for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
			Team *team = iter.cur();
			if (!team) {
				continue;
			}
			for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
				Object *pObj = iter.cur();
				if (!pObj) {
					continue;
				}

				if (types.m_types->isInSet(pObj->getTemplate())) {
					if (pObj->isInside(pTrig)) {

						//
						// dead objects will not be considered, except crates ... they are "dead" cause
						// they have no body and health, but are a class of object we want to
						// trigger this stuff
						//
						if (!(pObj->isEffectivelyDead() || pObj->isKindOf(KINDOF_INERT)) || pObj->isKindOf( KINDOF_CRATE ) ) {
							count++;
						}
					}
				}
			}
		}
	}
	
	Bool comparison = false;
	switch (pComparisonParm->getInt())
	{
		case Parameter::LESS_THAN :			comparison = (count < pCountParm->getInt()); break;
		case Parameter::LESS_EQUAL :		comparison = (count <= pCountParm->getInt()); break;
		case Parameter::EQUAL :					comparison = (count == pCountParm->getInt()); break; 
		case Parameter::GREATER_EQUAL :	comparison = (count >= pCountParm->getInt()); break;
		case Parameter::GREATER :				comparison = (count > pCountParm->getInt()); break;
		case Parameter::NOT_EQUAL :			comparison = (count != pCountParm->getInt()); break;
	}
	pCondition->setCustomData(-1); // false.
	if (comparison) {
		pCondition->setCustomData(1); // true.
	}
	pCondition->setCustomFrame(TheScriptEngine->getFrameObjectCountChanged());
	return comparison;
}  

//-------------------------------------------------------------------------------------------------
/** evaluatePlayerHasUnitKindInArea */
//-------------------------------------------------------------------------------------------------
// ?evaluatePlayerHasUnitKindInArea@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@1111@Z present-unmatched
Bool ScriptConditions::evaluatePlayerHasUnitKindInArea(Condition *pCondition, Parameter *pPlayerParm, Parameter *pComparisonParm, Parameter *pCountParm, Parameter *pKindParm, Parameter *pTriggerParm )
{
	AsciiString triggerName = pTriggerParm->getString();
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());
	if (pTrig == NULL) return false;

	KindOfType kind = (KindOfType)pKindParm->getInt();
	
	Player* pPlayer = playerFromParam(pPlayerParm);
	if (!pPlayer) {
		return false;
	}

	Player::PlayerTeamList::const_iterator it;
	Bool anyChanges = false;
	if (pCondition->getCustomData() == 0) anyChanges = true;


	for (it = pPlayer->getPlayerTeams()->begin(); it != pPlayer->getPlayerTeams()->end(); ++it) {
		if (anyChanges) break;
		for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
			if (anyChanges) break;
			Team *team = iter.cur();
			if (!team) {
				continue;
			}
			if (team->didEnterOrExit()) {
				anyChanges = true; 
			}
		}
	}
	if (TheScriptEngine->getFrameObjectCountChanged() > pCondition->getCustomFrame()) {
		anyChanges = true; // Objects were added/deleted since we cached, so count could have changed.  jba.
	}
	if (!anyChanges) {
		if (pCondition->getCustomData()==-1) return false;
		if (pCondition->getCustomData()==1) return true;

	}


	Int count = 0;
	for (it = pPlayer->getPlayerTeams()->begin(); it != pPlayer->getPlayerTeams()->end(); ++it) {
		for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
			Team *team = iter.cur();
			if (!team) {
				continue;
			}
			for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
				Object *pObj = iter.cur();
				if (!pObj) {
					continue;
				}
				if (pObj->isKindOf(kind)) {
					if (pObj->isInside(pTrig)) {
						if (!(pObj->isEffectivelyDead() || pObj->isKindOf(KINDOF_INERT))) {
							count++;
						}
					}
				}
			}
		}
	}
	
	Bool comparison = false;
	switch (pComparisonParm->getInt())
	{
		case Parameter::LESS_THAN :			comparison = (count < pCountParm->getInt()); break;
		case Parameter::LESS_EQUAL :		comparison = (count <= pCountParm->getInt()); break;
		case Parameter::EQUAL :					comparison = (count == pCountParm->getInt()); break; 
		case Parameter::GREATER_EQUAL :	comparison = (count >= pCountParm->getInt()); break;
		case Parameter::GREATER :				comparison = (count > pCountParm->getInt()); break;
		case Parameter::NOT_EQUAL :			comparison = (count != pCountParm->getInt()); break;
	}
	pCondition->setCustomData(TheScriptEngine->getFrameObjectCountChanged());
	return comparison;
}  

//-------------------------------------------------------------------------------------------------
/** evaluateTeamStateIs */
//-------------------------------------------------------------------------------------------------
// ?evaluateTeamStateIs@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditionsTeamState.cpp


//-------------------------------------------------------------------------------------------------
/** evaluateTeamStateIsNot */
//-------------------------------------------------------------------------------------------------
// ?evaluateTeamStateIsNot@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditionsTeamState.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateNamedOutsideArea */
//-------------------------------------------------------------------------------------------------
Bool ScriptConditions::evaluateNamedOutsideArea(Parameter *pUnitParm, Parameter *pTriggerParm)
{// This is actually NamedUnitInside(...)

	return !evaluateNamedInsideArea(pUnitParm, pTriggerParm);
}

//-------------------------------------------------------------------------------------------------
/** evaluateTeamInsideAreaEntirely */ 
//-------------------------------------------------------------------------------------------------
// Defined by the retail reconstruction in ScriptConditionsTriggerAreas.cpp.

//-------------------------------------------------------------------------------------------------
/** evaluateTeamOutsideAreaEntirely */
//-------------------------------------------------------------------------------------------------
Bool ScriptConditions::evaluateTeamOutsideAreaEntirely(Parameter *pTeamParm, Parameter *pTriggerParm, Parameter *pTypeParm)
{
	return !(evaluateTeamInsideAreaEntirely(pTeamParm, pTriggerParm, pTypeParm) ||
					 evaluateTeamInsideAreaPartially(pTeamParm, pTriggerParm, pTypeParm));
}

//-------------------------------------------------------------------------------------------------
/** evaluateNamedAttackedByType */
//-------------------------------------------------------------------------------------------------
// ?evaluateNamedAttackedByType@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditionsNamedByType.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateTeamAttackedByType */
//-------------------------------------------------------------------------------------------------
// ?evaluateTeamAttackedByType@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditionsTeamAttackedByType.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateNamedAttackedByPlayer */
//-------------------------------------------------------------------------------------------------
// ?evaluateNamedAttackedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z present-unmatched
Bool ScriptConditions::evaluateNamedAttackedByPlayer(Parameter *pUnitParm, Parameter *pPlayerParm)
{
	Object *theObj = TheScriptEngine->getUnitNamed( pUnitParm->getString() );
	if (!theObj) {
		return false;
	}

	BodyModuleInterface* theBodyModule = theObj->getBodyModule();
	if (!theBodyModule) {
		return false;
	}
	
	const DamageInfo* lastDamageInfo = theBodyModule->getLastDamageInfo();
	
	if (!lastDamageInfo) {
		return false;
	}
	
	ObjectID id = lastDamageInfo->in.m_sourceID;
	Object* pAttacker = TheGameLogic->findObjectByID(id);
	Player *pPlayer = NULL;
	if (lastDamageInfo->in.m_sourcePlayerMask) {
		pPlayer = ThePlayerList->getPlayerFromMask(lastDamageInfo->in.m_sourcePlayerMask);
	}
	if (pPlayer || pAttacker) {
		Player *victimPlayer = playerFromParam(pPlayerParm);
		if (pPlayer == victimPlayer) {
			return true;	
		}
		if (!pAttacker) return false; // wasn't attacked.
		return (pAttacker->getControllingPlayer() == victimPlayer);
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
/** evaluateTeamAttackedByPlayer */
//-------------------------------------------------------------------------------------------------
// ?evaluateTeamAttackedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditionsTeamMembers.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateBuiltByPlayer */
//-------------------------------------------------------------------------------------------------
// ?evaluateBuiltByPlayer@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@1@Z present-unmatched
Bool ScriptConditions::evaluateBuiltByPlayer(Condition *pCondition, Parameter* pTypeParm, Parameter* pPlayerParm)
{
	if (pCondition->getCustomData()!=0) {
		// We have a cached value.
		if (TheScriptEngine->getFrameObjectCountChanged() == pCondition->getCustomFrame()) {
			// object count hasn't changed.  Use cached value.
			if (pCondition->getCustomData()==1) return true;
			if (pCondition->getCustomData()==-1) return false;
		}
	}
	Player* pPlayer = playerFromParam(pPlayerParm);
	if (!pPlayer) {
		return false;
	}

	const ThingTemplate* pTemplate = TheThingFactory->findTemplate(pTypeParm->getString());
	if (!pTemplate) {
		return false;
	}

	ScriptConditionsObjectTypesTemp types;
	objectTypesFromParam(pTypeParm, types.m_types);

	std::vector<Int> counts;
	std::vector<const ThingTemplate *> templates;

	Int numTemplates = types.m_types->prepForPlayerCounting(templates, counts);
	if (numTemplates > 0) {
		pPlayer->countObjectsByThingTemplate(numTemplates, &(*templates.begin()), false, &(*counts.begin()));
	} else {
		return 0;
	}

	Int sumOfObjs = rts::sum(counts);
	pCondition->setCustomData(-1); // false.
	if (sumOfObjs != 0) {
		pCondition->setCustomData(1); // true.
	}
	pCondition->setCustomFrame(TheScriptEngine->getFrameObjectCountChanged());
	return (sumOfObjs != 0);
}

//-------------------------------------------------------------------------------------------------
/** evaluateNamedCreated */
//-------------------------------------------------------------------------------------------------
Bool ScriptConditions::evaluateNamedCreated(Parameter* pUnitParm)
{
	// This is actually evaluateNamedExists(...)
	///@todo - evaluate created, not exists...
	BfmeScriptConditionEngine *engine = reinterpret_cast<BfmeScriptConditionEngine *>(TheScriptEngine);
	return engine->getUnitNamed(*reinterpret_cast<const AsciiString *>(pUnitParm)) != NULL;
}

//-------------------------------------------------------------------------------------------------
/** evaluateTeamCreated */
//-------------------------------------------------------------------------------------------------
// ?evaluateTeamCreated@ScriptConditions@@IAE_NPAVParameter@@@Z: retail body is in ScriptConditionsTeamState.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateUnitHealth */
//-------------------------------------------------------------------------------------------------
// ?evaluateUnitHealth@ScriptConditions@@IAE_NPAVParameter@@00@Z: retail body is in ScriptConditionsCompare.cpp

//-------------------------------------------------------------------------------------------------
/** evaluatePlayerHasCredits */
//-------------------------------------------------------------------------------------------------
// ?evaluatePlayerHasCredits@ScriptConditions@@IAE_NPAVParameter@@00@Z: retail body is in ScriptConditionsPlayerMask.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateBuildingEntered */
//-------------------------------------------------------------------------------------------------
// ?evaluateBuildingEntered@ScriptConditions@@IAE_NPAVParameter@@0@Z present-unmatched
Bool ScriptConditions::evaluateBuildingEntered( Parameter *pPlayerParm, Parameter *pItemParm )
{
	Object *theObj = TheScriptEngine->getUnitNamed( pItemParm->getString() );
	if (!theObj) {
		return false;
	}

	ContainModuleInterface *contain = theObj->getContain();
	if( !contain )
	{
		DEBUG_CRASH( ("evaluateBuildingEntered script condition -- building doesn't have a container.") );
		return false;
	}
	PlayerMaskType playerMask = theObj->getContain()->getPlayerWhoEntered();
	if (playerMask==0) {
		return false;
	}

	Player *pPlayer = playerFromParam(pPlayerParm);
	if (!pPlayer) {
		return false;
	}
	if (playerMask == pPlayer->getPlayerMask()) {
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
/** evaluateIsBuildingEmpty */
//-------------------------------------------------------------------------------------------------

#define BFME_SCRIPT_CONDITION_SLOT(N) virtual void slot##N() = 0

class BfmeScriptConditionContain
{
public:
	BFME_SCRIPT_CONDITION_SLOT(00); BFME_SCRIPT_CONDITION_SLOT(01); BFME_SCRIPT_CONDITION_SLOT(02); BFME_SCRIPT_CONDITION_SLOT(03);
	BFME_SCRIPT_CONDITION_SLOT(04); BFME_SCRIPT_CONDITION_SLOT(05); BFME_SCRIPT_CONDITION_SLOT(06); BFME_SCRIPT_CONDITION_SLOT(07);
	BFME_SCRIPT_CONDITION_SLOT(08); BFME_SCRIPT_CONDITION_SLOT(09); BFME_SCRIPT_CONDITION_SLOT(10); BFME_SCRIPT_CONDITION_SLOT(11);
	BFME_SCRIPT_CONDITION_SLOT(12); BFME_SCRIPT_CONDITION_SLOT(13); BFME_SCRIPT_CONDITION_SLOT(14); BFME_SCRIPT_CONDITION_SLOT(15);
	BFME_SCRIPT_CONDITION_SLOT(16); BFME_SCRIPT_CONDITION_SLOT(17); BFME_SCRIPT_CONDITION_SLOT(18); BFME_SCRIPT_CONDITION_SLOT(19);
	BFME_SCRIPT_CONDITION_SLOT(20); BFME_SCRIPT_CONDITION_SLOT(21); BFME_SCRIPT_CONDITION_SLOT(22); BFME_SCRIPT_CONDITION_SLOT(23);
	BFME_SCRIPT_CONDITION_SLOT(24); BFME_SCRIPT_CONDITION_SLOT(25); BFME_SCRIPT_CONDITION_SLOT(26); BFME_SCRIPT_CONDITION_SLOT(27);
	BFME_SCRIPT_CONDITION_SLOT(28); BFME_SCRIPT_CONDITION_SLOT(29); BFME_SCRIPT_CONDITION_SLOT(30); BFME_SCRIPT_CONDITION_SLOT(31);
	BFME_SCRIPT_CONDITION_SLOT(32); BFME_SCRIPT_CONDITION_SLOT(33); BFME_SCRIPT_CONDITION_SLOT(34); BFME_SCRIPT_CONDITION_SLOT(35);
	BFME_SCRIPT_CONDITION_SLOT(36); BFME_SCRIPT_CONDITION_SLOT(37); BFME_SCRIPT_CONDITION_SLOT(38); BFME_SCRIPT_CONDITION_SLOT(39);
	BFME_SCRIPT_CONDITION_SLOT(40); BFME_SCRIPT_CONDITION_SLOT(41); BFME_SCRIPT_CONDITION_SLOT(42); BFME_SCRIPT_CONDITION_SLOT(43);
	BFME_SCRIPT_CONDITION_SLOT(44); BFME_SCRIPT_CONDITION_SLOT(45); BFME_SCRIPT_CONDITION_SLOT(46); BFME_SCRIPT_CONDITION_SLOT(47);
	BFME_SCRIPT_CONDITION_SLOT(48); BFME_SCRIPT_CONDITION_SLOT(49); BFME_SCRIPT_CONDITION_SLOT(50); BFME_SCRIPT_CONDITION_SLOT(51);
	BFME_SCRIPT_CONDITION_SLOT(52); BFME_SCRIPT_CONDITION_SLOT(53); BFME_SCRIPT_CONDITION_SLOT(54); BFME_SCRIPT_CONDITION_SLOT(55);
	BFME_SCRIPT_CONDITION_SLOT(56); BFME_SCRIPT_CONDITION_SLOT(57); BFME_SCRIPT_CONDITION_SLOT(58); BFME_SCRIPT_CONDITION_SLOT(59);
	BFME_SCRIPT_CONDITION_SLOT(60); BFME_SCRIPT_CONDITION_SLOT(61); BFME_SCRIPT_CONDITION_SLOT(62); BFME_SCRIPT_CONDITION_SLOT(63);
	virtual UnsignedInt getContainCount(Bool countRiders) const = 0;	// vtable +0x100
};

#undef BFME_SCRIPT_CONDITION_SLOT

class BfmeScriptConditionObject
{
public:
	unsigned char m_unreconstructed[0x1FC];
	BfmeScriptConditionContain *m_contain;
};

Bool ScriptConditions::evaluateIsBuildingEmpty( Parameter *pItemParm )
{
	// BFME's getUnitNamed path consumes this Parameter address directly, unlike the ZH accessor path.
	BfmeScriptConditionEngine *engine = reinterpret_cast<BfmeScriptConditionEngine *>(TheScriptEngine);
	BfmeScriptConditionObject *theBuilding = reinterpret_cast<BfmeScriptConditionObject *>(
		engine->getUnitNamed(*reinterpret_cast<const AsciiString *>(pItemParm)));
	if (theBuilding) {
		BfmeScriptConditionContain *contain = theBuilding->m_contain;
		if (contain) {
			if (contain->getContainCount(false) > 0) {
				return true;
			}
		}
	}
	return false;
}

namespace Rva00327D30 {
// BFME filters: virtual destructor, allow, getPlayerMask, then next at +4.
class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS>
class BitFlags
{
	_STL::bitset<NUMBITS> m_bits;

public:
	enum BogusInitType { kInit = 0 };

	BitFlags(BogusInitType, Int idx1, Int idx2)
	{
		m_bits._Unchecked_set((size_t)idx1);
		m_bits._Unchecked_set((size_t)idx2);
	}
};

// BFME's KindOfMaskType is 192 bits: KINDOFMASK_NONE is pinned as
// ?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B at VA 0x012ED8B8, six zero dwords.
typedef BitFlags<192> KindOfMaskType;

// vtable 0x01083B70. Its out-of-line ctor 0x000C3DD0 (ILT 0x000382FD, pinned
// ??0PartitionFilterAcceptByKindOf@@QAE@ABV?$BitFlags@$0MA@@@0@Z) copies the
// two masks to +0x08 and +0x20; LevelGrantSpecialPower::actionAt00260180
// calls it under this name. Inlined here.
class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);

	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	explicit Rva0025ED50ObjectFilter(Object *object)
		: m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);

	Object *m_object;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	enum RelationshipAllowTypes
	{
		ALLOW_ENEMIES = 1,
		ALLOW_NEUTRAL = 2,
		ALLOW_ALLIES = 4
	};

	PartitionFilterRelationship(Object *object, Int flags, Bool match)
		: m_obj(object), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();

	Object *m_obj;
	Int m_flags;
	Bool m_match;
};

class PartitionFilterPlayer : public PartitionFilter
{
public:
	PartitionFilterPlayer(const Player *player, Bool match)
		: m_player(player), m_match(match) {}
	virtual ~PartitionFilterPlayer() {}
	virtual Bool allow(Object *);

	const Player *m_player;
	Bool m_match;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		Int distanceCalculation, PartitionFilter *filters);
};

}

class Rva001DCBB0Filter : public Rva00327D30::PartitionFilter
{
public:
	Rva001DCBB0Filter(Object *object, unsigned char match);
	virtual ~Rva001DCBB0Filter() {}
	virtual Bool allow(Object *);

	Player *m_player;
	unsigned char m_match;
};

//-------------------------------------------------------------------------------------------------
/** evaluateEnemySighted */
//-------------------------------------------------------------------------------------------------
Bool ScriptConditions::evaluateEnemySighted(Parameter *pItemParm, Parameter *pAllianceParm, Parameter *pPlayerParm)
{
	typedef Rva00327D30::PartitionFilterPlayer SightedPlayerFilter;
	typedef Rva00327D30::PartitionFilterRelationship SightedRelationshipFilter;
	typedef Rva00327D30::Rva0025ED50RootFilter SightedRootFilter;
	typedef Rva00327D30::Rva0025ED50ObjectFilter SightedObjectFilter;
	typedef Rva00327D30::PartitionFilterAcceptByKindOf SightedKindFilter;

	Object *theObj = reinterpret_cast<BfmeScriptConditionEngine *>(TheScriptEngine)->getUnitNamed(*reinterpret_cast<const AsciiString *>(pItemParm));
	if (!theObj) {
		_WriteBarrier();
		return false;
	}

	Int relationDescriber;
	switch (*reinterpret_cast<const Int *>(reinterpret_cast<const char *>(pAllianceParm) + 0x08)) {
	case 0:
		relationDescriber = SightedRelationshipFilter::ALLOW_ENEMIES;
		break;
	case 1:
		relationDescriber = SightedRelationshipFilter::ALLOW_NEUTRAL;
		break;
	case 2:
		relationDescriber = SightedRelationshipFilter::ALLOW_ALLIES;
		break;
	default:
		relationDescriber = -1;
		break;
	}

	UnsignedShort mask = ((BfmeP1087 *)TheScriptEngine)->bfmeNext1087(pPlayerParm);
	while (mask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		Bool found = (reinterpret_cast<Rva00327D30::PartitionManager *>(ThePartitionManager)->getClosestObject(reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(theObj) + 0x38),
			theObj->getVisionRange(), 0,
			SightedPlayerFilter(player, true).link(
			SightedRelationshipFilter(theObj, relationDescriber, false).link(
			SightedRootFilter().link(
			Rva001DCBB0Filter(theObj, 0).link(
			SightedObjectFilter(theObj).link(
			&SightedKindFilter(*reinterpret_cast<const Rva00327D30::KindOfMaskType *>(&KINDOFMASK_NONE),
				Rva00327D30::KindOfMaskType(Rva00327D30::KindOfMaskType::kInit, 88, 133))))))))) != 0;
		if (found != false)
			return true;
	}

	_ReadWriteBarrier();
	return false;
}

//-------------------------------------------------------------------------------------------------
/** evaluateTypeSighted */
//-------------------------------------------------------------------------------------------------
// ?evaluateTypeSighted@ScriptConditions@@IAE_NPAVParameter@@00@Z present-unmatched
Bool ScriptConditions::evaluateTypeSighted(Parameter *pItemParm, Parameter *pTypeParm, Parameter* pPlayerParm)
{

	Object *theObj = TheScriptEngine->getUnitNamed( pItemParm->getString() );
	if (!theObj) {
		return false;
	}

	Player *pPlayer = playerFromParam(pPlayerParm);
	if (!pPlayer) {
		return false;
	}

	ScriptConditionsObjectTypesTemp types;
	objectTypesFromParam(pTypeParm, types.m_types);

	// and only stuff that is not dead
	PartitionFilterAlive filterAlive;

	// and only nonstealthed items.
	PartitionFilterRejectByObjectStatus filterStealth( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_STEALTHED ), 
																										 MAKE_OBJECT_STATUS_MASK2( OBJECT_STATUS_DETECTED, OBJECT_STATUS_DISGUISED ) );

	// and only on-map (or not)
	PartitionFilterSameMapStatus filterMapStatus(theObj);

	PartitionFilter *filters[] = { &filterAlive, &filterStealth, &filterMapStatus, NULL };

	Real visionRange = theObj->getVisionRange();

	SimpleObjectIterator *iter = ThePartitionManager->iterateObjectsInRange(
								theObj, visionRange, FROM_CENTER_2D, filters); 
	MemoryPoolObjectHolder hold(iter);
	for (Object *them = iter->first(); them; them = iter->next())
	{
		if (them->getControllingPlayer() == pPlayer) {
			if (types.m_types->isInSet(them->getTemplate()->getName()))
				return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
/** evaluateNamedDiscovered */
//-------------------------------------------------------------------------------------------------
// ?evaluateNamedDiscovered@ScriptConditions@@IAE_NPAVParameter@@0@Z present-unmatched
Bool ScriptConditions::evaluateNamedDiscovered(Parameter *pItemParm, Parameter* pPlayerParm)
{
	Object *theObj = TheScriptEngine->getUnitNamed( pItemParm->getString() );
	if (!theObj) {
		return false;
	}

	Player *pPlayer = playerFromParam(pPlayerParm);
	if (!pPlayer) {
		return false;
	}
	
	// We are held, so we are not visible.
	if( theObj->isDisabledByType( DISABLED_HELD ) ) 
	{
		return false;
	}

	// If we are stealthed we are not visible.
	if( theObj->getStatusBits().test( OBJECT_STATUS_STEALTHED ) && 
			!theObj->getStatusBits().test( OBJECT_STATUS_DETECTED ) &&
			!theObj->getStatusBits().test( OBJECT_STATUS_DISGUISED ) ) 
	{
		return false;
	}
	ObjectShroudStatus shroud = theObj->getShroudedStatus(pPlayer->getPlayerIndex());
	return (shroud == OBJECTSHROUD_CLEAR || shroud == OBJECTSHROUD_PARTIAL_CLEAR);
}

//-------------------------------------------------------------------------------------------------
/** evaluateTeamDiscovered */
//-------------------------------------------------------------------------------------------------
// ?evaluateTeamDiscovered@ScriptConditions@@IAE_NPAVParameter@@0@Z present-unmatched
Bool ScriptConditions::evaluateTeamDiscovered(Parameter *pTeamParm, Parameter *pPlayerParm)
{	
	Team *theTeam = TheScriptEngine->getTeamNamed( pTeamParm->getString() );
	if (!theTeam) {
		return false;
	}

	Player *pPlayer = playerFromParam(pPlayerParm);
	if (!pPlayer) {
		return false;
	}

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *pObj = iter.cur();
		if (!pObj) {
			continue;
		}

		// We are held, so we are not visible.
		if( pObj->isDisabledByType( DISABLED_HELD ) ) 
		{
			continue;
		}
		
		// If we are stealthed we are not visible.
		if( pObj->getStatusBits().test( OBJECT_STATUS_STEALTHED ) && 
				!pObj->getStatusBits().test( OBJECT_STATUS_DETECTED ) &&
				!pObj->getStatusBits().test( OBJECT_STATUS_DISGUISED ) )
		{
			continue;
		}
		ObjectShroudStatus shroud = pObj->getShroudedStatus(pPlayer->getPlayerIndex());
		
		if (shroud == OBJECTSHROUD_CLEAR || shroud == OBJECTSHROUD_PARTIAL_CLEAR) {
			return true;
		}
	}

	return false;
}

//-------------------------------------------------------------------------------------------------
/** evaluateMissionAttempts */
//-------------------------------------------------------------------------------------------------
// ?evaluateMissionAttempts@ScriptConditions@@IAE_NPAVParameter@@00@Z present-unmatched
Bool ScriptConditions::evaluateMissionAttempts(Parameter *pPlayerParm, Parameter *pComparisonParm, Parameter *pAttemptsParm)
{	
//Player* pPlayer = playerFromParam(pPlayerParm);
	return false;
}

//-------------------------------------------------------------------------------------------------
/** evaluateNamedOwnedByPlayer */
//-------------------------------------------------------------------------------------------------
// ?evaluateNamedOwnedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditionsPlayerMask.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateTeamOwnedByPlayer */
//-------------------------------------------------------------------------------------------------
// ?evaluateTeamOwnedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditionsTeamCompare.cpp


//-------------------------------------------------------------------------------------------------
/** evaluatePlayerHasNOrFewerBuildings */
//-------------------------------------------------------------------------------------------------
// ?evaluatePlayerHasNOrFewerBuildings@ScriptConditions@@IAE_NPAVParameter@@0@Z present-unmatched
Bool ScriptConditions::evaluatePlayerHasNOrFewerBuildings(Parameter *pBuildingCountParm, Parameter *pPlayerParm)
{
	Player* pPlayer = playerFromParam(pPlayerParm);
	if (!pPlayer) {
		return false;
	}

	return (pBuildingCountParm->getInt() >= pPlayer->countBuildings());
}

//-------------------------------------------------------------------------------------------------
/** evaluatePlayerHasNOrFewerFactionBuildings */
//-------------------------------------------------------------------------------------------------
// ?evaluatePlayerHasNOrFewerFactionBuildings@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditionsPlayerMask.cpp

//-------------------------------------------------------------------------------------------------
/** evaluatePlayerHasPower */
//-------------------------------------------------------------------------------------------------
// ?evaluatePlayerHasPower@ScriptConditions@@IAE_NPAVParameter@@@Z: retail body is in ScriptConditionsPlayerHasPower.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateNamedReachedWaypointsEnd */
//-------------------------------------------------------------------------------------------------
Bool ScriptConditions::evaluateNamedReachedWaypointsEnd(Parameter *pUnitParm, Parameter* pWaypointPathParm)
{
	Object *theObj = TheScriptEngine->getUnitNamed( pUnitParm->getString() );
	if (!theObj) {
		return false;
	}
	
	AIUpdateInterface *ai = theObj->getAIUpdateInterface();
	if (!ai) 
		return false;

	const Waypoint *targetWay = ai->getCompletedWaypoint();

	if (!targetWay) return false;

	AsciiString	pathName = pWaypointPathParm->getString();

	if (targetWay->getPathLabel1() == pathName) return true;
	if (targetWay->getPathLabel2() == pathName) return true;
	if (targetWay->getPathLabel3() == pathName) return true;

	return false;
}

//-------------------------------------------------------------------------------------------------
/** evaluateTeamReachedWaypointsEnd */
//-------------------------------------------------------------------------------------------------
// ?evaluateTeamReachedWaypointsEnd@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditions_evaluateTeamReachedWaypointsEnd.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateVideoHasCompleted */
//-------------------------------------------------------------------------------------------------
// ?evaluateVideoHasCompleted@ScriptConditions@@IAE_NPAVParameter@@@Z present-unmatched
Bool ScriptConditions::evaluateVideoHasCompleted(Parameter *pVideoParm)
{
	return TheScriptEngine->isVideoComplete(pVideoParm->getString(), true);
}

//-------------------------------------------------------------------------------------------------
/** evaluateSpeechHasCompleted */
//-------------------------------------------------------------------------------------------------
// ?evaluateSpeechHasCompleted@ScriptConditions@@IAE_NPAVParameter@@@Z present-unmatched
Bool ScriptConditions::evaluateSpeechHasCompleted(Parameter *pSpeechParm)
{
	return TheScriptEngine->isSpeechComplete(pSpeechParm->getString(), true);
}

//-------------------------------------------------------------------------------------------------
/** evaluateAudioHasCompleted */
//-------------------------------------------------------------------------------------------------
// The parameter's string is at Parameter+0x10 -- retail's `add edx,0x10` and a
// raw field read, no getString() call -- where the vendored layout puts it at
// +0x14, and the ScriptEngine virtual is vtable +0xA8. Retail folded this body
// with evaluateVideoHasCompleted and evaluateSpeechHasCompleted, which is why
// the slot is spelled by its offset: all three forward one Parameter to a
// (const AsciiString &, Bool) virtual, so nothing here distinguishes them.
Bool ScriptConditions::evaluateAudioHasCompleted(Parameter *pAudioParm)
{
	return ((BfmeScriptConditionEngine *)TheScriptEngine)->unidentifiedIsComplete(
		((BfmeScriptConditionParameter *)pAudioParm)->m_string, true);
}

//-------------------------------------------------------------------------------------------------
/** evaluatePlayerSpecialPowerFromUnitTriggered */
//-------------------------------------------------------------------------------------------------
// ?evaluatePlayerSpecialPowerFromUnitTriggered@ScriptConditions@@IAE_NPAVParameter@@00@Z: retail body is in ScriptConditionsPowerAndUpgradeFromUnit.cpp

//-------------------------------------------------------------------------------------------------
/** evaluatePlayerSpecialPowerFromUnitMidway */
//-------------------------------------------------------------------------------------------------
// ?evaluatePlayerSpecialPowerFromUnitMidway@ScriptConditions@@IAE_NPAVParameter@@00@Z: retail body is in ScriptConditionsPowerAndUpgradeFromUnit.cpp

//-------------------------------------------------------------------------------------------------
/** evaluatePlayerSpecialPowerFromUnitComplete */
//-------------------------------------------------------------------------------------------------
// ?evaluatePlayerSpecialPowerFromUnitComplete@ScriptConditions@@IAE_NPAVParameter@@00@Z: retail body is in ScriptConditionsPowerAndUpgradeFromUnit.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateUpgradeFromUnitComplete */
//-------------------------------------------------------------------------------------------------
// ?evaluateUpgradeFromUnitComplete@ScriptConditions@@IAE_NPAVParameter@@00@Z: retail body is in ScriptConditionsPowerAndUpgradeFromUnit.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateScienceAcquired */
//-------------------------------------------------------------------------------------------------
// ?evaluateScienceAcquired@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditionsScienceAcquired.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateCanPurchaseScience */
//-------------------------------------------------------------------------------------------------
// ?evaluateCanPurchaseScience@ScriptConditions@@IAE_NPAVParameter@@0@Z present-unmatched
Bool ScriptConditions::evaluateCanPurchaseScience(Parameter *pPlayerParm, Parameter *pScienceParm)
{
	Player *pPlayer = playerFromParam(pPlayerParm);
	if (pPlayer)
	{
		ScienceType science = TheScienceStore->getScienceFromInternalName(pScienceParm->getString());
		if (science == SCIENCE_INVALID)
			return FALSE;
		return pPlayer->isCapableOfPurchasingScience(science);
	}
	return FALSE;
}

//-------------------------------------------------------------------------------------------------
/** evaluateSciencePurchasePoints */
//-------------------------------------------------------------------------------------------------
// ?evaluateSciencePurchasePoints@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditionsSciencePurchasePoints.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateNamedHasFreeContainerSlots */
//-------------------------------------------------------------------------------------------------
// ?evaluateNamedHasFreeContainerSlots@ScriptConditions@@IAE_NPAVParameter@@@Z: retail body is in ScriptConditionsNamedContain.cpp


//-------------------------------------------------------------------------------------------------
/** evaluateNamedEnteredArea */
//-------------------------------------------------------------------------------------------------
// ?evaluateNamedEnteredArea@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditionsNamedEnteredArea.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateNamedExitedArea */
//-------------------------------------------------------------------------------------------------
// ?evaluateNamedExitedArea@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditionsTriggerAreas.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateTeamEnteredAreaEntirely */
//-------------------------------------------------------------------------------------------------
// ?evaluateTeamEnteredAreaEntirely@ScriptConditions@@IAE_NPAVParameter@@00@Z: retail body is in ScriptConditionsTriggerAreas.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateTeamEnteredAreaPartially */
//-------------------------------------------------------------------------------------------------
// ?evaluateTeamEnteredAreaPartially@ScriptConditions@@IAE_NPAVParameter@@00@Z: retail body is in ScriptConditionsTriggerAreas.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateTeamExitedAreaEntirely */
//-------------------------------------------------------------------------------------------------
// ?evaluateTeamExitedAreaEntirely@ScriptConditions@@IAE_NPAVParameter@@00@Z: retail body is in ScriptConditionsTriggerAreas.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateTeamExitedAreaPartially */
//-------------------------------------------------------------------------------------------------
// ?evaluateTeamExitedAreaPartially@ScriptConditions@@IAE_NPAVParameter@@00@Z: retail body is in ScriptConditionsTriggerAreas.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateMultiplayerAlliedVictory */
//-------------------------------------------------------------------------------------------------
// ?evaluateMultiplayerAlliedVictory@ScriptConditions@@IAE_NXZ present-unmatched
Bool ScriptConditions::evaluateMultiplayerAlliedVictory(void)
{
	return TheVictoryConditions->isLocalAlliedVictory();
}

//-------------------------------------------------------------------------------------------------
/** evaluateMultiplayerAlliedDefeat */
//-------------------------------------------------------------------------------------------------
// ?evaluateMultiplayerAlliedDefeat@ScriptConditions@@IAE_NXZ present-unmatched
Bool ScriptConditions::evaluateMultiplayerAlliedDefeat(void)
{
	return TheVictoryConditions->isLocalAlliedDefeat();
}

//-------------------------------------------------------------------------------------------------
/** evaluateMultiplayerPlayerDefeat */
//-------------------------------------------------------------------------------------------------
// ?evaluateMultiplayerPlayerDefeat@ScriptConditions@@IAE_NXZ: retail body is in BfmeConv895.cpp

//-------------------------------------------------------------------------------------------------
/** evaluatePlayerUnitCondition */
//-------------------------------------------------------------------------------------------------
// This body now lives in game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsPlayerUnitCondition.cpp.

//-------------------------------------------------------------------------------------------------
/** evaluatePlayerHasComparisonPercentPower */
//-------------------------------------------------------------------------------------------------
// ?evaluatePlayerHasComparisonPercentPower@ScriptConditions@@IAE_NPAVParameter@@00@Z: retail body is in ScriptConditionsPlayerMask.cpp
//-------------------------------------------------------------------------------------------------
/** evaluateRva003231E0: original retail condition spelling is unproven. */
//-------------------------------------------------------------------------------------------------
Bool ScriptConditions::evaluateRva003231E0(Parameter *pPlayerParm, Parameter *pComparisonParm, Parameter *pKWHParm)
{
	Int desiredKilowattExcess = reinterpret_cast<BfmeScriptConditionIntParameter *>(pKWHParm)->m_int;
	PlayerMaskType playerMask = ((BfmeP1087 *)TheScriptEngine)->bfmeNext1087(pPlayerParm);
	Parameter *comparisonParameter = pComparisonParm;
	while (playerMask) {
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(playerMask);
		BfmeScriptConditionEnergyPlayer *energy =
			reinterpret_cast<BfmeScriptConditionEnergyPlayer *>(pPlayer);
		Int actualKilowats = energy->m_production - energy->m_consumption;
		Bool comparison = false;
		switch (reinterpret_cast<BfmeScriptConditionIntParameter *>(comparisonParameter)->m_int)
		{
			case Parameter::LESS_THAN: comparison = (actualKilowats < desiredKilowattExcess); break;
			case Parameter::LESS_EQUAL: comparison = (actualKilowats <= desiredKilowattExcess); break;
			case Parameter::EQUAL: comparison = (actualKilowats == desiredKilowattExcess); break;
			case Parameter::GREATER_EQUAL: comparison = (actualKilowats >= desiredKilowattExcess); break;
			case Parameter::GREATER: comparison = (actualKilowats > desiredKilowattExcess); break;
			case Parameter::NOT_EQUAL: comparison = (actualKilowats != desiredKilowattExcess); break;
		}
		if (comparison) {
			return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
/** evaluateSkirmishSpecialPowerIsReady - does any unit have this special power ready to use? */
//-------------------------------------------------------------------------------------------------
// ?evaluateSkirmishSpecialPowerIsReady@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditionsSkirmishSpecialPowerIsReady.cpp


//-------------------------------------------------------------------------------------------------
/** evaluatePlayerDestroyedNOrMoreBuildings */
//-------------------------------------------------------------------------------------------------
// ?evaluatePlayerDestroyedNOrMoreBuildings@ScriptConditions@@IAE_NPAVParameter@@00@Z: retail body is in ScriptConditionsPlayerMask.cpp

//-------------------------------------------------------------------------------------------------
/** evaluateUnitHasEmptied */
//-------------------------------------------------------------------------------------------------
Bool ScriptConditions::evaluateUnitHasEmptied(Parameter *pUnitParm)
{
	BfmeScriptConditionEngine *scriptEngine =
		reinterpret_cast<BfmeScriptConditionEngine *>(TheScriptEngine);
	BfmeEvaluateUnitObject *object = reinterpret_cast<BfmeEvaluateUnitObject *>(
		scriptEngine->getUnitNamed(*(const AsciiString *)pUnitParm));
	if (!object) {
		return false;
	}

	// have we checked this one before?
	TransportStatus *stats = s_transportStatuses;
	while (stats) {
		if (stats->m_objID == object->getID()) {
			break;
		}

		stats = stats->m_nextStatus;
	}

	BfmeEvaluateContainModule *cmi = object->getContain();
	Int numPeeps = cmi ? cmi->getContainCount(0) : 0;

	UnsignedInt frameNum = reinterpret_cast<BfmeScriptConditionGameLogic *>(
		TheGameLogic)->m_frame;


	if (stats == NULL) 
	{
		TransportStatus *transportStatus = newInstance(TransportStatus);
		transportStatus->m_objID = object->getID();
		transportStatus->m_frameNumber = frameNum;
		transportStatus->m_unitCount = numPeeps;
		transportStatus->m_nextStatus = s_transportStatuses;
		s_transportStatuses = transportStatus;
		return false;
	}

	if (stats->m_frameNumber == frameNum - 1) {
		if (stats->m_unitCount > 0 && numPeeps == 0) {
			// don't actually update the info on this round, because we want to make sure that
			// multiple calls to this in the same frame actually work.
			return true;
		}
	}

	// perform the update.
	stats->m_frameNumber = frameNum;
	stats->m_unitCount = numPeeps;
	return false;
}

//-------------------------------------------------------------------------------------------------
// ?evaluateTeamIsContained@ScriptConditions@@MAE_NPAVParameter@@_N@Z: retail body is in ScriptConditionsTeamMembers.cpp

//-------------------------------------------------------------------------------------------------
// ?evaluateUnitHasObjectStatus@ScriptConditions@@IAE_NPAVParameter@@0@Z present-unmatched
Bool ScriptConditions::evaluateUnitHasObjectStatus(Parameter *pUnitParm, Parameter *pObjectStatus)
{
	Object *object = TheScriptEngine->getUnitNamed(pUnitParm->getString());
	if (!object) {
		return false;
	}

	return( object->getStatusBits().testForAny( pObjectStatus->getStatus() ) );
}

//-------------------------------------------------------------------------------------------------
// ?evaluateTeamHasObjectStatus@ScriptConditions@@IAE_NPAVParameter@@0_N@Z: retail body is in ScriptConditionsTeamMembers.cpp

//-------------------------------------------------------------------------------------------------
// The byte-matched BFME implementation lives in
// ScriptConditionsSkirmishValueInArea.cpp.

//-------------------------------------------------------------------------------------------------
// ?evaluateSkirmishPlayerIsFaction@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditionsPlayerMask.cpp

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_evaluateSkirmishSuppliesWithinDistancePerimeter_Thunk.cpp
// ?evaluateSkirmishSuppliesWithinDistancePerimeter@ScriptConditions@@ present-unmatched
Bool ScriptConditions::evaluateSkirmishSuppliesWithinDistancePerimeter(Parameter *pSkirmishPlayerParm, Parameter *pDistanceParm, Parameter *pLocationParm, Parameter *pValueParm)
{
	Player *player = playerFromParam(pSkirmishPlayerParm);
	if (!player) {
		return false;
	}

	PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(pLocationParm->getString());
	if (!trigger) {
		return false;
	}

	Coord3D center;
	trigger->getCenterPoint(&center);
	Real distance = trigger->getRadius() + pDistanceParm->getReal();
	
	Real compareToValue = pValueParm->getReal();

	PartitionFilterAcceptByKindOf f1(MAKE_KINDOF_MASK(KINDOF_STRUCTURE), KINDOFMASK_NONE);
	PartitionFilterPlayerAffiliation f2(player, ALLOW_NEUTRAL, true);
	PartitionFilterOnMap filterMapStatus;

	PartitionFilter *filters[] = { &f1, &f2, &filterMapStatus, 0 };

	SimpleObjectIterator *iter = ThePartitionManager->iterateObjectsInRange(&center, distance, FROM_CENTER_2D, filters, ITER_FASTEST);
	MemoryPoolObjectHolder hold(iter);

	Real maxValue = 0;
	for (Object *them = iter->first(); them; them = iter->next()) {
		static const NameKeyType key_warehouseUpdate = NAMEKEY("SupplyWarehouseDockUpdate");
		SupplyWarehouseDockUpdate *warehouseModule = (SupplyWarehouseDockUpdate*) them->findUpdateModule( key_warehouseUpdate );
		if (!warehouseModule) {
			continue;
		}

		Real value = player->getSupplyBoxValue() * warehouseModule->getBoxesStored();
		if (value > maxValue) {
			maxValue = value;
		}
	}

	return maxValue > compareToValue;
}

//-------------------------------------------------------------------------------------------------
// @todo: PERF_EVALUATE PERF_WARNING
// If this is called multiple times per frame, the cost could add up. This will infrequently (read:
// never) change, so it shouldn't be called very often. jkmcd
// ?evaluateSkirmishPlayerTechBuildingWithinDistancePerimeter@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@11@Z present-unmatched
Bool ScriptConditions::evaluateSkirmishPlayerTechBuildingWithinDistancePerimeter(Condition *pCondition, Parameter *pSkirmishPlayerParm, Parameter *pDistanceParm, Parameter *pLocationParm)
{
	Player *player = playerFromParam(pSkirmishPlayerParm);
	if (!player) {
		return false;
	}
	// If we have a chached value, return it. [8/8/2003]
	if (pCondition->getCustomData()==1) return true;
	if (pCondition->getCustomData()==-1) return false;

	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pLocationParm->getString());
	if (!pTrig) {
		return false;
	}

	Coord3D center;
	pTrig->getCenterPoint(&center);
	Real radius = pTrig->getRadius() + pDistanceParm->getReal();

	PartitionFilterAcceptByKindOf f1(MAKE_KINDOF_MASK(KINDOF_TECH_BUILDING), KINDOFMASK_NONE);
	PartitionFilterPlayerAffiliation f2(player, ALLOW_ALLIES, false);
	PartitionFilterPlayer f3(player, false);	// Don't find your own units, as our affiliation to self is neutral.
	PartitionFilterOnMap filterMapStatus;


	PartitionFilter *filters[] = { &f1, &f2, &f3, &filterMapStatus, 0 };

	Bool comparison = ThePartitionManager->getClosestObject(&center, radius, FROM_CENTER_2D, filters) != NULL;
	pCondition->setCustomData(-1); // false.
	if (comparison) {
		pCondition->setCustomData(1); // true.
	}
	return comparison;
}

//-------------------------------------------------------------------------------------------------
// ?evaluateSkirmishCommandButtonIsReady@ScriptConditions@@MAE_NPAVParameter@@00_N@Z: retail body is in ScriptConditionsTeamMembers.cpp

//-------------------------------------------------------------------------------------------------
// ?evaluateSkirmishUnownedFactionUnitComparison@ScriptConditions@@IAE_NPAVParameter@@00@Z: retail body is in ScriptConditionsUnownedFactionRva00329230.cpp

//-------------------------------------------------------------------------------------------------
// ?evaluateSkirmishPlayerHasPrereqsToBuild@ScriptConditions@@IAE_NPAVParameter@@0@Z present-unmatched
Bool ScriptConditions::evaluateSkirmishPlayerHasPrereqsToBuild( Parameter *pSkirmishPlayerParm, Parameter *pObjectTypeParm )
{
	Player *player = playerFromParam(pSkirmishPlayerParm);
	if (!player) {
		return FALSE;
	}

	ScriptConditionsObjectTypesTemp types;
	objectTypesFromParam(pObjectTypeParm, types.m_types);

	return types.m_types->canBuildAny(player);
}

//-------------------------------------------------------------------------------------------------
// ?evaluateSkirmishPlayerHasComparisonGarrisoned@ScriptConditions@@IAE_NPAVParameter@@00@Z: retail body is in ScriptConditionsGarrisonedUnits.cpp

//-------------------------------------------------------------------------------------------------
// ?evaluateSkirmishPlayerHasComparisonCapturedUnits@ScriptConditions@@IAE_NPAVParameter@@00@Z: retail body is in ScriptConditionsSkirmishPlayerHasComparisonCapturedUnits.cpp

//-------------------------------------------------------------------------------------------------
// ?evaluateSkirmishNamedAreaExists@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditionsTriggerAreas.cpp

//-------------------------------------------------------------------------------------------------
// ?evaluateSkirmishPlayerHasUnitsInArea@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@1@Z present-unmatched
Bool ScriptConditions::evaluateSkirmishPlayerHasUnitsInArea(Condition *pCondition, Parameter *pSkirmishPlayerParm, Parameter *pTriggerParm )
{
	AsciiString triggerName = pTriggerParm->getString();
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());
	if (pTrig == NULL) return false;

	Player* pPlayer = playerFromParam(pSkirmishPlayerParm);
	if (!pPlayer) {
		return false;
	}
	Player::PlayerTeamList::const_iterator it;
	Bool anyChanges = false;


	if (pCondition->getCustomData() == 0) anyChanges = true;

	for (it = pPlayer->getPlayerTeams()->begin(); it != pPlayer->getPlayerTeams()->end(); ++it) {
		if (anyChanges) break;
		for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
			if (anyChanges) break;
			Team *team = iter.cur();
			if (!team) {
				continue;
			}
			if (team->didEnterOrExit()) {
				anyChanges = true; 
			}
		}
	}

	if (TheScriptEngine->getFrameObjectCountChanged() > pCondition->getCustomFrame()) {
		anyChanges = true; // Objects were added/deleted last frame, so count could have changed.  jba.
	}

	if (!anyChanges) {
		if (pCondition->getCustomData()==-1) return false;
		if (pCondition->getCustomData()==1) return true;
	}

	Int count = 0;
	for (it = pPlayer->getPlayerTeams()->begin(); it != pPlayer->getPlayerTeams()->end(); ++it) {
		for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
			Team *team = iter.cur();
			if (!team) {
				continue;
			}
			for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
				Object *pObj = iter.cur();
				if (!pObj) {
					continue;
				}

				if (pObj->isInside(pTrig)) {

					//
					// dead objects will not be considered.
					//
					if (!(pObj->isEffectivelyDead() || pObj->isKindOf(KINDOF_INERT) || pObj->isKindOf(KINDOF_PROJECTILE)) ) {
						count++;
					}
				}
			}
		}
	}
	
	Bool comparison = count > 0;
	pCondition->setCustomData(-1); // false.
	if (comparison) {
		pCondition->setCustomData(1); // true.
	}
	pCondition->setCustomFrame(TheScriptEngine->getFrameObjectCountChanged());
	return comparison;
}

//-------------------------------------------------------------------------------------------------
/** evaluateRva00323650: original retail condition spelling is unproven. */
Bool ScriptConditions::evaluateRva00323650(Condition *pCondition, Parameter *pSkirmishPlayerParm, Parameter *pMinSupplyAmount )
{
	BfmeScriptConditionCache *cache =
		reinterpret_cast<BfmeScriptConditionCache *>(pCondition);
	UnsignedInt frame = reinterpret_cast<BfmeScriptConditionGameLogic *>(TheGameLogic)->m_frame;
	if (frame <= cache->m_customFrame) {
		if (cache->m_customData == -1) {
			return false;
		}
		if (cache->m_customData == 1) {
			return true;
		}
	}
	cache->m_customFrame = frame + 5;
	PlayerMaskType playerMask = ((BfmeP1087 *)TheScriptEngine)->bfmeNext1087(pSkirmishPlayerParm);
	while (playerMask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
		if (player && player->isSupplySourceSafe(
			reinterpret_cast<BfmeScriptConditionIntParameter *>(pMinSupplyAmount)->m_int)) {
			cache->m_customData = 1;
			return true;
		}
	}
	cache->m_customData = -1;
	return false;
}	

//-------------------------------------------------------------------------------------------------
Bool ScriptConditions::evaluateSkirmishSupplySourceAttacked(Parameter *pSkirmishPlayerParm)
{
	Player *player = playerFromParam(pSkirmishPlayerParm);
	if (!player) {
		return FALSE;
	}
	// BFME's Player::isSupplySourceAttacked is not ZH's: ZH forwards to m_ai,
	// retail inlines `cmp DWORD PTR [eax+0x30],0xffffffff` / `sete al`.
	struct SupplySourceView { char pad[0x30]; Int field; };
	if (((SupplySourceView *)player)->field != -1) {
		return FALSE;
	}
	return TRUE;
}	

//-------------------------------------------------------------------------------------------------
// ?evaluateSkirmishStartPosition@ScriptConditions@@IAE_NPAVParameter@@0@Z present-unmatched
Bool ScriptConditions::evaluateSkirmishStartPosition(Parameter *pSkirmishPlayerParm, Parameter *pStartNdx)
{
	Player *player = playerFromParam(pSkirmishPlayerParm);
	if (!player) {
		return FALSE;
	}
	Int ndx = pStartNdx->getInt()-1;  // externally 1, 2, 3, internally 0, 1, 2.
	Int startNdx = player->getMpStartIndex();
	return ndx == startNdx;
}	

//-------------------------------------------------------------------------------------------------
// ?evaluateSkirmishPlayerHasBeenAttackedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z present-unmatched
Bool ScriptConditions::evaluateSkirmishPlayerHasBeenAttackedByPlayer(Parameter *pSkirmishPlayerParm, Parameter *pAttackedByParm )
{
	Player *player = playerFromParam(pSkirmishPlayerParm);
	if (!player) {
		return FALSE;
	}
	
	Player *srcPlayer = playerFromParam(pAttackedByParm);
	if (!srcPlayer ) {
		return FALSE;
	}

	return player->getAttackedBy(srcPlayer->getPlayerIndex());
}

//-------------------------------------------------------------------------------------------------
// ?evaluateSkirmishPlayerIsOutsideArea@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@1@Z present-unmatched
Bool ScriptConditions::evaluateSkirmishPlayerIsOutsideArea(Condition *pCondition, Parameter *pSkirmishPlayerParm, Parameter *pTriggerParm )
{
	// Even though these will be prechecked in the other function, we want to preflight here as well.
	Player *player = playerFromParam(pSkirmishPlayerParm);
	if (!player) {
		return FALSE;
	}

	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());
	if (!pTrig) {
		return FALSE;
	}

	return !evaluateSkirmishPlayerHasUnitsInArea(pCondition, pSkirmishPlayerParm, pTriggerParm);
}

//-------------------------------------------------------------------------------------------------
// ?evaluateSkirmishPlayerHasDiscoveredPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditionsSkirmishPlayerHasDiscoveredPlayer.cpp

//-------------------------------------------------------------------------------------------------
// ?evaluateMusicHasCompleted@ScriptConditions@@IAE_NPAVParameter@@0@Z: retail body is in ScriptConditions_evaluateMusicHasCompleted_Bfme.cpp

//-------------------------------------------------------------------------------------------------
// ?evaluatePlayerLostObjectType@ScriptConditions@@IAE_NPAVParameter@@0@Z present-unmatched
Bool ScriptConditions::evaluatePlayerLostObjectType(Parameter *pPlayerParm, Parameter *pTypeParm)
{
	Player *player = playerFromParam(pPlayerParm);
	if (!player) {
		return FALSE;
	}
	
	ScriptConditionsObjectTypesTemp objs;
	objectTypesFromParam(pTypeParm, objs.m_types);

	std::vector<Int> counts;
	std::vector<const ThingTemplate *> templates;

	Int numTemplates = objs.m_types->prepForPlayerCounting(templates, counts);
	if (numTemplates > 0) {
		player->countObjectsByThingTemplate(numTemplates, &(*templates.begin()), true, &(*counts.begin()));
	} else {
		return FALSE;
	}

	Int sumOfObjs = rts::sum(counts);
	Int currentCount = TheScriptEngine->getObjectCount(player->getPlayerIndex(), pTypeParm->getString());

	if (sumOfObjs != currentCount) {
		TheScriptEngine->setObjectCount(player->getPlayerIndex(), pTypeParm->getString(), sumOfObjs);
	}

	return (sumOfObjs < currentCount);
}

//-------------------------------------------------------------------------------------------------
/** Evaluate a condition */
//-------------------------------------------------------------------------------------------------
// Scripts.h declares Condition::getConditionType as an inline accessor, so
// calling it here emits this TU's own COMDAT copy of
// ?getConditionType@Condition@@QAE?AW4ConditionType@1@XZ, which collides at link
// with retail's only copy of that body (the 4-byte accessor at 0x002ED4B0, owned
// by game/GameEngine/Source/GameLogic/ScriptEngine/Condition_getConditionType.cpp).
// Retail calls the accessor from evaluateCondition, so the same body over the same
// +0x04 member under a TU-local view name keeps the bytes and drops the colliding
// symbol. The leading pad is the Condition vtable pointer: no virtual member is
// declared here, so this view emits no vftable of its own.
struct Rva002ED4B0ConditionType
{
	unsigned char m_vtablePad[4];
	Condition::ConditionType m_conditionType;
	Condition::ConditionType getConditionType(void) { return m_conditionType; }
};

// byte-exact reconstruction: game/GameEngine/Source/GameLogic/ScriptEngine/script_conditions.cpp
// ?evaluateCondition@ScriptConditions@@UAE_NPAVCondition@@@Z present-unmatched
Bool ScriptConditions::evaluateCondition( Condition *pCondition )
{
	switch (((Rva002ED4B0ConditionType *)pCondition)->getConditionType()) {
		default: 
			DEBUG_CRASH(("Unknown ScriptCondition type %d", ((Rva002ED4B0ConditionType *)pCondition)->getConditionType())); 
			return false;
		case Condition::PLAYER_ALL_DESTROYED: 
			return evaluateAllDestroyed(pCondition->getParameter(0));
		case Condition::PLAYER_ALL_BUILDFACILITIES_DESTROYED: 
			return evaluateAllBuildFacilitiesDestroyed(pCondition->getParameter(0));
		case Condition::TEAM_INSIDE_AREA_PARTIALLY: 
			return evaluateTeamInsideAreaPartially(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		case Condition::NAMED_INSIDE_AREA: 
			return evaluateNamedInsideArea(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::TEAM_DESTROYED: 
			return evaluateIsDestroyed(pCondition->getParameter(0));
		case Condition::NAMED_DESTROYED: 
			return evaluateNamedUnitDestroyed(pCondition->getParameter(0));
		case Condition::NAMED_DYING: 
			return evaluateNamedUnitDying(pCondition->getParameter(0));
		case Condition::NAMED_TOTALLY_DEAD: 
			return evaluateNamedUnitTotallyDead(pCondition->getParameter(0));
		case Condition::NAMED_NOT_DESTROYED: 
			return evaluateNamedUnitExists(pCondition->getParameter(0));
		case Condition::TEAM_HAS_UNITS: 
			return evaluateHasUnits(pCondition->getParameter(0));
		case Condition::CAMERA_MOVEMENT_FINISHED: 
			return TheTacticalView->isCameraMovementFinished();
		case Condition::TEAM_STATE_IS: 
			return evaluateTeamStateIs(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::TEAM_STATE_IS_NOT: 
			return evaluateTeamStateIsNot(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::NAMED_OUTSIDE_AREA:
			return evaluateNamedOutsideArea(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::TEAM_INSIDE_AREA_ENTIRELY:
			return evaluateTeamInsideAreaEntirely(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		case Condition::TEAM_OUTSIDE_AREA_ENTIRELY:
			return evaluateTeamOutsideAreaEntirely(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		case Condition::NAMED_ATTACKED_BY_OBJECTTYPE:
			return evaluateNamedAttackedByType(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::TEAM_ATTACKED_BY_OBJECTTYPE:
			return evaluateTeamAttackedByType(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::NAMED_ATTACKED_BY_PLAYER:
			return evaluateNamedAttackedByPlayer(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::TEAM_ATTACKED_BY_PLAYER:
			return evaluateTeamAttackedByPlayer(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::BUILT_BY_PLAYER:
			return evaluateBuiltByPlayer(pCondition, pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::NAMED_CREATED:
			return evaluateNamedCreated(pCondition->getParameter(0));
		case Condition::TEAM_CREATED:
			return evaluateTeamCreated(pCondition->getParameter(0));
		case Condition::PLAYER_HAS_CREDITS:
			return evaluatePlayerHasCredits(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		case Condition::BRIDGE_REPAIRED:
			return evaluateBridgeRepaired(pCondition->getParameter(0));
		case Condition::BRIDGE_BROKEN:
			return evaluateBridgeBroken(pCondition->getParameter(0));
		case Condition::NAMED_DISCOVERED:
			return evaluateNamedDiscovered(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::TEAM_DISCOVERED:
			return evaluateTeamDiscovered(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::BUILDING_ENTERED_BY_PLAYER:
			return evaluateBuildingEntered(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::ENEMY_SIGHTED:
		{	
			Int numParameters = pCondition->getNumParameters();
			DEBUG_ASSERTCRASH(numParameters == 3, ("'Condition: [Unit] Unit has sighted a(n) friendly/neutral/enemy unit belonging to a side.' has too few parameters. Please fix in WB. (jkmcd)"));

			if (numParameters < 3) {
				return false;
			}

			return evaluateEnemySighted(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		}
		case Condition::TYPE_SIGHTED:
			return evaluateTypeSighted(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		case Condition::NAMED_BUILDING_IS_EMPTY:
			return evaluateIsBuildingEmpty(pCondition->getParameter(0));
		case Condition::MISSION_ATTEMPTS:
			return evaluateMissionAttempts(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		case Condition::NAMED_OWNED_BY_PLAYER:
			return evaluateNamedOwnedByPlayer(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::TEAM_OWNED_BY_PLAYER:
			return evaluateTeamOwnedByPlayer(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::PLAYER_HAS_N_OR_FEWER_BUILDINGS:
			return evaluatePlayerHasNOrFewerBuildings(pCondition->getParameter(1), pCondition->getParameter(0));
		case Condition::PLAYER_HAS_N_OR_FEWER_FACTION_BUILDINGS:
			return evaluatePlayerHasNOrFewerFactionBuildings(pCondition->getParameter(1), pCondition->getParameter(0));
		case Condition::PLAYER_HAS_POWER:
			return evaluatePlayerHasPower(pCondition->getParameter(0));
		case Condition::PLAYER_HAS_NO_POWER:
			return !evaluatePlayerHasPower(pCondition->getParameter(0));
		case Condition::NAMED_REACHED_WAYPOINTS_END:
			return evaluateNamedReachedWaypointsEnd(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::TEAM_REACHED_WAYPOINTS_END:
			return evaluateTeamReachedWaypointsEnd(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::NAMED_SELECTED:
			return evaluateNamedSelected(pCondition, pCondition->getParameter(0));
		case Condition::NAMED_ENTERED_AREA:
			return evaluateNamedEnteredArea(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::NAMED_EXITED_AREA:
			return evaluateNamedExitedArea(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::TEAM_ENTERED_AREA_ENTIRELY:
			return evaluateTeamEnteredAreaEntirely(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		case Condition::TEAM_ENTERED_AREA_PARTIALLY:
			return evaluateTeamEnteredAreaPartially(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		case Condition::TEAM_EXITED_AREA_ENTIRELY:
			return evaluateTeamExitedAreaEntirely(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		case Condition::TEAM_EXITED_AREA_PARTIALLY:
			return evaluateTeamExitedAreaPartially(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		case Condition::MULTIPLAYER_ALLIED_VICTORY:
			return evaluateMultiplayerAlliedVictory();
		case Condition::MULTIPLAYER_ALLIED_DEFEAT:
			return evaluateMultiplayerAlliedDefeat();
		case Condition::MULTIPLAYER_PLAYER_DEFEAT:
			return evaluateMultiplayerPlayerDefeat();
		case Condition::HAS_FINISHED_VIDEO:
			return evaluateVideoHasCompleted(pCondition->getParameter(0));
		case Condition::HAS_FINISHED_SPEECH:
			return evaluateSpeechHasCompleted(pCondition->getParameter(0));
		case Condition::HAS_FINISHED_AUDIO:
			return evaluateAudioHasCompleted(pCondition->getParameter(0));
		case Condition::UNIT_HEALTH:
			return evaluateUnitHealth(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		case Condition::PLAYER_TRIGGERED_SPECIAL_POWER:
			return evaluatePlayerSpecialPowerFromUnitTriggered(pCondition->getParameter(0), pCondition->getParameter(1), NULL);
		case Condition::PLAYER_TRIGGERED_SPECIAL_POWER_FROM_NAMED:
			return evaluatePlayerSpecialPowerFromUnitTriggered(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		case Condition::PLAYER_MIDWAY_SPECIAL_POWER:
			return evaluatePlayerSpecialPowerFromUnitMidway(pCondition->getParameter(0), pCondition->getParameter(1), NULL);
		case Condition::PLAYER_MIDWAY_SPECIAL_POWER_FROM_NAMED:
			return evaluatePlayerSpecialPowerFromUnitMidway(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		case Condition::PLAYER_COMPLETED_SPECIAL_POWER:
			return evaluatePlayerSpecialPowerFromUnitComplete(pCondition->getParameter(0), pCondition->getParameter(1), NULL);
		case Condition::PLAYER_COMPLETED_SPECIAL_POWER_FROM_NAMED:
			return evaluatePlayerSpecialPowerFromUnitComplete(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		case Condition::PLAYER_ACQUIRED_SCIENCE:
			return evaluateScienceAcquired(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::PLAYER_CAN_PURCHASE_SCIENCE:
			return evaluateCanPurchaseScience(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::PLAYER_HAS_SCIENCEPURCHASEPOINTS:
			return evaluateSciencePurchasePoints(pCondition->getParameter(0), pCondition->getParameter(1));
		case Condition::NAMED_HAS_FREE_CONTAINER_SLOTS:
			return evaluateNamedHasFreeContainerSlots(pCondition->getParameter(0));
		case Condition::DEFUNCT_PLAYER_SELECTED_GENERAL:
		case Condition::DEFUNCT_PLAYER_SELECTED_GENERAL_FROM_NAMED:
			DEBUG_CRASH(("PLAYER_SELECTED_GENERAL script conditions are no longer in use\n")); 
			return false;
		case Condition::PLAYER_BUILT_UPGRADE:
			return evaluateUpgradeFromUnitComplete(pCondition->getParameter(0), pCondition->getParameter(1), NULL);
		case Condition::PLAYER_BUILT_UPGRADE_FROM_NAMED:
			return evaluateUpgradeFromUnitComplete(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		case Condition::PLAYER_HAS_OBJECT_COMPARISON:
			return evaluatePlayerUnitCondition(pCondition, pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2), pCondition->getParameter(3));
		case Condition::PLAYER_DESTROYED_N_BUILDINGS_PLAYER:
			return evaluatePlayerDestroyedNOrMoreBuildings(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		case Condition::PLAYER_HAS_COMPARISON_UNIT_TYPE_IN_TRIGGER_AREA:
		{	
			Int numParameters = pCondition->getNumParameters();
			DEBUG_ASSERTCRASH(numParameters == 5, ("'Condition: [Player] has (comparison) unit type in an area' has too few parameters. Please fix in WB. (jkmcd)"));

			if (numParameters < 5) {
				return false;
			}

			return evaluatePlayerHasUnitTypeInArea(pCondition, pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2), pCondition->getParameter(3), pCondition->getParameter(4));
		}
		case Condition::PLAYER_HAS_COMPARISON_UNIT_KIND_IN_TRIGGER_AREA:
		{
			Int numParameters = pCondition->getNumParameters();
			DEBUG_ASSERTCRASH(numParameters == 5, ("'Condition: [Player] has (comparison) kind of unit or structure in an area' has too few parameters. Please fix in WB. (jkmcd)"));

			if (numParameters < 5) {
				return false;
			}

			return evaluatePlayerHasUnitKindInArea(pCondition, pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2), pCondition->getParameter(3), pCondition->getParameter(4));
		}
		case Condition::UNIT_EMPTIED:
			return evaluateUnitHasEmptied(pCondition->getParameter(0));
			
		case Condition::PLAYER_POWER_COMPARE_PERCENT:
			return evaluatePlayerHasComparisonPercentPower(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
			
		case Condition::PLAYER_EXCESS_POWER_COMPARE_VALUE:
			return evaluateRva003231E0(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
			
		case Condition::SKIRMISH_SPECIAL_POWER_READY:
			return evaluateSkirmishSpecialPowerIsReady(pCondition->getParameter(0), pCondition->getParameter(1));
			
		case Condition::UNIT_HAS_OBJECT_STATUS:
			return evaluateUnitHasObjectStatus(pCondition->getParameter(0), pCondition->getParameter(1));

		case Condition::TEAM_ALL_HAS_OBJECT_STATUS:
			return evaluateTeamHasObjectStatus(pCondition->getParameter(0), pCondition->getParameter(1), true);

		case Condition::TEAM_SOME_HAVE_OBJECT_STATUS:
			return evaluateTeamHasObjectStatus(pCondition->getParameter(0), pCondition->getParameter(1), false);
			
		case Condition::SKIRMISH_VALUE_IN_AREA:
			return evaluateSkirmishValueInArea(pCondition, pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2), pCondition->getParameter(3));

		case Condition::SKIRMISH_PLAYER_FACTION:
			return evaluateSkirmishPlayerIsFaction(pCondition->getParameter(0), pCondition->getParameter(1));

		case Condition::SKIRMISH_SUPPLIES_VALUE_WITHIN_DISTANCE:
			return evaluateSkirmishSuppliesWithinDistancePerimeter(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2), pCondition->getParameter(3));

		case Condition::SKIRMISH_TECH_BUILDING_WITHIN_DISTANCE:
			return evaluateSkirmishPlayerTechBuildingWithinDistancePerimeter(pCondition, pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));

		case Condition::SKIRMISH_COMMAND_BUTTON_READY_ALL:
			return evaluateSkirmishCommandButtonIsReady(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2), true);

		case Condition::SKIRMISH_COMMAND_BUTTON_READY_PARTIAL:
			return evaluateSkirmishCommandButtonIsReady(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2), false);

		case Condition::SKIRMISH_UNOWNED_FACTION_UNIT_EXISTS:
			return evaluateSkirmishUnownedFactionUnitComparison(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));

		case Condition::SKIRMISH_PLAYER_HAS_PREREQUISITE_TO_BUILD:
			return evaluateSkirmishPlayerHasPrereqsToBuild(pCondition->getParameter(0), pCondition->getParameter(1));
		
		case Condition::SKIRMISH_PLAYER_HAS_COMPARISON_GARRISONED:
			return evaluateSkirmishPlayerHasComparisonGarrisoned(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		
		case Condition::SKIRMISH_PLAYER_HAS_COMPARISON_CAPTURED_UNITS:
			return evaluateSkirmishPlayerHasComparisonCapturedUnits(pCondition->getParameter(0), pCondition->getParameter(1), pCondition->getParameter(2));
		
		case Condition::SKIRMISH_NAMED_AREA_EXIST:
			return evaluateSkirmishNamedAreaExists(pCondition->getParameter(0), pCondition->getParameter(1));
		
		case Condition::SKIRMISH_PLAYER_HAS_UNITS_IN_AREA:
			return evaluateSkirmishPlayerHasUnitsInArea(pCondition, pCondition->getParameter(0), pCondition->getParameter(1));
		
		case Condition::SKIRMISH_PLAYER_HAS_BEEN_ATTACKED_BY_PLAYER:
			return evaluateSkirmishPlayerHasBeenAttackedByPlayer(pCondition->getParameter(0), pCondition->getParameter(1));
		
		case Condition::SKIRMISH_PLAYER_IS_OUTSIDE_AREA:
			return evaluateSkirmishPlayerIsOutsideArea(pCondition, pCondition->getParameter(0), pCondition->getParameter(1));
		
		case Condition::SKIRMISH_PLAYER_HAS_DISCOVERED_PLAYER:
			return evaluateSkirmishPlayerHasDiscoveredPlayer(pCondition->getParameter(0), pCondition->getParameter(1));
		
		case Condition::MUSIC_TRACK_HAS_COMPLETED:
			return evaluateMusicHasCompleted(pCondition->getParameter(0), pCondition->getParameter(1));

		case Condition::SUPPLY_SOURCE_SAFE:
			return evaluateRva00323650(pCondition, pCondition->getParameter(0), pCondition->getParameter(1));
		
		case Condition::SUPPLY_SOURCE_ATTACKED:
			return evaluateSkirmishSupplySourceAttacked(pCondition->getParameter(0));
		
		case Condition::START_POSITION_IS:
			return evaluateSkirmishStartPosition(pCondition->getParameter(0), pCondition->getParameter(1));

		case Condition::PLAYER_LOST_OBJECT_TYPE:
			return evaluatePlayerLostObjectType(pCondition->getParameter(0), pCondition->getParameter(1));

		
	}
}
