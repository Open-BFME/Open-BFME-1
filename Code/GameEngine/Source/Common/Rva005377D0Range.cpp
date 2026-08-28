// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Open-BFME5: a second copy of the 27-byte range setter, at 0x005377D0,
// address-derived name. Byte-identical to the body already converted as
// rva005377A0; the retail image carries the two emissions back to back.

struct Rva005377D0Range
{
	unsigned m_0;
	unsigned m_4;
	unsigned m_8;
};

void rva005377D0(Rva005377D0Range *p, unsigned a, unsigned b, unsigned c)
{
	p->m_8 = a;
	p->m_0 = b;
	p->m_4 = c - b;
}
