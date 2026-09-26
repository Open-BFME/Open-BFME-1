class BfmeItemFU
{
public:
	unsigned char m_bfmeHeadFU[0x114];
	unsigned int m_bfmeFlagsFU;
};

class BfmeNodeFU
{
public:
	BfmeNodeFU *m_bfmeNextFU;
	unsigned char m_bfmeGapFU[4];
	BfmeItemFU *m_bfmeItemFU;
};

class BfmeListFU
{
public:
	BfmeNodeFU *m_bfmeHeadFU;
};

class BfmeBaseFU
{
public:
	virtual void bfmeSlot0FU();
	virtual void bfmeSlot1FU();
	virtual void bfmeSlot2FU();
	virtual void bfmeSlot3FU();
	virtual void bfmeSlot4FU();
	virtual void bfmeSlot5FU();
	virtual void bfmeSlot6FU();
	virtual void bfmeSlot7FU();
	virtual void bfmeSlot8FU();
	virtual void bfmeSlot9FU();
	virtual void bfmeSlot10FU();
	virtual void bfmeSlot11FU();
	virtual void bfmeSlot12FU();
	virtual void bfmeSlot13FU();
	virtual void bfmeSlot14FU();
	virtual void bfmeSlot15FU();
	virtual void bfmeSlot16FU();
	virtual void bfmeSlot17FU();
	virtual void bfmeSlot18FU();
	virtual void bfmeSlot19FU();
	virtual void bfmeSlot20FU();
	virtual void bfmeSlot21FU();
	virtual void bfmeSlot22FU();
	virtual void bfmeSlot23FU();
	virtual void bfmeSlot24FU();
	virtual void bfmeSlot25FU();
	virtual void bfmeSlot26FU();
	virtual void bfmeSlot27FU();
	virtual void bfmeSlot28FU();
	virtual void bfmeSlot29FU();
	virtual void bfmeSlot30FU();
	virtual void bfmeSlot31FU();
	virtual void bfmeSlot32FU();
	virtual void bfmeSlot33FU();
	virtual void bfmeSlot34FU();
	virtual void bfmeSlot35FU();
	virtual void bfmeSlot36FU();
	virtual void bfmeSlot37FU();
	virtual void bfmeSlot38FU();
	virtual void bfmeSlot39FU();
	virtual void bfmeSlot40FU();
	virtual void bfmeSlot41FU();
	virtual void bfmeSlot42FU();
	virtual void bfmeSlot43FU();
	virtual void bfmeSlot44FU();
	virtual void bfmeSlot45FU();
	virtual void bfmeSlot46FU();
	virtual void bfmeSlot47FU();
	virtual void bfmeSlot48FU();
	virtual void bfmeSlot49FU();
	virtual void bfmeSlot50FU();
	virtual void bfmeSlot51FU();
	virtual void bfmeSlot52FU();
	virtual void bfmeSlot53FU();
	virtual void bfmeSlot54FU();
	virtual void bfmeSlot55FU();
	virtual void bfmeSlot56FU();
	virtual void bfmeSlot57FU();
	virtual void bfmeSlot58FU();
	virtual void bfmeSlot59FU();
	virtual void bfmeSlot60FU();
	virtual void bfmeSlot61FU();
	virtual void bfmeSlot62FU();
	virtual void bfmeSlot63FU();
	virtual void bfmeSlot64FU();
	virtual BfmeListFU *bfmeListFU();
};

class BfmeHostFU
{
public:
	char bfmeAnyFU();
};

char BfmeHostFU::bfmeAnyFU()
{
	BfmeNodeFU *s = ((BfmeBaseFU *)((char *)this - 0xc4))->bfmeListFU()->m_bfmeHeadFU;

	for (BfmeNodeFU *n = s->m_bfmeNextFU; n != s; n = n->m_bfmeNextFU)
	{
		BfmeItemFU *it = n->m_bfmeItemFU;

		if (it != 0 && (it->m_bfmeFlagsFU & 0x10000000) != 0)
			return 1;
	}

	return 0;
}
