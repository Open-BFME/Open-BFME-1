// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: two more copies of the 31-byte refcounting assign, at
// 0x000BA5B0 and 0x0069C370, address-derived names. Byte-identical to the
// body already converted as gen_00698020, down to the same IAT slot; the
// retail image simply carries three separate emissions of it.
//
// IDENTITY IS NOT ASSERTED. See Gen_00698020.cpp for the reading of the
// bytes: a __cdecl helper taking a destination slot and a source slot; if
// the destination is null it does nothing, otherwise it copies the source
// pointer into it and, when that pointer is non-null, bumps a 32-bit counter
// at +4 of the pointee through KERNEL32 InterlockedIncrement.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long *addend);

void gen_000BA5B0(void **dst, void **src)
{
	if (dst == 0)
		return;

	void *p = *src;
	*dst = p;
	if (p != 0)
		InterlockedIncrement((long *)((char *)p + 4));
}

void gen_0069C370(void **dst, void **src)
{
	if (dst == 0)
		return;

	void *p = *src;
	*dst = p;
	if (p != 0)
		InterlockedIncrement((long *)((char *)p + 4));
}
