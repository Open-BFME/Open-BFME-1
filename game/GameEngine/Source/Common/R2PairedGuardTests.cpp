// Seven tiny __thiscall predicates that test TWO things in sequence and answer
// with a constant, or -- in one case -- with a third load:
//
//     mov eax,[ecx+<A>] / test eax,eax / je no
//     <second test> / je no
//     mov eax,1 / ret          (or mov al,1)
//     no: xor eax,eax / ret    (or xor al,al)
//
// WHAT THE BYTES SHOW.  `this` in ecx, bare `ret`: __thiscall, no stack
// arguments.  BOTH `je`s TARGET THE SAME `xor`, and the true arm falls out past
// it -- the short-circuit shape of `if ( a && b ) { return 1; } return 0;`.
// Nothing is relocated in any of the seven; every byte is concrete.
//
// THE RESULT WIDTH IS SOURCE EVIDENCE.  Five answer with `mov eax,1` (five
// bytes) where `mov al,1` (two) would have done, so those return a four-byte
// value; two use `mov al,1` with `xor al,al` and return one byte.  A size
// comparison alone cannot separate the two shapes, but the opcodes do.
//
// THE OPERAND WIDTH IS READ THE SAME WAY: `mov al,[ecx+K]` + `test al,al` is a
// one-byte flag, `mov eax,[ecx+K]` + `test eax,eax` is a four-byte one.  This
// family carries both, and 0x00409550 and 0x0075C990 test two four-byte fields
// OF THIS while 0x003968A0 and 0x005A44B0 test two adjacent one-byte flags.
//
// TWO MEMBERS ARE NOT PREDICATES AT ALL and are only in the family because the
// mnemonic sequence coincides:
//   0x003D4CA0 chains -- it tests a pointer, tests a pointer INSIDE it, and
//     then returns a third field rather than a constant;
//   0x0092D660 tests a BIT, not a value: `test ch,4` is the 0x400 bit of a
//     four-byte field read at +0x18, so the second condition is a mask test.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

// Two pointers, the second reached through the first.

#define R2_PAIRED_POINTER_TEST( NAME, A, B )                              \
	class NAME##Inner                                                     \
	{                                                                     \
	public:                                                               \
		char m_leading[ B ];                                                \
		void *m_second;                                                     \
	};                                                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char m_leading[ A ];                                                \
		NAME##Inner *m_first;                                               \
		int test();                                                         \
	};                                                                    \
	int NAME::test()                                                      \
	{                                                                     \
		if ( m_first && m_first->m_second )                                 \
		{                                                                   \
			return 1;                                                         \
		}                                                                   \
		return 0;                                                           \
	}

// Two adjacent one-byte flags of this, four-byte result.

#define R2_PAIRED_FLAG_TEST( NAME, A )                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char m_leading[ A ];                                                \
		bool m_first;                                                       \
		bool m_second;                                                      \
		int test();                                                         \
	};                                                                    \
	int NAME::test()                                                      \
	{                                                                     \
		if ( m_first && m_second )                                          \
		{                                                                   \
			return 1;                                                         \
		}                                                                   \
		return 0;                                                           \
	}

// Two four-byte fields of this, one-byte result.  THE TWO MEMBERS DISAGREE ON
// WHICH IS TESTED FIRST: 0x0075C990 loads +0xDC then +0xF8 (ascending) while
// 0x00409550 loads +8 then +4 (descending).  Load order is source order, so
// the two get different spellings; nothing else about them differs.

#define R2_PAIRED_FIELD_TEST( NAME, LOW, HIGH )                           \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char m_leadingA[ LOW ];                                             \
		void *m_first;                                                      \
		char m_leadingB[ HIGH - LOW - 4 ];                                  \
		void *m_second;                                                     \
		bool test();                                                        \
	};                                                                    \
	bool NAME::test()                                                     \
	{                                                                     \
		if ( m_first && m_second )                                          \
		{                                                                   \
			return true;                                                      \
		}                                                                   \
		return false;                                                       \
	}

#define R2_PAIRED_FIELD_TEST_ADJACENT( NAME, LOW )                       	class NAME                                                            	{                                                                     	public:                                                               		char m_leading[ LOW ];                                              		void *m_second;                                                     		void *m_first;                                                      		bool test();                                                        	};                                                                    	bool NAME::test()                                                     	{                                                                     		if ( m_first && m_second )                                          		{                                                                   			return true;                                                      		}                                                                   		return false;                                                       	}

R2_PAIRED_POINTER_TEST( Rva0026FD00, 0x30, 0x58 )
R2_PAIRED_FLAG_TEST( Rva003968A0, 0x2C )
R2_PAIRED_FLAG_TEST( Rva005A44B0, 0x4DA1 )
R2_PAIRED_FIELD_TEST_ADJACENT( Rva00409550, 0x04 )
R2_PAIRED_FIELD_TEST( Rva0075C990, 0xDC, 0xF8 )

// The chained accessor: tests two pointers and returns a field of the second.

class Rva003D4CA0Inner
{
public:
	char m_leading[ 0x28 ];
	int m_value;
};
class Rva003D4CA0Outer
{
public:
	char m_leading[ 8 ];
	Rva003D4CA0Inner *m_inner;
};
class Rva003D4CA0
{
public:
	Rva003D4CA0Outer *m_outer;
	int get();
};
int Rva003D4CA0::get()
{
	if ( m_outer && m_outer->m_inner )
	{
		return m_outer->m_inner->m_value;
	}
	return 0;
}

// The mask test: `test ch,4` is bit 0x400 of the four-byte field at +0x18.

class Rva0092D660Inner
{
public:
	char m_leading[ 0x18 ];
	unsigned int m_flags;
};
class Rva0092D660
{
public:
	char m_leading[ 0xC8 ];
	Rva0092D660Inner *m_inner;
	int test();
};
int Rva0092D660::test()
{
	if ( m_inner && ( m_inner->m_flags & 0x400 ) )
	{
		return 1;
	}
	return 0;
}
