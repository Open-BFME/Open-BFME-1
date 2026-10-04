// Six unclaimed five/six-byte free functions with one shape:
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

// 0x0134050C and 0x012D6DB4/0x012D6DB8 still have no free spelling anything
// defines, and all three ARE DX8Wrapper statics:
//
//   0x01340500 ZFar           0x012D6DB0 CurRenderDevice
//   0x0134050C <bool>        0x012D6DB4 ResolutionWidth  (640 in retail .data)
//   0x0134050D IsWindowed    0x012D6DB8 ResolutionHeight (480 in retail .data)
//   0x01340510 DisplayFormat 0x012D6DBC BitDepth
//   0x0134051C Light_Environment
//   0x01340524 Vertex_Processing_Behavior
//   0x01340528 FogEnable     0x0134052C FogColor
//   0x01340530 D3DInterface
//
// dxwrapper.obj lays the same run of statics out with the same offsets relative
// to ZFar (IsInitted +0x88 / IsWindowed +0x89 / DisplayFormat +0x8C / ... /
// D3DInterface +0xAC against retail's +0xD/+0xD/+0x10/.../+0x30, a constant
// +0x7C shift), which fixes the unnamed bool at 0x0134050C as
// DX8Wrapper::IsInitted.  All four are PROTECTED static members, though, and
// MSVC encodes access in the mangling: the defining spellings are
// ?ResolutionWidth@DX8Wrapper@@1HA and friends, and no spelling a free
// function may write produces them.  Referencing them here is impossible, not
// merely unproven -- a `friend` or a derived view would be invented, and
// `#define protected public` would renumber the access digit in the symbol.
extern bool g_0134050C;
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
bool Rva0090C7F0Global() { return g_0134050C; }