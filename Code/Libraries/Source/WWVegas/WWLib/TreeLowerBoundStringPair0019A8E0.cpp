// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	int compare(const AsciiString &str) const
	{
		const int len = str.m_data ? str.m_data->length : 0;
		const char *data = str.m_data ? &str.m_data->data[0] : "";
		const int myLen = m_data ? m_data->length : 0;
		const char *myData = m_data ? &m_data->data[0] : "";
		int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result == 0) {
			result = myLen - len;
		}
		return result;
	}

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

// Gen_t_0019a8e0_m12cd / Gen_t_0019bca0_m12cd from Code/gen_small/fam_009.cpp:
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
	return left.m_first.compare(right.m_first) < 0
		|| (!(right.m_first.compare(left.m_first) < 0)
			&& left.m_second.compare(right.m_second) < 0);
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
	return left.m_first.compare(right.m_first) < 0
		|| (!(right.m_first.compare(left.m_first) < 0)
			&& left.m_second.compare(right.m_second) < 0);
}

typedef _STL::_Rb_tree<Gen_t_0019bca0_m12cd, Gen_t_0019bca0_m12cd, _STL::_Identity<Gen_t_0019bca0_m12cd>,
	_STL::less<Gen_t_0019bca0_m12cd>, _STL::allocator<Gen_t_0019bca0_m12cd> > Rva0019BCA0Tree;

// retail 0x00199C80 (identical-code-folded with the tree above)
Bool BfmeTreeLowerBoundAnchor0019BCA0(const Rva0019BCA0Tree &tree, const Gen_t_0019bca0_m12cd &key)
{
	return tree.lower_bound(key) != tree.end();
}
