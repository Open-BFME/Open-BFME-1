// cl: /O2 /MD
class BfmeThing936G
{
public:
	BfmeThing936G *bfmeGo936G(void);
};

// Retail 0x00C6C7B0 is `mov ecx,0x0130A450; call bfmeGo936G;
// push 0x01070BE0; call atexit; pop ecx; ret`, so the cleanup this TU
// registers is retail RVA 0x00C70BE0 -- which the ledger owns as
// ?bfmeForward_00C70BE0@@YAXXZ (10 bytes, matched, game/
// GameEngine/Source/Common/S3SingletonForwarders.cpp).  Declaring a
// destructor here instead left ?1Rva00C6C7B0Init@@QAE@XZ undefined and the
// compiled _$E2 a second body for 0x00C70BE0 (LNK2001).  Registering the
// cleanup by its real name keeps the 22 bytes of _$E1 unchanged and drops
// the duplicate _$E2.
// Retail 0x00C70BE0 is `mov ecx,0x0130A450; jmp 0x00843610`, the _Dec
// paired with the _Inc at 0x00843D70 that this constructor calls.
extern "C" int __cdecl atexit(void (__cdecl *callback)());
void bfmeForward_00C70BE0(void);

class Rva00C6C7B0Init : public BfmeThing936G
{
public:
	Rva00C6C7B0Init()
	{
		bfmeGo936G();
		atexit(bfmeForward_00C70BE0);
	}
};

Rva00C6C7B0Init g_rva0130A450;