// ?setPolicies@RespawnPolicyMember@@QAEXURespawnPolicy@@0@Z
// partial score=0.85 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc

// RespawnPolicyMember::setPolicies, retail 0x0039FBA0, 421 bytes.
//
// Named by the already-matched RespawnBodyModuleData constructor, whose
// REL32 lands on ILT 0x0000D3E1 and follows to this body. The member is a
// single attribute-pool handle. The body releases a live handle the same
// way AttributeHandleStandIn::~AttributeHandleStandIn does (0x88-byte
// entries, magic 0x78787879), constructs a scratch entry, ORs the two
// by-value six-dword policies into the entry's plain blocks, marks the
// entry kind-1 and enables it when the first policy is nonzero, then
// interns the scratch and stores the new handle.
//
// Callees (ILT -> body): ctor 0x00008067 -> 0x0039DC20 (d_0039dc20),
// intern 0x00037FD8 -> 0x0039EE50 (d_0039ee50),
// dtor 0x00043699 -> 0x0039DCC0 (??1Gen00043699 already pinned).
//
// WALL: /O2 unrolls the 12 independent `|=` into a two-wide edx/esi
// pipeline. Retail is one-wide `mov eax,src; mov esi,dst; or esi,eax;
// mov eax,next; store; ...` of the same length (421B). Flag sweep
// /G5 /G6 /GB /Oi- /Ow /Ot /Ob0 /Ob1 left that schedule; /Os /Og- /Oy-
// dropped the unroll. #pragma optimize is function-scope only and an
// optimize-off helper was re-optimized on inline.

typedef unsigned int UnsignedInt;

enum { BFME_NO_ATTRIBUTE_HANDLE = 0xFFFFFFFF };

struct RespawnPolicy
{
	UnsignedInt values[6];
};

struct Gen00043699
{
	Gen00043699();
	~Gen00043699();

	unsigned char m_head[0x48];
	UnsignedInt m_firstPlain[6];
	UnsignedInt m_secondPlain[6];
	UnsignedInt m_kind;
	UnsignedInt m_index;
	bool m_enabled;
	unsigned char m_pad[3];
	UnsignedInt m_useCount;
};

struct BfmeAttributePool
{
	Gen00043699 *m_bfmeStart;
	Gen00043699 *m_bfmeFinish;
};

extern BfmeAttributePool TheBfmeAttributePool;
extern UnsignedInt bfmeInternAttributeEntry(Gen00043699 *entry);

class RespawnPolicyMember
{
public:
	void setPolicies(RespawnPolicy first, RespawnPolicy second);

private:
	UnsignedInt m_handle;
};

// ?setPolicies@RespawnPolicyMember@@QAEXURespawnPolicy@@0@Z
void RespawnPolicyMember::setPolicies(RespawnPolicy first, RespawnPolicy second)
{
	if (m_handle != BFME_NO_ATTRIBUTE_HANDLE)
	{
		if (m_handle <= (UnsignedInt)(TheBfmeAttributePool.m_bfmeFinish
				- TheBfmeAttributePool.m_bfmeStart))
		{
			--TheBfmeAttributePool.m_bfmeStart[m_handle].m_useCount;
			m_handle = BFME_NO_ATTRIBUTE_HANDLE;
		}
	}

	Gen00043699 entry;
	UnsignedInt i;
	for (i = 0; i < 6; ++i)
		entry.m_firstPlain[i] |= first.values[i];
	for (i = 0; i < 6; ++i)
		entry.m_secondPlain[i] |= second.values[i];
	entry.m_kind = 1;
	entry.m_enabled = false;
	for (i = 0; i < 6; ++i)
	{
		if (first.values[i] != 0)
		{
			entry.m_enabled = true;
			break;
		}
	}
	m_handle = bfmeInternAttributeEntry(&entry);
}
