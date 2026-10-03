// ??0TurretStateMachine@@QAE@PAVTurretAI@@PAVObject@@VAsciiString@@@Z
// partial score=1.0 date=2026-10-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/turretai /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib /I.
// stlport
// readable body of TurretStateMachine constructor: game/GameEngine/Source/GameLogic/AI/TurretAI.cpp
// Exact parent requires queued shared State/StateMachine/FireWeapon layout repair.
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

// TurretAI.cpp 
// Turret behavior implementation
// Author: Steven Johnson, April 2002

#include <windows.h>
#include "game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
#define ASCIISTRING_H
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

#define DEFINE_WEAPONSLOTTYPE_NAMES

#include "Common/GameAudio.h"
#include "Common/PerfTimer.h"
#include "Common/RandomValue.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"

#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/TurretAI.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/WeaponSet.h"

TurretStateMachine::TurretStateMachine( TurretAI* tai, Object *obj, AsciiString name ) : m_turretAI(tai), StateMachine( obj, name )
{
	static const StateConditionInfo fireConditions[] = 
	{
		StateConditionInfo(outOfWeaponRangeObject, TURRETAI_AIM, NULL),
		StateConditionInfo(NULL, NULL, NULL)	// keep last
	};

	// order matters: first state is the default state.
	defineState( TURRETAI_IDLE,					newInstance(TurretAIIdleState)( this ), TURRETAI_IDLE, TURRETAI_IDLESCAN );
	defineState( TURRETAI_IDLESCAN,			newInstance(TurretAIIdleScanState)( this ), TURRETAI_HOLD, TURRETAI_HOLD );
	defineState( TURRETAI_AIM,					newInstance(TurretAIAimTurretState)( this ), TURRETAI_FIRE, TURRETAI_HOLD );
	defineState( TURRETAI_FIRE,					newInstance(AIAttackFireWeaponState)( this, tai ), TURRETAI_AIM, TURRETAI_AIM, fireConditions );
	defineState( TURRETAI_RECENTER,			newInstance(TurretAIRecenterTurretState)( this ), TURRETAI_IDLE, TURRETAI_IDLE );
	defineState( TURRETAI_HOLD,					newInstance(TurretAIHoldTurretState)( this ), TURRETAI_RECENTER, TURRETAI_RECENTER );
}

