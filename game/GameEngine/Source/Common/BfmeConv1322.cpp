// cl: /Igame/Libraries/Source/WWVegas/WWDebug

// Open-BFME5 conversions.

// ?bfmeFreeTRB@BfmePoolTRB@@QAEXPAX@Z was a TU-local spelling of retail's
// ?Free_Object_Memory@?$ObjectPoolClass@VGridLinkClass@@$0BAA@@@QAEXPAVGridLinkClass@@@Z
// at 0x008DDA50: dis_retail 0x008DDED0 shows bfmeDelTRB pushing the object and
// loading 0x0133D1AC into ecx before that call, so pool and member are the real
// mempool.h template, forward-declared GridLinkClass.
#include "../../../Libraries/Source/WWVegas/WWLib/mempool.h"

class GridLinkClass;

// Keep the retail lock-bearing specialization in ObjectPoolFreeObjectMemory.cpp.
template<> void ObjectPoolClass<GridLinkClass,256>::Free_Object_Memory(GridLinkClass *);

// Retired unowned reference:
// ?g_bfmePoolTRB@@3V?$ObjectPoolClass@VGridLinkClass@@$0BAA@@@A
// gridcull.cpp owns AutoPoolClass<GridLinkClass,256>::Allocator at 0x0133D1AC.

class BfmeThingTRB
{
public:
	void *bfmeDelTRB(unsigned char flags);
	void bfmeDtorTRB();
};

// ?bfmeDelTRB@BfmeThingTRB@@QAEPAXE@Z
void *BfmeThingTRB::bfmeDelTRB(unsigned char flags)
{
	bfmeDtorTRB();
	if (flags & 1)
		AutoPoolClass<GridLinkClass,256>::operator delete(this);
	return this;
}

struct BfmeGuidTSA
{
	char m_bfmeBytes[16];
};

// retired debt ___GUID_ee883b17_0778_4b18_a12b_e44c0d298412: retail 0x0113DF00
// is DIR32-recorded as ?g_bfmeIidTSA@@3UBfmeGuidTSA@@A, the IFEBrowserEngine2
// interface ID. The TU defines the datum under the recorded name (16 bytes:
// ee883b17-0778-4b18-a12b-e44c0d298412) and references it below.
BfmeGuidTSA g_bfmeIidTSA =
{
	0x17, 0x3b, (char)0x88, (char)0xee,
	0x78, 0x07, 0x18, 0x4b,
	(char)0xa1, 0x2b, (char)0xe4, 0x4c,
	0x0d, 0x29, (char)0x84, 0x12
};

class BfmeThingTSA;

struct BfmeVtTSA
{
	void *m_bfmeSlot0;
	void *m_bfmeSlot1;
	void *m_bfmeSlot2;
	void *m_bfmeSlot3;
	void *m_bfmeSlot4;
	void *m_bfmeSlot5;
	void *m_bfmeSlot6;
	void *m_bfmeSlot7;
	long (__stdcall *m_bfmeOneTSA)(BfmeThingTSA *self);
	void *m_bfmeSlot9;
	void *m_bfmeSlot10;
	void *m_bfmeSlot11;
	void *m_bfmeSlot12;
	void *m_bfmeSlot13;
	void *m_bfmeSlot14;
	long (__stdcall *m_bfmeTwoTSA)(BfmeThingTSA *self);
};

void __stdcall bfmeReportTSA(long hr, BfmeThingTSA *o, BfmeGuidTSA *iid);

class BfmeThingTSA
{
public:
	long bfmeGoOneTSA();
	long bfmeGoTwoTSA();
	BfmeVtTSA *m_bfmeVt;
};

long BfmeThingTSA::bfmeGoOneTSA()
{
	long hr = m_bfmeVt->m_bfmeOneTSA(this);
	if (hr < 0)
		bfmeReportTSA(hr, this,
			&g_bfmeIidTSA);
	return hr;
}

long BfmeThingTSA::bfmeGoTwoTSA()
{
	long hr = m_bfmeVt->m_bfmeTwoTSA(this);
	if (hr < 0)
		bfmeReportTSA(hr, this,
			&g_bfmeIidTSA);
	return hr;
}
