// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
#include "dx8wrapper.h"

// Open-BFME5 conversions.

void __stdcall bfmeElem936B(void *p);
void __stdcall bfmeVecDtor936B(void *p, unsigned int size, int count, void (__stdcall *dtor)(void *));

class BfmeThing936B
{
public:
	void bfmeGo936B();
};

void BfmeThing936B::bfmeGo936B()
{
	bfmeVecDtor936B(this, 4, 0x80, bfmeElem936B);
}

struct BfmeVt936C
{
	char m_bfmePad[0x14];
	void (__stdcall *m_bfmeFn)(void *o);
};

struct BfmeObj936C
{
	BfmeVt936C *m_bfmeVt;
};

extern int g_bfme936Count;

void bfmeGo936C(void)
{
	BfmeObj936C *p = reinterpret_cast<BfmeObj936C *>(DX8Wrapper::_Get_D3D_Device8());
	p->m_bfmeVt->m_bfmeFn(p);
	++g_bfme936Count;
}

void bfmeCall936F(int f);

class BfmeThing936F
{
public:
	void bfmeGo936F();
	char m_bfmePad[0x60];
	unsigned int m_bfmeCount;
};

void BfmeThing936F::bfmeGo936F()
{
	--*(unsigned short *)&m_bfmeCount;
	if ((m_bfmeCount & 0xffff) == 0)
		bfmeCall936F(0);
}

extern void *g_bfme936GlobG;

class BfmeThing936G
{
public:
	BfmeThing936G *bfmeGo936G();
	void bfmeInit936G();
};

BfmeThing936G *BfmeThing936G::bfmeGo936G()
{
	if (!g_bfme936GlobG)
		bfmeInit936G();
	return this;
}
