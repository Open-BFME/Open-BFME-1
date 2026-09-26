// Twenty tiny __thiscall members that write ONE constant into ONE field of
// the object and return:
//
//     mov dword ptr [ecx+<OFFSET>],<VALUE> / ret
//
// WHAT THE BYTES SHOW.  Every byte of every one of these bodies is concrete --
// there is no relocation site anywhere in the family -- so the field offset,
// the stored value, and the fact that the store is four bytes wide are read
// directly off the instruction stream.  Nothing is loaded, nothing is called,
// and no flag is set: the store is the whole function.
//
// TWO AXES: the offset and the value.  Twelve members need the disp32 form
// (offset >= 0x80, up to 0x17084) and eight fit disp8; that split is forced by
// the offset alone, so it is not a third axis.
//
// WHAT THE BYTES CANNOT DECIDE.  The stored field is spelled `unsigned int` and
// the value is written in hex.  One member (Rva00422490) writes 0xBF800000,
// which is the IEEE-754 encoding of -1.0f, and MSVC 7.1 stores a float constant
// with exactly this integer `mov`; the bytes cannot tell a float field
// initialised to -1.0f from an integer field set to 0xBF800000.  The hex
// spelling is the one that asserts less.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define Q1_CONSTANT_STORE( NAME, OFFSET, VALUE )                          \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char m_lead[ OFFSET ];                                            \
		unsigned int m_value;                                             \
		void set();                                                       \
	};                                                                    \
	void NAME::set()                                                      \
	{                                                                     \
		m_value = VALUE;                                                  \
	}

Q1_CONSTANT_STORE( Rva000C98F0, 0x278, 0x00000000u )
Q1_CONSTANT_STORE( Rva0026F590, 0x1D8, 0x00000000u )
Q1_CONSTANT_STORE( Rva003368C0, 0x17080, 0x00000019u )
Q1_CONSTANT_STORE( Rva0043BA70, 0x814, 0x00000000u )
Q1_CONSTANT_STORE( Rva00537C00, 0x188, 0x00000000u )
Q1_CONSTANT_STORE( Rva00662E70, 0x12110, 0x00000000u )
Q1_CONSTANT_STORE( Rva0016A680, 0x160, 0x00000000u )
Q1_CONSTANT_STORE( Rva003368B0, 0x17080, 0x00000001u )
Q1_CONSTANT_STORE( Rva003368D0, 0x17084, 0x00000019u )
Q1_CONSTANT_STORE( Rva0036B9B0, 0x9C, 0x00000004u )
Q1_CONSTANT_STORE( Rva006C90A0, 0x2FE0, 0x00000000u )
Q1_CONSTANT_STORE( Rva0073A630, 0xC0, 0x00000000u )

Q1_CONSTANT_STORE( Rva0006BBD0, 0x34, 0x00000006u )
Q1_CONSTANT_STORE( Rva0014A100, 0x18, 0x00000000u )
Q1_CONSTANT_STORE( Rva0016AA60, 0x20, 0x00000000u )
Q1_CONSTANT_STORE( Rva00214610, 0x2C, 0x00000000u )
Q1_CONSTANT_STORE( Rva00360650, 0x20, 0x00000001u )
Q1_CONSTANT_STORE( Rva00422490, 0x4, 0xBF800000u )
Q1_CONSTANT_STORE( Rva00695A50, 0x30, 0x00000004u )
Q1_CONSTANT_STORE( Rva008D5E60, 0x24, 0x00000000u )
