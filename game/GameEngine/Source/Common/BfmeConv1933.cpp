extern "C" char *g_bfmeGameCW;

class BfmeSlotCZ
{
public:
	void *m_bfmeHeadCZ;
};

class BfmeReqCZ
{
public:
	BfmeReqCZ(BfmeSlotCZ *slot, int mode);
	~BfmeReqCZ();

	unsigned char m_bfmeHeadCZ[0x49];
	unsigned char m_bfmeFlagCZ;
	unsigned char m_bfmeTailCZ[0x26];
};

class BfmeGameCZ
{
public:
	void bfmeSendCZ(BfmeReqCZ *req);
};

class BfmeHostCZ
{
public:
	char bfmeRunCZ();

	unsigned char m_bfmeHeadCZ[0xc];
	BfmeSlotCZ m_bfmeSlotCZ;
};

char BfmeHostCZ::bfmeRunCZ()
{
	BfmeSlotCZ *slot = &m_bfmeSlotCZ;

	if (slot->m_bfmeHeadCZ != 0)
	{
		BfmeReqCZ req(slot, 1);

		req.m_bfmeFlagCZ = 1;
		((BfmeGameCZ *)g_bfmeGameCW)->bfmeSendCZ(&req);
	}

	return 1;
}
