// Open-BFME5 conversions.

class BfmeX1011;

class BfmeLook1011
{
public:
	BfmeX1011 *bfmeFind1011(int id);
};

extern BfmeLook1011 *g_bfmeLook1011;

class BfmeA1011
{
public:
	void bfmeGo1011A(int a, int b, int c, int d, int e);
	void bfmeSend1011(int a, int b, int c, int d, int e);

	char m_bfmePad[0x8c];
	int m_bfmeId;
	char m_bfmePad2[0x39];
	char m_bfmeFlag;
};

void BfmeA1011::bfmeGo1011A(int a, int b, int c, int d, int e)
{
	BfmeX1011 *x = g_bfmeLook1011->bfmeFind1011(m_bfmeId);

	if (x && m_bfmeFlag)
		return;

	bfmeSend1011(a, b, c, d, e);
}

class BfmeHeld1011
{
public:
	virtual void bfmeRelease1011(int n);
};

struct BfmeSlot1011
{
	char m_bfmePad[0x14];
	BfmeHeld1011 *m_bfmeHeld;
};

class BfmeB1011
{
public:
	void bfmeGo1011B(void *a, BfmeHeld1011 *b);
	BfmeSlot1011 *bfmeFind1011B(void *a);
	void **bfmeAdd1011(void *a);

	BfmeSlot1011 *m_bfmeEnd;
};

void BfmeB1011::bfmeGo1011B(void *a, BfmeHeld1011 *b)
{
	BfmeSlot1011 *s = bfmeFind1011B(a);

	if (s != m_bfmeEnd) {
		BfmeHeld1011 *h = s->m_bfmeHeld;

		if (h)
			h->bfmeRelease1011(1);

		s->m_bfmeHeld = b;
		return;
	}

	*bfmeAdd1011(a) = b;
}
