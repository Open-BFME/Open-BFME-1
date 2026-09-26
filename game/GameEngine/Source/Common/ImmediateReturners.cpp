// 20 six-byte __thiscall members with one shape:
//
//     mov eax,<immediate> / ret
//
// This is the residue of the family landed in LiteralNameGetters_01..04.cpp,
// separated from it by what the immediate turns out to be.  There, following
// the immediate into the image reached a printable NUL-terminated string in
// .rdata and the body is a name accessor.  Here, 17 immediates do not land
// inside any section at all, so they cannot be addresses and are returned as
// the plain constants they are; the other three land on a NUL byte -- the same
// address in all three -- so they are the empty string, which the build counts
// separately as an empty-string reference.
//
// Six of the constants read as four printable ASCII bytes in big-endian order
// -- 'modr', 'ANIM', 'MESH', 'PART', 'AGGR', 'NULL' -- which is the shape of a
// chunk tag in the W3D asset format the engine loads.  They are written here as
// hex because that is what the instruction holds and a multi-character literal
// would only re-encode the same dword through an implementation-defined rule.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define BFME_CONSTANT_RETURNER( NAME, VALUE )                                 \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		unsigned int value() const;                                           \
	};                                                                        \
	unsigned int NAME::value() const                                          \
	{                                                                         \
		return VALUE;                                                         \
	}

#define BFME_EMPTY_NAME_GETTER( NAME )                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		const char *name() const;                                             \
	};                                                                        \
	const char *NAME::name() const                                            \
	{                                                                         \
		return "";                                                            \
	}

BFME_CONSTANT_RETURNER( Rva000CB3C0Constant, 0x000000B5u )
BFME_CONSTANT_RETURNER( Rva000CD1D0Constant, 0x000000B5u )
BFME_CONSTANT_RETURNER( Rva001B4D60Constant, 0x00000130u )
BFME_CONSTANT_RETURNER( Rva001B5D50Constant, 0x00000130u )
BFME_CONSTANT_RETURNER( Rva001C0A20Constant, 0x00000056u )
BFME_CONSTANT_RETURNER( Rva001C2BB0Constant, 0x00000056u )
BFME_CONSTANT_RETURNER( Rva004B21E0Constant, 0x000000C0u )
BFME_CONSTANT_RETURNER( Rva004B22D0Constant, 0x000000C0u )
BFME_CONSTANT_RETURNER( Rva005A7650Constant, 0x80000000u )
BFME_CONSTANT_RETURNER( Rva006BDFF0Constant, 0x0000FFFFu )
BFME_CONSTANT_RETURNER( Rva00900490Constant, 0x6D6F6472u )  // "modr"
BFME_CONSTANT_RETURNER( Rva0090BCB0Constant, 0x414E494Du )  // "ANIM"
BFME_CONSTANT_RETURNER( Rva00970CB0Constant, 0x4D455348u )  // "MESH"
BFME_CONSTANT_RETURNER( Rva009711F0Constant, 0x50415254u )  // "PART"
BFME_CONSTANT_RETURNER( Rva00971C40Constant, 0x41474752u )  // "AGGR"
BFME_CONSTANT_RETURNER( Rva009721A0Constant, 0x00000044u )
BFME_CONSTANT_RETURNER( Rva00972910Constant, 0x4E554C4Cu )  // "NULL"

BFME_EMPTY_NAME_GETTER( Rva00148790EmptyNamed )
BFME_EMPTY_NAME_GETTER( Rva001487A0EmptyNamed )
BFME_EMPTY_NAME_GETTER( Rva001487B0EmptyNamed )
