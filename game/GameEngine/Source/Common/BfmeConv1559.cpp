// Open-BFME5 conversions.

class BfmeLogVPE
{
public:
	virtual void bfmeSlot0VPE();
	virtual void bfmeSlot1VPE();
	virtual void bfmeSlot2VPE();
	virtual void bfmeAssertVPE(const char *cond, const char *file, int line);
};

BfmeLogVPE *bfmeGetLogVPE();

struct BfmeSlotVPE
{
	char m_bfme00;
	char m_bfmePad01[0x17];
};

class BfmeMgrVPE
{
public:
	BfmeSlotVPE *bfmeAllocSlotVPE();
	char m_bfmePad000[0x10];
	int m_bfme10;
	char m_bfmePad014[0x394];
	BfmeSlotVPE m_bfme3a8[0x20];
};

BfmeSlotVPE *BfmeMgrVPE::bfmeAllocSlotVPE()
{
	int i;

	for (i = 0; i < 0x20; ++i)
	{
		if (m_bfme3a8[i].m_bfme00 == 0)
		{
			BfmeSlotVPE *s = &m_bfme3a8[i];

			s->m_bfme00 = 1;
			++i;
			if (i > m_bfme10)
				m_bfme10 = i;
			return s;
		}
	}

	bfmeGetLogVPE()->bfmeAssertVPE("false", "\\views\\feslbuild_main\\jabba\\fesl\\source\\transactor.cpp", 0x2ac);
	return 0;
}
