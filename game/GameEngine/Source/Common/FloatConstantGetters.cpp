// 17 seven-byte functions with one shape:
//
//     fld dword ptr [<address>] / ret
//
// WHAT THE BYTES SHOW.  A dword is loaded onto the x87 stack from a FIXED
// address and left there, which is the return convention for `float`; `this` is
// never touched and nothing is popped, so these are spelled as free functions.
//
// WHAT IS AT THE ADDRESS DECIDES THE SPELLING.  13 of them point into .rdata at
// a value the source can name -- 0.0f, 1.0f, -1.0f and FLT_MAX -- and reading
// the retail dwords is what identifies them: 00000000, 3f800000, bf800000,
// 7f7fffff.  Written as literals, MSVC 7.1 pools each into a `__real@<hex>`
// constant and emits exactly this load, so the eight bodies returning zero all
// reference one pooled symbol and the build's consistency check confirms they
// all resolve to retail's one address.  No `fldz` or `fld1` shortcut appears
// here: at these settings MSVC loads even 0.0f and 1.0f from the pool, which is
// what retail does too.
//
// The remaining 4 are spelled as external globals instead.  Two land in .data,
// which a pooled literal never does, so they are mutable globals.  The other
// two land in .rdata on 7fa00000 and 7f800000 -- a quiet NaN and positive
// infinity -- which are constants no C++ float literal can spell; declaring
// them as externals claims only what the bytes show, that the load comes from a
// fixed address, and the patcher fills the address from retail either way.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

extern float g_Va0112E8AC;
extern float g_Va0112E8B0;
extern float g_Va0113BD7C;
extern float g_Va0113BD80;
extern float g_Va01307200;
extern float g_Va01340574;

float Rva000B4A70GetFloat( void )
{
	return g_Va0112E8AC;
}

float Rva0020DB40GetFloat( void )
{
	return 0.0f;
}

float Rva0020DB50GetFloat( void )
{
	return 0.0f;
}

float Rva0020DC40GetFloat( void )
{
	return 0.0f;
}

float Rva00213CB0GetFloat( void )
{
	return 0.0f;
}

float Rva00213CC0GetFloat( void )
{
	return 0.0f;
}

float Rva00213D50GetFloat( void )
{
	return 0.0f;
}

float Rva00219540GetFloat( void )
{
	return 1.0f;
}

float Rva0045BCC0GetFloat( void )
{
	return 0.0f;
}

float Rva0045C070GetFloat( void )
{
	return 1.0f;
}

float Rva00694C80GetFloat( void )
{
	return g_Va0112E8B0;
}

float Rva006CF590GetFloat( void )
{
	return g_Va0113BD7C;
}

float Rva006CF5A0GetFloat( void )
{
	return g_Va0113BD80;
}

float Rva006DAB40GetFloat( void )
{
	return g_Va01340574;
}

float Rva00750170GetFloat( void )
{
	return 0.0f;
}

float Rva007CC3C0GetFloat( void )
{
	return g_Va01307200;
}

float Rva009558E0GetFloat( void )
{
	return g_Va0113BD80;
}
