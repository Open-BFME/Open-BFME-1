// Open-BFME5 conversions.

struct BfmeRecA980
{
	char m_bfmePad[0x2c];
	int m_bfmeVal;
};

struct BfmeRecB980
{
	char m_bfmePad[0x34];
	int m_bfmeVal;
};

class BfmeUseA980
{
public:
	void *bfmeApply980A(int a, int b);
};

class BfmeUseB980
{
public:
	void *bfmeApply980B(int a, int b);
};

class BfmeFindA980
{
public:
	BfmeUseA980 *bfmeFind980A(BfmeRecA980 *r);
};

class BfmeFindB980
{
public:
	BfmeUseB980 *bfmeFind980B(BfmeRecB980 *r);
};

extern BfmeFindA980 *g_bfmeFindA980;
extern BfmeFindB980 *g_bfmeFindB980;

class BfmeA980
{
public:
	void *bfmeGo980A(int a);
	BfmeRecA980 *bfmeMake980A(int a);

	char m_bfmePad[0x10];
	int m_bfmeSlot;
};

void *BfmeA980::bfmeGo980A(int a)
{
	BfmeRecA980 *r = bfmeMake980A(a);

	if (r) {
		int slot = m_bfmeSlot;
		BfmeUseA980 *u = g_bfmeFindA980->bfmeFind980A(r);

		if (u)
			return u->bfmeApply980A(slot, r->m_bfmeVal);
	}

	return 0;
}

class BfmeB980
{
public:
	void *bfmeGo980B(int a);
	BfmeRecB980 *bfmeMake980B(int a);

	char m_bfmePad[0x10];
	int m_bfmeSlot;
};

void *BfmeB980::bfmeGo980B(int a)
{
	BfmeRecB980 *r = bfmeMake980B(a);

	if (r) {
		int slot = m_bfmeSlot;
		BfmeUseB980 *u = g_bfmeFindB980->bfmeFind980B(r);

		if (u)
			return u->bfmeApply980B(slot, r->m_bfmeVal);
	}

	return 0;
}

class BfmeYC980
{
public:
	virtual void bfmeRun980C(int b);
};

class BfmeMgrC980
{
public:
	virtual void bfmeVM0980();
	virtual void bfmeVM1980();
	virtual void bfmeVM2980();
	virtual void bfmeVM3980();
	virtual void bfmeVM4980();
	virtual void bfmeVM5980();
	virtual void bfmeVM6980();
	virtual void bfmeVM7980();
	virtual void bfmeVM8980();
	virtual void bfmeVM9980();
	virtual void bfmeVM10980();
	virtual void bfmeVM11980();
	virtual void bfmeVM12980();
	virtual void bfmeVM13980();
	virtual void bfmeVM14980();
	virtual void bfmeVM15980();
	virtual void bfmeVM16980();
	virtual void bfmeVM17980();
	virtual void bfmeVM18980();
	virtual void bfmeVM19980();
	virtual void bfmeVM20980();
	virtual void bfmeVM21980();
	virtual void bfmeVM22980();
	virtual void bfmeVM23980();
	virtual void bfmeVM24980();
	virtual void bfmeVM25980();
	virtual BfmeYC980 *bfmeMake980C();
};

struct BfmeXC980
{
	char m_bfmePad[0x1fc];
	BfmeMgrC980 *m_bfmeMgr;
};

struct BfmeArgC980
{
	char m_bfmePad[8];
	int m_bfmeKey;
};

class BfmeLookC980
{
public:
	BfmeXC980 *bfmeFind980C(int k);
};

extern BfmeLookC980 *g_bfmeLookC980;

void __stdcall bfmeGo980C(BfmeArgC980 *a, int b)
{
	BfmeXC980 *x = g_bfmeLookC980->bfmeFind980C(a->m_bfmeKey);

	if (!x)
		return;

	BfmeMgrC980 *m = x->m_bfmeMgr;

	if (!m)
		return;

	m->bfmeMake980C()->bfmeRun980C(b);
}
