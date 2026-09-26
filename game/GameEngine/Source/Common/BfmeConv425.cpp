class BfmeOneATC
{
public:
	void bfmeStopATC(int what);
};

struct BfmeTwoATC
{
	unsigned char m_bfmeHead[0x59];
	bool m_bfmeFlag;
};

extern BfmeOneATC *g_bfmeOneATC;
extern BfmeTwoATC *g_bfmeTwoATC;

class BfmeThingATC
{
public:
	void bfmeGoATC();
	unsigned char m_bfmeHead[0x264];
	int m_bfmeState;
};

void BfmeThingATC::bfmeGoATC()
{
	if (m_bfmeState == 2)
	{
		m_bfmeState = 0;
		g_bfmeOneATC->bfmeStopATC(0);
		g_bfmeTwoATC->m_bfmeFlag = true;
		return;
	}
	g_bfmeTwoATC->m_bfmeFlag = true;
}
