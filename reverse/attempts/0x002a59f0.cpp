// ?bfmeReady@Gen_002A59F0@@QBEHXZ
// partial score=0.7 date=2026-09-04
// cl: /DNDEBUG /MD

class BfmeAi59F0
{
private:
	unsigned char m_gap[0x204];

public:
	void *m_work;
};

class BfmeThing59F0
{
public:
	int bfmeReady59F0(void) const;

private:
	unsigned char m_gap00[8];
	BfmeAi59F0 *m_ai;
	unsigned char m_gap0c[0xd4];
	unsigned char m_marked;
	unsigned char m_working;
};

static __forceinline unsigned char falseByte59F0(void)
{
	return 0;
}

// ?bfmeReady59F0@BfmeThing59F0@@QBEHXZ
int BfmeThing59F0::bfmeReady59F0(void) const
{
	BfmeAi59F0 *ai = m_ai;
	if (ai->m_work == 0)
	{
		return (int)((unsigned int)ai & 0xffffff00);
	}
	if (m_marked != 0 && m_working != 0)
		return 0;
	return 1;
}
