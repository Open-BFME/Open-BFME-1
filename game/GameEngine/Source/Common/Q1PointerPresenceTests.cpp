// Eleven fourteen-byte __thiscall members that answer "is this field
// non-zero?":
//
//     mov edx,[ecx+<OFFSET>] / xor eax,eax / test edx,edx / setne al / ret
//
// WHAT THE BYTES SHOW.  All fourteen bytes are concrete -- no relocation site.
// The loaded dword is only ever tested, never used, and the result is
// materialised with `setne` into a zeroed eax, which is MSVC 7.1's shape for
// returning a one-byte boolean.  `xor eax,eax` ahead of the test is the
// load-bearing detail: the whole of eax is being defined, so the return is a
// `bool`, not a `char` with three garbage bytes above it.
//
// ONE AXIS: the field offset (disp32 in every member -- every offset is >=
// 0x80).
//
// WHAT THE BYTES CANNOT DECIDE.  The field is spelled `void *` because it is
// tested against zero and used for nothing else; an `int` compared against 0
// compiles to the same fourteen bytes.  Neither spelling is provable here.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define Q1_PRESENCE_TEST( NAME, OFFSET )                                  \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char m_lead[ OFFSET ];                                            \
		void *m_field;                                                    \
		bool has();                                                       \
	};                                                                    \
	bool NAME::has()                                                      \
	{                                                                     \
		return m_field != 0;                                              \
	}

Q1_PRESENCE_TEST( Rva001BE100, 0x284 )
Q1_PRESENCE_TEST( Rva001BEF30, 0x280 )
Q1_PRESENCE_TEST( Rva000C3EA0, 0x9C )
Q1_PRESENCE_TEST( Rva0016E350, 0x214 )
Q1_PRESENCE_TEST( Rva0034C400, 0x244 )
Q1_PRESENCE_TEST( Rva003829B0, 0x1B8 )
Q1_PRESENCE_TEST( Rva004105F0, 0x2E0 )
Q1_PRESENCE_TEST( Rva00427460, 0x3B0 )
Q1_PRESENCE_TEST( Rva004653C0, 0x1EC )
Q1_PRESENCE_TEST( Rva005111F0, 0x118 )
Q1_PRESENCE_TEST( Rva00728160, 0xB8 )
