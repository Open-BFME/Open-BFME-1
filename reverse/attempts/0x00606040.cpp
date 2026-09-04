// ?Rva00606040@@YGXPAII@Z
// partial score=0.95 date=2026-09-04
// cl: /O2 /Ob0
// Converted from Code/gen_asm/d_005e97b0.asm (?d_00606040@@YAXXZ).
// stdcall: helper(&v, v) then *out = *returned.

unsigned *__stdcall Rva00605F00(unsigned *slot, unsigned value);

void __stdcall Rva00606040(unsigned *out, unsigned value)
{
	*out = *Rva00605F00(&value, value);
}
