// Open-BFME5 conversions.

class BfmeKickVLL
{
public:
	void bfmeKickVLL();
};

class BfmeCtlVLL
{
public:
	void bfmeNotifyVLL();
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	char m_bfmePad18[0x40];
	BfmeKickVLL *m_bfme58;
	BfmeKickVLL *m_bfme5c;
};

struct BfmeVbVLL
{
	int m_bfme00;
	int m_bfme04;
};

class BfmeOwnVLL
{
public:
	BfmeVbVLL *m_bfme00;
};

static BfmeCtlVLL *bfmeBaseVLL(BfmeOwnVLL *p)
{
	return (BfmeCtlVLL *)((char *)p + p->m_bfme00->m_bfme04);
}

bool bfmeCheckVLL(BfmeOwnVLL *p)
{
	if (bfmeBaseVLL(p)->m_bfme08 == 0)
	{
	if (bfmeBaseVLL(p)->m_bfme58 == 0)
	{
		BfmeCtlVLL *b = bfmeBaseVLL(p);
		int f = b->m_bfme08 | 1;
		if (b->m_bfme58 == 0)
			f |= 1;
		b->m_bfme08 = f;
		if ((b->m_bfme14 & f) != 0)
			b->bfmeNotifyVLL();
	}
	if (bfmeBaseVLL(p)->m_bfme5c != 0)
		bfmeBaseVLL(p)->m_bfme5c->bfmeKickVLL();
	return bfmeBaseVLL(p)->m_bfme08 == 0;
	}
	return false;
}
