// ?refresh@Rva000F72D0FrameCachedValue@@AAEXM@Z
// partial score=0.4 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc
// Prior 0.5(submitted 0.2) stash never defined refresh() (probe: NOT IN OBJECT).
// This is a real, compiling reconstruction of the full algorithm from
// tools/dis_retail.py 0x000F67B0 403: ours=319B vs retail=403B, structurally
// close (tail free logic matches operation-for-operation) but not byte-exact.
// Newly resolved vs the prior stash's notes:
//  - bfmeEstimateXQ(&outBuf) writes a 12B Coord3D-shaped estimate at the top
//    of the frame; its address becomes bfmeForwardWideC's FIRST arg.
//  - Confirmed bfmeForwardWideC call has a HIDDEN SRET pointer (6 pushes
//    total for a 5-"H" mangled signature), sret slot reused post-call as the
//    tail's "result" pointer. Args (declaration order a..e) = (&estimate,
//    range, 0, filterChain, 0); filterChain = fc.link(fb.link(&fa)) i.e.
//    B links to A FIRST, then C links to B (chain head is C, walks C->B->A).
//  - Filter B (vtable 0x1083B80) is 8B (vptr+next only, no data field) --
//    still an unconfirmed class name. Filter C (vtable 0x1085DC0) is 12B
//    like A, same data pointer (this+0xc). Neither B nor C has a confirmed
//    real name yet.
//  - The sret result is a refcounted, node_alloc-backed buffer: layout
//    {begin,end,endOfStorage,cursor,refCount}, elements are 8B {Overridable*
//    node, unused}. cursor==end means empty (value stays 0.0f). Otherwise
//    node is read and cursor advanced+stored back (state persists on the
//    result object, so possibly a round-robin/shared cache, not confirmed).
//  - Override-chain read: if node->m_nextOverride==0, the fallback reads
//    *(float*)(0x3fc) through a NULL base (verified byte-for-byte in the
//    dump; semantic reason unresolved). Otherwise, if that override's own
//    m_nextOverride is non-null, call getFinalOverride() (thunk 0x22BB) and
//    read ITS +0x3fc field; else read the override's own +0x3fc directly.
//  - Tail: this->m_value=newValue, this->m_frame=TheBfmeGameLogic->m_frame+
//    0x19 (25 frames), then --result->m_refCount; on reaching 0, free the
//    buffer (node_alloc _M_deallocate if size<=0x80 else operator delete)
//    then operator delete the result object itself. Confirmed operation-
//    for-operation against retail's tail bytes (same call order, same 0x80
//    threshold, same and/shift masking intent).
// STILL UNRESOLVED: exact frame/local layout (ours=0x2c vs retail=0x38
// locals, so some local is missing/misplaced), B/C real class names, the
// null+0x3fc fallback's true meaning, and whether cursor state genuinely
// persists across calls or bfmeForwardWideC always returns a fresh buffer.

struct Coord3D
{
	float x, y, z;
};

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};

struct WideResultEntry
{
	Overridable *node;
	unsigned int unused;
};

class WideResultHandle
{
public:
	WideResultEntry *m_begin;
	WideResultEntry *m_end;
	WideResultEntry *m_endOfStorage;
	WideResultEntry *m_cursor;
	unsigned int m_refCount;
};

class PartitionFilter
{
public:
	PartitionFilter *link(PartitionFilter *next)
	{
		m_next = next;
		return this;
	}

	unsigned int m_vptr;
	PartitionFilter *m_next;
};

class PartitionFilterB : public PartitionFilter
{
public:
	PartitionFilterB()
	{
		m_next = 0;
		m_vptr = 0x1083B80;
	}
	~PartitionFilterB()
	{
		m_vptr = 0x1083B5C;
	}
};

class PartitionFilterA : public PartitionFilter
{
public:
	PartitionFilterA(void *object)
	{
		m_next = 0;
		m_vptr = 0x1085DD0;
		m_data = object;
	}
	~PartitionFilterA()
	{
		m_vptr = 0x1083B5C;
	}
	void *m_data;
};

class PartitionFilterC : public PartitionFilter
{
public:
	PartitionFilterC(void *object)
	{
		m_next = 0;
		m_vptr = 0x1085DC0;
		m_data = object;
	}
	~PartitionFilterC()
	{
		m_vptr = 0x1083B5C;
	}
	void *m_data;
};

class PartitionManager
{
public:
	WideResultHandle *bfmeForwardWideC(const Coord3D *pos, float range, int c, PartitionFilter *filters, int e);
};

extern PartitionManager *ThePartitionManager;

class GameLogicFrameSlice
{
public:
	unsigned char m_unmodelled_000[0x3c];
	unsigned int m_frame;
};

extern GameLogicFrameSlice *TheBfmeGameLogic;

extern "C" void __cdecl operator_delete_marker(); // unused, keeps grep-friendly

class Rva000F72D0FrameCachedValue
{
public:
	float value(float range);

private:
	void refresh(float range);
	void bfmeEstimateXQ(Coord3D *outPos) const;

	unsigned char m_unmodelled_000[0xc];
	void *m_object;
	unsigned char m_unmodelled_010[0xe4];
	float m_value;
	unsigned int m_frame;
};

namespace _STL
{
template <bool __threads, int __inst>
class __node_alloc
{
public:
	static void _M_deallocate(void *p, unsigned int n);
};
}

void Rva000F72D0FrameCachedValue::refresh(float range)
{
	Coord3D estimate;
	bfmeEstimateXQ(&estimate);

	void *object = m_object;
	if (object == 0)
		return;

	PartitionFilterB fb;
	PartitionFilterA fa(object);
	PartitionFilterC fc(object);

	WideResultHandle *result = ThePartitionManager->bfmeForwardWideC(
		&estimate, range, 0, fc.link(fb.link(&fa)), 0);

	float newValue = 0.0f;
	if (result->m_cursor != result->m_end)
	{
		Overridable *node = result->m_cursor->node;
		result->m_cursor++;
		if (node != 0)
		{
			Overridable *override_ = node->m_nextOverride;
			if (override_ != 0)
			{
				const Overridable *final_ = (override_->m_nextOverride != 0) ? override_->getFinalOverride() : override_;
				newValue = 0.0f + *(float *)((char *)final_ + 0x3fc);
			}
			else
			{
				newValue = 0.0f + *(float *)((char *)0 + 0x3fc);
			}
		}
	}

	m_value = newValue;
	m_frame = TheBfmeGameLogic->m_frame + 0x19;

	if (--result->m_refCount == 0)
	{
		void *begin = result->m_begin;
		if (begin != 0)
		{
			unsigned int size = (unsigned int)((char *)result->m_endOfStorage - (char *)begin);
			size = (size >> 3) << 3;
			if (size > 0x80)
				::operator delete(begin);
			else
				_STL::__node_alloc<true, 0>::_M_deallocate(begin, size);
		}
		::operator delete(result);
	}
}
