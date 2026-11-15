// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
#include "dx8wrapper.h"

#include <new.h>

class Bfme5OwnerLink;
class Bfme5OwnerList
{
public:
	void bfmeClear(void);
	Bfme5OwnerLink *m_bfmeNode;
};

struct BfmeThingELAa
{
	void bfmeGoELAa();
	void *m_bfmeP;
};

void BfmeThingELAa::bfmeGoELAa()
{
	reinterpret_cast<Bfme5OwnerList *>(this)->bfmeClear();
	void *p = m_bfmeP;
	if (p)
		::operator delete(p);
}

class BfmeObjELB
{
public:
	void bfmeTailELB(int n);
};

extern BfmeObjELB *g_bfmeObjELB;

void __stdcall bfmeGoELB(int unused)
{
	BfmeObjELB *o = g_bfmeObjELB;
	if (o)
		o->bfmeTailELB(1);
}

struct BfmeThingDYA
{
	void bfmeGoDYA(void *a);
	unsigned char m_bfmeHead[0x20];
	unsigned char m_bfmeFlags;
	unsigned char m_bfmePadA[3];
	int m_bfmeX;
	void *m_bfmeA;
	int m_bfmeT;
};

struct BfmeSubELC
{
	unsigned char m_bfmeHead[0x20];
	unsigned char m_bfmeFlags;
};

struct BfmeThingELC
{
	void bfmeGoELC(int unused);
	unsigned char m_bfmeHead[0x10];
	BfmeSubELC *m_bfmeS;
};

void BfmeThingELC::bfmeGoELC(int unused)
{
	BfmeSubELC *s = m_bfmeS;
	if (s->m_bfmeFlags & 1)
		reinterpret_cast<BfmeThingDYA *>(s)->bfmeGoDYA(
			reinterpret_cast<void *>(0x1f4));
}


struct BfmeThingELDa
{
	void bfmeGoELDa(void *a);
	void *m_bfmeP;
};

void BfmeThingELDa::bfmeGoELDa(void *a)
{
	void *old = m_bfmeP;
	if (a != old)
	{
		::operator delete(old);
		m_bfmeP = a;
	}
}

struct BfmeThingELDb
{
	void bfmeGoELDb(void *a);
	void *m_bfmeP;
};

void BfmeThingELDb::bfmeGoELDb(void *a)
{
	void *old = m_bfmeP;
	if (a != old)
	{
		::operator delete(old);
		m_bfmeP = a;
	}
}

class GameWindow;
class LANGameInfo;
void LANDisplayGameList(GameWindow *gameListbox, LANGameInfo *gameList);

struct BfmeThingELE
{
	void bfmeGoELE(void *a);
	unsigned char m_bfmeHeadA[0x3d];
	char m_bfmeFlag;
	unsigned char m_bfmeHeadB[0x26];
	void *m_bfmeP;
};

void BfmeThingELE::bfmeGoELE(void *a)
{
	if (m_bfmeFlag)
		LANDisplayGameList(static_cast<GameWindow *>(m_bfmeP),
			static_cast<LANGameInfo *>(a));
}

struct BfmeThingELF
{
	void bfmeGoELF(void *a);
	unsigned char m_bfmeHead[4];
	void (__cdecl *m_bfmeFn)(void *ctx, void *a);
	void *m_bfmeCtx;
};

void BfmeThingELF::bfmeGoELF(void *a)
{
	void (__cdecl *fn)(void *, void *) = m_bfmeFn;
	if (fn)
		fn(m_bfmeCtx, a);
}

class BfmeSubELGa;
class Rva006DF050
{
public:
	void eraseKey(int key);
};

struct BfmeThingELGa
{
	void bfmeGoELGa(void *a);
	unsigned char m_bfmeHead[0x30b4];
	BfmeSubELGa *m_bfmeS;
};

void BfmeThingELGa::bfmeGoELGa(void *a)
{
	BfmeSubELGa *s = m_bfmeS;
	if (s && a)
		reinterpret_cast<Rva006DF050 *>(s)->eraseKey(
			reinterpret_cast<int>(a));
}

class BfmeSubELGb
{
public:
	void bfmeTailELGb(void *a);
};

struct BfmeThingELGb
{
	void bfmeGoELGb(void *a);
	unsigned char m_bfmeHead[0x10];
	BfmeSubELGb *m_bfmeS;
};

void BfmeThingELGb::bfmeGoELGb(void *a)
{
	BfmeSubELGb *s = m_bfmeS;
	if (s && a)
		s->bfmeTailELGb(a);
}

struct BfmeObjELH;

struct BfmeVtblELH
{
	void (__stdcall *m_bfmeF0)(void *o, void *a);
	void (__stdcall *m_bfmeF1)(void *o, void *a);
	void (__stdcall *m_bfmeF2)(void *o, void *a);
	void (__stdcall *m_bfmeF3)(void *o, void *a);
	void (__stdcall *m_bfmeF4)(void *o, void *a);
	void (__stdcall *m_bfmeF5)(void *o, void *a);
	void (__stdcall *m_bfmeF6)(void *o, void *a);
	void (__stdcall *m_bfmeF7)(void *o, void *a);
	void (__stdcall *m_bfmeF8)(void *o, void *a);
	void (__stdcall *m_bfmeF9)(void *o, void *a);
	void (__stdcall *m_bfmeF10)(void *o, void *a);
	void (__stdcall *m_bfmeF11)(void *o, void *a);
	void (__stdcall *m_bfmeF12)(void *o, void *a);
	void (__stdcall *m_bfmeF13)(void *o, void *a);
	void (__stdcall *m_bfmeF14)(void *o, void *a);
	void (__stdcall *m_bfmeF15)(void *o, void *a);
	void (__stdcall *m_bfmeF16)(void *o, void *a);
	void (__stdcall *m_bfmeF17)(void *o, void *a);
	void (__stdcall *m_bfmeF18)(void *o, void *a);
	void (__stdcall *m_bfmeF19)(void *o, void *a);
	void (__stdcall *m_bfmeF20)(void *o, void *a);
	void (__stdcall *m_bfmeF21)(void *o, void *a);
	void (__stdcall *m_bfmeF22)(void *o, void *a);
	void (__stdcall *m_bfmeF23)(void *o, void *a);
	void (__stdcall *m_bfmeF24)(void *o, void *a);
	void (__stdcall *m_bfmeF25)(void *o, void *a);
	void (__stdcall *m_bfmeF26)(void *o, void *a);
	void (__stdcall *m_bfmeF27)(void *o, void *a);
	void (__stdcall *m_bfmeF28)(void *o, void *a);
	void (__stdcall *m_bfmeF29)(void *o, void *a);
	void (__stdcall *m_bfmeF30)(void *o, void *a);
	void (__stdcall *m_bfmeF31)(void *o, void *a);
	void (__stdcall *m_bfmeF32)(void *o, void *a);
	void (__stdcall *m_bfmeF33)(void *o, void *a);
	void (__stdcall *m_bfmeF34)(void *o, void *a);
	void (__stdcall *m_bfmeF35)(void *o, void *a);
	void (__stdcall *m_bfmeF36)(void *o, void *a);
	void (__stdcall *m_bfmeF37)(void *o, void *a);
	void (__stdcall *m_bfmeF38)(void *o, void *a);
	void (__stdcall *m_bfmeF39)(void *o, void *a);
	void (__stdcall *m_bfmeF40)(void *o, void *a);
	void (__stdcall *m_bfmeF41)(void *o, void *a);
	void (__stdcall *m_bfmeF42)(void *o, void *a);
	void (__stdcall *m_bfmeF43)(void *o, void *a);
	void (__stdcall *m_bfmeF44)(void *o, void *a);
	void (__stdcall *m_bfmeF45)(void *o, void *a);
	void (__stdcall *m_bfmeF46)(void *o, void *a);
	void (__stdcall *m_bfmeF47)(void *o, void *a);
	void (__stdcall *m_bfmeF48)(void *o, void *a);
	void (__stdcall *m_bfmeF49)(void *o, void *a);
	void (__stdcall *m_bfmeF50)(void *o, void *a);
	void (__stdcall *m_bfmeF51)(void *o, void *a);
	void (__stdcall *m_bfmeF52)(void *o, void *a);
	void (__stdcall *m_bfmeF53)(void *o, void *a);
	void (__stdcall *m_bfmeF54)(void *o, void *a);
	void (__stdcall *m_bfmeF55)(void *o, void *a);
	void (__stdcall *m_bfmeF56)(void *o, void *a);
	void (__stdcall *m_bfmeF57)(void *o, void *a);
	void (__stdcall *m_bfmeF58)(void *o, void *a);
	void (__stdcall *m_bfmeF59)(void *o, void *a);
	void (__stdcall *m_bfmeF60)(void *o, void *a);
	void (__stdcall *m_bfmeF61)(void *o, void *a);
	void (__stdcall *m_bfmeF62)(void *o, void *a);
	void (__stdcall *m_bfmeF63)(void *o, void *a);
	void (__stdcall *m_bfmeF64)(void *o, void *a);
	void (__stdcall *m_bfmeF65)(void *o, void *a);
	void (__stdcall *m_bfmeF66)(void *o, void *a);
	void (__stdcall *m_bfmeF67)(void *o, void *a);
	void (__stdcall *m_bfmeF68)(void *o, void *a);
	void (__stdcall *m_bfmeF69)(void *o, void *a);
	void (__stdcall *m_bfmeF70)(void *o, void *a);
	void (__stdcall *m_bfmeF71)(void *o, void *a);
	void (__stdcall *m_bfmeF72)(void *o, void *a);
	void (__stdcall *m_bfmeF73)(void *o, void *a);
	void (__stdcall *m_bfmeF74)(void *o, void *a);
	void (__stdcall *m_bfmeF75)(void *o, void *a);
	void (__stdcall *m_bfmeF76)(void *o, void *a);
	void (__stdcall *m_bfmeF77)(void *o, void *a);
	void (__stdcall *m_bfmeF78)(void *o, void *a);
	void (__stdcall *m_bfmeF79)(void *o, void *a);
	void (__stdcall *m_bfmeF80)(void *o, void *a);
	void (__stdcall *m_bfmeF81)(void *o, void *a);
	void (__stdcall *m_bfmeF82)(void *o, void *a);
	void (__stdcall *m_bfmeF83)(void *o, void *a);
	void (__stdcall *m_bfmeF84)(void *o, void *a);
	void (__stdcall *m_bfmeF85)(void *o, void *a);
	void (__stdcall *m_bfmeF86)(void *o, void *a);
	void (__stdcall *m_bfmeF87)(void *o, void *a);
	void (__stdcall *m_bfmeF88)(void *o, void *a);
	void (__stdcall *m_bfmeF89)(BfmeObjELH *o, void *a);
	void (__stdcall *m_bfmeF90)(BfmeObjELH *o, void *a);
	void (__stdcall *m_bfmeF91)(BfmeObjELH *o, void *a);
	void (__stdcall *m_bfmeF92)(BfmeObjELH *o, void *a);
};

struct BfmeObjELH
{
	BfmeVtblELH *m_bfmeVtbl;
};

// Retail 0x01340594: use the existing data owner; retain the local pointee view.
extern unsigned int number_of_DX8_calls;

void bfmeGoELHa(void *a)
{
	BfmeObjELH *o = reinterpret_cast<BfmeObjELH *>(DX8Wrapper::_Get_D3D_Device8());
	o->m_bfmeVtbl->m_bfmeF89(o, a);
	++number_of_DX8_calls;
}

void bfmeGoELHb(void *a)
{
	BfmeObjELH *o = reinterpret_cast<BfmeObjELH *>(DX8Wrapper::_Get_D3D_Device8());
	o->m_bfmeVtbl->m_bfmeF92(o, a);
	++number_of_DX8_calls;
}

