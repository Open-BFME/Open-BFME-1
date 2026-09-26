// Dword-field getter bodies of the single shape
//
//     mov eax, dword ptr [ecx+<DISP32>] / ret
//
// WHAT THE BYTES SHOW.  One 32-bit field is loaded straight through `this` at
// a fixed displacement and returned in EAX: a dword-field getter,
// `unsigned int C::get() { return m_value; }`.  The disp32 form (opcode 8B 81)
// rather than disp8 is forced by every offset here being >= 0x80, so the
// encoding is a consequence of the offset, not a choice.
//
// ONE AXIS, READ DIRECTLY: the member offset.
//
// IDENTITY IS NOT RECOVERED.  Every class name is derived from the retail RVA.

#define BFME_DWORD_FIELD_GETTER( NAME, OFFSET )                           \
	class NAME                                                             \
	{                                                                      \
	public:                                                                \
		unsigned int get();                                                 \
		char m_lead[ OFFSET ];                                              \
		unsigned int m_value;                                               \
	};                                                                     \
	unsigned int NAME::get()                                               \
	{                                                                      \
		return m_value;                                                     \
	}

BFME_DWORD_FIELD_GETTER( Rva001E0AD0, 0x2A0 )
BFME_DWORD_FIELD_GETTER( Rva001E0C50, 0x4F4 )
BFME_DWORD_FIELD_GETTER( Rva001E0C80, 0x518 )
