// Open-BFME5 conversions.

int __stdcall bfmeCall940A(void *a);

int __stdcall bfmeGo940A(void *a)
{
	int r = bfmeCall940A(a);
	return r != 0;
}

class BfmeThing940B
{
public:
	char bfmeGo940B();
	void bfmeOne940B();
	void bfmeTwo940B();
};

char BfmeThing940B::bfmeGo940B()
{
	bfmeOne940B();
	bfmeTwo940B();
	return 0;
}

class BfmeSub940C
{
public:
	virtual void bfmeSlot940C00();
	virtual void bfmeSlot940C01();
	virtual void bfmeVirt940C();
};

class BfmeThing940C
{
public:
	void bfmeGo940C();
	void bfmeOne940C();
	char m_bfmePad[0x20];
	BfmeSub940C m_bfmeSub;
};

void BfmeThing940C::bfmeGo940C()
{
	bfmeOne940C();
	m_bfmeSub.bfmeVirt940C();
}

class BfmeRes940D
{
public:
	virtual void bfmeSlot940D00();
	virtual void bfmeSlot940D01();
	virtual void bfmeSlot940D02();
	virtual void bfmeSlot940D03();
	virtual void bfmeSlot940D04();
	virtual void bfmeSlot940D05();
	virtual void bfmeSlot940D06();
	virtual void bfmeSlot940D07();
	virtual void bfmeSlot940D08();
	virtual void bfmeSlot940D09();
	virtual void bfmeSlot940D10();
	virtual void bfmeSlot940D11();
	virtual void bfmeSlot940D12();
	virtual void bfmeSlot940D13();
	virtual void bfmeSlot940D14();
	virtual void bfmeSlot940D15();
	virtual void bfmeSlot940D16();
	virtual void bfmeVirt940D(int f);
};

class BfmeSrc940D
{
public:
	BfmeRes940D *bfmeFind940D();
};

class BfmeThing940D
{
public:
	void bfmeGo940D();
	char m_bfmePad[8];
	BfmeSrc940D *m_bfmeSrc;
};

void BfmeThing940D::bfmeGo940D()
{
	BfmeRes940D *r = m_bfmeSrc->bfmeFind940D();
	r->bfmeVirt940D(0);
}

class BfmeGlob940E
{
public:
	void bfmeCall940E(void *p);
};

extern BfmeGlob940E *g_bfme940GlobE;

class BfmeThing940E
{
public:
	int bfmeGo940E();
};

int BfmeThing940E::bfmeGo940E()
{
	void *p = *(void **)((char *)this - 8);
	g_bfme940GlobE->bfmeCall940E(p);
	return 0x3fffffff;
}

struct BfmeA940G
{
	char m_bfmePad[8];
	void *m_bfmeVal;
};

class BfmeB940G
{
public:
	void bfmeCall940G(void *v, int f);
};

class BfmeThing940G
{
public:
	void bfmeGo940G();
	char m_bfmePad[4];
	char m_bfmeFlag;
};

void BfmeThing940G::bfmeGo940G()
{
	BfmeA940G *a = *(BfmeA940G **)((char *)this - 0xc);
	m_bfmeFlag = 0;
	void *v = a->m_bfmeVal;
	BfmeB940G *b = *(BfmeB940G **)((char *)this - 8);
	b->bfmeCall940G(v, 2);
}

