// Seven ten-byte __thiscall bodies that leave `this` in eax and write ONE
// constant into ONE field:
//
//     mov eax,ecx / mov dword ptr [eax+<OFFSET>],<VALUE> / ret
//
// WHAT THE BYTES SHOW.  All ten bytes are concrete -- no relocation site.  The
// leading `mov eax,ecx` is the load-bearing byte pair: a plain `void` member
// storing a constant writes straight through ecx and needs no eax at all (see
// Q1ConstantFieldStores.cpp, which is exactly that and two bytes shorter).
// Leaving `this` in eax is what MSVC 7.1 does at the end of a CONSTRUCTOR, so
// these are spelled as constructors.
//
// TWO AXES: the offset and the value.
//
// WHAT THE BYTES CANNOT DECIDE.  Any member that explicitly returned `this`
// compiles to the same ten bytes; the constructor spelling is chosen because it
// needs no invented method name and no invented return type.  Two pairs are
// byte-identical to each other (0x00072A60 / 0x000763F0 store 0xA590217B at +4,
// 0x00083FF0 / 0x00084020 store 0x254B6FAE at +4).  They are four distinct
// addresses in retail, so they are four distinct classes here; the bytes cannot
// say whether the duplicates came from one inline definition or two.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define Q1_CONSTANT_CTOR( NAME, OFFSET, VALUE )                           \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char m_lead[ OFFSET ];                                            \
		unsigned int m_value;                                             \
		NAME();                                                           \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_value = VALUE;                                                  \
	}

Q1_CONSTANT_CTOR( Rva00072A60, 0x4, 0xA590217Bu )
Q1_CONSTANT_CTOR( Rva000763F0, 0x4, 0xA590217Bu )
Q1_CONSTANT_CTOR( Rva00083FF0, 0x4, 0x254B6FAEu )
Q1_CONSTANT_CTOR( Rva00084020, 0x4, 0x254B6FAEu )
Q1_CONSTANT_CTOR( Rva001075E0, 0x4C, 0x00000000u )
Q1_CONSTANT_CTOR( Rva00386070, 0x18, 0x00000000u )
Q1_CONSTANT_CTOR( Rva0073A780, 0x28, 0x00000000u )
