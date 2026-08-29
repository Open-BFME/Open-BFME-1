// Open-BFME5 conversions.

struct BfmeNodeLC
{
	virtual void bfmeSlot92500();
	virtual void bfmeSlot92501();
	virtual void bfmeSlot92502();
	virtual void bfmeSlot92503();
	virtual void bfmeSlot92504();
	virtual void bfmeSlot92505();
	virtual void bfmeSlot92506();
	virtual void bfmeTail925B();
	char m_bfmePad0[4];
	void *m_bfmeP;
	char m_bfmePad1[0x10];
	unsigned short m_bfmeU;
	unsigned short m_bfmeV;
	char m_bfmePad2[0xc];
	void *m_bfmeQ;
	char m_bfmePad3[4];
	void *m_bfmeR;
};

class BfmeKeyLC
{
public:
	BfmeNodeLC *bfmeFindLC();
};

void *bfmeGo925A(BfmeKeyLC *k)
{
	BfmeNodeLC *o = k->bfmeFindLC();
	if (o) {
		void *p = o->m_bfmeQ;
		if (p)
			return p;
	}
	return 0;
}

void bfmeGo925B(BfmeKeyLC *k)
{
	if (!k)
		return;
	BfmeNodeLC *o = k->bfmeFindLC();
	if (!o)
		return;
	o->bfmeTail925B();
}

void bfmeCall925C(void *p);

class BfmeThing925C
{
public:
	void bfmeGo925C();
	BfmeKeyLC *m_bfmeKey;
};

void BfmeThing925C::bfmeGo925C()
{
	BfmeKeyLC *k = m_bfmeKey;
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		bfmeCall925C(o->m_bfmeP);
	}
}

class BfmeThing925D
{
public:
	void bfmeGo925D(void *v);
	BfmeKeyLC *m_bfmeKey;
};

void BfmeThing925D::bfmeGo925D(void *v)
{
	BfmeKeyLC *k = m_bfmeKey;
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		BfmeNodeLC *p = ((BfmeKeyLC *)o->m_bfmeP)->bfmeFindLC();
		p->m_bfmeR = v;
	}
}

int bfmeCall925E(void *p);

class BfmeThing925E
{
public:
	int bfmeGo925E();
	BfmeKeyLC *m_bfmeKey;
};

int BfmeThing925E::bfmeGo925E()
{
	BfmeKeyLC *k = m_bfmeKey;
	if (!k)
		return 0;
	BfmeNodeLC *o = k->bfmeFindLC();
	return bfmeCall925E(o->m_bfmeP);
}
