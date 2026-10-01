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

// Retail: 0x012F0898 is EA's GameLogic *TheGameLogic (see
// game/GameEngine/Source/GameLogic/System/GameLogic.cpp). This TU only needs
// its 0x012F0898-facing view, so declare the canonical symbol and cast.
class GameLogic;
extern GameLogic *TheGameLogic;

BfmeObjEVB *__cdecl bfmeCastEVB(void *a);
BfmeObjEVB *__cdecl bfmeCast2EVB(void *a);

void __stdcall bfmeGoEVBa(void *a)
{
	if (!a)
		return;
	BfmeObjEVB *o = bfmeCastEVB(a);
	if (!o)
		return;
	BfmeObjEVB *p = ((BfmeGlobEVB *)TheGameLogic)->bfmeFindEVB(o->bfmeGet1EVB());
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
	BfmeObjEVB *p = ((BfmeGlobEVB *)TheGameLogic)->bfmeFindEVB(o->bfmeGet1EVB());
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
	BfmeObjEVB *p = ((BfmeGlobEVB *)TheGameLogic)->bfmeFindEVB(o->bfmeGet1EVB());
	if (!p)
		return;
	BfmeObjEVB *q = bfmeCast2EVB(p);
	if (!q)
		return;
	q->bfmeRun3EVB();
}

