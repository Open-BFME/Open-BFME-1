extern "C" __declspec(dllimport) int __stdcall bfmeStatusDXD(void *h);

struct BfmeThingEQA
{
	char bfmeGoEQA();
	unsigned char m_bfmeFlagEQA;
	unsigned char m_bfmePadEQA[3];
	void *m_bfmeHEQA;
	unsigned char m_bfmeMidEQA[4];
	unsigned char m_bfmeReadyEQA;
};

char BfmeThingEQA::bfmeGoEQA()
{
	if (m_bfmeFlagEQA != 0)
		return 0;
	if (m_bfmeReadyEQA == 0)
		return 0;
	void *h = m_bfmeHEQA;
	if (!h)
		return 1;
	return bfmeStatusDXD(h) != 4;
}
