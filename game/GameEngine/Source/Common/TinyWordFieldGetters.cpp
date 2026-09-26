// Word-field getter bodies of the single shape
//
//     mov ax, word ptr [ecx+<DISP32>] / ret
//
// WHAT THE BYTES SHOW.  One 16-bit field is loaded straight through `this` at
// a fixed displacement and returned in AX: a word-field getter,
// `unsigned short C::get() const { return m_value; }`.  The disp32 form
// (opcode 66 8B 81) rather than disp8 is forced by every offset here being
// >= 0x80, so the encoding is a consequence of the offset, not a choice.
//
// ONE AXIS, READ DIRECTLY: the member offset.
//
// IDENTITY IS NOT RECOVERED.  Every class name is derived from the retail RVA.

#define BFME_WORD_FIELD_GETTER( NAME, OFFSET )                            \
	class NAME                                                             \
	{                                                                      \
	public:                                                                \
		unsigned short get() const;                                         \
		char m_lead[ OFFSET ];                                              \
		unsigned short m_value;                                             \
	};                                                                     \
	unsigned short NAME::get() const                                       \
	{                                                                      \
		return m_value;                                                     \
	}

BFME_WORD_FIELD_GETTER( Rva003CBA80, 0x94 )
BFME_WORD_FIELD_GETTER( Rva00642A70, 0x158 )
