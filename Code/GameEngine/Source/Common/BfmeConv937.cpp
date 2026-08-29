// Open-BFME5 conversions.

extern char g_bfme937Obj[];
void bfmeCall937A(char *p);

int bfmeGo937A(void)
{
	bfmeCall937A(g_bfme937Obj);
	return 0;
}

class BfmeSub937B
{
public:
	void bfmeCall937B(void *r);
};

class BfmeThing937B
{
public:
	virtual void *bfmeVirt937B();
	void bfmeGo937B();
	char m_bfmePad[0x10];
	BfmeSub937B *m_bfmeSub;
};

void BfmeThing937B::bfmeGo937B()
{
	void *r = bfmeVirt937B();
	m_bfmeSub->bfmeCall937B(r);
}

void __stdcall bfmeThrow937C(unsigned int code);

class BfmeThing937C
{
public:
	void *bfmeGo937C();
	void *m_bfmeP;
};

void *BfmeThing937C::bfmeGo937C()
{
	if (m_bfmeP == 0)
		bfmeThrow937C(0x80004003);
	return m_bfmeP;
}

class BfmeItem937E
{
public:
	virtual void bfmeVirt937E();
};

class BfmeThing937E
{
public:
	void bfmeGo937E(BfmeItem937E *item);
	int m_bfmeCount;
	int m_bfmePad;
	BfmeItem937E **m_bfmeArr;
};

void BfmeThing937E::bfmeGo937E(BfmeItem937E *item)
{
	int n = m_bfmeCount;
	m_bfmeArr[n] = item;
	++m_bfmeCount;
	item->bfmeVirt937E();
}
