// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
//
// Retail 0x002E32A0, 143 bytes. Sibling of SkirmishBattleHonors::intAsStr
// (0x000A9010, in SkirmishBattleHonorsLoyalGames.cpp): same "%d" format-into-
// AsciiString shape (fuzzy twin, tools/fuzzy_twin_scan.py), but the literal read
// out of retail .rdata at 0x010CF4F0 is "ObjID#%08x" and the value is the id at
// +0x74 of the incoming object. Identity unproven; landed under an
// address-derived name. Reading the id into a local AFTER the result string is
// declared is what keeps the value in eax (retail); before it, or through the
// expression, the allocator mirrors ecx/edx.

// The canonical string keeps normal exits inlined to releaseBuffer while
// the compiler-generated unwind action calls AsciiString::~AsciiString.
#include "ascii_string.h"

#include "../../Include/Common/ScalarTypes.h"

struct Rva002E4030Template;
struct Rva002E32A0IdOwner
{
	unsigned char pad00[4];
	Rva002E4030Template *m_template;
	char m_unknown08[0x74 - 0x08];
	int m_id;
	char m_unknown78[0x204 - 0x78];
	void *m_ai;
};

static AsciiString Rva002E32A0ObjectIdAsStr(const Rva002E32A0IdOwner *p)
{
	AsciiString result;
	Int id = p->m_id;
	result.format("ObjID#%08x", id);
	return result;
}

// The body is STATIC in retail (internal linkage is what orders the return-slot
// load before the local's zero store; the same function with external linkage
// compiles 53 bytes apart), so this TU-local caller keeps it emitted.
// ?Rva002E32A0Caller@@YAXPBURva002E32A0IdOwner@@PAVAsciiString@@@Z absent-from-retail
void Rva002E32A0Caller(const Rva002E32A0IdOwner *p, AsciiString *out)
{
	*out = Rva002E32A0ObjectIdAsStr(p);
}

struct lua_State;

// Retain the bank's spelling as an alias to the canonical owning string.
typedef AsciiString Rva002E32A0AsciiString;

extern "C" void lua_settop(lua_State *state, int index);
extern "C" void lua_getglobal(lua_State *state, const char *name);
extern "C" int lua_type(lua_State *state, int index);
extern "C" void lua_setglobal(lua_State *state, const char *name);

unsigned Rva00990030Lookup(lua_State *range, int index) throw();
extern "C" void bfmeGoUPC(lua_State *state, int objectId);

#define __PLACEMENT_VEC_NEW_INLINE
#include "Common/GameMemory.h"
#pragma auto_inline(off)
#include "Common/Overridable.h"
#pragma auto_inline(on)

struct Rva002E4030Template
{
	unsigned char pad00[4];
	const Overridable *m_nextOverride;
	char m_unknown08[0x4c8 - 0x08];
	unsigned char m_ready;
};

class Rva002E4030LuaHost
{
public:
	void updateObjectGlobal(Rva002E32A0IdOwner *object);

	char m_unknown00[8];
	lua_State *m_state;
	lua_State *m_stackState;
};

// Retail 002E4030: native string cleanup with nonthrowing Lua lookup and C API.
// See identity_evidence/002e4030-native-string-lifetime.md.
void Rva002E4030LuaHost::updateObjectGlobal(Rva002E32A0IdOwner *object)
{
	if (object->m_ai == 0)
	{
		Rva002E4030Template *objectTemplate = object->m_template;
		if (objectTemplate != 0)
		{
			const Overridable *overrideNode = objectTemplate->m_nextOverride;
			if (overrideNode != 0)
				objectTemplate = (Rva002E4030Template *)overrideNode->getFinalOverride();
		}
		if (objectTemplate->m_ready == 0)
			return;
	}

	lua_settop(m_stackState, 0);
	const Rva002E32A0AsciiString objectName = Rva002E32A0ObjectIdAsStr(object);
	int objectId = object->m_id;
	lua_getglobal(m_state, objectName.str());
	if (lua_type(m_state, 1) != 1 &&
		(unsigned)objectId == Rva00990030Lookup(m_state, 1))
	{
		lua_settop(m_state, -2);
		return;
	}
	lua_settop(m_state, -2);
	bfmeGoUPC(m_state, objectId);
	lua_setglobal(m_state, objectName.str());
}
