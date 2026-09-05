// 38 sixteen-byte __thiscall constructors that write exactly two dwords and
// return `this`, in the two possible source orders:
//
//     mov eax,ecx / mov [eax],<A>      / mov [eax+<OFF>],<B> / ret      (20)
//     mov eax,ecx / mov [eax+4],<B>    / mov [eax],<A>       / ret      (18)
//
// WHAT THE BYTES SHOW.  THE ORDER OF THE TWO STORES IS SOURCE ORDER, and it is
// the whole difference between the two groups -- no other byte differs in shape.
// In the first group the leading store comes first and its operand is, in
// seventeen of twenty members, an address in the image's read-only data; one of
// those seventeen (0x004B2C80) is called as a base constructor by the vptr-only
// constructors in MidVptrOnlyDerivedCtors.cpp, which requires a vptr at offset
// 0, so the first group is spelled as a polymorphic class whose constructor
// initialises one data member.  In the second group the leading store comes
// LAST, which a vptr store cannot do -- MSVC always writes the vptr before any
// member initialiser -- so there the leading dword is an ordinary pointer member
// and the class is not polymorphic.
//
// The three first-group members whose leading operand is 0 or -1 (0x00233C80,
// 0x002320A0, 0x000AF850) are plain integers, not addresses, and are spelled
// with two data members accordingly.
//
// AXES: the two stored values and the second member's offset (4, 8, 0xC or 0x2C).
// Stored values include 99999.0f, 1.0f, 1, 0 and -1; a float constant is stored
// as its raw dword by an immediate move, exactly as an int is.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

// polymorphic: vptr at offset 0 written first, then one member
#define BFME_VPTR_MEMBER_CTOR( NAME, TYPE, VALUE )                        \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		virtual void handle();                                            \
		TYPE m_value;                                                     \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_value = VALUE;                                                  \
	}

#define BFME_VPTR_GAP_MEMBER_CTOR( NAME, TYPE, PAD, VALUE )               \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		virtual void handle();                                            \
		char m_gap[ PAD ];                                                \
		TYPE m_value;                                                     \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_value = VALUE;                                                  \
	}

// two plain data members, leading one written first
#define BFME_LEADING_FIRST_CTOR( NAME, TYPE0, VALUE0, TYPE1, VALUE1 )     \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		TYPE0 m_first;                                                    \
		TYPE1 m_second;                                                   \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_first = VALUE0;                                                 \
		m_second = VALUE1;                                                \
	}

#define BFME_LEADING_FIRST_GAP_CTOR( NAME, TYPE0, VALUE0, TYPE1, PAD, VALUE1 ) \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		TYPE0 m_first;                                                    \
		char m_gap[ PAD ];                                                \
		TYPE1 m_second;                                                   \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_first = VALUE0;                                                 \
		m_second = VALUE1;                                                \
	}

// two plain data members, trailing one written first
#define BFME_TRAILING_FIRST_CTOR( NAME, TABLE )                           \
	extern int TABLE;                                                     \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		const void *m_pointer;                                            \
		int m_value;                                                      \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_value = 0;                                                      \
		m_pointer = &TABLE;                                               \
	}

BFME_VPTR_GAP_MEMBER_CTOR( Rva001FABC0, float, 4, 99999.0f )
BFME_LEADING_FIRST_GAP_CTOR( Rva00233C80, int, 0, int, 8, 0 )
BFME_VPTR_MEMBER_CTOR( Rva004B2C80, int, 0 )
BFME_VPTR_MEMBER_CTOR( Rva00087320, int, 0 )
BFME_VPTR_MEMBER_CTOR( Rva000AF7C0, int, 0 )
BFME_LEADING_FIRST_CTOR( Rva000AF850, int, -1, float, 1.0f )
BFME_VPTR_MEMBER_CTOR( Rva000C3B70, int, 0 )
BFME_VPTR_GAP_MEMBER_CTOR( Rva001246D0, int, 4, 1 )
BFME_LEADING_FIRST_CTOR( Rva002320A0, int, 0, int, -1 )
BFME_VPTR_MEMBER_CTOR( Rva00336720, int, 0 )
BFME_VPTR_MEMBER_CTOR( Rva003B7B60, int, 0 )
BFME_VPTR_GAP_MEMBER_CTOR( Rva003BD6D0, int, 8, 0 )
BFME_VPTR_GAP_MEMBER_CTOR( Rva003BEA00, int, 8, 0 )
BFME_VPTR_MEMBER_CTOR( Rva0042ECB0, int, 0 )
BFME_VPTR_MEMBER_CTOR( Rva005FDB40, int, 0 )
BFME_VPTR_MEMBER_CTOR( Rva005FE8C0, int, 0 )
BFME_VPTR_GAP_MEMBER_CTOR( Rva0073A790, int, 40, 0 )
BFME_VPTR_MEMBER_CTOR( Rva007D0CB0, int, 0 )

BFME_TRAILING_FIRST_CTOR( Rva000C3E60, g_target_000C3E60 )
BFME_TRAILING_FIRST_CTOR( Rva000FBDC0, g_target_000FBDC0 )
BFME_TRAILING_FIRST_CTOR( Rva0015B910, g_target_0015B910 )
BFME_TRAILING_FIRST_CTOR( Rva00160C70, g_target_00160C70 )
BFME_TRAILING_FIRST_CTOR( Rva00218000, g_target_00218000 )
BFME_TRAILING_FIRST_CTOR( Rva00291860, g_target_00291860 )
BFME_TRAILING_FIRST_CTOR( Rva00292520, g_target_00292520 )
BFME_TRAILING_FIRST_CTOR( Rva002C74F0, g_target_002C74F0 )
BFME_TRAILING_FIRST_CTOR( Rva003850D0, g_target_003850D0 )
BFME_TRAILING_FIRST_CTOR( Rva0046EF80, g_target_0046EF80 )
BFME_TRAILING_FIRST_CTOR( Rva00472DD0, g_target_00472DD0 )
BFME_TRAILING_FIRST_CTOR( Rva00499FA0, g_target_00499FA0 )
BFME_TRAILING_FIRST_CTOR( Rva004C5560, g_target_004C5560 )
BFME_TRAILING_FIRST_CTOR( Rva004C55B0, g_target_004C55B0 )
BFME_TRAILING_FIRST_CTOR( Rva0051D450, g_target_0051D450 )
BFME_TRAILING_FIRST_CTOR( Rva005891C0, g_target_005891C0 )
BFME_TRAILING_FIRST_CTOR( Rva0058B300, g_target_0058B300 )
BFME_TRAILING_FIRST_CTOR( Rva007D1E60, g_target_007D1E60 )
