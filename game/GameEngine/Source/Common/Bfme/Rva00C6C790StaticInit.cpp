// cl: /O2 /MD
class BfmeThingTB
{
public:
	BfmeThingTB *bfmeGoTB(void);
};

// Retail 0x00C6C790 is `mov ecx,0x0130A451; call bfmeGoTB;
// push 0x01070BD0; call atexit; pop ecx; ret`, so the cleanup this TU
// registers is retail RVA 0x00C70BD0 -- which the ledger owns as
// ?bfmeForward_00C70BD0@@YAXXZ (10 bytes, matched, game/
// GameEngine/Source/Common/S3SingletonForwarders.cpp).  Declaring a
// destructor here instead left ?1Rva00C6C790Init@@QAE@XZ undefined and the
// compiled _$E2 a second body for 0x00C70BD0 (LNK2001).  Registering the
// cleanup by its real name keeps the 22 bytes of _$E1 unchanged and drops
// the duplicate _$E2.
// Retail 0x00C70BD0 is `mov ecx,0x0130A451; jmp 0x00832740`, the locale
// _Dec paired with the _Inc at 0x0083CB30 that this constructor calls.
extern "C" int __cdecl atexit(void (__cdecl *callback)());
void bfmeForward_00C70BD0(void);

class Rva00C6C790Init : public BfmeThingTB
{
public:
	Rva00C6C790Init()
	{
		bfmeGoTB();
		atexit(bfmeForward_00C70BD0);
	}
};

Rva00C6C790Init g_rva0130A451;