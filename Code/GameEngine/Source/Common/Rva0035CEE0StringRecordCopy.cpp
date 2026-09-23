// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: Rva0035CEE0(Rva00359330Record *, const Rva00359330Record *) --
// retail 0x0035CEE0, 605 bytes including its catch(...) block (0x0035D0AC)
// and the inlined deque destructor tail (0x0035D0C1). The carved row stops
// at the loop back-edge (460 bytes).
//
// Copies one 20-byte string record: the two leading dwords, the AsciiString
// name through StringBase<char>::set (0x00887C90), the released byte, the
// reference word, then the +0x10 node chain. The chain is walked into a
// local stack<node *> and rebuilt by pushing copies on the front, so the
// copy keeps the source order. A throw while rebuilding drains what was
// built with clearRva00359330Nodes (ILT 0x0001612B) and rethrows.
//
// Record layout and names: Rva00359330StringRecordClearNodes.cpp and
// Rva00359330StringRecordAddDefaultNode.cpp (same +0x10 chain, same
// 0x010E855C node). The node value copy is the Rva003529B0(const
// Rva003529B0 *) body (0x003529B0) inlined behind a zeroed link. Only caller
// is 0x0035E030 through ILT 0x0001CADF, which is unnamed, so the function
// name stays address-derived.

#include "ascii_string.h"

class Rva00354BC0;

struct Rva00359330Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	Rva00354BC0 *m_nodes;
};

void clearRva00359330Nodes(Rva00359330Record *record);

class Rva003525E0Pair
{
public:
	Rva003525E0Pair(Rva003525E0Pair const &other);

private:
	void *m_a;
	void *m_b;
};

class Rva003529B0
{
public:
	Rva003529B0(const Rva003529B0 *other)
		: m_pair(*(other ? &other->m_pair : 0))
	{
		m_vptr = (void *)0x010E855C;
		m_10 = other->m_10;
		m_11 = other->m_11;
		m_12 = 0;
	}

private:
	void *m_vptr;
	Rva003525E0Pair m_pair;
	char m_10;
	char m_11;
	char m_12;
};

class Rva00354BC0
{
public:
	Rva00354BC0(const Rva00354BC0 *other)
		: m_link(0), m_value(&other->m_value)
	{
	}

	Rva00354BC0 *m_link;

private:
	Rva003529B0 m_value;
};

#define _STLP_NO_EXCEPTIONS 1
#include <stack>

void Rva0035CEE0(Rva00359330Record *dest, const Rva00359330Record *src)
{
	dest->m_previous = src->m_previous;
	dest->m_next = src->m_next;
	dest->m_name = src->m_name;
	dest->m_released = src->m_released;
	dest->m_references = src->m_references;
	dest->m_nodes = 0;

	_STL::stack<Rva00354BC0 *> pending;
	for (Rva00354BC0 *node = src->m_nodes; node; node = node->m_link)
	{
		pending.push(node);
	}
	try
	{
		while (!pending.empty())
		{
			Rva00354BC0 *copy = new Rva00354BC0(pending.top());
			pending.pop();
			copy->m_link = dest->m_nodes;
			dest->m_nodes = copy;
		}
	}
	catch (...)
	{
		clearRva00359330Nodes(dest);
		throw;
	}
}
