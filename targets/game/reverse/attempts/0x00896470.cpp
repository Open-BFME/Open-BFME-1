// ?bfmeRva00896470@@YAXVBfmeRefHolder@@@Z
// partial score=1.0 date=2026-10-10
// cl: /EHsc


extern void (*TheBfmeFree)(void *p, unsigned int bytes);

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA(void);

	void operator delete(void *p, unsigned int bytes) { TheBfmeFree(p, bytes); }

private:
	char m_bfmePad[0x18];
};

class BfmeRefHolder;

class BfmeTracker4310
{
public:
	void bfmeSubmit4310(BfmeRefHolder obj);
};

extern BfmeTracker4310 *g_bfmeTracker4310;		// retail 0x013377F8

extern int g_bfme1017I;				// retail 0x013377DC

class BfmeStrVKI;
class Gen_uw_00893e70;
extern Gen_uw_00893e70 *g_rva00893e70Receiver;		// retail 0x013377F0

class Gen_uw_00893e70
{
public:
	void bfmeBuild893E70(const BfmeStrVKI &arg, int a, int b, int c);
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

// Ownership guide: Open BFME 2 Code/GameEngine/Source/Common/Bfme5ThirtyFour.cpp.
void __cdecl bfmeRva00896470(BfmeRefHolder obj)
{


	g_bfmeTracker4310->bfmeSubmit4310(obj);

	if (g_bfme1017I)
	{
		const BfmeStrVKI *string = (const BfmeStrVKI *)((char *)obj.m_obj + 4);
		g_rva00893e70Receiver->bfmeBuild893E70(*string, 1, 3, 2);
	}
}
