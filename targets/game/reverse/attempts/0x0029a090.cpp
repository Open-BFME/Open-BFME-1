// ??0PhysicsBehaviorModuleData@@QAE@XZ
// partial score=0.2063 date=2026-10-02
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
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

// PhysicsBehavior.cpp 
// Simple rigid body physics
// Author: Michael S. Booth, November 2001

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// please talk to MDC (x36804) before taking this out
#define NO_DEBUG_CRC

#include "Common/PerfTimer.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/CrushDie.h"		// for CrushEnum
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/LogicRandomValue.h"

// Snapshot.cpp and retail 0x0006B180 show only the implicit vptr store.
inline Snapshot::Snapshot() {}

// The native ZH declaration is smaller. This view applies only to the BFME
// factory allocation witnessed below; the additional fields keep their offsets.
// No behavioral names are assigned to the unknown BFME words.
// BFME factory 0x0011AA70 allocates 0x5c then calls this through ILT 0x41d0d.
struct Rva0029A090Fields {
    const void *slot_00;
    unsigned slot_04;
    float slot_08,slot_0c,slot_10,slot_14;
    int slot_18,slot_1c,slot_20,slot_24;
    float slot_28,slot_2c,slot_30,slot_34,slot_38,slot_3c;
    bool slot_40,slot_41,slot_42;
    float slot_44,slot_48,slot_4c;
    unsigned slot_50,slot_54;
    bool slot_58,slot_59;
};
PhysicsBehaviorModuleData::PhysicsBehaviorModuleData()
{
    Rva0029A090Fields *p=(Rva0029A090Fields*)this;
    p->slot_08=1.3f;p->slot_0c=1.3f;p->slot_2c=1.3f;p->slot_30=1.3f;
    p->slot_3c=0;p->slot_40=false;p->slot_41=false;p->slot_42=false;
    p->slot_50=0;p->slot_54=0;p->slot_58=false;p->slot_59=false;
    p->slot_00=__identifier("??_7PhysicsBehaviorModuleData@@6B@");
    p->slot_10=.33f;p->slot_14=.66f;
    p->slot_24=2;p->slot_28=5.0f;
    p->slot_34=.33f;p->slot_38=.66f;
    p->slot_44=.33f;p->slot_48=.66f;p->slot_4c=1.0f;
    p->slot_18=5;p->slot_1c=10;p->slot_20=5;
}
