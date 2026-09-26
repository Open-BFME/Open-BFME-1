// ?rva00849E20DecodeFlags@@YGII@Z
// partial score=0.75 date=2026-09-06
// ?rva00849E20DecodeFlags@@YAIK@Z
// Address-derived: decode the low 2 bits of an unsigned parameter into a
// fixed size constant (8/16/24), and for the remaining case (low bits == 3)
// pass the value through with bit0 set when bit 0x800 is set and bit2 set
// when bit 0x8000 is set.
unsigned int __stdcall rva00849E20DecodeFlags(unsigned int p)
{
	switch (p & 3)
	{
	case 0:
		return 8;
	case 1:
		return 0x10;
	case 2:
		return 0x18;
	default:
		break;
	}

	unsigned int result = p;
	if (p & 0x800)
		result |= 1;
	if (p & 0x8000)
		result |= 4;
	return result;
}
