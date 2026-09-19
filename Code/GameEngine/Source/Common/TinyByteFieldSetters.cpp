// Byte-field setter bodies of the single shape
//
//     mov byte ptr [ecx+<DISP32>],<IMM8> / ret
//
// WHAT THE BYTES SHOW.  A one-byte constant is written straight through `this`
// at a fixed displacement and nothing else happens: a byte-field setter,
// `void C::set() { m_flag = K; }`.  The disp32 form (opcode C6 81) rather than
// disp8 is forced by every offset here being >= 0x80, so the encoding is a
// consequence of the offset, not a choice.  Nothing is read back, so the field
// is only known to be one byte wide.
//
// TWO AXES, BOTH READ DIRECTLY: the member offset and the stored constant
// (0 or 1 throughout, which is what a flag-width field looks like).
//
// IDENTITY IS NOT RECOVERED.  Every class name is derived from the retail RVA.

#define BFME_BYTE_FIELD_SETTER( NAME, OFFSET, VALUE )                     \
	class NAME                                                             \
	{                                                                      \
	public:                                                                \
		void apply();                                                       \
		char m_lead[ OFFSET ];                                              \
		char m_flag;                                                        \
	};                                                                     \
	void NAME::apply()                                                     \
	{                                                                      \
		m_flag = VALUE;                                                     \
	}

BFME_BYTE_FIELD_SETTER( Rva00383730, 0x148, 1 )
BFME_BYTE_FIELD_SETTER( Rva005165F0, 0x17, 0 )
BFME_BYTE_FIELD_SETTER( Rva00516600, 0x13, 1 )
BFME_BYTE_FIELD_SETTER( Rva00516B50, 0x26F, 1 )
BFME_BYTE_FIELD_SETTER( Rva005BDD90, 0x1A7, 0 )
BFME_BYTE_FIELD_SETTER( Rva005BDDA0, 0x1A7, 1 )
BFME_BYTE_FIELD_SETTER( Rva006FA030, 0xBC, 1 )
BFME_BYTE_FIELD_SETTER( Rva0073D440, 0x2429, 0 )
BFME_BYTE_FIELD_SETTER( Rva000C8F60, 0x88, 1 )
BFME_BYTE_FIELD_SETTER( Rva0010CED0, 0x110, 1 )
BFME_BYTE_FIELD_SETTER( Rva0016A7D0, 0x333, 1 )
BFME_BYTE_FIELD_SETTER( Rva0016A7E0, 0x334, 1 )
BFME_BYTE_FIELD_SETTER( Rva0016A7F0, 0x333, 0 )
BFME_BYTE_FIELD_SETTER( Rva0016A800, 0x334, 0 )
BFME_BYTE_FIELD_SETTER( Rva0020FB50, 0xA6, 1 )
BFME_BYTE_FIELD_SETTER( Rva002307C0, 0x11A, 1 )
BFME_BYTE_FIELD_SETTER( Rva002326F0, 0x13C, 0 )
BFME_BYTE_FIELD_SETTER( Rva002ED2D0, 0x108, 1 )
BFME_BYTE_FIELD_SETTER( Rva0035F0C0, 0x13C, 0 )
BFME_BYTE_FIELD_SETTER( Rva0035F0D0, 0x13C, 1 )
BFME_BYTE_FIELD_SETTER( Rva00382780, 0x111, 1 )
BFME_BYTE_FIELD_SETTER( Rva00382790, 0x111, 0 )
BFME_BYTE_FIELD_SETTER( Rva004A64F0, 0x347, 1 )
BFME_BYTE_FIELD_SETTER( Rva004C7460, 0x259, 0 )
BFME_BYTE_FIELD_SETTER( Rva004CAEF0, 0x26C, 1 )
BFME_BYTE_FIELD_SETTER( Rva00537510, 0x43C, 0 )
BFME_BYTE_FIELD_SETTER( Rva0055BD60, 0x258, 1 )
BFME_BYTE_FIELD_SETTER( Rva0056A800, 0x259, 1 )
BFME_BYTE_FIELD_SETTER( Rva0060D340, 0x288, 0 )
BFME_BYTE_FIELD_SETTER( Rva0060D350, 0x288, 0 )
BFME_BYTE_FIELD_SETTER( Rva00695EE0, 0x637, 1 )
BFME_BYTE_FIELD_SETTER( Rva006C5610, 0x1E1CCE, 1 )
BFME_BYTE_FIELD_SETTER( Rva006C5620, 0x1E1CCC, 1 )
BFME_BYTE_FIELD_SETTER( Rva006C5650, 0x2A7CB6, 1 )
BFME_BYTE_FIELD_SETTER( Rva006C5660, 0x2A7CB4, 1 )
BFME_BYTE_FIELD_SETTER( Rva006D1C50, 0x2A7CB8, 1 )
BFME_BYTE_FIELD_SETTER( Rva006D1C60, 0x1E1CD0, 1 )
BFME_BYTE_FIELD_SETTER( Rva006E7AC0, 0x149, 1 )
BFME_BYTE_FIELD_SETTER( Rva006E7AD0, 0x14A, 1 )
BFME_BYTE_FIELD_SETTER( Rva006E7170, 0x54, 1 )
BFME_BYTE_FIELD_SETTER( Rva006E7180, 0x54, 0 )
BFME_BYTE_FIELD_SETTER( Rva0073A5A0, 0x4E0D, 0 )
BFME_BYTE_FIELD_SETTER( Rva00745FE0, 0x23C0, 1 )
BFME_BYTE_FIELD_SETTER( Rva0075B440, 0x12F8, 1 )
BFME_BYTE_FIELD_SETTER( Rva0020A7C0, 0x4C, 0 )
BFME_BYTE_FIELD_SETTER( Rva00465B80, 0x1AC, 1 )
