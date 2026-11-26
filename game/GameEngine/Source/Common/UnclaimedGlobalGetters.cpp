// Eight unclaimed five/six-byte free functions with one shape:
//
//     mov eax,[<global>] / ret      (mov al,[<global>] / ret for the byte)
//
// Each returns a global read from a fixed .data address and touches nothing
// else (precedent: GlobalDwordGetters.cpp).  Each sat alone in a .text gap no
// ledger row covered: 16-byte-aligned start after an int3 pad run, ret
// followed by int3 padding, and no call, ILT stub, table slot, code immediate,
// pin or dir32 name at the address.  0x008A4B00 and 0x008A4B10 read the same
// global, 0x013379BC.
//
// IDENTITY IS NOT RECOVERED for the functions.  Every name is derived from an
// address.  Each global is declared under the one name that already DEFINES its
// retail address, so every relocation resolves to a symbol that exists in
// another TU instead of to a name nothing defines.

// 0x013379BC is owned by the Apt append TU as an `AptValue *` (data_rows.csv
// ?g_bfmeFallbackDB@@3PAVAptValue@@A); declare it under that one spelling with
// the real class forward-declared so the reference resolves instead of the
// invented local view.  The load is a plain `mov eax,[...]`, so the view type
// does not touch the compiled bytes.
class AptValue;
extern AptValue *g_bfmeFallbackDB;

// The original byte at VA 0x0134050C is DX8Wrapper::IsInitted, already
// defined in dxwrapper.cpp. Its Init/Shutdown stores and Reset_Device read
// bind the same cell. Use its exact protected COFF data name, as the
// existing IsWindowed references below do; no duplicate global or view.
extern "C" bool __identifier("?IsInitted@DX8Wrapper@@1_NA");

// The width and height references retain their existing address spellings.
extern int g_Va012D6DB4;
extern int g_Va012D6DB8;

// 0x0130CE50 is INI's registration head: ini.cpp defines it as
// `BlockParse *theBlockParseList`, proves 0x0130CE50 is that head in its own
// ledger evidence, and both it and PathfinderConstructor.cpp reach it by that
// name.  Only the forward declaration is repeated here -- the pointee is never
// dereferenced, so no layout is needed or claimed.
struct BlockParse;
extern BlockParse *theBlockParseList;

int Rva008FD5F0Global() { return g_Va012D6DB4; }
int Rva008FD600Global() { return g_Va012D6DB8; }
void *Rva008A4B00Global() { return g_bfmeFallbackDB; }
void *Rva008A4B10Global() { return g_bfmeFallbackDB; }
void *Rva00850720Global() { return theBlockParseList; }
bool Rva0090C7F0Global() { return __identifier("?IsInitted@DX8Wrapper@@1_NA"); }

// 0x0134050D is DX8Wrapper::IsWindowed, a protected static (data_rows.csv
// ?IsWindowed@DX8Wrapper@@1_NA, defined in dxwrapper.cpp).  The free functions
// below reach that defining symbol through __identifier instead of a friend or
// derived view; the load is a plain `mov al,[...]`.
extern "C" bool __identifier("?IsWindowed@DX8Wrapper@@1_NA");

bool Rva008FD610IsWindowed() { return __identifier("?IsWindowed@DX8Wrapper@@1_NA"); }
bool Rva008FD780IsWindowed() { return __identifier("?IsWindowed@DX8Wrapper@@1_NA"); }
