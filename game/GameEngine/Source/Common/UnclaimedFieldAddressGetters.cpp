// Unclaimed tiny bodies with one shape:
//
//     lea eax,[ecx+disp] / ret
//
// A __thiscall member returns the address of a member at a fixed
// displacement inside `this`.  The member type is not witnessed; int is
// spelled so the address arithmetic is plain.
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

#define BFME_FIELD_ADDRESS( NAME, LEAD ) \
	class NAME \
	{ \
	public: \
		int *field(); \
\
		char m_lead[ LEAD ]; \
		int m_value; \
	}; \
	int *NAME::field() \
	{ \
		return &m_value; \
	}

BFME_FIELD_ADDRESS( Rva007F1D90FieldAddress, 0x8 )
BFME_FIELD_ADDRESS( Rva007F21B0FieldAddress, 0x10 )
BFME_FIELD_ADDRESS( Rva007F21C0FieldAddress, 0x30 )
BFME_FIELD_ADDRESS( Rva007F21E0FieldAddress, 0x54 )
BFME_FIELD_ADDRESS( Rva007F5100FieldAddress, 0x31 )
BFME_FIELD_ADDRESS( Rva007F5110FieldAddress, 0xC )
BFME_FIELD_ADDRESS( Rva007F5180FieldAddress, 0x8 )
BFME_FIELD_ADDRESS( Rva007F5260FieldAddress, 0x94 )
BFME_FIELD_ADDRESS( Rva007F5290FieldAddress, 0x10 )
BFME_FIELD_ADDRESS( Rva007F52A0FieldAddress, 0x90 )
BFME_FIELD_ADDRESS( Rva007F52B0FieldAddress, 0x190 )
BFME_FIELD_ADDRESS( Rva007F52E0FieldAddress, 0x1E0 )
BFME_FIELD_ADDRESS( Rva007FFFA0FieldAddress, 0x8 )
BFME_FIELD_ADDRESS( Rva00800510FieldAddress, 0x4 )
BFME_FIELD_ADDRESS( Rva00800680FieldAddress, 0x28C )
BFME_FIELD_ADDRESS( Rva00801190FieldAddress, 0x2A8 )
BFME_FIELD_ADDRESS( Rva008011A0FieldAddress, 0x2B0 )
BFME_FIELD_ADDRESS( Rva00801490FieldAddress, 0x30 )
BFME_FIELD_ADDRESS( Rva008014C0FieldAddress, 0x55 )
BFME_FIELD_ADDRESS( Rva00802170FieldAddress, 0x10 )
BFME_FIELD_ADDRESS( Rva00802190FieldAddress, 0x14 )
BFME_FIELD_ADDRESS( Rva008021C0FieldAddress, 0xB4 )
BFME_FIELD_ADDRESS( Rva008021D0FieldAddress, 0x2B8 )
BFME_FIELD_ADDRESS( Rva00802780FieldAddress, 0x18 )
BFME_FIELD_ADDRESS( Rva008027C0FieldAddress, 0x98 )
BFME_FIELD_ADDRESS( Rva00802DA0FieldAddress, 0xC )
BFME_FIELD_ADDRESS( Rva00802DB0FieldAddress, 0x8C )
BFME_FIELD_ADDRESS( Rva008088F0FieldAddress, 0x18 )
BFME_FIELD_ADDRESS( Rva00808AE0FieldAddress, 0xC )
BFME_FIELD_ADDRESS( Rva00808B10FieldAddress, 0x8C )
BFME_FIELD_ADDRESS( Rva0087DD70FieldAddress, 0x44 )
BFME_FIELD_ADDRESS( Rva00882490FieldAddress, 0xC )
BFME_FIELD_ADDRESS( Rva00894CA0FieldAddress, 0x4 )
BFME_FIELD_ADDRESS( Rva00897480FieldAddress, 0x8 )
BFME_FIELD_ADDRESS( Rva00899490FieldAddress, 0x8 )
BFME_FIELD_ADDRESS( Rva0089A390FieldAddress, 0x8 )
BFME_FIELD_ADDRESS( Rva0089A610FieldAddress, 0x8 )
BFME_FIELD_ADDRESS( Rva0089A7B0FieldAddress, 0x8 )
BFME_FIELD_ADDRESS( Rva0089A950FieldAddress, 0x8 )
BFME_FIELD_ADDRESS( Rva0089AAF0FieldAddress, 0x8 )
BFME_FIELD_ADDRESS( Rva008CBD30FieldAddress, 0x8 )
BFME_FIELD_ADDRESS( Rva008DCC30FieldAddress, 0x58 )
BFME_FIELD_ADDRESS( Rva008DCCD0FieldAddress, 0xC )
BFME_FIELD_ADDRESS( Rva008DCD00FieldAddress, 0xF0 )
BFME_FIELD_ADDRESS( Rva008DCD10FieldAddress, 0xFC )
BFME_FIELD_ADDRESS( Rva009187C0FieldAddress, 0xC )
BFME_FIELD_ADDRESS( Rva00942F10FieldAddress, 0x18 )
BFME_FIELD_ADDRESS( Rva00955940FieldAddress, 0xC )
BFME_FIELD_ADDRESS( Rva00979450FieldAddress, 0xF4 )
BFME_FIELD_ADDRESS( Rva00979460FieldAddress, 0x100 )
BFME_FIELD_ADDRESS( Rva0097E660FieldAddress, 0x208 )
BFME_FIELD_ADDRESS( Rva009CC320FieldAddress, 0x8 )
BFME_FIELD_ADDRESS( Rva00B021D0FieldAddress, 0x4 )

#pragma pack( pop )
