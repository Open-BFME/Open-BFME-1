// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AnimationSoundClientBehaviorModuleDataMember's destructor, retail 0x00605E60, 124 bytes. The
// body carried only a machine byte-dump row; targets/game/reverse/reloc_names.csv holds the
// name with identity=real.
//
// When the count at +0x04 says the tree holds something, the field at +0x04 of
// the header goes to the erase member and the header is then put back to
// pointing at itself with that field cleared -- the header re-read from the
// member before each store, since the erase could have moved it.
//
// Retail erase 0x00605820 follows right at +0x0c recursively and left at
// +0x08 iteratively, matching inputs/vendor/stlport/stl/_tree.c::_M_erase;
// _tree.h::clear independently identifies the parent/root and extremal links.
//
// The 0x70-byte header itself goes back to the pool afterwards, and that is a
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

class Rva00605E60TreeHeader
{
public:
	char m_bfmeHead[0x04];
	void *m_parent;					// +0x04
	Rva00605E60TreeHeader *m_left;				// +0x08
	Rva00605E60TreeHeader *m_right;				// +0x0C
	char m_bfmeTail[0x70 - 0x10];
};

class Rva00605180HeaderHandle
{
public:
	~Rva00605180HeaderHandle()
	{
		if (m_bfmeHeader)
			_STL::__node_alloc<true, 0>::_M_deallocate(m_bfmeHeader, 0x70);
	}

	Rva00605E60TreeHeader *m_bfmeHeader;				// +0x00
};

class AnimationSoundClientBehaviorModuleDataMember
{
public:
	~AnimationSoundClientBehaviorModuleDataMember();

private:
	void bfmeErase(void *root);				// ILT 0x000082D3

	Rva00605180HeaderHandle m_bfmeHandle;				// +0x00
	Int m_bfmeCount;					// +0x04
};

// ??1AnimationSoundClientBehaviorModuleDataMember@@QAE@XZ
AnimationSoundClientBehaviorModuleDataMember::~AnimationSoundClientBehaviorModuleDataMember()
{
	if (m_bfmeCount)
	{
		bfmeErase(m_bfmeHandle.m_bfmeHeader->m_parent);

		m_bfmeHandle.m_bfmeHeader->m_left = m_bfmeHandle.m_bfmeHeader;
		m_bfmeHandle.m_bfmeHeader->m_parent = 0;
		m_bfmeHandle.m_bfmeHeader->m_right = m_bfmeHandle.m_bfmeHeader;

		m_bfmeCount = 0;
	}
}
