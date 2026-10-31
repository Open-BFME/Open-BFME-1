// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Retail 0x00340980 (149 bytes, ret 4): a stdcall walk over the hash map at
// TheFXListStore+8 (dir32-recorded global 0x012F144C) that hands each
// entry's AsciiString name (+0xC inside the mapped value) to virtual slot 0 of
// its one argument.  The begin() it calls is retail 0x0033CD30 via ILT
// 0x000068B1; the map hashes its key by identity.  STLport's iterator
// increment, including _M_skip_to_next, is inlined (/Ob2), each step copies the
// iterator into a const_iterator, and the walk only schedules like retail with
// the begin() body visible.  Caller, owner and value type names are unproven,
// so they stay address-derived.

#define _STLP_NO_EXCEPTIONS 1
#define private public
#include <hash_map>
#undef private
#include "ascii_string.h"

namespace rts
{
	template <class T> struct hash { size_t operator()(T value) const { return (size_t)value; } };
	template <class T> struct equal_to { bool operator()(T a, T b) const { return a == b; } };
}

struct Rva00340980Value
{
	unsigned char m_head[0xC];
	AsciiString m_name;
};

typedef _STL::hash_map<unsigned int, Rva00340980Value, rts::hash<unsigned int>,
	rts::equal_to<unsigned int> > Rva00340980Map;

// Retail 0x0033CD30: the map's out-of-line STLport hashtable::begin().
class Rva0033CD30Table : public Rva00340980Map::_Ht
{
public:
	Rva00340980Map::iterator begin()
	{
		for (size_t n = 0; n < _M_buckets.size(); ++n)
			if (_M_buckets[n])
				return Rva00340980Map::iterator((Rva00340980Map::_Ht::_Node *)_M_buckets[n], this);
		return end();
	}
};

// hash_map::begin()/end() forward to the table inline.
struct Rva0033CD30Map
{
	Rva00340980Map::iterator begin() { return m_table.begin(); }
	Rva00340980Map::iterator end() { return m_table.end(); }

	Rva0033CD30Table m_table;
};

class FXListStore
{
public:
	unsigned char m_head[8];
	Rva0033CD30Map m_fxmap;
};

extern FXListStore *TheFXListStore;

class Rva00340980Sink
{
public:
	virtual void visit(const char *name);
};

void __stdcall rva00340980VisitFXListNames(Rva00340980Sink *sink)
{
	Rva00340980Map::iterator it = TheFXListStore->m_fxmap.begin();
	while (it != TheFXListStore->m_fxmap.end())
	{
		Rva00340980Map::const_iterator entry = it;
		sink->visit(entry->second.m_name.str());
		++it;
	}
}
