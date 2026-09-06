// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: STLport _Rb_tree<Gen_t,Gen_t,_Identity<Gen_t>,less<Gen_t>>::
// _M_lower_bound, one 137-byte body shared (ICF) by two distinct value
// types (Gen_t_000934b0_m12cd and Gen_t_00093610_m12cd -- forward-declared
// only, with an opaque operator< in Code/gen_small/fam_008.cpp).  The
// comparator is opaque there, so MSVC cannot fold the walk the way retail
// did; a visible body for operator< recovers the identical shape (see the
// same family solved for a plain AsciiString key in
// RvaTreeBoundsAsciiString.cpp: repe cmpsb over the shorter side, break the
// tie on length, with the empty string modelled as a null Header pointer at
// 0x0107388B).  Each Gen_t here is a 12-byte value whose first four bytes
// are the AsciiString the comparison actually reads; the other eight bytes
// are never touched by this walk, so they exist only to make the node's
// value the right width for the two instantiations to fold into one body.

#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef int Int;
typedef bool Bool;

#include <string.h>

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

struct Gen_t_000934b0_m12cd
{
public:
	AsciiString m_key;
	int m_extra[2];
};

inline bool operator<(const Gen_t_000934b0_m12cd &a, const Gen_t_000934b0_m12cd &b)
{
	return a.m_key.compare(b.m_key) < 0;
}

typedef _STL::_Rb_tree<Gen_t_000934b0_m12cd, Gen_t_000934b0_m12cd,
	_STL::_Identity<Gen_t_000934b0_m12cd>, _STL::less<Gen_t_000934b0_m12cd>,
	_STL::allocator<Gen_t_000934b0_m12cd> > Rva000934b0Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor000934b0( const Rva000934b0Tree &tree, const Gen_t_000934b0_m12cd &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Gen_t_00093610_m12cd
{
public:
	AsciiString m_key;
	int m_extra[2];
};

inline bool operator<(const Gen_t_00093610_m12cd &a, const Gen_t_00093610_m12cd &b)
{
	return a.m_key.compare(b.m_key) < 0;
}

typedef _STL::_Rb_tree<Gen_t_00093610_m12cd, Gen_t_00093610_m12cd,
	_STL::_Identity<Gen_t_00093610_m12cd>, _STL::less<Gen_t_00093610_m12cd>,
	_STL::allocator<Gen_t_00093610_m12cd> > Rva00093610Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor00093610( const Rva00093610Tree &tree, const Gen_t_00093610_m12cd &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}
