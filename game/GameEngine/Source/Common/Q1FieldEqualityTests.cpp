// Seven fifteen-byte __thiscall members that answer "does this field equal
// this small constant?":
//
//     mov edx,[ecx+<OFFSET>] / xor eax,eax / cmp edx,<VALUE> / sete al / ret
//
// WHAT THE BYTES SHOW.  All fifteen bytes are concrete -- no relocation site --
// so the offset and the compared constant are read directly off the
// instruction stream.  Same `xor eax,eax` + `set<cc> al` shape as
// Q1PointerPresenceTests.cpp, so the return is a one-byte boolean; the only
// difference is `sete` against an imm8 instead of `setne` against zero.
//
// TWO AXES: the offset and the constant.  Six of the seven read the SAME offset
// (0x10C) and differ only in the constant, and those constants run 1..7 with no
// gaps -- the shape of a set of "is this the Nth kind?" predicates over one
// small enumerated field.  The bytes support that pattern; they do not name the
// field or any of the seven values, and nothing here assumes the six that share
// an offset share a type, so each is spelled as its own class.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define Q1_EQUALS_CONSTANT( NAME, OFFSET, VALUE )                         \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char m_lead[ OFFSET ];                                            \
		int m_field;                                                      \
		bool is();                                                        \
	};                                                                    \
	bool NAME::is()                                                       \
	{                                                                     \
		return m_field == VALUE;                                          \
	}

Q1_EQUALS_CONSTANT( Rva0036BA40, 0x9C, 4 )
Q1_EQUALS_CONSTANT( Rva0006B020, 0x10C, 5 )
Q1_EQUALS_CONSTANT( Rva000C8890, 0x10C, 2 )
Q1_EQUALS_CONSTANT( Rva000E6970, 0x10C, 3 )
Q1_EQUALS_CONSTANT( Rva00321EC0, 0x10C, 6 )
Q1_EQUALS_CONSTANT( Rva004E2570, 0x10C, 1 )
Q1_EQUALS_CONSTANT( Rva0052ADA0, 0x10C, 7 )
