// 69 seven-byte __thiscall members with one shape:
//
//     lea eax,[ecx+<DISP>] / ret
//
// Nothing is dereferenced: the ADDRESS of a fixed displacement from `this` is
// returned.  That is the whole difference from the load-and-return families in
// DispByteFieldGetters.cpp and DispDwordFieldGetters.cpp, and it is why the
// accessed member is spelled `char` and the accessor returns `char *` -- the
// bytes witness where the member starts and nothing at all about its type or
// size.  One displacement (0x203) is not four-aligned, which a dword or float
// member could not produce and a byte member can.
//
// WHAT THE BYTES SHOW AND WHAT THEY DO NOT.  The displacement is a disp32 in
// every member -- MSVC 7.1 uses disp8 whenever the offset fits in a signed
// byte, so every offset here is at least 0x80, and the encoding itself is why
// this family is separable from the far larger disp8 one.  The operand size and
// the displacement are read straight off the instruction stream; nothing else
// about these functions is asserted.  Members before the accessed one are
// spelled as a lead array because their types are not witnessed here, only
// their total size.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define BFME_DISP_ADDRESS_GETTER( NAME, DISP )                                     \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		char *get();                                                          \
                                                                              \
		char m_lead[ DISP ];                                                  \
		char m_value;                                                         \
	};                                                                        \
	char *NAME::get()                                                         \
	{                                                                         \
		return &m_value;                                                      \
	}

BFME_DISP_ADDRESS_GETTER( Rva000EC210FieldAddress, 0x110 )
BFME_DISP_ADDRESS_GETTER( Rva000EC400FieldAddress, 0x14 )
BFME_DISP_ADDRESS_GETTER( Rva000EC420FieldAddress, 0x12C )
BFME_DISP_ADDRESS_GETTER( Rva000EC620FieldAddress, 0xE4 )
BFME_DISP_ADDRESS_GETTER( Rva000EC760FieldAddress, 0x1A8 )
BFME_DISP_ADDRESS_GETTER( Rva000EC9E0FieldAddress, 0x294 )
BFME_DISP_ADDRESS_GETTER( Rva000ECA00FieldAddress, 0x2D0 )
BFME_DISP_ADDRESS_GETTER( Rva000F9200FieldAddress, 0x374 )
BFME_DISP_ADDRESS_GETTER( Rva000F9210FieldAddress, 0x374 )
BFME_DISP_ADDRESS_GETTER( Rva000F9220FieldAddress, 0x224 )
BFME_DISP_ADDRESS_GETTER( Rva000FB8C0FieldAddress, 0x684 )
BFME_DISP_ADDRESS_GETTER( Rva00160450FieldAddress, 0x288 )
BFME_DISP_ADDRESS_GETTER( Rva001B2BA0FieldAddress, 0xB4 )
BFME_DISP_ADDRESS_GETTER( Rva001B4090FieldAddress, 0x47C )
BFME_DISP_ADDRESS_GETTER( Rva001BDAF0FieldAddress, 0xBC )
BFME_DISP_ADDRESS_GETTER( Rva001BEF20FieldAddress, 0x29C )
BFME_DISP_ADDRESS_GETTER( Rva001E0C30FieldAddress, 0x4E8 )
BFME_DISP_ADDRESS_GETTER( Rva001ECE80FieldAddress, 0x2A8 )
BFME_DISP_ADDRESS_GETTER( Rva001ED5E0FieldAddress, 0x1B0 )
BFME_DISP_ADDRESS_GETTER( Rva00200150FieldAddress, 0x250 )
BFME_DISP_ADDRESS_GETTER( Rva0020DDC0FieldAddress, 0x98 )
BFME_DISP_ADDRESS_GETTER( Rva0020DDD0FieldAddress, 0x9C )
BFME_DISP_ADDRESS_GETTER( Rva0022A070FieldAddress, 0xC4 )
BFME_DISP_ADDRESS_GETTER( Rva00232080FieldAddress, 0x9C )
BFME_DISP_ADDRESS_GETTER( Rva00294E90FieldAddress, 0x198 )
BFME_DISP_ADDRESS_GETTER( Rva0029BEE0FieldAddress, 0x98 )
BFME_DISP_ADDRESS_GETTER( Rva0029BEC0FieldAddress, 0x10 )
BFME_DISP_ADDRESS_GETTER( Rva0029C0D0FieldAddress, 0x2E8 )
BFME_DISP_ADDRESS_GETTER( Rva002BB900FieldAddress, 0x498 )
BFME_DISP_ADDRESS_GETTER( Rva002D40D0FieldAddress, 0x328 )
BFME_DISP_ADDRESS_GETTER( Rva00360610FieldAddress, 0xB0 )
BFME_DISP_ADDRESS_GETTER( Rva00360630FieldAddress, 0x94 )
BFME_DISP_ADDRESS_GETTER( Rva0037D070FieldAddress, 0x248 )
BFME_DISP_ADDRESS_GETTER( Rva003BC5F0FieldAddress, 0xB8 )
BFME_DISP_ADDRESS_GETTER( Rva003BC8F0FieldAddress, 0x104 )
BFME_DISP_ADDRESS_GETTER( Rva003C5F80FieldAddress, 0xC )
BFME_DISP_ADDRESS_GETTER( Rva003CBA50FieldAddress, 0x98 )
BFME_DISP_ADDRESS_GETTER( Rva003D5C50FieldAddress, 0x848 )
BFME_DISP_ADDRESS_GETTER( Rva00402260FieldAddress, 0xC9C )
BFME_DISP_ADDRESS_GETTER( Rva0043A650FieldAddress, 0x4D10 )
BFME_DISP_ADDRESS_GETTER( Rva00470340FieldAddress, 0x24C )
BFME_DISP_ADDRESS_GETTER( Rva004901F0FieldAddress, 0xD0 )
BFME_DISP_ADDRESS_GETTER( Rva00490200FieldAddress, 0xB8 )
BFME_DISP_ADDRESS_GETTER( Rva004A3AF0FieldAddress, 0x188 )
BFME_DISP_ADDRESS_GETTER( Rva00519B60FieldAddress, 0x138 )
BFME_DISP_ADDRESS_GETTER( Rva00538E20FieldAddress, 0x138 )
BFME_DISP_ADDRESS_GETTER( Rva00584D50FieldAddress, 0x98 )
BFME_DISP_ADDRESS_GETTER( Rva00588810FieldAddress, 0x698 )
BFME_DISP_ADDRESS_GETTER( Rva005A44F0FieldAddress, 0x1100 )
BFME_DISP_ADDRESS_GETTER( Rva005A73C0FieldAddress, 0x358 )
BFME_DISP_ADDRESS_GETTER( Rva005A73D0FieldAddress, 0x3C8 )
BFME_DISP_ADDRESS_GETTER( Rva005A73E0FieldAddress, 0x438 )
BFME_DISP_ADDRESS_GETTER( Rva005C27A0FieldAddress, 0x1C8 )
BFME_DISP_ADDRESS_GETTER( Rva005C27C0FieldAddress, 0x94 )
BFME_DISP_ADDRESS_GETTER( Rva005C27E0FieldAddress, 0x8C )
BFME_DISP_ADDRESS_GETTER( Rva005C2810FieldAddress, 0x1C0 )
BFME_DISP_ADDRESS_GETTER( Rva005C2820FieldAddress, 0x1C4 )
BFME_DISP_ADDRESS_GETTER( Rva005C2C20FieldAddress, 0xB0 )
BFME_DISP_ADDRESS_GETTER( Rva005C2C30FieldAddress, 0xB4 )
BFME_DISP_ADDRESS_GETTER( Rva005C2C40FieldAddress, 0xB8 )
BFME_DISP_ADDRESS_GETTER( Rva005C2C50FieldAddress, 0xBC )
BFME_DISP_ADDRESS_GETTER( Rva005C2C60FieldAddress, 0xC0 )
BFME_DISP_ADDRESS_GETTER( Rva005E5EF0FieldAddress, 0x94 )
BFME_DISP_ADDRESS_GETTER( Rva005F6640FieldAddress, 0xC0 )
BFME_DISP_ADDRESS_GETTER( Rva00630700FieldAddress, 0x6D4 )
BFME_DISP_ADDRESS_GETTER( Rva0063A7B0FieldAddress, 0x104 )
BFME_DISP_ADDRESS_GETTER( Rva00661BF0FieldAddress, 0x1E4 )
BFME_DISP_ADDRESS_GETTER( Rva00663D60FieldAddress, 0x1FFC )
BFME_DISP_ADDRESS_GETTER( Rva006948A0FieldAddress, 0x8C )
BFME_DISP_ADDRESS_GETTER( Rva006C5580FieldAddress, 0x110 )
BFME_DISP_ADDRESS_GETTER( Rva007EA660FieldAddress, 0x203 )
BFME_DISP_ADDRESS_GETTER( Rva00746070FieldAddress, 0x78 )
BFME_DISP_ADDRESS_GETTER( Rva00696310FieldAddress, 0x70 )

// Six further members outside the 0x80..0x8000 window, four of them at a
// NEGATIVE displacement.  Returning the address of a member cannot produce a
// negative offset, so those four are spelled as the pointer arithmetic they
// are; nothing about a containing object is claimed.

#define BFME_DISP_ADDRESS_GETTER_BEFORE( NAME, BACK )                         \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		char *get();                                                          \
	};                                                                        \
	char *NAME::get()                                                         \
	{                                                                         \
		return (char *)this - ( BACK );                                       \
	}

BFME_DISP_ADDRESS_GETTER_BEFORE( Rva001D3F60FieldAddress, 0x314 )
BFME_DISP_ADDRESS_GETTER_BEFORE( Rva001D3FE0FieldAddress, 0x388 )
BFME_DISP_ADDRESS_GETTER_BEFORE( Rva002307B0FieldAddress, 0xAC )
BFME_DISP_ADDRESS_GETTER_BEFORE( Rva00230830FieldAddress, 0xE4 )
BFME_DISP_ADDRESS_GETTER( Rva00336C20FieldAddress, 0x1607C )
BFME_DISP_ADDRESS_GETTER( Rva006044D0FieldAddress, 0x17604 )
