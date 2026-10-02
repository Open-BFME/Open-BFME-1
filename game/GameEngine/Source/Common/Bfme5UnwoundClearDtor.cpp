// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GR- /EHsc- /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Include/Precompiled /Igame/GameEngine/Source/Common/System /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// A destructor that deletes what its vector holds, empties it and then lets
// the vector member go away.
//
// The base whose destructor it chains to at the end is SubsystemInterface: the
// body at 0x009A1A40 is ??1SubsystemInterface@@UAE@XZ.  Its vptr + m_name make
// it eight bytes, so the vector member stays at +0x08.
//
// The unwind state word tells the parts apart: it holds 1 while the body runs
// -- the delete walk and the clear -- drops to 0 for the member's own
// destructor, which is the release of the block by size, and returns to -1
// before the base destructor. The most-derived vftable goes in at the entry
// because the base is polymorphic.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h

#include "PreRTS.h"

#include "subsystem_interface.h"
#include <stl/_alloc.h>

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

static inline void bfmeRelease(void *block, unsigned int bytes)
{
	_STL::__node_alloc<true, 0>::deallocate(block, bytes);
}

class BfmeOwnedAA
{
public:
	virtual ~BfmeOwnedAA(void);				// slot +0x00
};

inline BfmeOwnedAA **bfmeCopyOwned(BfmeOwnedAA **destination, BfmeOwnedAA **first, BfmeOwnedAA **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeOwnedAA **)((char *)memmove(destination, first, bytes) + bytes);
}

class BfmeVecAA
{
public:
	~BfmeVecAA(void)
	{
		BfmeOwnedAA **start = m_bfmeStart;

		if (start)
			bfmeRelease(start, sizeof(BfmeOwnedAA *) * (m_bfmeEnd - start));
	}

	void bfmeErase(BfmeOwnedAA **first, BfmeOwnedAA **last)
	{
		m_bfmeFinish = bfmeCopyOwned(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	BfmeOwnedAA **m_bfmeStart;				// +0x00
	BfmeOwnedAA **m_bfmeFinish;				// +0x04
	BfmeOwnedAA **m_bfmeEnd;				// +0x08
};

class Gen_0039C6D0 : public SubsystemInterface
{
public:
	virtual ~Gen_0039C6D0(void);

private:
	BfmeVecAA m_bfmeVector;					// +0x08
};

// ??1Gen_0039C6D0@@UAE@XZ
Gen_0039C6D0::~Gen_0039C6D0(void)
{
	BfmeOwnedAA **it = m_bfmeVector.m_bfmeStart;
	BfmeOwnedAA **last = m_bfmeVector.m_bfmeFinish;

	while (it != last)
	{
		delete *it;

		last = m_bfmeVector.m_bfmeFinish;

		++it;
	}

	m_bfmeVector.bfmeClear();
}
