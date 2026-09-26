class BfmeThingJT
{
public:
	unsigned char m_bfmeHeadJT[0x264];
	void *m_bfme264JT;
	void *m_bfme268JT;
	int m_bfme26cJT;
	void *m_bfme270JT;
	void *m_bfme274JT;
	int m_bfme278JT;
	void *m_bfme27cJT;
	void *m_bfme280JT;
	void *m_bfme284JT;
	void *m_bfme288JT;
	void *m_bfme28cJT;
	void *m_bfme290JT;
};

void bfmeFreeOneJT(void *q);

class Bucket
{
public:
	enum BucketMagicEnum { BFME_ZERO_JT = 0 };

	static void *operator new(unsigned int n, BucketMagicEnum m);
};

void bfmeFreeJT(BfmeThingJT *p)
{
	if (p->m_bfme274JT != 0)
		bfmeFreeOneJT(p->m_bfme274JT);

	if (p->m_bfme28cJT != 0)
		bfmeFreeOneJT(p->m_bfme28cJT);

	if (p->m_bfme288JT != 0)
		bfmeFreeOneJT(p->m_bfme288JT);

	if (p->m_bfme280JT != 0)
		bfmeFreeOneJT(p->m_bfme280JT);

	if (p->m_bfme268JT != 0)
		bfmeFreeOneJT(p->m_bfme268JT);

	p->m_bfme274JT = 0;
	p->m_bfme28cJT = 0;
	p->m_bfme288JT = 0;
	p->m_bfme280JT = 0;
	p->m_bfme268JT = 0;
	p->m_bfme270JT = 0;
	p->m_bfme290JT = 0;
	p->m_bfme284JT = 0;
	p->m_bfme27cJT = 0;
	p->m_bfme264JT = 0;
}

int bfmeAllocJT(BfmeThingJT *p)
{
	bfmeFreeJT(p);

	void *a = Bucket::operator new(0xa0, Bucket::BFME_ZERO_JT);

	p->m_bfme274JT = a;

	if (a == 0)
	{
		bfmeFreeJT(p);

		return 0;
	}

	p->m_bfme270JT = (void *)(((unsigned int)a + 0x1f) & 0xffffffe0);

	void *b = Bucket::operator new(0xa0, Bucket::BFME_ZERO_JT);

	p->m_bfme288JT = b;

	if (b == 0)
	{
		bfmeFreeJT(p);

		return 0;
	}

	p->m_bfme284JT = (void *)(((unsigned int)b + 0x1f) & 0xffffffe0);

	void *c = Bucket::operator new(0x120, Bucket::BFME_ZERO_JT);

	p->m_bfme28cJT = c;

	if (c == 0)
	{
		bfmeFreeJT(p);

		return 0;
	}

	p->m_bfme290JT = (void *)(((unsigned int)c + 0x1f) & 0xffffffe0);

	void *d = Bucket::operator new(0xa0, Bucket::BFME_ZERO_JT);

	p->m_bfme280JT = d;

	if (d == 0)
	{
		bfmeFreeJT(p);

		return 0;
	}

	p->m_bfme27cJT = (void *)(((unsigned int)d + 0x1f) & 0xffffffe0);

	return 1;
}
