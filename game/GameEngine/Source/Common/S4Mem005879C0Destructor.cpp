// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: S4Mem005879C0's destructor, retail 0x005879C0, 124 bytes. The
// body carried only a machine byte-dump row; targets/game/reverse/reloc_names.csv holds the
// name with identity=real.
//
// When the count at +0x04 says the list holds something, the field at +0x04 of
// the header goes to the erase member and the header is then put back to
// pointing at itself with that field cleared -- the header re-read from the
// member before each store, since the erase could have moved it.
//
// The 0x50-byte header itself goes back to the pool afterwards, and that is a
// member's destructor rather than part of this body: the unwind slot stands at
// 0 across the clearing and drops to -1 for the release, which is what a
// destructible member gives.

typedef int Int;

namespace _STL
{

template <bool __threads, int __inst> class __node_alloc
{
public:
	static void _M_deallocate(void *block, unsigned int bytes);
};

}

class BfmeListHeader
{
public:
	char m_bfmeHead[0x04];
	void *m_bfmeFirst;					// +0x04
	BfmeListHeader *m_bfmeNext;				// +0x08
	BfmeListHeader *m_bfmePrev;				// +0x0C
	char m_bfmeTail[0x50 - 0x10];
};

class BfmeHeaderHandle
{
public:
	~BfmeHeaderHandle()
	{
		if (m_bfmeHeader)
			_STL::__node_alloc<true, 0>::_M_deallocate(m_bfmeHeader, 0x50);
	}

	BfmeListHeader *m_bfmeHeader;				// +0x00
};

class S4Mem005879C0
{
public:
	~S4Mem005879C0();

private:
	void bfmeErase(void *first);				// ILT 0x00037353

	BfmeHeaderHandle m_bfmeHandle;				// +0x00
	Int m_bfmeCount;					// +0x04
};

// ??1S4Mem005879C0@@QAE@XZ
S4Mem005879C0::~S4Mem005879C0()
{
	if (m_bfmeCount)
	{
		bfmeErase(m_bfmeHandle.m_bfmeHeader->m_bfmeFirst);

		m_bfmeHandle.m_bfmeHeader->m_bfmeNext = m_bfmeHandle.m_bfmeHeader;
		m_bfmeHandle.m_bfmeHeader->m_bfmeFirst = 0;
		m_bfmeHandle.m_bfmeHeader->m_bfmePrev = m_bfmeHandle.m_bfmeHeader;

		m_bfmeCount = 0;
	}
}
