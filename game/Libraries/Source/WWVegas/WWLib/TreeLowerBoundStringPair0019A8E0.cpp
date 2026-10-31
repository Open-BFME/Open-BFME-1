// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME: STLport _Rb_tree<Gen_..._m12cd, V>::_M_lower_bound, one 364-byte
// body shared (identical-code-folded) by two set<> instantiations whose key
// is a 12-byte struct: two AsciiStrings (the compared fields, at +0x0 and
// +0x4) plus a third untouched dword that pads the type to "m12cd" (12 bytes,
// declared copy ctor/dtor).  Retail's descent inlines the same three-site
// comparison the sibling _M_find file (RvaTreeFindStringPair.cpp) leaves as
// calls: first.compare(other.first), then the swapped-operand call, then
// second.compare(other.second) as the tie-break -- pair<AsciiString,
// AsciiString>::operator< spelled out with all three sites inlined instead of
// left as calls, which is what the extra descent bytes (relative to the
// plain-AsciiString lower_bound in RvaTreeBoundsAsciiString.cpp) buy.
//
// There is no allocation here, so the third dword's width/meaning is not
// knowable; it rides along unread by the comparator, same as the sibling
// _M_find file's note about the untouched mapped type.

#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

#include "ascii_string.h"

// AsciiString::compare(const AsciiString &), expanded in place.  Calling the
// member emits a ?compare@AsciiString@@QBEHABV1@@Z COMDAT that is not retail's
// 0x0005FEB0 body.  The buffer pointer is the string's first word; its length
// is the unsigned short at +4 and the characters start at +8.  The body is a
// member of a TU-local view: as a free function it left operator< out of line.
namespace
{
struct AsciiCompareView
{
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};
	Header *m_data;
	int compare( const AsciiCompareView &s ) const
	{
		int thatLen = s.m_data ? s.m_data->length : 0;
		const char *thatData = s.m_data ? &s.m_data->data[0] : (const char *)"";
		int thisLen = m_data ? m_data->length : 0;
		const char *thisData = m_data ? &m_data->data[0] : (const char *)"";
		int n = thisLen < thatLen ? thisLen : thatLen;
		int c = memcmp(thisData, thatData, n);
		if (c != 0)
			return c;
		return thisLen - thatLen;
	}
};

}

static __forceinline int asciiCompare( const AsciiString &left, const AsciiString &right )
{
	return reinterpret_cast<const AsciiCompareView &>(left).compare(reinterpret_cast<const AsciiCompareView &>(right));
}

// Gen_t_0019a8e0_m12cd / Gen_t_0019bca0_m12cd from game/gen_small/fam_009.cpp:
// a 12-byte key with a declared copy ctor/dtor -- two AsciiStrings (the
// fields the descent actually compares) plus a third dword the comparator
// never reads.  Names match the generator's declared struct names exactly so
// the _Rb_tree<T, T, _Identity<T>, less<T>, allocator<T>> instantiation
// mangles to the pinned symbol.
struct Gen_t_0019a8e0_m12cd
{
	AsciiString m_first;
	AsciiString m_second;
	Int m_unused;
};

inline bool operator<(const Gen_t_0019a8e0_m12cd &left, const Gen_t_0019a8e0_m12cd &right)
{
	return asciiCompare(left.m_first, right.m_first) < 0
		|| (!(asciiCompare(right.m_first, left.m_first) < 0)
			&& asciiCompare(left.m_second, right.m_second) < 0);
}

typedef _STL::_Rb_tree<Gen_t_0019a8e0_m12cd, Gen_t_0019a8e0_m12cd, _STL::_Identity<Gen_t_0019a8e0_m12cd>,
	_STL::less<Gen_t_0019a8e0_m12cd>, _STL::allocator<Gen_t_0019a8e0_m12cd> > Rva0019A8E0Tree;

// retail 0x00199C80
Bool BfmeTreeLowerBoundAnchor0019A8E0(const Rva0019A8E0Tree &tree, const Gen_t_0019a8e0_m12cd &key)
{
	return tree.lower_bound(key) != tree.end();
}

struct Gen_t_0019bca0_m12cd
{
	AsciiString m_first;
	AsciiString m_second;
	Int m_unused;
};

inline bool operator<(const Gen_t_0019bca0_m12cd &left, const Gen_t_0019bca0_m12cd &right)
{
	return asciiCompare(left.m_first, right.m_first) < 0
		|| (!(asciiCompare(right.m_first, left.m_first) < 0)
			&& asciiCompare(left.m_second, right.m_second) < 0);
}

typedef _STL::_Rb_tree<Gen_t_0019bca0_m12cd, Gen_t_0019bca0_m12cd, _STL::_Identity<Gen_t_0019bca0_m12cd>,
	_STL::less<Gen_t_0019bca0_m12cd>, _STL::allocator<Gen_t_0019bca0_m12cd> > Rva0019BCA0Tree;

// retail 0x00199C80 (identical-code-folded with the tree above)
Bool BfmeTreeLowerBoundAnchor0019BCA0(const Rva0019BCA0Tree &tree, const Gen_t_0019bca0_m12cd &key)
{
	return tree.lower_bound(key) != tree.end();
}
