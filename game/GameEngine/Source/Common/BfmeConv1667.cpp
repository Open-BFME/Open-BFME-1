extern "C" __declspec(dllimport) int __stdcall AIL_3D_sample_status(void *h);

struct BfmeThingEQA
{
	char bfmeGoEQA();
	unsigned char m_bfmeFlagEQA;
	unsigned char m_bfmePadEQA[3];
	void *m_sample;
	unsigned char m_bfmeMidEQA[4];
	unsigned char m_bfmeReadyEQA;
};

char BfmeThingEQA::bfmeGoEQA()
{
	if (m_bfmeFlagEQA != 0)
		return 0;
	if (m_bfmeReadyEQA == 0)
		return 0;
	void *sample = m_sample;
	if (!sample)
		return 1;
	return AIL_3D_sample_status(sample) != 4;
}
