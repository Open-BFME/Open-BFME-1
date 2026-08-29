// Open-BFME5 conversions.

struct BfmeNodeLC
{
	char m_bfmeA;
	char m_bfmePad0[3];
	int m_bfmeB;
	char m_bfmePad1[4];
	unsigned int m_bfmeBits;
	unsigned short m_bfmeW;
	char m_bfmePad2[0x16];
	char m_bfmeC;
	char m_bfmePad3[3];
	int m_bfmeD;
};

class BfmeKeyLC
{
public:
	BfmeNodeLC *bfmeFindLC();
};

void bfmeGo924A(BfmeKeyLC *k, char v)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o)
			*((char *)&o->m_bfmeBits + 3) = (v == 0);
	}
}

int bfmeGo924B(BfmeKeyLC *k)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o && o->m_bfmeA)
			return o->m_bfmeB;
	}
	return 0x64;
}

int bfmeGo924C(BfmeKeyLC *k)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o && o->m_bfmeC)
			return o->m_bfmeD;
	}
	return 0;
}

void bfmeGo924D(BfmeKeyLC *k, unsigned int mask)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o) {
			unsigned int m = mask;
			o->m_bfmeBits = o->m_bfmeBits | m;
		}
	}
}

void bfmeGo924E(BfmeKeyLC *k, unsigned int mask)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o) {
			unsigned int m = ~mask;
			o->m_bfmeBits = o->m_bfmeBits & m;
		}
	}
}

void bfmeGo924F(BfmeKeyLC *k, unsigned short w)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o)
			o->m_bfmeW = w;
	}
}

class BfmeOne924G
{
public:
	void bfmeCall924G();
};

class BfmeTwo924G
{
public:
	virtual void bfmeSlot92400();
	virtual void bfmeSlot92401();
	virtual void bfmeSlot92402();
	virtual void bfmeSlot92403();
	virtual void bfmeSlot92404();
	virtual void bfmeTail924G();
};

extern BfmeOne924G *g_bfme924OneG;
extern BfmeTwo924G *g_bfme924TwoG;

void bfmeGo924G(void)
{
	if (g_bfme924OneG)
		g_bfme924OneG->bfmeCall924G();
	if (g_bfme924TwoG)
		g_bfme924TwoG->bfmeTail924G();
}
