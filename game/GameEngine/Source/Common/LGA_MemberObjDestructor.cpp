// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LGA_MemberObj's destructor, retail 0x003D4490, 129 bytes. The
// body carried only a machine byte-dump row; the symbols.csv pin names it, and
// the cdecl cleanup it starts with is pinned with this row.
//
// Two things happen. The destructor body hands this to that cleanup, and then
// the member vector at +0x00 is released -- its destructor inlined, with the
// STLport allocator inlined inside that. The unwind slot says as much: it
// stands at 0 across the cleanup call, when the member is still alive, and
// drops to -1 for the release.
//
// The release is the node allocator's own rule: the byte count is recovered by
// dividing the pointer range by the element size and multiplying back, and a
// block over 128 bytes goes to operator delete while anything smaller goes back
// to the pool. Four-byte elements are what make that divide and multiply a
// matched pair of shifts.

namespace _STL
{

template <bool __threads, int __inst> class __node_alloc
{
public:
	static void _M_deallocate(void *block, unsigned int bytes);
};

}

class LGA_MemberObj;

void bfmeClearMembers(LGA_MemberObj *self);			// ILT 0x00034DC9

class BfmeMemberVector
{
public:
	~BfmeMemberVector()
	{
		if (m_bfmeStart)
		{
			unsigned int bytes = (m_bfmeEndOfStorage - m_bfmeStart)
					* sizeof(void *);

			if (bytes > 128)
				::operator delete(m_bfmeStart);
			else
				_STL::__node_alloc<true, 0>::_M_deallocate(
						m_bfmeStart, bytes);
		}
	}

	void **m_bfmeStart;					// +0x00
	void **m_bfmeFinish;					// +0x04
	void **m_bfmeEndOfStorage;				// +0x08
};

class LGA_MemberObj
{
public:
	~LGA_MemberObj();

private:
	BfmeMemberVector m_bfmeMembers;				// +0x00
};

// ??1LGA_MemberObj@@QAE@XZ
LGA_MemberObj::~LGA_MemberObj()
{
	bfmeClearMembers(this);
}
