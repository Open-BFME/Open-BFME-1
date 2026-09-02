// Open-BFME5 conversions.

class BfmeSubVOQ
{
public:
	void bfmeHandleVOQ();
	char m_bfmePad00[0x18];
};

class BfmeItemVOQ
{
public:
	virtual void bfmeSlot0VOQ();
	virtual void bfmeDropVOQ();
};

class BfmeThingVOQ
{
public:
	virtual void bfmeSlot00VOQ();
	virtual void bfmeSlot01VOQ();
	virtual void bfmeSlot02VOQ();
	virtual void bfmeSlot03VOQ();
	virtual void bfmeSlot04VOQ();
	virtual void bfmeSlot05VOQ();
	virtual void bfmeSlot06VOQ();
	virtual void bfmeSlot07VOQ();
	virtual void bfmeSlot08VOQ();
	virtual void bfmeSlot09VOQ();
	virtual void bfmeSlot10VOQ();
	virtual void bfmeSlot11VOQ();
	virtual void bfmeSlot12VOQ();
	virtual void bfmeSlot13VOQ();
	virtual void bfmeSlot14VOQ();
	virtual void bfmeSlot15VOQ();
	virtual void bfmeNotifyVOQ(int a, int b);
	void bfmeResetVOQ();
	char m_bfmePad04[4];
	BfmeSubVOQ m_bfme08;
	int *m_bfme20;
	int m_bfme24;
	int m_bfme28;
};

void BfmeThingVOQ::bfmeResetVOQ()
{
	m_bfme08.bfmeHandleVOQ();
	bfmeNotifyVOQ(0, 0);
	m_bfme24 = 0;
	if (m_bfme20 != 0)
	{
		int i = 0;

		if (m_bfme28 > 0)
		{
			do
			{
				unsigned v = (unsigned)m_bfme20[i];
				BfmeItemVOQ *p = (BfmeItemVOQ *)(v & 0xfffffffe);

				if (p != 0 && (v & 1) != 0)
				{
					p->bfmeDropVOQ();
					m_bfme20[i] = 0;
				}
				++i;
			} while (i < m_bfme28);
		}
	}
}
