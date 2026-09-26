class BfmeHostBU;
class BfmeThingBU;

class BfmeThingBU
{
public:
	void bfmeStopBU(int mode);
};

class Radar
{
public:
	void bfmeRemoveBU(BfmeHostBU *o);
};

extern Radar *TheRadar;

class BfmePathBU
{
public:
	void bfmeDropBU(BfmeHostBU *o);
};

class AI
{
public:
	unsigned char m_bfmeHeadBU[0xc];
	BfmePathBU *m_bfmePathBU;
};

extern AI *TheAI;

class BfmeSubBU
{
public:
	void bfmeUnlinkBU(BfmeHostBU *o);
};

class Glo012F4B98Type
{
public:
	unsigned char m_bfmeHeadBU[0x2b8];
	BfmeSubBU m_bfmeSubBU;
};

extern Glo012F4B98Type *Glo012F4B98;

class BfmeHostBU
{
public:
	virtual void bfmeSlot00BU();
	virtual void bfmeSlot01BU();
	virtual void bfmeSlot02BU();
	virtual void bfmeSlot03BU();
	virtual void bfmeSlot04BU();
	virtual void bfmeSlot05BU();
	virtual void bfmeSlot06BU();
	virtual void bfmeSlot07BU();
	virtual void bfmeSlot08BU();
	virtual void bfmeSlot09BU();
	virtual BfmeThingBU *bfmeGetBU();

	void bfmeDieBU();
	void bfmeCleanBU();
	void bfmeFinishBU();
	void bfmeNotifyBU(int what);

	unsigned char m_bfmeHeadBU[0x90];
	int m_bfmeFlagsBU;
};

void BfmeHostBU::bfmeDieBU()
{
	if ((m_bfmeFlagsBU & 0x40000) != 0)
	{
		BfmeThingBU *t = bfmeGetBU();

		if (t != 0)
			t->bfmeStopBU(0);

		TheRadar->bfmeRemoveBU(this);
		TheAI->m_bfmePathBU->bfmeDropBU(this);

		if (Glo012F4B98 != 0)
			Glo012F4B98->m_bfmeSubBU.bfmeUnlinkBU(this);

		bfmeCleanBU();
		bfmeFinishBU();
		bfmeNotifyBU(0x32);
	}
}
