// Byte-field getter bodies of the single shape
//
//     mov al, byte ptr [ecx+<DISP32>] / ret
//
// WHAT THE BYTES SHOW.  One byte is loaded straight through `this` at a fixed
// displacement and returned in AL: a byte-field getter,
// `unsigned char C::get() { return m_value; }`.  The disp32 form (opcode 8A 81)
// rather than disp8 is forced by every offset here being >= 0x80, so the
// encoding is a consequence of the offset, not a choice.  Nothing else is
// touched, so the field is only known to be one byte wide.
//
// ONE AXIS, READ DIRECTLY: the member offset.
//
// IDENTITY IS NOT RECOVERED.  Every class name is derived from the retail RVA.

#define BFME_BYTE_FIELD_GETTER( NAME, OFFSET )                            \
	class NAME                                                             \
	{                                                                      \
	public:                                                                \
		unsigned char get();                                                \
		char m_lead[ OFFSET ];                                              \
		unsigned char m_value;                                              \
	};                                                                     \
	unsigned char NAME::get()                                              \
	{                                                                      \
		return m_value;                                                     \
	}

BFME_BYTE_FIELD_GETTER( Rva000ECA10, 0x486 )
