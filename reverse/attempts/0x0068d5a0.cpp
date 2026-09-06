// ?bfmeEmitBA@@YAPAGPAGH0@Z (identity unknown)
// partial score=0.98 date=2026-09-06
// 49/50. 0x0068D620 is a byte-identical second copy, so this stash serves
// both. Everything matches: the push-ecx frame slot, the stdcall function
// pointer at 0x00F5972C, the optional limit guard with its two unsigned
// compares (dst and dst+1), the word store and the two-byte advance.
// Residue is ONE byte: retail reads the spilled result as a word
// (`66 8b 0c 24`, mov cx,[esp]) where MSVC reads the full dword
// (`8b 0c 24`). Getting the spill at all needs `volatile int`; without it
// MSVC keeps the value in edx and the body is 45 bytes. Tried for the narrow
// read: a plain int with *(unsigned short*)&, a union of int and unsigned
// short, a volatile union, a volatile-short-pointer cast, and a two-short
// struct returned by value from the pointer (all four optimise back into a
// register, 45 bytes).
extern int (__stdcall *g_bfmeConvBA)(int value);	// pin ?g_bfmeConvBA@@3P6GHH@ZA,0x00F5972C

unsigned short * __cdecl bfmeEmitBA(unsigned short *dst, int value, unsigned short *limit)
{
	volatile int converted = g_bfmeConvBA(value);

	if (limit != 0)
	{
		if (dst > limit)
			return dst;

		if (dst + 1 > limit)
			return dst;
	}

	*dst = (unsigned short)converted;

	return dst + 1;
}
