// cl: /O2 /GR- /EHsc- /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
// BfmeObjEBJ only ever receives the INI* receiver of INI::initFromINI, so the
// call below goes through the real header rather than a stand-in member whose
// name nothing defines.
#include "Common/INI/INI.h"

class BfmeObjEBJ;

extern "C" unsigned char bfmeStrEBJ[];

void __stdcall bfmeGoEBJ(BfmeObjEBJ *o, void *b)
{
	reinterpret_cast<INI *>(o)->initFromINI(b, (const FieldParse *)bfmeStrEBJ);
}

class BfmeObjEBK
{
public:
	void bfmeOneEBK(void *x, int n);
	void bfmeTwoEBK(void *x, void *b);
};

extern void *g_bfmeXEBK;

void __stdcall bfmeGoEBKa(BfmeObjEBK *o)
{
	o->bfmeOneEBK(g_bfmeXEBK, 0);
}

void __stdcall bfmeGoEBKb(BfmeObjEBK *o, void *b)
{
	o->bfmeTwoEBK(g_bfmeXEBK, b);
}

class BfmeObjEBL
{
public:
	void bfmeCallEBL(void *a, void *b);
	void *m_bfmeA;
	void *m_bfmeB;
};

extern BfmeObjEBL g_bfmeObjEBL;

void bfmeGoEBL()
{
	g_bfmeObjEBL.bfmeCallEBL(g_bfmeObjEBL.m_bfmeA, g_bfmeObjEBL.m_bfmeB);
}

char bfmeCmpEBMa(void *a, void *b);
char bfmeCmpEBMb(void *a, void *b);

bool bfmeGoEBMa(void *a, void *b)
{
	return bfmeCmpEBMa(a, b) == 0;
}

bool bfmeGoEBMb(void *a, void *b)
{
	return bfmeCmpEBMb(a, b) == 0;
}

struct BfmeSubEBN
{
	unsigned char m_bfmeHead[0x20];
	char m_bfmeC;
	unsigned char m_bfmePad[3];
	void *m_bfmeP;
};

class BfmeObjEBN
{
public:
	BfmeSubEBN *bfmeGetEBN();
};

void *bfmeGoEBNa(BfmeObjEBN *o)
{
	if (!o)
		return 0;
	BfmeSubEBN *s = o->bfmeGetEBN();
	if (!s)
		return 0;
	return s->m_bfmeP;
}

char bfmeGoEBNb(BfmeObjEBN *o)
{
	if (!o)
		return 0;
	BfmeSubEBN *s = o->bfmeGetEBN();
	if (!s)
		return 0;
	return s->m_bfmeC;
}
