// The five byte-identical 13-byte setters at 0x001A1DE0, 0x00360800,
// 0x0045C170, 0x0049C9B0 and 0x0060A6B0.  Retail:
//
//     mov eax,[esp+4] / mov [ecx+0xA4],eax / ret 4
//
// WHAT THE BYTES SHOW.  `this` in ecx and `ret 4`: __thiscall with one dword
// argument, stored whole into the member at offset 0xA4 and nothing else.  The
// store is a full dword with no narrowing and no null check, so the argument is
// four bytes wide; a pointer parameter compiles to the identical thirteen bytes,
// so the bytes do not decide between `int` and a pointer and the spelling below
// asserts only the width.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  A trivial setter is the shape most likely to
// coincide between unrelated classes, and these five sit in five unrelated
// gen_asm dumps spanning 0x001A1DE0 to 0x0060A6B0 -- five different classes that
// happen to keep a member at the same offset, not one function emitted five
// times.  Each is its own class below.
//
// 0xA4 IS A REAL MEMBER OFFSET, and it is the only thing these five have in
// common.  It says the member is the forty-second dword of its class, which
// alone names nothing.
//
// IDENTITY IS NOT RECOVERED.  No name is witnessed for any of the five classes
// or for the member, so each name is derived from its own address.

#define BFME_OFFSET_A4_SETTER( NAME )                                         	class NAME                                                                 	{                                                                          	public:                                                                    		char m_pad[ 0xA4 ];                                                     		int m_value;                                                            		void setValue( int value );                                             	};                                                                         	void NAME::setValue( int value )                                           	{                                                                          		m_value = value;                                                        	}

BFME_OFFSET_A4_SETTER( Rva001A1DE0Owner )
BFME_OFFSET_A4_SETTER( Rva00360800Owner )
BFME_OFFSET_A4_SETTER( Rva0045C170Owner )
BFME_OFFSET_A4_SETTER( Rva0049C9B0Owner )
BFME_OFFSET_A4_SETTER( Rva0060A6B0Owner )
