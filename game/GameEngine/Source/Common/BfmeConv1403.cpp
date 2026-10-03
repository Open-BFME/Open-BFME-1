// Open-BFME5 conversions.

extern "C" void *memcpy(void *d, const void *s, unsigned n);
#pragma intrinsic(memcpy)

struct BfmeHdrVKJ
{
	unsigned short m_bfme00;
	unsigned short m_bfme02;
};

struct BfmeAllocVKJ
{
	void *(__cdecl *m_bfmeAlloc)(unsigned n);
	void (__cdecl *m_bfmeFree)(void *p);
};

// The pointer at VA 0x01337A30 has one canonical global; this TU keeps its own
// view type of the two-slot {alloc, free} table and casts at the use.
struct BfmeStringPool3AF0;

extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

static __forceinline BfmeAllocVKJ *localPool()
{
	return (BfmeAllocVKJ *)g_rva01337A30AllocPair;
}

class BfmeStrVKJ
{
public:
	BfmeStrVKJ *bfmeAssignVKJ(const BfmeStrVKJ &o);
	BfmeHdrVKJ *m_bfme00;
};

// The reserve call is EAStringC::ChangeBuffer at retail 0x0089E570.
class EAStringC
{
	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	void ChangeBuffer(unsigned int reserve, unsigned int offset,
		unsigned int copy, CBPushZero pushZero, unsigned int internalSize);

	friend class BfmeStrVKJ;
};

BfmeStrVKJ *BfmeStrVKJ::bfmeAssignVKJ(const BfmeStrVKJ &o)
{
	unsigned len = m_bfme00->m_bfme02;
	if (len == 0)
	{
		++o.m_bfme00->m_bfme00;
		BfmeHdrVKJ *h = m_bfme00;
		if (--h->m_bfme00 == 0)
			localPool()->m_bfmeFree(h);
		m_bfme00 = o.m_bfme00;
		return this;
	}
	unsigned olen = o.m_bfme00->m_bfme02;
	if (olen != 0)
	{
		unsigned total = olen + len;
		reinterpret_cast<EAStringC *>(this)->ChangeBuffer(
			total, 0, len, EAStringC::CB_NO_PUSH_ZERO, total);
		memcpy((char *)m_bfme00 + len + 8, (char *)o.m_bfme00 + 8, olen + 1);
	}
	return this;
}
