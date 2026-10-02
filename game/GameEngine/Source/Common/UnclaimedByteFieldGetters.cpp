// Unclaimed tiny bodies with one shape:
//
//     mov al,[ecx+disp] / ret
//
// A __thiscall member returns one byte read from a fixed displacement inside
// `this`; only al is written, so the return type is one byte wide.
//
// Every body here sat in a .text gap no ledger row covered.  Both ends are
// proven by the retail layout: the start is 16-byte aligned directly after an
// int3 pad run, and the terminal instruction is followed by int3 padding or by
// the next matched row.  Retail was linked without identical-COMDAT folding,
// so each address is its own function even where the bytes repeat.  Most are
// unreferenced (no call, ILT stub or table slot reaches them); the notes column
// of each ledger row lists the references that do exist.  Members before an
// accessed field are spelled as a lead array because only their total size is
// witnessed.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#pragma pack( push, 1 )

#define BFME_BYTE_GETTER( NAME, LEAD ) \
	class NAME \
	{ \
	public: \
		unsigned char get() const; \
\
		char m_lead[ LEAD ]; \
		unsigned char m_value; \
	}; \
	unsigned char NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_FIRST_BYTE_GETTER( NAME ) \
	class NAME \
	{ \
	public: \
		unsigned char get() const; \
\
		unsigned char m_value; \
	}; \
	unsigned char NAME::get() const \
	{ \
		return m_value; \
	}

BFME_BYTE_GETTER( Rva007F0BB0ByteField, 0x1C )
BFME_BYTE_GETTER( Rva007F0BD0ByteField, 0x1D )
BFME_BYTE_GETTER( Rva007F5510ByteField, 0x14 )
BFME_BYTE_GETTER( Rva007F9090ByteField, 0x30 )
BFME_BYTE_GETTER( Rva008012C0ByteField, 0x64 )
BFME_BYTE_GETTER( Rva008012D0ByteField, 0x65 )
BFME_BYTE_GETTER( Rva00850770ByteField, 0x42C )
BFME_FIRST_BYTE_GETTER( Rva00881230ByteField )
BFME_BYTE_GETTER( Rva00894D20ByteField, 0xC )
BFME_BYTE_GETTER( Rva00898260ByteField, 0x8 )
BFME_BYTE_GETTER( Rva009036A0ByteField, 0x13A )
BFME_BYTE_GETTER( Rva0090C7C0ByteField, 0x4 )
BFME_BYTE_GETTER( Rva0090C800ByteField, 0x13C )
BFME_BYTE_GETTER( Rva00910F40ByteField, 0x276 )
BFME_BYTE_GETTER( Rva0091CDA0ByteField, 0x138 )
BFME_BYTE_GETTER( Rva0091CDB0ByteField, 0x13B )
BFME_BYTE_GETTER( Rva0092CBD0ByteField, 0x30 )
BFME_BYTE_GETTER( Rva00938D40ByteField, 0x69 )
BFME_BYTE_GETTER( Rva009454E0ByteField, 0xED )
BFME_BYTE_GETTER( Rva009454F0ByteField, 0xEE )
BFME_BYTE_GETTER( Rva00945500ByteField, 0xEC )
BFME_BYTE_GETTER( Rva0097E1F0ByteField, 0x12C )
BFME_FIRST_BYTE_GETTER( Rva009E1280ByteField )
BFME_BYTE_GETTER( Rva009E1310ByteField, 0x1 )

#pragma pack( pop )
