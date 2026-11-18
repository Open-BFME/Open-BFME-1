// cl: /O2 /Ob2 /DNDEBUG /MD

// The carved 32-byte body walks the circular list rooted at this+0x24 and
// returns whether the list contains at least one node. No caller or type table
// proves a semantic owner name, so the class and method keep the retail address.
//
// Retail counts the nodes into an unsigned counter and returns `0 < count`,
// which MSVC 7.1 materialises with xor/cmp/sbb/neg.

#include "../../Include/Common/ScalarTypes.h"

class Rva00256AB0Node
{
public:
	Rva00256AB0Node *m_next;
};

class Rva00256AB0Owner
{
public:
	Int hasEntries(void) const;

private:
	unsigned char m_beforeList[0x24];
	Rva00256AB0Node *m_list;
};

// ?hasEntries@Rva00256AB0Owner@@QBEHXZ
Int Rva00256AB0Owner::hasEntries(void) const
{
	Rva00256AB0Node *list = m_list;
	unsigned int count = 0;
	for (Rva00256AB0Node *node = list->m_next; node != list; node = node->m_next)
		++count;
	return 0 < count;
}
