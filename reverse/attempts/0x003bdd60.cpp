// ?rva003BDD60@Glo012F1028Type@@QAEHXZ
// partial score=0.94 date=2026-09-09
// ?rva003BDD60@Glo012F1028Type@@QAEHXZ
// cl: /O2 /DNDEBUG /MD /EHsc
// The worker's Gen_003BDD60 owner was only an address-shaped guess. The
// 0x0000353F ILT is called as Glo012F1028Type::j_0000353f by the named
// BfmePlayerMapState::bfmeNewMap path, and matched Glo012F1028 sources witness
// that owner's +0x28 m_bfmeSub field. Keep the method spelling address-derived;
// the subobject's +0x38 value is likewise opaque.

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

class Rva003BDD60Sub
{
public:
	char m_bfmeHead[0x38];
	int m_rva003BDD60Value;
};

class Glo012F1028Type
{
public:
	int rva003BDD60(void);

private:
	char m_bfmeHead[0x28];
	Rva003BDD60Sub *m_bfmeSub;
};

extern BfmeSwitchDR *g_bfmeSwitchDR;
extern BfmeBaseDS *g_bfmeBaseDS;

static __forceinline const int &bfmeMinDR(const int &a, const int &b)
{
	return a < b ? a : b;
}

int Glo012F1028Type::rva003BDD60(void)
{
	Rva003BDD60Sub *child = m_bfmeSub;
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
		value = child->m_rva003BDD60Value;
		return bfmeMinDR(value, difference);
	}
	return 0;
}
