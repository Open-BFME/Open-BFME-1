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

// The retail call at 0x002AB0B0 targets the five-byte ILT thunk at 0x000044C1,
// whose address-derived identity is ?j_000044c1@@YAXXZ (functions.csv,
// game/gen_small/thunks_001.cpp).  Naming it as itself is what lets this
// object link; the stdcall shape and the pushed argument are unchanged.
extern void j_000044c1();

typedef void (__stdcall *BfmePrepWJ_t)(BfmeObjWJ *);

void __stdcall bfmeVirtWJ(BfmeObjWJ *p)
{
	union { void (__cdecl *raw)(); BfmePrepWJ_t prep; } call;
	call.raw = j_000044c1;
	call.prep(p);
	if (!p->v4())
	{
		unsigned char n[2];
		n[0] = 1;
		n[1] = 1;
		p->v10(n);
	}
}
