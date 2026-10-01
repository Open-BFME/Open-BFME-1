// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail RVA 0x0056A1B0.

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadPT[0x10c];
	int m_bfmeModePT;
};

// Retail's GameLogic singleton (0x012F0898) is EA's `GameLogic *TheGameLogic`
// (mangled ?TheGameLogic@@3PAVGameLogic@@A, defined in GameLogic.cpp).  This TU
// keeps its own partial view of the object and casts at each use.
class GameLogic;

extern GameLogic *TheGameLogic;
extern void j_000445da(void);
extern void j_00002941(void);

class BfmeOwnerPT
{
public:
	int bfmeStopPT(void);
	void bfmeCallAPT(void);
	void bfmeCallBPT(void);

	unsigned char m_bfmeHeadPT[0x259];
	char m_bfmeFlagPT;
	char m_bfmeActivePT;
};

int BfmeOwnerPT::bfmeStopPT(void)
{
	if (m_bfmeActivePT == 0)
		return 1;

	m_bfmeActivePT = 0;
	int mode = ((Rva00367E30Logic *)TheGameLogic)->m_bfmeModePT;

	if (mode == 1)
		goto call_a;
	if (mode == 5)
		goto call_a;

	if (mode == 2)
		m_bfmeFlagPT = 1;

	j_00002941();
	return 1;

call_a:
	j_000445da();
	return 1;
}
