// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: constructor of the 0x88-byte attribute-pool entry, retail
// 0x0039DC20, 125 bytes. ILT 0x00008067 is pinned ??0Gen00043699@@QAE@XZ and
// jumps here. Layout matches Gen_t_0039e9d0_p128pod / S4Elem0039EBE0: six
// 12-byte pointer vectors (named, not an array — an array walked with add
// edx,0xC) then two 24-byte plain blocks, then kind=3, index=0, enabled=1,
// useCount=0. In-class vector and memset block ctors keep push esi after the
// eighteen dword stores.

extern "C" void *memset(void *, int, unsigned);

struct BfmePtrVec
{
	BfmePtrVec()
	{
		m_start = 0;
		m_finish = 0;
		m_end = 0;
	}

	void *m_start;
	void *m_finish;
	void *m_end;
};

struct BfmeAttributePlainBlock
{
	BfmeAttributePlainBlock()
	{
		memset(this, 0, sizeof(*this));
	}

	unsigned m_values[6];
};

class Gen00043699
{
public:
	Gen00043699();

private:
	BfmePtrVec m_names;
	BfmePtrVec m_values;
	BfmePtrVec m_list0;
	BfmePtrVec m_list1;
	BfmePtrVec m_list2;
	BfmePtrVec m_list3;
	BfmeAttributePlainBlock m_firstPlain;
	BfmeAttributePlainBlock m_secondPlain;
	unsigned m_kind;
	unsigned m_index;
	bool m_enabled;
	unsigned char m_pad[3];
	unsigned m_useCount;
};

// ??0Gen00043699@@QAE@XZ
Gen00043699::Gen00043699()
	: m_kind(3)
	, m_index(0)
	, m_enabled(true)
	, m_useCount(0)
{
}
