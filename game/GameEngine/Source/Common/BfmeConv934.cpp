// Open-BFME5 conversions.

struct BfmeSub934A
{
	int m_bfmeVal;
};

class BfmeOther934A
{
public:
	void bfmeCall934A(BfmeSub934A *s);
};

class BfmeThing934A
{
public:
	void bfmeGo934A(BfmeOther934A *o, void *b);
	char m_bfmePad[0xb4];
	BfmeSub934A m_bfmeSub;
};

void BfmeThing934A::bfmeGo934A(BfmeOther934A *o, void *b)
{
	o->bfmeCall934A(&m_bfmeSub);
}

void __stdcall bfmeCall934B(void *a, int f, int g);

void __stdcall bfmeGo934B(void *a)
{
	bfmeCall934B(a, 0, 1);
}

class BfmeThing934C;

class BfmeThing934C
{
public:
	int bfmeGo934C();
	char m_bfmePad[0x1f0];
	void (*m_bfmeFn)(BfmeThing934C *t);
};

int BfmeThing934C::bfmeGo934C()
{
	void (*fn)(BfmeThing934C *) = m_bfmeFn;
	if (fn) {
		fn(this);
		return 1;
	}
	return 0;
}

class BfmeNode934D
{
public:
	void bfmeCall934D();
	char m_bfmePad[0x14];
	BfmeNode934D *m_bfmeNext;
};

class BfmeThing934D
{
public:
	void bfmeGo934D();
	char m_bfmePad[0x28];
	BfmeNode934D *m_bfmeHead;
};

void BfmeThing934D::bfmeGo934D()
{
	BfmeNode934D *n = m_bfmeHead;
	while (n) {
		n->bfmeCall934D();
		n = n->m_bfmeNext;
	}
}

class BfmeGlob932D
{
public:
	int bfmeCount932D(void *a, int f);
};

class BfmeThing934E
{
public:
	char bfmeGo934E(void *a);
};

char BfmeThing934E::bfmeGo934E(void *a)
{
	int r = ((BfmeGlob932D *)this)->bfmeCount932D(a, 0);
	return (char)(r > 0);
}

struct BfmeSlot934F
{
	int m_bfmeVal;
};

class BfmeOther934F
{
public:
	void bfmeCall934F(BfmeSlot934F *a, BfmeSlot934F *b);
};

class BfmeThing934F
{
public:
	void bfmeGo934F(BfmeOther934F *o);
	char m_bfmePad[0x74];
	BfmeSlot934F m_bfmeA;
	char m_bfmePad2[8];
	BfmeSlot934F m_bfmeB;
};

void BfmeThing934F::bfmeGo934F(BfmeOther934F *o)
{
	o->bfmeCall934F(&m_bfmeA, &m_bfmeB);
}

class BfmeThing934G
{
public:
	int bfmeGo934G();
	int bfmeOne934G();
	int bfmeTwo934G();
};

int BfmeThing934G::bfmeGo934G()
{
	int a = bfmeOne934G();
	return bfmeTwo934G() + a;
}
