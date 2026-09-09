// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Raw-ABI reconstruction of the 0x006A43D0 table growth member.  The linked
// sibling insertion body allocates an eight-byte node: next at +0 and one
// pointer-valued payload at +4.  A non-null payload exposes its bucket key at
// payload +0x08.  That layout rules out the generated pair/three-int label;
// this TU keeps the owner address-derived and states only the observed key
// access and resize ABI.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

struct Rva006A43D0Payload
{
	char m_prefix[8];
	unsigned int m_bucketKey;
};

struct Rva006A43D0ExtractKey
{
	unsigned int operator()(Rva006A43D0Payload *value) const
	{
		return value == 0 ? 0 : value->m_bucketKey;
	}
};

typedef Rva006A43D0Payload *Rva006A43D0Value;
typedef _STL::hashtable<Rva006A43D0Value, unsigned int,
	_STL::hash<unsigned int>, Rva006A43D0ExtractKey,
	_STL::equal_to<unsigned int>, _STL::allocator<Rva006A43D0Value> >
	Rva006A43D0Table;

// The visible call emits only the concrete resize member.
void Rva006A43D0ResizeAnchor(Rva006A43D0Table &table, unsigned int count)
{
	table.resize(count);
}
