// Ten 25-byte __thiscall const members that answer the element count of a
// half-open pointer range held in the object:
//
//   mov eax,[ecx]      / mov edx,[ecx+<END>] / sub edx,eax
//   mov eax,<MAGIC>    / imul edx / sar edx,<SHIFT>
//   mov eax,edx / shr eax,31 / add eax,edx / ret
//
// WHAT THE BYTES SHOW.  The subtraction is followed by MSVC's SIGNED
// divide-by-constant sequence (magic multiply, arithmetic shift, then the
// shr-31/add that rounds a negative quotient toward zero), which is what a
// T* - T* difference compiles to.  The divisor is therefore sizeof(T), and it
// is recovered exactly from the (magic, shift) pair: 2^(32+SHIFT)/MAGIC.
// The result leaves in eax at full int width, so the return type is int, not
// a short or a bool.
//
// TWO AXES, BOTH FULLY CONCRETE.  These bodies carry NO relocation at all --
// all 25 bytes of every row are compared against retail, nothing is copied in
// from the target.  The axes are the element size and the offset the END
// pointer sits at (+4 for two adjacent pointers, +8 when one dword separates
// them; the BEGIN pointer is always at offset 0 because `sub edx,eax`
// subtracts the offset-0 load from the other one, and a count is not negative).
//
// WHAT THE BYTES DO NOT DECIDE.  Nothing distinguishes `return m_end -
// m_begin;`, `return (int)(m_end - m_begin);` and a two-local spelling -- all
// three compile to the identical 25 bytes, so the least-asserting one is used.
// The element TYPE is not recovered, only its size; Q2ElemNN is a placeholder
// of the right width.  The dword between the two pointers in the +8 rows is
// unidentified.  Two rows (0x00251A60 and 0x0075D200) agree on every byte, so
// nothing here tells them apart; they get one class each because one source
// function cannot occupy two addresses.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define Q2_RANGE_ELEMENT( SIZE )                                          \
	class Q2Elem##SIZE                                                    \
	{                                                                     \
		char m_unreconstructed[ SIZE ];                                   \
	};

Q2_RANGE_ELEMENT( 44 )
Q2_RANGE_ELEMENT( 88 )
Q2_RANGE_ELEMENT( 96 )
Q2_RANGE_ELEMENT( 108 )
Q2_RANGE_ELEMENT( 220 )
Q2_RANGE_ELEMENT( 236 )
Q2_RANGE_ELEMENT( 528 )

// End pointer immediately after the begin pointer: the second load is [ecx+4].
#define Q2_RANGE_COUNT( NAME, ELEM )                                      \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		int count() const;                                                \
	private:                                                              \
		ELEM *m_begin;                                                    \
		ELEM *m_end;                                                      \
	};                                                                    \
	int NAME::count() const                                               \
	{                                                                     \
		return m_end - m_begin;                                           \
	}

// One unidentified dword between the two pointers: the second load is [ecx+8].
#define Q2_RANGE_COUNT_GAP( NAME, ELEM )                                  \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		int count() const;                                                \
	private:                                                              \
		ELEM *m_begin;                                                    \
		ELEM *m_unreconstructed_04;                                       \
		ELEM *m_end;                                                      \
	};                                                                    \
	int NAME::count() const                                               \
	{                                                                     \
		return m_end - m_begin;                                           \
	}

Q2_RANGE_COUNT( Rva000F9330, Q2Elem96 )
Q2_RANGE_COUNT( Rva00133350, Q2Elem236 )
Q2_RANGE_COUNT_GAP( Rva00133370, Q2Elem236 )
Q2_RANGE_COUNT( Rva00251A60, Q2Elem44 )
Q2_RANGE_COUNT( Rva00360B20, Q2Elem88 )
Q2_RANGE_COUNT( Rva003A5D30, Q2Elem220 )
Q2_RANGE_COUNT_GAP( Rva003B2E50, Q2Elem220 )
Q2_RANGE_COUNT( Rva00607EB0, Q2Elem528 )
Q2_RANGE_COUNT( Rva0075D200, Q2Elem44 )
Q2_RANGE_COUNT( Rva0075DCC0, Q2Elem108 )
