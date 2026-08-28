struct BfmeObjEVB
{
	virtual void bfmeV0();
	virtual void *bfmeGet1EVB();
	virtual void bfmeRun2EVB();
	virtual void bfmeRun3EVB();
};

class BfmeGlobEVB
{
public:
	BfmeObjEVB *bfmeFindEVB(void *k);
};

extern BfmeGlobEVB *g_bfmeObjEVB;

BfmeObjEVB *__cdecl bfmeCastEVB(void *a);
BfmeObjEVB *__cdecl bfmeCast2EVB(void *a);

void __stdcall bfmeGoEVBa(void *a)
{
	if (!a)
		return;
	BfmeObjEVB *o = bfmeCastEVB(a);
	if (!o)
		return;
	BfmeObjEVB *p = g_bfmeObjEVB->bfmeFindEVB(o->bfmeGet1EVB());
	if (!p)
		return;
	BfmeObjEVB *q = bfmeCast2EVB(p);
	if (!q)
		return;
	q->bfmeRun3EVB();
}

void __stdcall bfmeGoEVBb(void *a)
{
	if (!a)
		return;
	BfmeObjEVB *o = bfmeCastEVB(a);
	if (!o)
		return;
	BfmeObjEVB *p = g_bfmeObjEVB->bfmeFindEVB(o->bfmeGet1EVB());
	if (!p)
		return;
	BfmeObjEVB *q = bfmeCast2EVB(p);
	if (!q)
		return;
	q->bfmeRun2EVB();
}

void __stdcall bfmeGoEVBc(void *a)
{
	if (!a)
		return;
	BfmeObjEVB *o = bfmeCastEVB(a);
	if (!o)
		return;
	BfmeObjEVB *p = g_bfmeObjEVB->bfmeFindEVB(o->bfmeGet1EVB());
	if (!p)
		return;
	BfmeObjEVB *q = bfmeCast2EVB(p);
	if (!q)
		return;
	q->bfmeRun3EVB();
}

