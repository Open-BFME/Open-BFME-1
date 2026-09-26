// Six tiny __thiscall readers that widen a sub-dword member into eax and return
// it:
//
//     movzx eax,word ptr [ecx+<OFFSET>] / ret      (five of them)
//     movzx eax,byte ptr [ecx+<OFFSET>] / ret      (one of them)
//
// WHAT THE BYTES SHOW.  The whole body is eight concrete bytes with no
// relocation site, so nothing here is copied from retail -- the offset, the
// operand width and the widening are all proven.
//
// THE RETURN TYPE IS DECIDED BY THE WIDENING, not guessed.  MSVC 7.1 keeps a
// narrow return narrow: `unsigned short get() const { return m_v; }` compiles
// to `mov ax,[ecx+K]` (66 8B 81 ..) and `unsigned char get()` to `mov al,..`
// (8A 81 ..).  Only a WIDER return type forces the zero-extend, so these are
// int-returning accessors over an unsigned short / unsigned char member.  The
// zero-extend (movzx, not movsx) proves the member is unsigned.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address, and the
// leading char array is padding that reproduces the proven offset -- it is not
// a claim about what else lives in the object.  Two of the six (000F9430 and
// 001BDB10) are byte-for-byte identical; the bytes cannot say whether they are
// two accessors of one class or one accessor of two.

#define BFME_WIDENED_U16_GETTER( NAME, OFFSET )                           \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		int get() const;                                                  \
		char m_lead[ OFFSET ];                                            \
		unsigned short m_value;                                           \
	};                                                                    \
	int NAME::get() const                                                 \
	{                                                                     \
		return m_value;                                                   \
	}

#define BFME_WIDENED_U8_GETTER( NAME, OFFSET )                            \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		int get() const;                                                  \
		char m_lead[ OFFSET ];                                            \
		unsigned char m_value;                                            \
	};                                                                    \
	int NAME::get() const                                                 \
	{                                                                     \
		return m_value;                                                   \
	}

BFME_WIDENED_U16_GETTER( Rva000F9430, 0x47A )
BFME_WIDENED_U16_GETTER( Rva000FBFB0, 0x480 )
BFME_WIDENED_U16_GETTER( Rva000FBFC0, 0x47C )
BFME_WIDENED_U16_GETTER( Rva001BDB10, 0x47A )
BFME_WIDENED_U16_GETTER( Rva001BDB20, 0x47E )
BFME_WIDENED_U8_GETTER( Rva002DB190, 0x509 )
