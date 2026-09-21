// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

extern void j_0002e596(void);

// address-derived stand-in for the 4-byte mapped payload the tree at +0x1b8
// stores per key (Rva005C7490Value in RvaTreeInsertUniquePlain.cpp, same
// retail insert_unique at 0x005C8B10 reached here through its own ILT
// thunk); identity of the payload itself is unproven.
struct Rva006ACE90Value
{
	void *m_raw;
};

struct Rva006ACE90Pair
{
	AsciiString m_key;
	Rva006ACE90Value m_value;

	Rva006ACE90Pair(const AsciiString &name, void *payload) : m_key(name)
	{
		m_value.m_raw = payload;
	}
};

struct Rva006ACE90InsertResult
{
	void *m_iterator;
	int m_inserted;
};

// address-derived stand-in for the AsciiString-keyed STL map living at
// this+0x1b8; the member-pointer cast reaches insert_unique's own ILT
// thunk (0x0002E596 -> retail 0x005C8B10) the same way retail calls it.
class Rva006ACE90Tree
{
public:
	void insertUnique(Rva006ACE90InsertResult *result, const Rva006ACE90Pair *value)
	{
		typedef void (Rva006ACE90Tree::*InsertUniqueFn)(Rva006ACE90InsertResult *, const Rva006ACE90Pair *);
		union
		{
			void (*freeFn)(void);
			InsertUniqueFn memberFn;
		} thunk;
		thunk.freeFn = j_0002e596;
		(this->*thunk.memberFn)(result, value);
	}
};

class Rva006ACE90Owner
{
public:
	void addNamedRoom(const AsciiString &name, void *payload);

private:
	char m_pad00[0x1b8];
	Rva006ACE90Tree m_tree;
};

// Retail 0x006ACE90 (113B): copy-construct an AsciiString key from a
// caller-owned name, pair it with a raw 4-byte payload taken by value, and
// insert into the tree at this+0x1b8. No caller or owning class identity
// survived the identity sweep (blocked once: "by-value GameSpy room
// operation has unresolved owning method identity", t=5m model=gpt-5.6);
// every name here is address-derived.
void Rva006ACE90Owner::addNamedRoom(const AsciiString &name, void *payload)
{
	Rva006ACE90Pair pair(name, payload);

	Rva006ACE90InsertResult result;
	m_tree.insertUnique(&result, &pair);
}
