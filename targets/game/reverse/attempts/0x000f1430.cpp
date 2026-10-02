// ?updateGenericScripts@Team@@QAEXXZ
// partial score=0.6626 date=2026-10-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/asciistringsetoutofline /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "ascii_string.h"
#define ASCIISTRING_H
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

// FILE: Team.cpp /////////////////////////////////////////////////////////////////////////////////
// Team interface implementation
// Author: Michael S. Booth, March 2001
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/GameState.h"
#pragma push_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
extern "C" void free(void *);
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
		return MP_GLUE_ALLOCATE(ARGCLASS); \
	} \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		free(p); \
	} \
protected: \
	inline void *operator new(size_t s) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
		return ::operator new(s); \
	} \
	inline void operator delete(void *p) \
	{ \
		free(p); \
	} \
private: \
	virtual MemoryPool *getObjectMemoryPool() \
	{ \
		return ARGCLASS::getClassMemoryPool(); \
	} \
public:
#include "Common/Team.h"
#pragma pop_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")
#include "Common/ThingFactory.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/PlayerTemplate.h"
#include "Common/ThingTemplate.h"
#include "Common/WellKnownKeys.h"
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"

#include "GameLogic/SidesList.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/PolygonTrigger.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/ScriptActions.h"
#include "GameLogic/ScriptEngine.h"


// Banked 0x000F1430, true extent 415 bytes.
// Delay early-continue reproduces the loop entry/backedge and temporary slots.
// getGenericScript callee ILT 0x1fa8c -> 0xed6f0 independently decoded as
// ECX receiver, index, narrow-string output, ret 8. The opaque invoke declaration
// intentionally has no production pin yet; masked probes are not link proof.
struct Rva000F1430TeamFields {
    void *slot_00;
    TeamPrototype *slot_04;
    char pad_08[0x44-8];
    bool slot_44[32];
    unsigned slot_64[32];
};
struct Rva000F1430ScriptFields {
    char pad_00[0x10];
    int slot_10;
    bool slot_14;
    char slot_15;
    bool slot_16;
    char pad_17[0x20-0x17];
    ScriptAction *slot_20;
};
class Rva000F1430ScriptEngineView {
public:
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void slot_1c();
    virtual void slot_20();
    virtual void slot_24();
    virtual void slot_28();
    virtual void slot_2c();
    virtual void slot_30();
    virtual void slot_34();
    virtual void slot_38();
    virtual void slot_3c();
    virtual void slot_40();
    virtual void slot_44();
    virtual void slot_48();
    virtual void slot_4c();
    virtual void slot_50();
    virtual void slot_54();
    virtual void slot_58();
    virtual void slot_5c();
    virtual bool slot_60(AsciiString *, Script *, Team *, Player *);
    virtual void slot_64(AsciiString *, ScriptAction *, Team *);
};
// Independently decoded ECX receiver, index and narrow-string output; ret 8.
class Rva000ED6F0Prototype {
public:
    Script *invoke(int, AsciiString *);
    char pad_00[0x1f0];
    AsciiString slot_1f0[32];
    const AsciiString &name(int i) const {return slot_1f0[i];}
};
static const AsciiString &rva000F1430TeamName(TeamPrototype *proto)
{
    if (!proto) return AsciiString::TheEmptyString;
    return *(AsciiString *)((char *)proto + 0x14);
}
static unsigned rva000F1430Frame()
{
    return *(unsigned *)((char *)TheGameLogic + 0x3c);
}
void Team::updateGenericScripts(void)
{
    Rva000F1430TeamFields *fields = (Rva000F1430TeamFields *)this;
    if (!fields->slot_04) return;
    for (int i = 0; i < 32; ++i) {
        if (fields->slot_44[i]) {
            AsciiString scriptName;
            Script *script = ((Rva000ED6F0Prototype *)fields->slot_04)->invoke(i, &scriptName);
            Rva000F1430ScriptFields *sf = (Rva000F1430ScriptFields *)script;
            if (script && sf->slot_14) {
                if (sf->slot_10 > 0 && fields->slot_64[i] > rva000F1430Frame()) continue;
                {
                    if (((Rva000F1430ScriptEngineView *)TheScriptEngine)->slot_60(&scriptName, script, this, 0)) {
                        if (sf->slot_16) fields->slot_44[i] = false;
                        ScriptAction *actions = sf->slot_20;
                        ((Rva000F1430ScriptEngineView *)TheScriptEngine)->slot_64(&scriptName, actions, this);
                        AsciiString msg("Generic script '");
                        msg.concat(((Rva000ED6F0Prototype *)fields->slot_04)->name(i));
                        msg.concat("' run on team ");
                        msg.concat(rva000F1430TeamName(fields->slot_04));
                        TheScriptEngine->AppendDebugMessage(msg, false);
                    }
                    int delay = sf->slot_10;
                    if (delay > 0) fields->slot_64[i] = rva000F1430Frame() + delay * 5;
                }
            } else fields->slot_44[i] = false;
        }
    }
}

