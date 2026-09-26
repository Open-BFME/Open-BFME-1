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

class BfmeOwnBZ
{
public:
	void bfmeRunBZ(void);
	void bfmeInitBZ(void);
	char bfmeStepBZ(void);

	unsigned char m_bfmeHeadBZ[4];
	BfmeCfgBZ *m_bfmeCfgBZ;
	unsigned char m_bfmeMidBZ[0xe0];
	BfmeListBZ *m_bfmeListBZ;
	unsigned char m_bfmeMid2BZ[0xc];
	char m_bfmeDoneBZ;
};

void BfmeOwnBZ::bfmeRunBZ(void)
{
	bfmeInitBZ();

	BfmeCfgBZ *cfg = m_bfmeCfgBZ;

	if (cfg->m_bfmeFlagBZ == 0 && m_bfmeListBZ->m_bfmeNextBZ == m_bfmeListBZ)
	{
		m_bfmeDoneBZ = 1;
		return;
	}

	int index = 0;

	while (index < cfg->m_bfmeCountBZ)
	{
		m_bfmeDoneBZ = bfmeStepBZ();
		++index;

		if (m_bfmeDoneBZ)
			return;
	}
}
