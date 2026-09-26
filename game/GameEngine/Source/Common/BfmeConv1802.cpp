class BfmeStateVT
{
public:
	unsigned char m_bfmeHeadVT[0x5e];
	char m_bfmeFlagVT;
};

class BfmeUnitVT
{
public:
	unsigned char m_bfmeHeadVT[0x208];
	BfmeStateVT *m_bfmeStateVT;
};

class BfmeOwnerVT
{
public:
	int bfmeTouchVT(void);
	void bfmeNotifyVT(void);

	unsigned char m_bfmeHeadVT[0x2c];
	unsigned char m_bfmeMaskVT;
	unsigned char m_bfmeGapVT[3];
	char m_bfmeDirtyVT;
};

int BfmeOwnerVT::bfmeTouchVT(void)
{
	BfmeUnitVT *unit = *(BfmeUnitVT **)((char *)this - 8);

	if (unit->m_bfmeStateVT->m_bfmeFlagVT)
		m_bfmeDirtyVT = 1;

	if (m_bfmeMaskVT & 1)
		bfmeNotifyVT();

	return 1;
}
