struct Rva006C9270GlobalData
{
	unsigned char m_bfmeHeadRW[0x1ac];
	float m_bfmeScaleRW;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;
extern float g_bfmeKRW;

class BfmeOwnerRW
{
public:
	virtual float bfmeComputeRW(void);

	int bfmeCheckRW(void);

	unsigned char m_bfmeHeadRW[0x50];
	float m_bfmeCachedRW;
	unsigned char m_bfmeGapRW[4];
	int m_bfmeFlagsRW;
};

int BfmeOwnerRW::bfmeCheckRW(void)
{
	if ((m_bfmeFlagsRW & 2) == 0)
	{
		m_bfmeCachedRW = bfmeComputeRW();
		m_bfmeFlagsRW |= 2;
	}

	return *(volatile float *)&TheWritableGlobalData->m_bfmeScaleRW * g_bfmeKRW < m_bfmeCachedRW;
}
