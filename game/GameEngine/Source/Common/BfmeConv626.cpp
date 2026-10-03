// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// The call at +0x0024 goes through the ILT entry at 0x00032DEE, which is
// Object::setStatusBit( Int, Bool )'s thunk; the body it reaches is matched at
// 0x000D3EB0.  Retail pushes the Bool and the bit index and leaves `this` in
// ecx, which is what a thiscall to the real member spells, so the call uses
// the real name.  Only the bitset type is needed; the header is included for
// its declaration rather than redeclared.
#include "../GameLogic/Object/ObjectStatusBits.h"

class BfmeThingCNE
{
public:
	virtual void bfmeSpareCNE0();
	virtual void bfmeSpareCNE1();
	virtual void bfmeSpareCNE2();
	virtual void bfmeSpareCNE3();
	virtual void bfmeSpareCNE4();
	virtual void bfmeSpareCNE5();
	virtual void bfmeSpareCNE6();
	virtual void bfmeSpareCNE7();
	virtual void bfmeSpareCNE8();
	virtual void bfmeSpareCNE9();
	virtual void bfmeSpareCNE10();
	virtual void bfmeSpareCNE11();
	virtual void bfmeSpareCNE12();
	virtual void bfmeSpareCNE13();
	virtual void bfmeSpareCNE14();
	virtual void bfmeSpareCNE15();
	virtual void bfmeSpareCNE16();
	virtual void bfmeSpareCNE17();
	virtual void bfmeSpareCNE18();
	virtual void bfmeSpareCNE19();
	virtual void bfmeSpareCNE20();
	virtual void bfmeRunCNE(void *what);
	void bfmeGoCNE(void *what);
	unsigned char m_bfmeGap[0x90];
	unsigned int m_bfmeFlags;
	unsigned char m_bfmeGap2[0x1a4];
	void *m_bfmeCur;
};

void BfmeThingCNE::bfmeGoCNE(void *what)
{
	if (what == 0)
		return;
	if (m_bfmeFlags & 0x20000000)
		return;
	if (what == m_bfmeCur)
		return;
	((Object *)this)->setStatusBit(0x3d, true);
	bfmeRunCNE(what);
}
