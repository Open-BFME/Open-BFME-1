// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
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

typedef int Int;

struct Rva002E32A0IdOwner
{
	unsigned char pad00[ 0x74 ];
	Int m_id;			// +0x74, the object id the "ObjID#%08x" literal names
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
