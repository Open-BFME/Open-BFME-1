// Float-field getter bodies of the single shape
//
//     fld dword ptr [ecx+<DISP32>] / ret
//
// WHAT THE BYTES SHOW.  One 32-bit IEEE float is loaded straight through
// `this` at a fixed displacement and returned in ST(0): a float-field getter,
// `float C::get() { return m_value; }`.  The disp32 form (opcode D9 81)
// rather than disp8 is forced by every offset here being >= 0x80, so the
// encoding is a consequence of the offset, not a choice.
//
// ONE AXIS, READ DIRECTLY: the member offset.
//
// IDENTITY IS NOT RECOVERED.  Every class name is derived from the retail RVA.

#define BFME_FLOAT_FIELD_GETTER( NAME, OFFSET )                           \
	class NAME                                                             \
	{                                                                      \
	public:                                                                \
		float get();                                                        \
		char m_lead[ OFFSET ];                                              \
		float m_value;                                                      \
	};                                                                     \
	float NAME::get()                                                      \
	{                                                                      \
		return m_value;                                                     \
	}

BFME_FLOAT_FIELD_GETTER( Rva001B4070, 0x470 )
