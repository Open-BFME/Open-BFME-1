class BfmeListBZ
{
public:
	BfmeListBZ *m_bfmeNextBZ;
};

class BfmeCfgBZ
{
public:
	unsigned char m_bfmeHeadBZ[0x260];
	int m_bfmeCountBZ;
	unsigned char m_bfmeMidBZ[4];
	char m_bfmeFlagBZ;
};

void __cdecl j_0003fa30(void);
void __cdecl j_00039257(void);

class BfmeOwnBZ
{
public:
	void bfmeRunBZ(void);

	unsigned char m_bfmeHeadBZ[4];
	BfmeCfgBZ *m_bfmeCfgBZ;
	unsigned char m_bfmeMidBZ[0xe0];
	BfmeListBZ *m_bfmeListBZ;
	unsigned char m_bfmeMid2BZ[0xc];
	char m_bfmeDoneBZ;
};

void BfmeOwnBZ::bfmeRunBZ(void)
{
	((void (__cdecl *)(void))&j_0003fa30)();

	BfmeCfgBZ *cfg = m_bfmeCfgBZ;

	if (cfg->m_bfmeFlagBZ == 0 && m_bfmeListBZ->m_bfmeNextBZ == m_bfmeListBZ)
	{
		m_bfmeDoneBZ = 1;
		return;
	}

	int index = 0;

	while (index < cfg->m_bfmeCountBZ)
	{
		union StepCall
		{
			char (__cdecl *freeCall)(void);
			char (BfmeOwnBZ::*memberCall)(void);
		} stepCall;
		stepCall.freeCall = (char (__cdecl *)(void))&j_00039257;
		m_bfmeDoneBZ = (this->*stepCall.memberCall)();
		++index;

		if (m_bfmeDoneBZ)
			return;
	}
}
