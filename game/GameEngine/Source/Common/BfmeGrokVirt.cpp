// cl: /O2

struct BfmeObjWJ
{
	virtual void *d0();
	virtual void *d1();
	virtual void *d2();
	virtual void *d3();
	virtual unsigned char v4();
	virtual void *d5();
	virtual void *d6();
	virtual void *d7();
	virtual void *d8();
	virtual void *d9();
	virtual void v10(void *);
};

void __stdcall bfmePrepWJ(BfmeObjWJ *p);

void __stdcall bfmeVirtWJ(BfmeObjWJ *p)
{
	bfmePrepWJ(p);
	if (!p->v4())
	{
		unsigned char n[2];
		n[0] = 1;
		n[1] = 1;
		p->v10(n);
	}
}
