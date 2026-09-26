// ?bfmeRva00896470@@YAXPAVBfmeDropObjectA@@@Z
// partial score=0.34 date=2026-09-21
// cl: /EHsc

// Retail 0x00896470 mirrors the already-landed Gen_00895670 constructor's
// AddRef/DecRef+delete idiom (BfmeHolder95670.cpp: same 0x18-byte
// BfmeDropObjectA, same TheBfmeFree sized delete) with two extra manager
// calls sandwiched in between: an unconditional no-arg submit through the
// 0x013377F8 tracker and, when the 0x013377DC (g_bfme1017I) flag is set, a
// four-argument build call through the 0x013377F0 receiver on obj+4. No
// C++ emitter or owning class was previously recovered for either manager
// call, so both stay address-derived; only their target addresses (pinned
// through the already-matched gen_asm rows at 0x00896390/0x00895790) are
// proven.

extern void (*TheBfmeFree)(void *p, unsigned int bytes);

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA(void);

	void operator delete(void *p, unsigned int bytes) { TheBfmeFree(p, bytes); }

private:
	char m_bfmePad[0x18];
};

class BfmeTracker4310
{
public:
	void bfmeSubmit4310(void);
};

extern BfmeTracker4310 *g_bfmeTracker4310;		// retail 0x013377F8

extern int g_bfme1017I;				// retail 0x013377DC

class Gen_uw_00893e70;
extern Gen_uw_00893e70 *g_rva00893e70Receiver;		// retail 0x013377F0

class Gen_uw_00893e70
{
public:
	void bfmeBuild893E70(void *arg, int a, int b, int c);
};

class BfmeRefHolder
{
public:
	BfmeRefHolder(BfmeDropObjectA *obj) : m_obj(obj)
	{
		if (obj)
			++*(int *)obj;
	}

	~BfmeRefHolder()
	{
		if (m_obj && --*(int *)m_obj == 0)
			delete m_obj;
	}

private:
	BfmeDropObjectA *m_obj;
};

void __cdecl bfmeRva00896470(BfmeDropObjectA *obj)
{
	BfmeRefHolder holder(obj);

	g_bfmeTracker4310->bfmeSubmit4310();

	if (g_bfme1017I)
	{
		g_rva00893e70Receiver->bfmeBuild893E70((char *)obj + 4, 1, 3, 2);
	}
}
