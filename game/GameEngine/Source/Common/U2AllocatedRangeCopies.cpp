// Two byte-identical 55-byte rows at 0x0083F2F0 and 0x0083F330: allocate room
// for N four-byte elements, and if the allocation succeeded copy the source
// range into it.
//
//     n <<= 2                       -- the element width, the only one visible
//     p = alloc(n)                  -- indirect call through the import slot
//     if (p) {                         at 0x0135944C, one argument, returns a
//         low  = arg1;                 pointer
//         high = low + n;
//         if (high != low)          -- the redundant-looking guard is in the
//             copy(p, low, high-low);  bytes, not added here
//     }
//     return p;
//
// The two calls go through IMPORT SLOTS (`call dword ptr [0x0135944C]` and
// `call dword ptr [0x0135945C]`), not through relative calls, which is why they
// are declared __declspec(dllimport) rather than as ordinary externs: an
// ordinary extern compiles to `call rel32` and cannot produce these bytes.  The
// slot addresses are DIR32 the patcher fills; their arities are what the pushes
// show -- one argument for the allocator, three for the copy -- and nothing
// else about them is claimed here, so both names are derived from their slots.
//
// `high != low` rather than `n != 0` is what the compiler was given: it forms
// `lea eax,[edi+ecx]` and compares against ecx instead of testing edi, which is
// the same tell the range copies in T2CtypeTableFacets.cpp carry.
//
// TWO ROWS, TWO FUNCTIONS.  The bodies are byte-for-byte equal because a copy
// of a four-byte-element range has nothing to distinguish; they are two
// addresses, so they are two functions.

extern "C" __declspec(dllimport) void *__cdecl u2_import_0135944C(unsigned int bytes);
extern "C" __declspec(dllimport) void *__cdecl u2_import_0135945C(void *dst, const void *src, unsigned int bytes);

void *Rva0083F2F0Duplicate(const void *src, unsigned int count)
{
	unsigned int bytes = count * 4;
	void *p = u2_import_0135944C(bytes);
	if (p != 0)
	{
		const char *low = (const char *)src;
		const char *high = low + bytes;
		if (high != low)
			u2_import_0135945C(p, low, (unsigned int)(high - low));
	}
	return p;
}

void *Rva0083F330Duplicate(const void *src, unsigned int count)
{
	unsigned int bytes = count * 4;
	void *p = u2_import_0135944C(bytes);
	if (p != 0)
	{
		const char *low = (const char *)src;
		const char *high = low + bytes;
		if (high != low)
			u2_import_0135945C(p, low, (unsigned int)(high - low));
	}
	return p;
}
