// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport map::operator[] body at retail 0x004B1B90, 183 bytes; its only
// caller is the dump at 0x004B1C80 through ILT 0x00432722.
//
// It inserts through the same tree insert_unique (ILT 0x0002FDDD, body
// 0x004B1370) as the hinted map::insert at 0x004B1880, so it is a member of
// that same map and keeps the address-derived key and mapped type names from
// Rva004B1880MapInsertBody.cpp. This body adds what the insert could not see:
// the key compares unsigned (jb/jae on the node's +0x10 key), the mapped value
// is one dword default-constructed to zero, and its unwind funclets release it
// through 0x004AFF40, which drops the count at +4 of the pointee and calls the
// deleting destructor at slot 0 once it reaches zero.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>

class Rva004B1880Counted
{
public:
	virtual ~Rva004B1880Counted();
	int m_refCount;
};

struct Rva004B1880Key
{
	unsigned int m_value;

	bool operator<(const Rva004B1880Key &other) const
	{
		return m_value < other.m_value;
	}
};

struct Rva004B1880Value
{
	Rva004B1880Value() { m_counted = 0; }
	Rva004B1880Value(const Rva004B1880Value &other)
		: m_counted(other.m_counted)
	{
	}
	~Rva004B1880Value()
	{
		if (m_counted != 0 && --m_counted->m_refCount <= 0)
			delete m_counted;
	}
	Rva004B1880Counted *m_counted;
};

typedef _STL::map<Rva004B1880Key, Rva004B1880Value> Rva004B1880Map;

// ??A?$map@URva004B1880Key@@URva004B1880Value@@U?$less@URva004B1880Key@@@_STL@@V?$allocator@U?$pair@$$CBURva004B1880Key@@URva004B1880Value@@@_STL@@@4@@_STL@@QAEAAURva004B1880Value@@ABURva004B1880Key@@@Z
template Rva004B1880Value &Rva004B1880Map::operator[](
	const Rva004B1880Key &key);
