// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport map::operator[] at 0x00406C50. The body carried only a
// machine byte-dump row. Inlined lower_bound walks node+0x10 as a 4-byte
// unsigned key; a miss value-initialises a 32-byte mapped POD and hinted-inserts
// through the same insert_unique ILT (0x00018D7C) as the landed map insert at
// 0x00406AE0. Types are scoped to this body: the old insert wrapper guessed4B. The32-byte
// mapped size is from this body's frame and rep movsd, not from the insert.

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>

struct Rva00406C50Key
{
	unsigned int m_v;
};

struct Rva00406C50Value
{
	unsigned int m_data[8];
};

namespace _STL
{
template <>
struct less<Rva00406C50Key>
{
	bool operator()(const Rva00406C50Key &a, const Rva00406C50Key &b) const
	{
		return a.m_v < b.m_v;
	}
};
}

typedef _STL::map<Rva00406C50Key, Rva00406C50Value, _STL::less<Rva00406C50Key>,
	_STL::allocator<_STL::pair<const Rva00406C50Key, Rva00406C50Value> > >
	Rva00406AE0Map;

template Rva00406C50Value &Rva00406AE0Map::operator[](const Rva00406C50Key &key);
