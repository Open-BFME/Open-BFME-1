// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Iinputs/reference/shims/player /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Open-BFME5 conversions.

#include "Common/Player.h"

struct BfmeNodeLC
{
	char m_bfmePad0[8];
	void *m_bfmeP;
	char m_bfmePad1[0x14];
	char m_bfmeFlag;
};

class BfmeKeyLC
{
public:
	BfmeNodeLC *bfmeFindLC();
	void bfmeUse926B(BfmeNodeLC *o);
};

void bfmeCall926A(void *p, void *b, void *a, int f);

class BfmeThing926A
{
public:
	void bfmeGo926A(void *a, void *b);
	BfmeKeyLC *m_bfmeKey;
};

void BfmeThing926A::bfmeGo926A(void *a, void *b)
{
	BfmeKeyLC *k = m_bfmeKey;
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		bfmeCall926A(o->m_bfmeP, b, a, 0);
	}
}

BfmeNodeLC *bfmeMake926B(void);

void bfmeGo926B(BfmeKeyLC *k, char v)
{
	if (!k)
		return;
	BfmeNodeLC *o = k->bfmeFindLC();
	if (!o)
		o = bfmeMake926B();
	o->m_bfmeFlag = v;
	k->bfmeUse926B(o);
}

class BfmeTail926C
{
public:
	void bfmeTail926C();
	int bfmeTail926D(int f);
};

struct BfmeObj926C
{
	char m_bfmePad[0x22c];
	BfmeTail926C *m_bfmeUse;
};

class BfmeKey926C
{
public:
	BfmeObj926C *bfmeFind926C();
};

class BfmeThing926D
{
public:
	int bfmeGo926D(void *a);
};

int BfmeThing926D::bfmeGo926D(void *a)
{
	BfmeKey926C *k = *(BfmeKey926C **)((char *)this - 0x18);
	BfmeObj926C *o = k->bfmeFind926C();
	if (o) {
		BfmeTail926C *u = o->m_bfmeUse;
		if (u)
			return u->bfmeTail926D(0);
	}
	return 0;
}

