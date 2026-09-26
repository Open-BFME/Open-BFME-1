// Twenty-seven leaf predicates, three shapes, no calls.
//
// (1) 0x001FC390 & co -- "is this member exactly K?"
//
//     mov edx,<slot> / xor eax,eax / cmp edx,K / sete al / ret
//
//     The `xor eax,eax` AHEAD of the compare is MSVC 7.1's zero-extend for a
//     `bool` result, so the return is bool, not int.  `cmp` against a signed
//     8-bit immediate (0x83 /7) versus a full dword (0x81 /7) is only an
//     encoding difference and says nothing extra.
//
//     Two members take the value in ecx off the STACK rather than out of an
//     object -- those are free functions of one argument, not accessors.
//
//     Two more compare against 0x004489A0 / 0x00411F54.  Those are not data:
//     both are incremental-link thunk entries the ledger already names, and the
//     address of a function in this image IS its thunk, so the member being
//     compared is a function pointer.  WHICH function is not recovered; the
//     names below are the thunks' own address-derived ledger names.
//
// (2) 0x0018F0D0 & co -- "is this member non-zero?"
//
//     mov eax,<slot> / test eax,eax / setne al / ret
//
//     Note what is ABSENT: no `xor eax,eax`.  Spelling the test as `m_v != 0`
//     makes MSVC zero-extend first (mov edx / xor eax,eax / test edx,edx /
//     setne al) and that is five bytes longer.  The retail shape comes from the
//     branchy spelling `if (m_v) return true; return false;`.  A `mov al,` load
//     with `test al,al` proves the member is one byte wide; a dword load proves
//     it is not.
//
// (3) 0x000B55B0 & co -- "is bit N of this member set?"
//
//     mov eax,<slot> / shr eax,N / and eax,1 / ret
//
//     `shr`, never `sar`: the member is UNSIGNED.  The result is left in the
//     full eax with no `setne`, so the return is int-width, not bool -- except
//     at 0x005887C0, where the whole computation is done in `al` (shr al,N /
//     and al,1) and the member is a byte.  Keeping MSVC in 8-bit arithmetic
//     needs the shift and mask written as statements on a byte variable; the
//     one-expression spelling promotes to int and emits the dword form.
//
// IDENTITY IS NOT RECOVERED.  Every class and function name is derived from the
// address of the row it stands for.  Member offsets, constants and shift counts
// are read straight out of the bytes; the names given to those members are not
// evidence of anything.

// ------------------------------------------------------------------ shape (1)

#define BFME_MEMBER_EQUALS( NAME, OFFSET, VALUE )                         \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		bool is() const;                                                  \
		char m_lead[ OFFSET ];                                            \
		int m_value;                                                      \
	};                                                                    \
	bool NAME::is() const                                                 \
	{                                                                     \
		return m_value == VALUE;                                          \
	}

BFME_MEMBER_EQUALS( Rva001FC390, 0x28, 1 )
BFME_MEMBER_EQUALS( Rva00266340, 0x38, 3 )
BFME_MEMBER_EQUALS( Rva00360690, 0x20, 2 )
BFME_MEMBER_EQUALS( Rva0049AB70, 0x04, 2 )
BFME_MEMBER_EQUALS( Rva00681A00, 0x0c, 1 )
BFME_MEMBER_EQUALS( Rva006959D0, 0x68, -1 )
BFME_MEMBER_EQUALS( Rva00673690, 0x24, 0x447 )

bool Rva003D5140( int value ) { return value == 1; }
bool Rva00538B40( int value ) { return value == -1; }

void j_000489a0();
void j_00011f54();

typedef void ( *R1PlainRoutine )();

class Rva00477D80
{
public:
	bool is() const;
	char m_lead[ 0x1e0 ];
	R1PlainRoutine m_routine;
};
bool Rva00477D80::is() const { return m_routine == &j_000489a0; }

class Rva00477DD0
{
public:
	bool is() const;
	char m_lead[ 0x1e0 ];
	R1PlainRoutine m_routine;
};
bool Rva00477DD0::is() const { return m_routine == &j_00011f54; }

// ------------------------------------------------------------------ shape (2)

#define BFME_MEMBER_NONZERO( NAME, OFFSET )                               \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		bool has() const;                                                 \
		char m_lead[ OFFSET ];                                            \
		int m_value;                                                      \
	};                                                                    \
	bool NAME::has() const                                                \
	{                                                                     \
		if( m_value )                                                     \
			return true;                                                  \
		return false;                                                     \
	}

#define BFME_MEMBER_BYTE_NONZERO( NAME, OFFSET )                          \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		bool has() const;                                                 \
		char m_lead[ OFFSET ];                                            \
		char m_value;                                                     \
	};                                                                    \
	bool NAME::has() const                                                \
	{                                                                     \
		if( m_value )                                                     \
			return true;                                                  \
		return false;                                                     \
	}

BFME_MEMBER_NONZERO( Rva0018F0D0, 0x14 )
BFME_MEMBER_NONZERO( Rva0060D2C0, 0xa8 )
BFME_MEMBER_NONZERO( Rva00610D50, 0x220 )
BFME_MEMBER_NONZERO( Rva006E1C50, 0xb0 )
BFME_MEMBER_BYTE_NONZERO( Rva001BD680, 0x3ac )
BFME_MEMBER_BYTE_NONZERO( Rva001BE120, 0x291 )
BFME_MEMBER_BYTE_NONZERO( Rva00890F70, 0x04 )

// ------------------------------------------------------------------ shape (3)

#define BFME_MEMBER_BIT( NAME, OFFSET, SHIFT )                            \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		int bit() const;                                                  \
		char m_lead[ OFFSET ];                                            \
		unsigned int m_bits;                                              \
	};                                                                    \
	int NAME::bit() const                                                 \
	{                                                                     \
		return ( m_bits >> SHIFT ) & 1;                                   \
	}

#define BFME_MEMBER_BIT_HEAD( NAME, SHIFT )                               \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		int bit() const;                                                  \
		unsigned int m_bits;                                              \
	};                                                                    \
	int NAME::bit() const                                                 \
	{                                                                     \
		return ( m_bits >> SHIFT ) & 1;                                   \
	}

BFME_MEMBER_BIT( Rva000B55B0, 0x98, 1 )
BFME_MEMBER_BIT( Rva000B55C0, 0x98, 3 )
BFME_MEMBER_BIT( Rva000C4D30, 0x90, 6 )
BFME_MEMBER_BIT( Rva001B52B0, 0x3f0, 7 )
BFME_MEMBER_BIT( Rva001EDBF0, 0x98, 9 )
BFME_MEMBER_BIT( Rva002BC820, 0x3f0, 6 )
BFME_MEMBER_BIT( Rva0038A0A0, 0x90, 4 )
BFME_MEMBER_BIT_HEAD( Rva00910D50, 0x14 )

class Rva005887C0
{
public:
	unsigned char bit() const;
	char m_lead[ 0x20 ];
	unsigned char m_bits;
};
unsigned char Rva005887C0::bit() const
{
	unsigned char value = m_bits;
	value >>= 2;
	value &= 1;
	return value;
}
