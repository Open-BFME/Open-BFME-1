// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport _Rb_tree<...>::_M_lower_bound at 0x00605550, a
// case-insensitive AsciiString-keyed tree. It calls _memicmp through the CRT
// import at VA 0x01359310 (reverse/imports.csv: 0x01359310,MSVCR71.dll,
// _memicmp,434) rather than inlining a memcmp intrinsic, which is what makes
// it longer than the case-sensitive siblings in RvaTreeBoundsAsciiString.cpp
// (166B here vs 145B there) despite the identical descent shape. The
// comparator is spelled out exactly as RvaTreeInsertUniqueNoCase.cpp already
// established for the insert_unique siblings at this address range:
// StringBase<char>::compareNoCase loads the CRT import into a register once
// (retail keeps it live across the whole loop) and calls it once per node
// visited.
//
// This body additionally tie-breaks on a trailing float member when the two
// strings compare equal (fld/fcomp/fnstsw ax; test ah,5) -- a
// set<{AsciiString,int,float}> ordered primarily by name, secondarily by the
// float. Node layout is STLport's: colour/parent/left/right then the value at
// +0x10. The comparator needs three separate early-return branches (c<0,
// c>0, then the float) rather than `return c ? c < 0 : floatCompare` --
// collapsing them materializes a `setl`/bool that retail's fully inlined
// three-way branch does not have.

#define _STLP_NO_EXCEPTIONS 1
#include <set>

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *buf1, const void *buf2, unsigned int count);

extern const char g_bfmeEmptyAscii[];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	int compareNoCase(const AsciiString &str) const
	{
		const int len = str.m_data ? str.m_data->length : 0;
		const char *data = str.m_data ? &str.m_data->data[0] : g_bfmeEmptyAscii;
		const int myLen = m_data ? m_data->length : 0;
		const char *myData = m_data ? &m_data->data[0] : g_bfmeEmptyAscii;
		int result = _memicmp(myData, data, myLen < len ? myLen : len);
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

// ---- 0x00605550: AsciiString primary key, float secondary tiebreak. -------

struct Rva00605800Value
{
	AsciiString m_key;
	int m_pad;
	float m_weight;
};

struct Rva00605800Less
{
	bool operator()( const Rva00605800Value &left, const Rva00605800Value &right ) const
	{
		int c = left.m_key.compareNoCase( right.m_key );
		if ( c < 0 )
			return true;
		if ( c > 0 )
			return false;
		return left.m_weight < right.m_weight;
	}
};

typedef _STL::_Rb_tree<Rva00605800Value, Rva00605800Value, _STL::_Identity<Rva00605800Value>,
	Rva00605800Less, _STL::allocator<Rva00605800Value> > Rva00605800Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor00605800( const Rva00605800Tree &tree, const Rva00605800Value &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}
