// cl: /DNDEBUG /MD /EHsc
struct Rva00171B20Flag { unsigned char padding[0x94]; unsigned bits; };
struct Rva00171B20Mid { unsigned char padding[0x10]; Rva00171B20Flag *flags; };
struct Rva00171B20Outer { unsigned char padding[0x1c]; Rva00171B20Mid *mid; };

// ?Rva00171B20FlagNotSet@@YAIPBURva00171B20Outer@@@Z
unsigned Rva00171B20FlagNotSet(const Rva00171B20Outer *outer)
{
	return ~(outer->mid->flags->bits >> 4) & 1u;
}
