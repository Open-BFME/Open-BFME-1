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

extern BfmeHoldCW *g_bfmeHoldCW;
extern BfmeTextCW g_bfmeDefaultCW;

BfmeTextCW * __stdcall bfmeSelectCW(int which)
{
	BfmeHoldCW *hold = g_bfmeHoldCW;

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
