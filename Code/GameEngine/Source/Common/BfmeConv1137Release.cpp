// cl: /DNDEBUG /MD /EHsc
// Open-BFME5 conversions.
// ghidra: FUN_00b23ac0 retail @ 0x00723AC0 size 117 (BfmeA1137's own resource
// release helper -- releases m_bfme70 (a COM-style interface pointer), then
// m_bfme68 (a manually inlined RefCountClass-style pointer), then m_bfme6c
// (the same texture-like reference item7's destructor also touches).
// Called by the destructor thunk at 0x000491C5 -- see BfmeConv1137Term.cpp.

void __cdecl W3DRadarResetLock();
char __cdecl bfmeUnlockVJR();

class BfmeTexRel1137
{
public:
	void Release_Ref();
};

class BfmeRefBase1137
{
public:
	virtual void bfmeVSlot0();
	int m_refcount;
};

struct BfmeIfaceVtbl1137
{
	void *pad0;
	void *pad1;
	void(__stdcall *Release)(void *self);
};

struct BfmeIface1137
{
	BfmeIfaceVtbl1137 *vtbl;
};

class W3DResourceResetGuard
{
public:
	W3DResourceResetGuard() { W3DRadarResetLock(); }
	~W3DResourceResetGuard() { bfmeUnlockVJR(); }
};

class BfmeA1137Release
{
public:
	void bfmeReleaseResources();
	char m_bfmePad[0x68];
	BfmeRefBase1137 *m_bfme68;
	BfmeTexRel1137 *m_bfme6c;
	BfmeIface1137 *m_bfme70;
};

void BfmeA1137Release::bfmeReleaseResources()
{
	W3DResourceResetGuard lock;

	BfmeTexRel1137 *t = m_bfme6c;
	if (t)
	{
		t->Release_Ref();
		m_bfme6c = 0;
	}

	BfmeIface1137 *u = m_bfme70;
	if (u)
		u->vtbl->Release(u);
	m_bfme70 = 0;

	BfmeRefBase1137 *r = m_bfme68;
	if (r)
	{
		if (--r->m_refcount == 0)
			r->bfmeVSlot0();
		m_bfme68 = 0;
	}
}
