// Seven seventeen-byte __thiscall constructors:
//
//     mov eax,ecx / xor ecx,ecx / mov dword ptr [eax],<HEAD>
//     mov [eax+<A>],ecx / mov [eax+<A>+4],ecx / ret
//
// WHAT THE BYTES SHOW.  `mov eax,ecx` with no other use of eax is MSVC 7.1's
// constructor tail (compare Q1ConstantFieldConstructors.cpp).  ecx is zeroed
// once and reused as the source for BOTH later stores, so both of those fields
// are set to the same value and that value is zero.  The store offsets are
// always adjacent dwords.
//
// THE HEAD STORE IS THE TYPE DISCRIMINATOR.  Six of the seven write a RELOCATED
// address into offset 0, with the object`s own constructor doing it and nothing
// else living at offset 0 -- that is a vftable pointer, so those six are
// spelled as classes with a virtual function.  SIX DISTINCT ADDRESSES APPEAR,
// so these are SIX DISTINCT TYPES.  Sharing one class across two of them would
// still byte-match -- the patcher copies a DIR32 operand straight out of retail
// -- while quietly asserting a false identity, and verify_dir32_consistency,
// not the byte gate, is the check that would catch it.  The seventh
// (Rva005886B0) writes the literal 2, which is not an address and carries no
// relocation, so it is spelled as a plain class with an integer first field and
// all seventeen of its bytes are concrete.
//
// WHAT THE BYTES CANNOT DECIDE.  THE FOUR RELOCATED BYTES ARE NOT EVIDENCE.
// Nothing identifies which class each vftable belongs to, how many virtual
// functions it has, or what any of them are; one `virtual void v()` is the
// minimum that makes MSVC lay the object out this way, and no more than that is
// claimed.  The zeroed fields are spelled `int`; a pointer set to null compiles
// identically.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define Q1_VFTABLE_ZERO_CTOR( NAME )                                      \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		virtual void v();                                                 \
		int m_a;                                                          \
		int m_b;                                                          \
		NAME();                                                           \
	};                                                                    \
	void NAME::v()                                                        \
	{                                                                     \
	}                                                                     \
	NAME::NAME()                                                          \
	{                                                                     \
		m_a = 0;                                                          \
		m_b = 0;                                                          \
	}

#define Q1_VFTABLE_ZERO_CTOR_PAD( NAME, PAD )                             \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		virtual void v();                                                 \
		char m_lead[ PAD ];                                               \
		int m_a;                                                          \
		int m_b;                                                          \
		NAME();                                                           \
	};                                                                    \
	void NAME::v()                                                        \
	{                                                                     \
	}                                                                     \
	NAME::NAME()                                                          \
	{                                                                     \
		m_a = 0;                                                          \
		m_b = 0;                                                          \
	}

#define Q1_PLAIN_ZERO_CTOR( NAME, HEAD )                                  \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		unsigned int m_head;                                              \
		int m_a;                                                          \
		int m_b;                                                          \
		NAME();                                                           \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_head = HEAD;                                                    \
		m_a = 0;                                                          \
		m_b = 0;                                                          \
	}

Q1_VFTABLE_ZERO_CTOR( Rva007F01B0 )                     /* vftable 0x0107301C */
Q1_VFTABLE_ZERO_CTOR( Rva000CBAA0 )                     /* vftable 0x01083D18 */
Q1_VFTABLE_ZERO_CTOR( Rva000FBDF0 )                     /* vftable 0x010860C0 */
Q1_VFTABLE_ZERO_CTOR_PAD( Rva00103160, 0xC )           /* vftable 0x01086348 */
Q1_VFTABLE_ZERO_CTOR( Rva00202E50 )                     /* vftable 0x010A5580 */
Q1_PLAIN_ZERO_CTOR( Rva005886B0, 0x2u )
Q1_VFTABLE_ZERO_CTOR( Rva005FC5C0 )                     /* vftable 0x01112A4C */
