// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: list<crateCreationEntry>::_M_insert_dispatch over a
// const-iterator range, retail 0x00379C60, 75 bytes.
//
// The retail node is 0x10 bytes: two list links followed by the eight-byte
// crateCreationEntry (one AsciiString handle and one Real).  Keeping the
// element construction out of line reproduces STLport's allocator/construct/
// link loop used by CrateSystem's two range-insertion call sites.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CrateSystem.h
struct crateCreationEntry
{
	void *crateName;
	Real crateChance;
};

namespace _STL
{
template <>
void _Construct(crateCreationEntry *p, const crateCreationEntry &value);
}

void BfmeCrateCreationEntryListInsertAnchor(
	_STL::list<crateCreationEntry> &destination,
	_STL::list<crateCreationEntry>::iterator where,
	const _STL::list<crateCreationEntry> &source)
{
	destination.insert(where, source.begin(), source.end());
}
