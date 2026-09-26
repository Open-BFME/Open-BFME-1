// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: intern a 24-byte by-value plain block into the attribute-pool
// handle at this+0, retail 0x0039FDB0, 298 bytes. Same release/intern pair as
// the banked RespawnPolicyMember::setPolicies sibling at 0x0039FBA0, but one
// 6-dword block ORed into m_secondPlain with kind 3. Ctor ILT 0x00008067
// jumps to 0x0039DC20; intern ILT 0x00037FD8 jumps to 0x0039EE50; dtor ILT
// 0x00043699 jumps to the landed ??1S4Elem0039EBE0@@QAE@XZ.

typedef unsigned int UnsignedInt;

enum { BFME_NO_ATTRIBUTE_HANDLE = 0xFFFFFFFF };

struct BfmeAttributePlainBlock
{
	UnsignedInt m_values[6];
};

class Gen00043699
{
public:
	Gen00043699();
	~Gen00043699();

	unsigned char m_head[0x48];
	BfmeAttributePlainBlock m_firstPlain;
	BfmeAttributePlainBlock m_secondPlain;
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

class BfmeSecondPlainMember
{
public:
	void setSecondPlain(BfmeAttributePlainBlock block);

private:
	UnsignedInt m_handle;
};

void BfmeSecondPlainMember::setSecondPlain(BfmeAttributePlainBlock block)
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
	entry.m_secondPlain.m_values[0] |= block.m_values[0];
	entry.m_secondPlain.m_values[1] |= block.m_values[1];
	entry.m_secondPlain.m_values[2] |= block.m_values[2];
	entry.m_secondPlain.m_values[3] |= block.m_values[3];
	entry.m_secondPlain.m_values[4] |= block.m_values[4];
	entry.m_enabled = true;
	entry.m_kind = 3;
	entry.m_secondPlain.m_values[5] |= block.m_values[5];
	m_handle = bfmeInternAttributeEntry(&entry);
}
