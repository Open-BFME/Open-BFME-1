// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: TunnelTracker::getContainCount, retail 0x000F8810, 67 bytes. The
// body carried only a machine byte-dump row; the name comes from the ILT pin
// in reverse/symbols.csv.
//
// The mangled name says the argument is an Int, and the ledger's note on that
// pin records why: BFME gives the function an argument the reference build does
// not have, and CaveSystem::canSwitchIndexToIndex passes zero at both of its
// call sites. Zero is the fast path here -- the cached count at +0x10 goes
// straight back. Anything else is a filter, which the body immediately uses as
// a this pointer, so the source has to cast the Int back.
//
// The list of contained objects hangs off the sentinel pointer at +8, the same
// shape the id list at +4 has in onTunnelCreated: twelve-byte nodes with next
// at +0 and the value at +8. end() is re-read from the member on every trip
// because the filter call could have moved it.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Object;
class Player;

class Rva2225E0Filter
{
public:
	Bool accepts(Object *object, Player *player);	// retail 0x003A04A0
};

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;			// +0x00
	BfmeListNodeBase *m_bfmePrev;			// +0x04
};

struct BfmeObjectNode : public BfmeListNodeBase
{
	Object *m_bfmeValue;				// +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TunnelTracker.h
class TunnelTracker
{
public:
	UnsignedInt getContainCount(Int filterArg);

private:
	unsigned char m_bfmeHead[0x08 - 0x00];
	BfmeListNodeBase *m_bfmeContainList;		// +0x08, the list's sentinel
	unsigned char m_bfmeGap[0x10 - 0x0C];
	UnsignedInt m_bfmeContainCount;			// +0x10
};

// ?getContainCount@TunnelTracker@@QAEIH@Z
UnsignedInt TunnelTracker::getContainCount(Int filterArg)
{
	Rva2225E0Filter *filter = (Rva2225E0Filter *)filterArg;

	if (!filter)
		return m_bfmeContainCount;

	UnsignedInt count = 0;

	for (BfmeListNodeBase *it = m_bfmeContainList->m_bfmeNext;
			it != m_bfmeContainList;
			it = it->m_bfmeNext)
	{
		if (filter->accepts(((BfmeObjectNode *)it)->m_bfmeValue, 0))
			++count;
	}

	return count;
}
