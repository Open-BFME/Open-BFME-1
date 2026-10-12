// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /I.
// Retail 0x00896470, 142 bytes: submits a by-value ref-counted handle to the
// tracker singleton at 0x013377F8, then - when the flag at 0x013377DC is set -
// hands the object's string at +4 to the builder reached through the receiver
// at 0x013377F0.
// Both callees are still machine dumps, so each keeps the dump name the ledger
// already gives its body (0x00896390, 0x00895790) and is bound to the ABI view
// this call site proves through the function-pointer/member-pointer union idiom
// Rva00896060Owner.cpp uses; no new symbols.csv pin is invented here.
// Identity stays address-derived: no owning class name survives, and only the
// 0x00896540 / 0x008965B0 dump callers reach this body.

extern void (*TheBfmeBufferFree)(void *p, int bytes);

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA(void);

	void operator delete(void *p, unsigned int bytes) { TheBfmeBufferFree(p, bytes); }

private:
	char m_bfmePad[0x18];
};

class BfmeRefHolder
{
public:
	BfmeRefHolder(BfmeDropObjectA *obj) : m_obj(obj)
	{
		if (obj)
			++*(int *)obj;
	}

	BfmeRefHolder(const BfmeRefHolder &other) : m_obj(other.m_obj)
	{
		if (m_obj) ++*(int *)m_obj;
	}

	~BfmeRefHolder()
	{
		if (m_obj && --*(int *)m_obj == 0)
			delete m_obj;
	}

public:
	BfmeDropObjectA *m_obj;
};

class BfmeTracker4310
{
};

class BfmeStrVKI;

class Gen_uw_00893e70
{
};

extern BfmeTracker4310 *g_bfmeTracker4310;
extern int g_bfme1017I;
extern Gen_uw_00893e70 *g_rva013377F0;

extern void d_00896390();
extern void d_00895790();

typedef void (BfmeTracker4310::*Submit4310Call)(BfmeRefHolder);
__forceinline Submit4310Call Rva00896390Binding()
{
	union { void (*raw)(); Submit4310Call member; } fn;
	fn.raw = d_00896390;
	return fn.member;
}

typedef void (Gen_uw_00893e70::*Build893E70Call)(const BfmeStrVKI &, int, int, int);
__forceinline Build893E70Call Rva00895790Binding()
{
	union { void (*raw)(); Build893E70Call member; } fn;
	fn.raw = d_00895790;
	return fn.member;
}

// ?bfmeRva00896470@@YAXVBfmeRefHolder@@@Z
void __cdecl bfmeRva00896470(BfmeRefHolder obj)
{
	(g_bfmeTracker4310->*Rva00896390Binding())(obj);

	if (g_bfme1017I)
	{
		const BfmeStrVKI *string = (const BfmeStrVKI *)((char *)obj.m_obj + 4);
		(g_rva013377F0->*Rva00895790Binding())(*string, 1, 3, 2);
	}
}
