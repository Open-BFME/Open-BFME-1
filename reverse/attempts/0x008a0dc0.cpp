// ??1Gen_uwm_008a0dc0@@QAE@XZ
// partial score=0.93 date=2026-09-02
// Open-BFME: 512-slot refcounted pointer table destructor, retail 0x008A0DC0.

class BfmeRef008A0DC0
{
public:
	virtual void addRef();
	virtual void release();
};

class Gen_uwm_008a0dc0
{
public:
	~Gen_uwm_008a0dc0();

	int m_count;
	BfmeRef008A0DC0 *m_slots[512];
};

Gen_uwm_008a0dc0::~Gen_uwm_008a0dc0()
{
	int remaining = m_count;
	int i = 0;
	BfmeRef008A0DC0 **slot = m_slots;
	for (; i < 512; ++i, ++slot)
	{
		if (*slot != 0)
		{
			(*slot)->release();
			if (--remaining == 0)
				break;
		}
	}
}
