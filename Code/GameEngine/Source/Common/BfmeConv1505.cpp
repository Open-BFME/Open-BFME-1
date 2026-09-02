// Open-BFME5 conversions.

struct BfmeRectVND
{
	char m_bfmePad00[0x50];
	float m_bfme50;
	float m_bfme54;
};

class BfmeScaleVND
{
public:
	virtual void bfmeSlot0VND();
	virtual void bfmeSlot1VND();
	virtual void bfmeSlot2VND();
	virtual void bfmeSlot3VND();
	virtual void bfmeSlot4VND();
	virtual void bfmeSlot5VND();
	virtual float bfmeScaleVND();
};

struct BfmeOwnerVND
{
	char m_bfmePad000[0x200];
	BfmeScaleVND *m_bfme200;
};

struct BfmeSubVND
{
	char m_bfmePad00[0x38];
	int m_bfme38;
	float m_bfme3c;
};

static const int &bfmeMaxVND(const int &a, const int &b)
{
	return a > b ? a : b;
}

class BfmeThingVND
{
public:
	int bfmeCalcVND(const BfmeRectVND *r);
};

int BfmeThingVND::bfmeCalcVND(const BfmeRectVND *r)
{
	int n1 = (int)(r->m_bfme50 - r->m_bfme54);
	BfmeOwnerVND *o = *(BfmeOwnerVND **)((char *)this - 0x1c);
	BfmeScaleVND *sc = o->m_bfme200;
	float f = (float)n1 / sc->bfmeScaleVND();
	BfmeSubVND *s = *(BfmeSubVND **)((char *)this - 0x20);
	int n3 = 1;
	int n2 = (int)(f * s->m_bfme3c) + s->m_bfme38;

	return bfmeMaxVND(n2, n3);
}
