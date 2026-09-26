// Six predicates of the form `return x == A || x == B;`:
//
//     mov eax,<x> / cmp eax,A / je true / cmp eax,B / je true
//     xor eax,eax / ret / true: mov eax,1 / ret
//
// WHAT THE BYTES SHOW.  Five rows end `mov eax,1` -- a five-byte immediate into
// the full register -- which is an INT return; the sixth (0x004D8F50) ends
// `mov al,1` after `xor al,al`, which is a one-byte return.  Both are written
// accordingly.  The two comparisons are separate `cmp`/`je` pairs sharing a
// destination, which is short-circuit `||` and not an arithmetic fold.
//
// A `bool` return written as `return a || b;` does NOT give the one-byte form:
// MSVC 7.1 materialises the `||` as an int and emits `mov eax,1` regardless.
// Only `if (a || b) return true; return false;` produces `xor al,al`/`mov al,1`.
//
// FIVE MEMBERS, ONE FREE FUNCTION.  Four read a member at a fixed offset
// (0x004, 0x034, 0x0A8 twice, 0x10C); 0x004D8F50 reads its single __cdecl
// argument off [esp+4].  0x00410890 and 0x004108B0 read the SAME offset with
// different constant pairs, so they are two predicates on one class and share
// a declaration here.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived, and the compared field
// is typed `int` only because the compare is a dword compare -- an enum with
// int underlying type encodes identically.

#define BFME_TWO_VALUE_TEST( NAME, OFFSET, A, B )                         \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		int isEither() const;                                             \
		char m_lead[ OFFSET ];                                            \
		int m_state;                                                      \
	};                                                                    \
	int NAME::isEither() const                                            \
	{                                                                     \
		return m_state == ( A ) || m_state == ( B );                      \
	}

// @?isEither@Rva0029BBC0@@QBEHXZ 0x0029BBC0
BFME_TWO_VALUE_TEST( Rva0029BBC0, 0x004, 1, 3 )
// @?isEither@Rva0075AF00@@QBEHXZ 0x0075AF00
BFME_TWO_VALUE_TEST( Rva0075AF00, 0x034, 0x400, 0x800 )
// @?isEither@Rva0005C5E0@@QBEHXZ 0x0005C5E0
BFME_TWO_VALUE_TEST( Rva0005C5E0, 0x10C, 1, 5 )

class Rva00410890
{
public:
	int isOneOrTwo() const;
	int isThreeOrFour() const;
	char m_lead[ 0xA8 ];
	int m_state;
};

// @?isOneOrTwo@Rva00410890@@QBEHXZ 0x00410890
int Rva00410890::isOneOrTwo() const
{
	return m_state == 1 || m_state == 2;
}

// @?isThreeOrFour@Rva00410890@@QBEHXZ 0x004108B0
int Rva00410890::isThreeOrFour() const
{
	return m_state == 3 || m_state == 4;
}

// @?Rva004D8F50@@YA_NH@Z 0x004D8F50
bool Rva004D8F50( int state )
{
	if( state == 3 || state == 2 )
		return true;
	return false;
}
