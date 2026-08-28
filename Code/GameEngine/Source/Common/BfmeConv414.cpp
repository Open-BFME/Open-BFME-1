class BfmeSubAQA
{
public:
	void bfmeStopTwoAQA();
};

class BfmeOneAQA
{
public:
	void bfmeStopAQA();
};

class BfmeTwoAQA
{
public:
	void bfmeSendAQA(void *what);
	void bfmeFinishAQA();
	unsigned char m_bfmeHead[0x28];
	BfmeSubAQA *m_bfmeSub;
};

extern BfmeOneAQA *g_bfmeOneAQA;
extern BfmeTwoAQA *g_bfmeTwoAQA;

void __stdcall bfmeGoAQA(void *what)
{
	if (g_bfmeOneAQA != 0)
		g_bfmeOneAQA->bfmeStopAQA();
	if (g_bfmeTwoAQA->m_bfmeSub != 0)
		g_bfmeTwoAQA->m_bfmeSub->bfmeStopTwoAQA();
	g_bfmeTwoAQA->bfmeSendAQA(what);
	g_bfmeTwoAQA->bfmeFinishAQA();
}
