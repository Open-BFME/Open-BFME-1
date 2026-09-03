// ??1Gen_uwm_008a0e70@@QAE@XZ
// partial score=0.93 date=2026-09-02
// Open-BFME: 64-slot refcounted pointer table destructor, retail 0x008A0E70.

class BfmeRef008A0E70
{
public:
	virtual void addRef();
	virtual void release();
};

class Gen_uwm_008a0e70
{
public:
	~Gen_uwm_008a0e70();

	int m_count;
	BfmeRef008A0E70 *m_slots[64];
};

Gen_uwm_008a0e70::~Gen_uwm_008a0e70()
{
	int remaining = m_count;
	int i = 0;
	char *slot = (char *)this + 4;
	for (; i < 64; ++i, slot += 4)
	{
		int obj = *(int *)slot;
		if (obj != 0)
		{
			((BfmeRef008A0E70 *)obj)->release();
			if (--remaining == 0)
				break;
		}
	}
}
