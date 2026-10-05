// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// readable body of ?reset@BuildAssistant@@UAEXXZ: game/GameEngine/Source/Common/System/BuildAssistant.cpp
//
// BuildAssistant::reset, retail 0x000FD0B0 (134 bytes): SubsystemInterface
// slot 4 of BuildAssistant's table 0x010860D8 (see
// targets/game/reverse/identity_evidence/000fbe80-000fd0b0-buildassistant-init-reset.md).
//
// Zero Hour's reset on BuildAssistant's layout: the sell list at this+0x10 is
// walked twice, first destroying each ObjectSellInfo, then returning each node
// to the small allocator (m_sellList.clear()); the sentinel is reset to
// self-links. BFME then also frees the cookie-prefixed Coord3D array
// m_buildPositions (this+0x08) with the EH vector destructor and zeroes
// m_buildPositionSize (this+0x0C).
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

// The sell-list element; its table 0x010860C0 is the one sellObject installs.
class ObjectSellInfo
{
public:
	virtual ~ObjectSellInfo(void);
};

struct ObjectSellListNode
{
	ObjectSellListNode *next;
	ObjectSellListNode *prev;
	ObjectSellInfo *value;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BuildAssistant.h
class BuildAssistant
{
public:
	virtual void reset(void);

private:
	unsigned char m_unreconstructed_04[0x08 - 0x04];
	Coord3D *m_buildPositions;							///< retail this+0x08
	int m_buildPositionSize;							///< retail this+0x0C
	ObjectSellListNode *m_sellList;						///< retail this+0x10 (list sentinel)
};

// ?reset@BuildAssistant@@UAEXXZ
void BuildAssistant::reset(void)
{
	ObjectSellListNode *sentinel = m_sellList;
	ObjectSellListNode *node = sentinel->next;

	while (node != sentinel)
	{
		delete node->value;
		node = node->next;
		sentinel = m_sellList;
	}

	sentinel = m_sellList;
	node = sentinel->next;
	while (node != sentinel)
	{
		ObjectSellListNode *current = node;
		node = node->next;
		bfmeDeallocate(current, sizeof(ObjectSellListNode));
		sentinel = m_sellList;
	}

	m_sellList->next = m_sellList;
	m_sellList->prev = m_sellList;

	if (m_buildPositions != 0)
	{
		delete[] m_buildPositions;
		m_buildPositions = 0;
		m_buildPositionSize = 0;
	}
}
