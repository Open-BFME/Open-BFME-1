struct BfmeInfoBB
{
	unsigned char m_bfmeFlagBB;
	unsigned char m_bfmeLevelBB;
};

class BfmeAgentBB
{
public:
	virtual void bfmeSlot00BB();
	virtual char bfmeReadingBB();
	virtual void bfmeSlot02BB();
	virtual void bfmeSlot03BB();
	virtual void bfmeSlot04BB();
	virtual void bfmeSlot05BB();
	virtual void bfmeSlot06BB();
	virtual void bfmeSlot07BB();
	virtual void bfmeSlot08BB();
	virtual void bfmeSlot09BB();
	virtual void bfmeFillBB(BfmeInfoBB *info);
	virtual void bfmeSlot11BB();
	virtual void bfmeSlot12BB();
	virtual void bfmeSlot13BB();
	virtual void bfmeSlot14BB();
	virtual void bfmeSlot15BB();
	virtual void bfmeSlot16BB();
	virtual void bfmeSlot17BB();
	virtual void bfmeSlot18BB();
	virtual void bfmeSlot19BB();
	virtual void bfmeSlot20BB();
	virtual void bfmeSlot21BB();
	virtual void bfmeSlot22BB();
	virtual void bfmeSlot23BB();
	virtual void bfmeMarkBB(void *dst);
	virtual void bfmeSlot25BB();
	virtual void bfmeSlot26BB();
	virtual void bfmeLateBB(void *dst);
	virtual void bfmeSlot28BB();
	virtual void bfmeSlot29BB();
	virtual void bfmeWordBB(void *dst);
	virtual void bfmeSlot31BB();
	virtual void bfmeSlot32BB();
	virtual void bfmeSlot33BB();
	virtual void bfmeSlot34BB();
	virtual void bfmeByteBB(unsigned char *dst);
};

extern "C" char *__cdecl bfmeCopyBB(char *first, char *last, char *dst, int *tag, int kind);
extern "C" void __cdecl bfmeXferVecBB(BfmeAgentBB *ag, void *dst);

class BfmeHostBB
{
public:
	void bfmeSaveBB(BfmeAgentBB *ag);
	void bfmeBeginBB(BfmeAgentBB *ag);

	unsigned char m_bfmeHeadBB[0x20];
	char *m_bfmeBeginBB;
	char *m_bfmeEndBB;
	unsigned char m_bfmePadOneBB[4];
	unsigned char m_bfmeSlotABB[4];
	unsigned char m_bfmePadTwoBB[8];
	unsigned char m_bfmeSlotBBB[4];
	unsigned char m_bfmePadThreeBB[8];
	unsigned char m_bfmeSlotCBB[4];
	unsigned char m_bfmeSlotDBB[4];
	unsigned char m_bfmeSlotEBB[4];
	unsigned char m_bfmeSlotFBB[4];
	unsigned char m_bfmeSlotGBB[4];
	unsigned char m_bfmeSlotHBB[4];
	unsigned char m_bfmeSlotIBB;
	unsigned char m_bfmeSlotJBB;
	unsigned char m_bfmeSlotKBB;
	unsigned char m_bfmeSlotLBB;
};

void BfmeHostBB::bfmeSaveBB(BfmeAgentBB *ag)
{
	BfmeInfoBB info;

	info.m_bfmeFlagBB = 1;
	info.m_bfmeLevelBB = 2;
	ag->bfmeFillBB(&info);

	bfmeBeginBB(ag);

	ag->bfmeWordBB(m_bfmeSlotEBB);
	ag->bfmeLateBB(m_bfmeSlotCBB);
	ag->bfmeLateBB(m_bfmeSlotDBB);
	ag->bfmeMarkBB(m_bfmeSlotABB);
	ag->bfmeMarkBB(m_bfmeSlotBBB);
	ag->bfmeWordBB(m_bfmeSlotHBB);
	ag->bfmeByteBB(&m_bfmeSlotIBB);
	ag->bfmeByteBB(&m_bfmeSlotJBB);
	ag->bfmeWordBB(m_bfmeSlotGBB);
	ag->bfmeByteBB(&m_bfmeSlotKBB);
	ag->bfmeByteBB(&m_bfmeSlotLBB);
	ag->bfmeWordBB(m_bfmeSlotFBB);

	if (info.m_bfmeLevelBB >= 2)
	{
		if (ag->bfmeReadingBB() != 0)
		{
			int tag;
			char *dst = m_bfmeBeginBB;

			m_bfmeEndBB = bfmeCopyBB(m_bfmeEndBB, m_bfmeEndBB, dst, &tag, 0);
		}

		bfmeXferVecBB(ag, &m_bfmeBeginBB);
	}
}
