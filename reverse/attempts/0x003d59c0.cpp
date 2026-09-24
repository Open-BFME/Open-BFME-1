// ?rva003D59C0@@YGHHPBURva003D59C0Obj@@HH@Z
// partial score=0.72 date=2026-09-24
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Open-BFME5: stdcall filter at retail 0x003D59C0 (39B).
// Sibling of rva003D5AE0 (0x003D5AE0): same msg+0xC bitfield shape.
//
// PARTIAL: the conjunction reproduces retail's two JE branches and early
// return. MSVC 7.1 still keeps the word in EAX instead of ECX and eliminates
// retail's MOVZX EAX,CL before the final AND 1.

struct Rva003D59C0Obj
{
	char m_pad[0xC];
	unsigned m_bits;
};

int __stdcall rva003D59C0(int, const Rva003D59C0Obj *obj, int, int)
{
	unsigned bits = obj->m_bits;
	unsigned low = bits & 7u;
	if (low != 0u && low != 1u)
		return 1;
	return (int)(((unsigned char)(bits >> 18)) & 1u);
}
