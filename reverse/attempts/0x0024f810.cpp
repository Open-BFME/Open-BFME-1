// ?bfmeGoGH@BfmeSecondGH@@QAEXXZ (identity unknown)
// partial score=0.95 date=2026-09-06
// 60/60 exact size; retail loads the owner before the inner pointer, MSVC the
// reverse, and the three register names follow from that one choice.
// Pins: check 0x0001E0AB, send 0x0004A12E, logic global 0x00EF0898
class BfmeLogicGH
{
public:
	char bfmeCheckGH(void);
};

extern BfmeLogicGH *g_bfmeGameLogicGH;

void __stdcall bfmeSendGH(int delta, int first, int second);

class BfmeInnerGH
{
public:
	unsigned char m_bfmeHeadGH[0x28];
	int m_bfmeStartGH;
};

class BfmeStateGH
{
public:
	unsigned char m_bfmeHeadGH[0x210];
	BfmeInnerGH *m_bfmeInnerGH;
};

class BfmeOwnerGH
{
public:
	unsigned char m_bfmeHeadGH[8];
	int m_bfmeTimeGH;
	char m_bfmeFlagGH;
};

class BfmeSecondGH
{
public:
	void bfmeGoGH(void);
};

void BfmeSecondGH::bfmeGoGH(void)
{
	char *base = (char *)this;

	if ((*(BfmeOwnerGH **)(base - 0xc))->m_bfmeFlagGH != 0
		&& g_bfmeGameLogicGH->bfmeCheckGH() == 0)
		return;

	BfmeStateGH *state = *(BfmeStateGH **)(base - 8);
	BfmeOwnerGH *owner = *(BfmeOwnerGH **)(base - 0xc);
	BfmeInnerGH *inner = state->m_bfmeInnerGH;
	int now = owner->m_bfmeTimeGH;
	int start = inner->m_bfmeStartGH;

	bfmeSendGH(now - start, 0, 0);
}
