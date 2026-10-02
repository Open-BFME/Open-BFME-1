struct BfmeTextCW
{
	char m_bfmeRawCW[4];
};

class BfmeHoldCW
{
public:
	unsigned char m_bfmeHeadCW[0x188];
	BfmeTextCW m_bfmeThirdCW;
	BfmeTextCW m_bfmeSecondCW;
	BfmeTextCW m_bfmeFirstCW;
};

// Retail spells this singleton `BfmeGameCW *g_bfmeGameCW`
// (?g_bfmeGameCW@@3PAVBfmeGameCW@@A) at 0x012F706C; this TU reads three
// adjacent members of it, so the retail pointer is reinterpreted here.
class BfmeGameCW;
extern BfmeGameCW *g_bfmeGameCW;
extern BfmeTextCW g_bfmeDefaultCW;

BfmeTextCW * __stdcall bfmeSelectCW(int which)
{
	BfmeHoldCW *hold = (BfmeHoldCW *)g_bfmeGameCW;

	switch (which)
	{
	case 0:
		return &hold->m_bfmeFirstCW;

	case 1:
		return &hold->m_bfmeSecondCW;

	case 2:
		return &hold->m_bfmeThirdCW;
	}

	return &g_bfmeDefaultCW;
}
