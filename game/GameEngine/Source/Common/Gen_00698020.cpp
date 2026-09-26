// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the 31-byte refcounting assign at 0x00698020, address-derived
// name. Converted out of game/gen_asm/d_00693e20.asm.
//
// IDENTITY IS NOT ASSERTED. The bytes say: a __cdecl helper taking a
// destination slot and a source slot; if the destination is null it does
// nothing, otherwise it copies the source pointer into it and, when that
// pointer is non-null, bumps a 32-bit counter at +4 of the pointee through
// KERNEL32 InterlockedIncrement.
//
// Relocation note: the only relocation is the indirect `ff 15` at 0x00698038
// against IAT slot 0x01358E5C, which the import directory names
// InterlockedIncrement. __declspec(dllimport) reproduces the six-byte form
// directly; no pin and no other row involved.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long *addend);

void gen_00698020(void **dst, void **src)
{
	if (dst == 0)
		return;

	void *p = *src;
	*dst = p;
	if (p != 0)
		InterlockedIncrement((long *)((char *)p + 4));
}
