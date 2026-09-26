// ?bfmeUpdateHJ@BfmeStateHJ@@QAEXD@Z
// partial score=0.98 date=2026-09-16
extern const float BfmeZeroRange;

class BfmeThingHJ
{
public:
	BfmeThingHJ *bfmeGetHJ();

	unsigned char m_bfmeHeadHJ[4];
	BfmeThingHJ *m_bfmeSubHJ;
	unsigned char m_bfmeGapHJ[8];
	void *m_bfmeValueHJ;
};

class BfmeOwnerHJ
{
public:
	unsigned char m_bfmeHeadHJ[8];
	void *m_bfmeArgHJ;
};

void bfmeCallHJ(void *a, void *b, void *c, void *d);

class BfmeStateHJ
{
public:
	void bfmeUpdateHJ(char on);

	unsigned char m_bfmeHeadHJ[4];
	BfmeThingHJ *m_bfme04HJ;
	unsigned char m_bfmeGap0HJ[4];
	BfmeOwnerHJ *m_bfme0cHJ;
	char m_bfme10HJ;
	unsigned char m_bfmePadHJ[3];
	int m_bfme14HJ;
	float m_bfme18HJ;
};

static __forceinline BfmeThingHJ *bfmeDerefHJ(BfmeThingHJ *p)
{
	if (p->m_bfmeSubHJ != 0)
		return p->m_bfmeSubHJ->bfmeGetHJ();

	return p;
}

void BfmeStateHJ::bfmeUpdateHJ(char on)
{
	if (m_bfme18HJ != BfmeZeroRange && on == 0)
	{
		volatile BfmeStateHJ *vv = this;

		vv->m_bfme18HJ = 0;
		vv->m_bfme14HJ = 0;

		BfmeThingHJ *p = vv->m_bfme04HJ;
		BfmeThingHJ *r;

		if (p == 0)
			r = 0;
		else
			r = bfmeDerefHJ(p);

		void *v = r->m_bfmeValueHJ;
		void *a = vv->m_bfme0cHJ->m_bfmeArgHJ;
		void * volatile home = v;

		bfmeCallHJ(a, v, v, v);
	}
	else if (m_bfme10HJ == 0 && on != 0)
	{
		m_bfme18HJ = 1.0f;
		m_bfme14HJ = 0;
	}
}
