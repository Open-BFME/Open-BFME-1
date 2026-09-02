// cl: /O2 /Ob0

struct BfmeVecCC0
{
	int a;
	int b;
	int c;
};

class BfmeGlobCC0
{
public:
	virtual int v0();
	virtual int v1();
	virtual int v2();
	virtual int v3();
	virtual int v4();
	virtual int v5();
	virtual int v6();
	virtual int v7();
	virtual int v8();
	virtual int v9();
	virtual bool bfmePredCC0();
	virtual int v11();
	virtual int v12();
	virtual BfmeVecCC0 *bfmeGetCC0(BfmeVecCC0 *);
};

extern BfmeGlobCC0 *g_bfmeGlobCC0;

class BfmeThingCC0
{
public:
	BfmeVecCC0 *bfmeFetchCC0();
	char m_pad[0x90];
	BfmeVecCC0 m_v;
};

BfmeVecCC0 *BfmeThingCC0::bfmeFetchCC0()
{
	if (g_bfmeGlobCC0)
	{
		if (g_bfmeGlobCC0->bfmePredCC0())
		{
			BfmeVecCC0 tmp;
			BfmeVecCC0 *p = g_bfmeGlobCC0->bfmeGetCC0(&tmp);
			BfmeVecCC0 *d = &m_v;
			d->a = p->a;
			d->b = p->b;
			d->c = p->c;
			return d;
		}
	}
	return 0;
}
