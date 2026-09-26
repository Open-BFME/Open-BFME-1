// cl: /DNDEBUG /MD

typedef unsigned char Bool;

class BfmeAi59F0
{
private:
	unsigned char m_gap[0x204];

public:
	void *m_work;
};

class Gen_002A59F0
{
public:
	int bfmeReady(void) const;

private:
	unsigned char m_gap00[8];
	BfmeAi59F0 *m_ai;
	unsigned char m_gap0c[0xd4];
	unsigned char m_marked;
	unsigned char m_working;
};

int Gen_002A59F0::bfmeReady(void) const
{
	BfmeAi59F0 *ai = m_ai;
	if (ai->m_work == 0)
	{
		__asm
		{
			xor al, al
			ret
		}
	}
	if (m_marked != 0 && m_working != 0)
		return 0;
	return 1;
}
