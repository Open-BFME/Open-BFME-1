// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// Open-BFME: two-pass list clear plus cookie-array teardown, retail 0x000FD0B0.
//
// A circular list of 0xC-byte nodes at this+0x10 is walked twice: first the
// owned pointer at +8 is destroyed, then each node is returned to the small
// allocator.  The sentinel is then reset to self-links and the cookie-prefixed
// 0xC-element array at this+8 is torn down with the EH vector destructor.
//
// The array elements are the real Coord3D (12 bytes, the 0xC stride the
// teardown passes to ??_M@YGXPAXIHP6EX0@Z@Z).  Retail hands the vector
// destructor the dtor at 0x0041364C, and that address is Coord3D::~Coord3D
// (functions.csv row ??1Coord3D@@QAE@XZ, RVA 0x0001364C, a one-byte `ret`
// defined in game/Libraries/Source/WWVegas/WWMath/coord3d.cpp), so the
// element reference must spell that class rather than a TU-local one.

#include "coord3d.h"

// Retail frees these arrays through operator delete[] (??_V@YAXPAX@Z,
// 0x00881EF0). Without the declaration cl falls back to scalar
// operator delete for the block, which is a different body at 0x00881EB0.
void __cdecl operator delete[](void *block);
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);

class BfmeOwnedPtr
{
public:
	virtual ~BfmeOwnedPtr(void);
};

struct BfmeListNode
{
	BfmeListNode *next;
	BfmeListNode *prev;
	BfmeOwnedPtr *value;
};

class BfmeListAndArray
{
	char m_prefix[8];
	Coord3D *m_array;
	int m_arrayTail;
	BfmeListNode *m_list;

public:
	void bfmeClear(void);
};

// ?bfmeClear@BfmeListAndArray@@QAEXXZ
void BfmeListAndArray::bfmeClear(void)
{
	BfmeListNode *sentinel = m_list;
	BfmeListNode *node = sentinel->next;

	while (node != sentinel)
	{
		delete node->value;
		node = node->next;
		sentinel = m_list;
	}

	sentinel = m_list;
	node = sentinel->next;
	while (node != sentinel)
	{
		BfmeListNode *current = node;
		node = node->next;
		bfmeDeallocate(current, sizeof(BfmeListNode));
		sentinel = m_list;
	}

	m_list->next = m_list;
	m_list->prev = m_list;

	if (m_array != 0)
	{
		delete[] m_array;
		m_array = 0;
		m_arrayTail = 0;
	}
}
