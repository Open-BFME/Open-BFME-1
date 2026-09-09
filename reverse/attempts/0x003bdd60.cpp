// ?bfmeLimitAdjusted@Gen_003BDD60@@QAEHXZ
// partial score=0.94 date=2026-09-09
// ?bfmeLimitAdjusted@Gen_003BDD60@@QAEHXZ
// cl: /O2 /DNDEBUG /MD /EHsc

class BfmeSwitchDR
{
public:
	char m_bfmeHead[0x1C];
	bool m_bfmeUseHigh;
};

class BfmeBaseDS
{
public:
	char m_bfmeHead[0xE70];
	int m_bfmeLow;
	int m_bfmeHigh;
	char m_bfmeGap[0x40];
	int m_bfmeLowLarge;
	int m_bfmeHighLarge;
};

class Gen_003BDD60Child
{
public:
	char m_bfmeHead[0x38];
	int m_bfmeValue;
};

class Gen_003BDD60
{
public:
	int bfmeLimitAdjusted(void);

private:
	char m_bfmeHead[0x28];
	Gen_003BDD60Child *m_bfmeChild;
};

extern BfmeSwitchDR *g_bfmeSwitchDR;
extern BfmeBaseDS *g_bfmeBaseDS;

static __forceinline const int &bfmeMinDR(const int &a, const int &b)
{
	return a < b ? a : b;
}

int Gen_003BDD60::bfmeLimitAdjusted(void)
{
	Gen_003BDD60Child *child = m_bfmeChild;
	if (child != 0)
	{
		BfmeSwitchDR *state = g_bfmeSwitchDR;
		int high = state != 0 ? state->m_bfmeUseHigh : 0;
		int limit;
		register int offset;
		BfmeBaseDS *base;
		if (state != 0 && high != 0)
		{
			base = g_bfmeBaseDS;
			limit = base->m_bfmeHighLarge;
		}
		else
		{
			base = g_bfmeBaseDS;
			limit = base->m_bfmeLowLarge;
		}
		high = state != 0 ? state->m_bfmeUseHigh : 0;
		if (state != 0 && high != 0)
			offset = base->m_bfmeHigh;
		else
			offset = base->m_bfmeLow;

		int value;
		int difference = limit - offset;
		value = child->m_bfmeValue;
		return bfmeMinDR(value, difference);
	}
	return 0;
}
