// Open-BFME5 conversions.

struct BfmeSlotJA;

class BfmeHookJA
{
public:
	BfmeSlotJA *bfmeCallJA();
};

struct BfmeSlotJA
{
	char m_bfmePad[4];
	BfmeHookJA *m_bfmeHook;
	char m_bfmePad2[0xc4];
	unsigned int m_bfmeBits;
};

class BfmeSub916C
{
public:
	void bfmeDo916C(void *a);
};

class BfmeThing916C
{
public:
	void bfmeGo916C(void *a);
	int m_bfmePad;
	BfmeSlotJA *m_bfmeSlot;
	char m_bfmePad2[0x3a8];
	BfmeSub916C *m_bfmeSub;
};

void BfmeThing916C::bfmeGo916C(void *a)
{
	BfmeSub916C *s = m_bfmeSub;
	if (!s)
		return;
	BfmeSlotJA *x = m_bfmeSlot;
	if (x) {
		BfmeHookJA *h = x->m_bfmeHook;
		if (h)
			x = h->bfmeCallJA();
	}
	if (!(x->m_bfmeBits & 0x100000))
		s->bfmeDo916C(a);
}

class BfmeSub916D
{
public:
	virtual void bfmeSlot91600();
	virtual void bfmeSlot91601();
	virtual void bfmeSlot91602();
	virtual void bfmeSlot91603();
	virtual void bfmeSlot91604();
	virtual void bfmeSlot91605();
	virtual void bfmeSlot91606();
	virtual void bfmeSlot91607();
	virtual void bfmeSlot91608();
	virtual void bfmeSlot91609();
	virtual void bfmeSlot91610();
	virtual void bfmeSlot91611();
	virtual void bfmeSlot91612();
	virtual void bfmeSlot91613();
	virtual void bfmeSlot91614();
	virtual void bfmeSlot91615();
	virtual void bfmeSlot91616();
	virtual void bfmeSlot91617();
	virtual void bfmeSlot91618();
	virtual void bfmeSlot91619();
	virtual void bfmeSlot91620();
	virtual void bfmeSlot91621();
	virtual void bfmeSlot91622();
	virtual void bfmeSlot91623();
	virtual void bfmeSlot91624();
	virtual void bfmeSlot91625();
	virtual void bfmeSlot91626();
	virtual void bfmeSlot91627();
	virtual void bfmeSlot91628();
	virtual void bfmeSlot91629();
	virtual void bfmeSlot91630();
	virtual void bfmeSlot91631();
	virtual void bfmeSlot91632();
	virtual void bfmeSlot91633();
	virtual void bfmeSlot91634();
	virtual void bfmeSlot91635();
	virtual void bfmeSlot91636();
	virtual void bfmeSlot91637();
	virtual void bfmeSlot91638();
	virtual void bfmeSlot91639();
	virtual void bfmeSlot91640();
	virtual void bfmeSlot91641();
	virtual void bfmeSlot91642();
	virtual void bfmeSlot91643();
	virtual void bfmeSlot91644();
	virtual void bfmeSlot91645();
	virtual void bfmeSlot91646();
	virtual void bfmeSlot91647();
	virtual void bfmeSlot91648();
	virtual void bfmeSlot91649();
	virtual void bfmeSlot91650();
	virtual void bfmeSlot91651();
	virtual void bfmeSlot91652();
	virtual void bfmeSlot91653();
	virtual void bfmeSlot91654();
	virtual void bfmeSlot91655();
	virtual void bfmeSlot91656();
	virtual void bfmeSlot91657();
	virtual void bfmeSlot91658();
	virtual void bfmeSlot91659();
	virtual void bfmeSlot91660();
	virtual void bfmeSlot91661();
	virtual void bfmeSlot91662();
	virtual void bfmeSlot91663();
	virtual void bfmeSlot91664();
	virtual void bfmeSlot91665();
	virtual void bfmeSlot91666();
	virtual void bfmeSlot91667();
	virtual void bfmeSlot91668();
	virtual void bfmeSlot91669();
	virtual void bfmeSlot91670();
	virtual void bfmeSlot91671();
	virtual void bfmeSlot91672();
	virtual void bfmeSlot91673();
	virtual void bfmeSlot91674();
	virtual void bfmeSlot91675();
	virtual void bfmeSlot91676();
	virtual void bfmeSlot91677();
	virtual void bfmeSlot91678();
	virtual void bfmeSlot91679();
	virtual void bfmeSlot91680();
	virtual void bfmeSlot91681();
	virtual void bfmeSlot91682();
	virtual void bfmeSlot91683();
	virtual void bfmeSlot91684();
	virtual void bfmeSlot91685();
	virtual void bfmeVirt916D(void *a);
};

class BfmeTail916D
{
public:
	void bfmeCall916D(void *a);
};

class BfmeThing916D
{
public:
	void bfmeGo916D(void *a);
	char m_bfmePad[0x90];
	unsigned char m_bfmeBits;
	char m_bfmePad2[0x16b];
	BfmeSub916D *m_bfmeSub;
	char m_bfmePad3[0x64];
	BfmeTail916D m_bfmeTail;
};

void BfmeThing916D::bfmeGo916D(void *a)
{
	if (m_bfmeBits & 1)
		return;
	BfmeSub916D *s = m_bfmeSub;
	if (s)
		s->bfmeVirt916D(a);
	m_bfmeTail.bfmeCall916D(a);
}
