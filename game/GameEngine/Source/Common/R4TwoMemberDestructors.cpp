// Seven destructors of a NON-polymorphic class with exactly two destructible
// members and an empty body:
//
//     ~D() {}   //  m2.~M2();  m1.~M1();   emitted in reverse declaration order
//
// WHAT THE BYTES SHOW.  A __thiscall with the standard fs:[0] frame, `this`
// saved into the frame's object slot, and then exactly two `lea ecx,[esi+OFF]`
// / `call REL32` pairs at DESCENDING offsets -- reverse declaration order, which
// is what makes them members rather than statements.  The EH state is driven to
// 0 before the first and to -1 before the second, so after the second nothing
// remains to unwind: THERE IS NO BASE AND NO THIRD MEMBER.  There is also no
// vftable store anywhere, so the class is not polymorphic.
//
// TWO AXES: the two member OFFSETS (which also fix the first member's WIDTH,
// since the second begins where the first ends) and the two destructor REL32s.
// Six of the seven rows are 77 bytes; 0x00740C80 is 83 because its offsets,
// 0xAC and 0xB0, no longer fit the `lea ecx,[esi+imm8]` form.  That is not a
// third axis.
//
// FIVE OF THE SEVEN HAVE BOTH MEMBERS OF THE SAME TYPE (one destructor address
// used twice), which is why they are spelled with one element class used twice
// rather than two.  0x00385F50 and 0x0048C270 are byte-for-byte identical --
// same offsets, same destructor -- so retail carries two copies; each address
// gets its own definition here rather than one claim spread over two.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.
//
// WHAT THE BYTES CANNOT DECIDE.  The SECOND member's width and the class's own
// size -- nothing reads past it -- and whether the leading padding is one field
// or many.  Only the first member's width is pinned, by the offset difference.

#define R4_MEMBER_ELEM( T, SZ )                                               \
	struct T                                                                  \
	{                                                                         \
		char m_body[ SZ ];                                                    \
		T();                                                                  \
		~T();                                                                 \
	};

#define R4_TWO_MEMBER_DTOR( NAME, LEAD, M1, M2 )                              \
	struct NAME                                                               \
	{                                                                         \
		char m_lead[ LEAD ];                                                  \
		M1 m_first;                                                           \
		M2 m_second;                                                          \
		~NAME();                                                              \
	};                                                                        \
	NAME::~NAME() {}

#define R4_TWO_MEMBER_DTOR_HEAD( NAME, M1, M2 )                               \
	struct NAME                                                               \
	{                                                                         \
		M1 m_first;                                                           \
		M2 m_second;                                                          \
		~NAME();                                                              \
	};                                                                        \
	NAME::~NAME() {}

R4_MEMBER_ELEM( Gen008881D0, 4 )
R4_MEMBER_ELEM( Gen00887940, 4 )
R4_MEMBER_ELEM( Gen00196F30, 0xC )
R4_MEMBER_ELEM( Gen002237F0, 0xC )
R4_MEMBER_ELEM( Gen0037B4D0, 4 )
R4_MEMBER_ELEM( Gen002360C0, 0xC )

R4_TWO_MEMBER_DTOR( Rva00072490, 0x28, Gen008881D0, Gen00887940 )
R4_TWO_MEMBER_DTOR( Rva001976F0, 4, Gen00196F30, Gen00196F30 )
R4_TWO_MEMBER_DTOR( Rva0037B990, 0x14, Gen002237F0, Gen0037B4D0 )
R4_TWO_MEMBER_DTOR( Rva00385F50, 4, Gen00887940, Gen00887940 )
R4_TWO_MEMBER_DTOR( Rva0048C270, 4, Gen00887940, Gen00887940 )
R4_TWO_MEMBER_DTOR( Rva00591890, 0x10, Gen002360C0, Gen002360C0 )
R4_TWO_MEMBER_DTOR( Rva00740C80, 0xAC, Gen00887940, Gen00887940 )
