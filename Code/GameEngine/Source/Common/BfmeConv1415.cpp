// Open-BFME5 conversions.

class BfmeSubVLN
{
public:
	virtual void bfmeSlot0VLN();
	virtual void bfmeSlot1VLN();
	virtual void bfmeSlot2VLN();
	virtual void bfmeSlot3VLN();
	virtual int bfmeStateVLN();
};

class BfmeCtlVLN
{
public:
	void bfmeNotifyVLN();
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	char m_bfmePad18[0x40];
	BfmeSubVLN *m_bfme58;
};

struct BfmeVbVLN
{
	int m_bfme00;
	int m_bfme04;
};

class BfmeOwnVLN
{
public:
	BfmeOwnVLN *bfmeApplyVLN();
	BfmeVbVLN *m_bfme00;
};

static BfmeCtlVLN *bfmeBaseVLN(BfmeOwnVLN *p)
{
	return (BfmeCtlVLN *)((char *)p + p->m_bfme00->m_bfme04);
}

BfmeOwnVLN *BfmeOwnVLN::bfmeApplyVLN()
{
	BfmeSubVLN *s = bfmeBaseVLN(this)->m_bfme58;
	if (s != 0 && s->bfmeStateVLN() == -1)
	{
		BfmeCtlVLN *b = bfmeBaseVLN(this);
		int f = b->m_bfme08 | 1;
		if (b->m_bfme58 == 0)
			f |= 1;
		b->m_bfme08 = f;
		if ((b->m_bfme14 & f) != 0)
			b->bfmeNotifyVLN();
	}
	return this;
}
