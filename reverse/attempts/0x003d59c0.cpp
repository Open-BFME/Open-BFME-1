// ?rva003D59C0@@YGHHPBURva003D59C0Obj@@HH@Z
// partial score=0.72 date=2026-09-04
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Open-BFME5: stdcall filter at retail 0x003D59C0 (39B).
// Sibling of rva003D5AE0 (0x003D5AE0): same msg+0xC bitfield shape.
//
// PARTIAL: semantics match; MSVC 7.1 emits mov eax,[eax+0xC] / je+jne
// layout instead of retail mov ecx,[eax+0xC] / je+je / movzx. Banked.

struct Rva003D59C0Obj
{
	char m_pad[0xC];
	unsigned m_bits;
};

int __stdcall rva003D59C0(int, const Rva003D59C0Obj *obj, int, int)
{
	unsigned bits = obj->m_bits;
	unsigned low = bits & 7u;
	if (low == 0u)
		goto extract;
	if (low == 1u)
		goto extract;
	return 1;
extract:
	return (int)(((unsigned char)(bits >> 18)) & 1u);
}
