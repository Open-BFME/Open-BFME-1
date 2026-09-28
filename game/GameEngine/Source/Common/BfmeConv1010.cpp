// Open-BFME5 conversions.

class BfmeItem1010;

class BfmeSink1010
{
public:
	void bfmeDrop1010(BfmeItem1010 *it);
};

extern BfmeSink1010 *g_bfmeSink1010;

struct BfmeNode1010
{
	BfmeNode1010 *m_bfmeNext;
	char m_bfmePad[4];
	BfmeItem1010 *m_bfmeItem;
};

class BfmeA1010
{
public:
	void bfmeGo1010A();
	void bfmeFinish1010A();

	char m_bfmePad[0x9bc];
	BfmeNode1010 *m_bfmeList;
};

void BfmeA1010::bfmeGo1010A()
{
	BfmeNode1010 *n = m_bfmeList->m_bfmeNext;

	while (n != m_bfmeList) {
		BfmeItem1010 *it = n->m_bfmeItem;

		n = n->m_bfmeNext;
		g_bfmeSink1010->bfmeDrop1010(it);
	}

	bfmeFinish1010A();
}

struct BfmeOwner1010
{
	char m_bfmePad[0x74];
	int m_bfmeVal;
};

class BfmeHeld1010
{
public:
	virtual void bfmeRelease1010(int n);

	void bfmeAttach1010(BfmeOwner1010 *o);

	char m_bfmePad[4];
	int m_bfmeVal;
};

class BfmeMake1010
{
public:
	BfmeHeld1010 *bfmeMake1010(void *a, int n);
};

extern BfmeMake1010 *g_bfmeMake1010;

class BfmeC1010
{
public:
	void bfmeGo1010C(void *a);

	char m_bfmePad[8];
	BfmeOwner1010 *m_bfmeOwner;
	char m_bfmePad2[0x14];
	BfmeHeld1010 *m_bfmeHeld;
};

void BfmeC1010::bfmeGo1010C(void *a)
{
	if (!a)
		return;

	BfmeHeld1010 *h = m_bfmeHeld;

	if (h)
		h->bfmeRelease1010(1);

	m_bfmeHeld = g_bfmeMake1010->bfmeMake1010(a, 0);
	m_bfmeHeld->m_bfmeVal = m_bfmeOwner->m_bfmeVal;
	m_bfmeHeld->bfmeAttach1010(m_bfmeOwner);
}
