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
};

class BfmeThing932A
{
public:
	BfmeSlotJA *bfmeGo932A();
	char m_bfmePad[0x18];
	BfmeSlotJA *m_bfmeSlot;
};

BfmeSlotJA *BfmeThing932A::bfmeGo932A()
{
	BfmeSlotJA *s = m_bfmeSlot;
	if (s) {
		BfmeHookJA *h = s->m_bfmeHook;
		if (h)
			return h->bfmeCallJA();
		return s;
	}
	return 0;
}

class BfmeSub932C
{
public:
	unsigned char bfmeQuery932C();
};

class BfmeThing932C
{
public:
	int bfmeGo932C();
	char m_bfmePad[0x24];
	BfmeSub932C *m_bfmeSub;
};

int BfmeThing932C::bfmeGo932C()
{
	BfmeSub932C *s = m_bfmeSub;
	if (s)
		return s->bfmeQuery932C();
	return 0;
}

class BfmeGlob932D
{
public:
	int bfmeCount932D(void *a, int f);
};

extern BfmeGlob932D *g_bfme932GlobD;

class BfmeThing932D
{
public:
	char bfmeGo932D();
	int m_bfmePad;
	void *m_bfmeP;
};

char BfmeThing932D::bfmeGo932D()
{
	int r = g_bfme932GlobD->bfmeCount932D(m_bfmeP, 0);
	return (char)(r > 0);
}

class BfmeThing932E
{
public:
	void bfmeGo932E();
	int bfmeTest932E();
	void bfmeTail932E();
};

void BfmeThing932E::bfmeGo932E()
{
	if (!bfmeTest932E())
		bfmeTail932E();
}

