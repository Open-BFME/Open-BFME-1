// Six unclaimed six-byte free functions with one shape:
//
//     mov eax,[<global>] / ret      (mov al,[<global>] / ret for the byte)
//
// Each returns a global read from a fixed .data address and touches nothing
// else (precedent: GlobalDwordGetters.cpp).  Each sat alone in a .text gap no
// ledger row covered: 16-byte-aligned start after an int3 pad run, ret
// followed by int3 padding, and no call, ILT stub, table slot, code immediate,
// pin or dir32 name at the address.  Every global is declared under the one
// name dir32_addresses.csv already records for its address and that no class
// header owns, so each relocation resolves to a known symbol with no new pin.
// 0x008A4B00 and 0x008A4B10 read the same global, 0x013379BC.
//
// IDENTITY IS NOT RECOVERED for the functions.  Every name is derived from an
// address.

extern bool g_0134050C;
extern int g_Va012D6DB4;
extern int g_Va012D6DB8;
extern void *g_bfmeFallbackDB;
extern void *bfmeRva0130CE50RegistrationHead;

bool Rva0090C7F0Global() { return g_0134050C; }
int Rva008FD5F0Global() { return g_Va012D6DB4; }
int Rva008FD600Global() { return g_Va012D6DB8; }
void *Rva008A4B00Global() { return g_bfmeFallbackDB; }
void *Rva008A4B10Global() { return g_bfmeFallbackDB; }
void *Rva00850720Global() { return bfmeRva0130CE50RegistrationHead; }
