// Eight leaf members from the character-facet neighbourhood of
// T2CtypeTableFacets.cpp.  None of them contains a relocation, so every byte
// here is concrete and the only thing to get right is the shape.
//
// TWO PASS-THROUGHS.  0x00840830 is `mov al,[esp+4] / ret 4` and 0x00840870 is
// `mov al,[esp+4] / ret 8`: a __thiscall member that never reads ecx, takes one
// char and returns it unchanged, and its two-argument twin that returns the
// FIRST argument and ignores the second.  That is the widen/narrow pair of a
// facet whose two character types are the same width, so the conversion is the
// identity and the default character of the narrowing form is dead.  They sit
// a few rows from the mask-table `is` at 0x00840910, which is what places them
// in this family rather than among the general one-argument forwarders.
//
// ONE CONSTANT.  0x00848090 is `mov ax,20h / ret` with no arguments at all,
// returning ' ' as a SIXTEEN-bit value.  A member returning `char` would leave
// the byte in al, so the operand size says the return type is two bytes wide.
// Nothing in these bytes names the class, so the class is an address.  The two
// neighbours that used to sit here, 0x00844500 and 0x00844510, are slots 1 and
// 2 of the wide numpunct vtable at VA 0x0112EB18 and now come from
// game/Libraries/Source/WWVegas/WWLib/stlport_numpunct_wide_leaves.cpp.
//
// The three all-ones members that used to sit here are gone. 0x0083FF70,
// 0x0083FF80 and 0x0083FF90 are slots 7, 9 and 12 of the wide basic_streambuf
// vtable at VA 0x0112EC10, so they are underflow, pbackfail and overflow and
// they now come from the explicit instantiation in
// game/Libraries/Source/WWVegas/WWLib/stlport_wide_streambuf_xsgetn.cpp.

struct Rva00840830Facet
{
	char widen(char c) const;
	char narrow(char c, char dflt) const;
};

char Rva00840830Facet::widen(char c) const
{
	return c;
}

char Rva00840830Facet::narrow(char c, char) const
{
	return c;
}

struct Rva00848090Punct
{
	unsigned short fill() const;
};

unsigned short Rva00848090Punct::fill() const
{
	return (unsigned short)' ';
}
