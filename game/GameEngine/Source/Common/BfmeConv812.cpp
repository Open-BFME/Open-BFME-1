struct BfmeSubEHA
{
	char m_bfmeFlag;
	unsigned char m_bfmePad[3];
	void *m_bfmeP;
	void *m_bfmeQ;
};

class BfmeObjEHA
{
public:
	BfmeSubEHA *bfmeGetEHA();
};

void *bfmeGoEHAa(BfmeObjEHA *o)
{
	if (o)
	{
		BfmeSubEHA *s = o->bfmeGetEHA();
		if (s && s->m_bfmeFlag)
			return s->m_bfmeP;
	}
	return 0;
}

void *bfmeGoEHAb(BfmeObjEHA *o)
{
	if (o)
	{
		BfmeSubEHA *s = o->bfmeGetEHA();
		if (s && s->m_bfmeFlag)
			return s->m_bfmeQ;
	}
	return 0;
}

class BfmeSubEHBa
{
public:
	void bfmeDtorEHBa();
};

class BfmeSubEHBb
{
public:
	void bfmeDtorEHBb();
};

void __cdecl bfmeFreeEHB(void *p, unsigned int n);

struct BfmeThingEHBa
{
	unsigned char m_bfmeHead[4];
	BfmeSubEHBa m_bfmeSub;
};

void __stdcall bfmeGoEHBa(BfmeThingEHBa *o)
{
	o->m_bfmeSub.bfmeDtorEHBa();
	if (o)
		bfmeFreeEHB(o, 0x2c);
}

struct BfmeThingEHBb
{
	unsigned char m_bfmeHead[4];
	BfmeSubEHBb m_bfmeSub;
};

void __stdcall bfmeGoEHBb(BfmeThingEHBb *o)
{
	o->m_bfmeSub.bfmeDtorEHBb();
	if (o)
		bfmeFreeEHB(o, 0x34);
}

struct BfmeThingEHCa
{
	int bfmeGoEHCa(void *a, void *b, void *c);
	unsigned char m_bfmeHead[0x1e0];
	int (__cdecl *m_bfmeFn)(void *self, void *a, void *b, void *c);
};

int BfmeThingEHCa::bfmeGoEHCa(void *a, void *b, void *c)
{
	int (__cdecl *fn)(void *, void *, void *, void *) = m_bfmeFn;
	if (fn)
		return fn(this, a, b, c);
	return 0;
}

struct BfmeThingEHCb
{
	int bfmeGoEHCb(void *a, void *b, void *c);
	unsigned char m_bfmeHead[0x1e4];
	int (__cdecl *m_bfmeFn)(void *self, void *a, void *b, void *c);
};

int BfmeThingEHCb::bfmeGoEHCb(void *a, void *b, void *c)
{
	int (__cdecl *fn)(void *, void *, void *, void *) = m_bfmeFn;
	if (fn)
		return fn(this, a, b, c);
	return 0;
}

struct BfmeNodeEHD
{
	void bfmeRunEHDa();
	void bfmeRunEHDb();
	unsigned char m_bfmeHead[0x104];
	BfmeNodeEHD *m_bfmeNext;
};

class BfmeThingEHDa
{
public:
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual void bfmeV9();
	virtual void bfmeV10();
	virtual void bfmeV11();
	virtual BfmeNodeEHD *bfmeFirstEHD();
	void bfmeGoEHDa();
	void bfmeGoEHDb();
};

void BfmeThingEHDa::bfmeGoEHDa()
{
	for (BfmeNodeEHD *n = bfmeFirstEHD(); n; n = n->m_bfmeNext)
		n->bfmeRunEHDa();
}

void BfmeThingEHDa::bfmeGoEHDb()
{
	for (BfmeNodeEHD *n = bfmeFirstEHD(); n; n = n->m_bfmeNext)
		n->bfmeRunEHDb();
}

