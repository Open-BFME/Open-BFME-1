// The three byte-identical 11-byte pointer-presence predicates at 0x001ED500,
// 0x003BC7D0 and 0x0040E080:
//
//     mov edx,[ecx+0x34] / xor eax,eax / test edx,edx / setne al / ret
//
// WHAT THE BYTES SHOW.  `this` in ecx, nothing on the stack, plain `ret`:
// __thiscall taking no arguments.  `xor eax,eax` ahead of the flag-setting
// instruction and a write to AL ONLY is MSVC's canonical bool return -- the
// upper three bytes are zeroed before the compare so the setcc can write one
// byte; a wider return type would sign- or zero-extend afterwards instead.
//
// `setne` rather than `sete` is a source fact: this returns `member != 0`, and
// the opposite sense is a different byte.  The member is loaded as a full dword
// and compared only against zero, and nothing reads through it, so it is a
// pointer whose pointee never appears.
//
// These three are the whole family: the same eleven bytes occur nowhere else in
// the image.  That is unusual for a body this short, and it is the offset that
// makes it so -- the 0x00 and 0x04 variants of the same predicate fold into
// dozens of copies each and are already claimed as separate hand-reconciled
// bodies in this drawer, while 0x34 has exactly these three.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Three addresses far apart in the image, each
// its own accessor on its own class.
//
// IDENTITY IS NOT RECOVERED.  The names are address-derived and disclaim
// identity.

#define BFME_NONZERO_TEST_AT_34( NAME )                                       \
	class NAME##Held;                                                         \
	class NAME##Holder                                                        \
	{                                                                         \
	public:                                                                   \
		char m_leading[ 0x34 ];                                               \
		NAME##Held *m_tested;                                                 \
		bool isSet() const;                                                   \
	};                                                                        \
	bool NAME##Holder::isSet() const { return m_tested != 0; }

BFME_NONZERO_TEST_AT_34( Rva001ED500 )
BFME_NONZERO_TEST_AT_34( Rva003BC7D0 )
BFME_NONZERO_TEST_AT_34( Rva0040E080 )
