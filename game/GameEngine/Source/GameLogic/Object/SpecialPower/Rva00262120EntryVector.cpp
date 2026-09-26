// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmekindof /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Retail [0x00262120, 0x0026222E): 270 bytes, ending in RET 20.
// The verified collector at 0x002622D0 calls this overflow operation on
// 16-byte entries. Keep its out-of-line entry-copy context separate from
// the collector's forced-inline copy; both contexts are independently gated.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"

class Object;
class Rva002622D0Subject;

struct Rva00262120Entry
{
	Object *object;
	std::vector<Rva002622D0Subject *> grouped;

	__declspec(noinline) Rva00262120Entry(const Rva00262120Entry &that)
		: object(that.object), grouped(that.grouped) {}
};

namespace _STL
{
	template <>
	__forceinline void _Construct<Rva00262120Entry, Rva00262120Entry>(
		Rva00262120Entry *dest, const Rva00262120Entry &source)
	{
		_STLP_PLACEMENT_NEW (dest) Rva00262120Entry(source);
	}

	template void vector<Rva00262120Entry,
		allocator<Rva00262120Entry> >::_M_insert_overflow(
		Rva00262120Entry *, const Rva00262120Entry &,
		const __false_type &, unsigned int, bool);
}
