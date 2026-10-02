// Unclaimed tiny bodies with one shape:
//
//     fld dword ptr [ecx+disp] / ret
//
// A __thiscall member returns one float loaded onto the x87 stack from a
// fixed displacement inside `this`.
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

#define BFME_FLOAT_GETTER( NAME, LEAD ) \
	class NAME \
	{ \
	public: \
		float get() const; \
\
		char m_lead[ LEAD ]; \
		float m_value; \
	}; \
	float NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_FIRST_FLOAT_GETTER( NAME ) \
	class NAME \
	{ \
	public: \
		float get() const; \
\
		float m_value; \
	}; \
	float NAME::get() const \
	{ \
		return m_value; \
	}

BFME_FLOAT_GETTER( Rva00898280FloatField, 0x8 )
BFME_FLOAT_GETTER( Rva008F7C20FloatField, 0x20 )
BFME_FLOAT_GETTER( Rva008F7C30FloatField, 0x1C )
BFME_FLOAT_GETTER( Rva00903860FloatField, 0x10C )
BFME_FLOAT_GETTER( Rva009038A0FloatField, 0x114 )
BFME_FLOAT_GETTER( Rva009187B0FloatField, 0x8 )
BFME_FLOAT_GETTER( Rva009187D0FloatField, 0x18 )
BFME_FLOAT_GETTER( Rva009187E0FloatField, 0x24 )
BFME_FLOAT_GETTER( Rva009187F0FloatField, 0x28 )
BFME_FLOAT_GETTER( Rva00918810FloatField, 0x2C )
BFME_FLOAT_GETTER( Rva00918CE0FloatField, 0x11C )
BFME_FLOAT_GETTER( Rva00918CF0FloatField, 0x128 )
BFME_FLOAT_GETTER( Rva00918D00FloatField, 0x12C )
BFME_FLOAT_GETTER( Rva00918D20FloatField, 0x130 )
BFME_FLOAT_GETTER( Rva00918DC0FloatField, 0x10C )
BFME_FLOAT_GETTER( Rva0094F9A0FloatField, 0x1C )
BFME_FLOAT_GETTER( Rva0094FBB0FloatField, 0xF8 )
BFME_FLOAT_GETTER( Rva0094FBC0FloatField, 0x104 )
BFME_FLOAT_GETTER( Rva0094FBD0FloatField, 0x108 )
BFME_FLOAT_GETTER( Rva00955930FloatField, 0x8 )
BFME_FLOAT_GETTER( Rva00955950FloatField, 0x18 )
BFME_FLOAT_GETTER( Rva00955970FloatField, 0x1C )
BFME_FLOAT_GETTER( Rva00955B20FloatField, 0x100 )
BFME_FLOAT_GETTER( Rva00955B40FloatField, 0x104 )
BFME_FLOAT_GETTER( Rva00955B60FloatField, 0xF0 )
BFME_FLOAT_GETTER( Rva00973660FloatField, 0x4 )
BFME_FLOAT_GETTER( Rva00973670FloatField, 0x8 )
BFME_FLOAT_GETTER( Rva0097E5F0FloatField, 0x1A8 )
BFME_FLOAT_GETTER( Rva0097E600FloatField, 0x1AC )
BFME_FLOAT_GETTER( Rva0097E610FloatField, 0x1E0 )
BFME_FLOAT_GETTER( Rva00B02090FloatField, 0x4 )
BFME_FLOAT_GETTER( Rva00B022A0FloatField, 0x4 )
BFME_FLOAT_GETTER( Rva00B023A0FloatField, 0x4 )
BFME_FLOAT_GETTER( Rva00B024F0FloatField, 0x8 )
BFME_FLOAT_GETTER( Rva00B02500FloatField, 0x4 )

#pragma pack( pop )
