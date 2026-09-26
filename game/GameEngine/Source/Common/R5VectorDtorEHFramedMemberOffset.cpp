// cl: /EHsc
// stlport
//
// Open-BFME5: eight STLport vector<T> destructors whose element holds ONE
// subobject needing destruction, at a fixed offset, destroyed non-virtually
// -- the shape Q4VectorDtorMemberOffset.cpp already lands seven of, here with
// the exception frame that comes with EH left on.
//
//     for (p = _M_start; p != _M_finish; p += <SIZE>)
//         lea ecx,[p+<OFFSET>] / call <MEMBER DTOR>
//
// The element's own destructor is INLINED -- there is no call to it, only a
// `lea` to a subobject and a direct call -- so the element is an aggregate
// whose only non-trivial part is that one member, and the direct call says
// the member's destructor is not virtual.
//
// Seven of the eight call 0x00887940, the large ICF fold holding among others
// ?releaseBuffer@AsciiString@@IAEXXZ; it is referenced under the
// address-derived alias Q4PairSubobjectDtors.cpp pinned, because no one of
// the folded names can be singled out.  The eighth calls 0x00026AB2 and gets
// its own.
//
// TWO FIELDS VARY AND ARE INDEPENDENT: stride and offset.  Stride 0xC appears
// at offsets 8 and 4, stride 0x14 at offsets 0xC and 8, so neither stands in
// for the other.
//
// IDENTITY IS NOT RECOVERED.  `m_lead` and `m_trail` place the destroyed
// member at the observed offset inside an element of the observed stride; the
// one-byte stand-in for the member is a placeholder, since nothing in these
// bytes fixes its size.

#include <vector>

struct Mem00026AB2
{
	~Mem00026AB2();
};

struct Mem00887940
{
	~Mem00887940();
};

#define R5_MEMBER_ELEM( T, MEM, SIZE, OFFSET )                                \
	struct T                                                                  \
	{                                                                         \
		char m_lead[ OFFSET ];                                                \
		MEM m_owned;                                                          \
		char m_trail[ SIZE - OFFSET - 1 ];                                    \
	};                                                                        \
	template class _STL::vector<T >;

R5_MEMBER_ELEM( Gen000E5300, Mem00887940, 0xC, 0x8 )	// 166B at 0x000E5300
R5_MEMBER_ELEM( Gen000FF700, Mem00887940, 0x24, 0x1C )	// 167B at 0x000FF700
R5_MEMBER_ELEM( Gen0013C200, Mem00887940, 0x14, 0xC )	// 167B at 0x0013C200
R5_MEMBER_ELEM( Gen00252DA0, Mem00026AB2, 0x2C, 0x4 )	// 164B at 0x00252DA0
R5_MEMBER_ELEM( Gen002E1260, Mem00887940, 0xC, 0x4 )	// 166B at 0x002E1260
R5_MEMBER_ELEM( Gen0035A980, Mem00887940, 0x14, 0x8 )	// 167B at 0x0035A980
R5_MEMBER_ELEM( Gen0035AA50, Mem00887940, 0x14, 0x8 )	// 167B at 0x0035AA50
R5_MEMBER_ELEM( Gen00532580, Mem00887940, 0xC, 0x4 )	// 166B at 0x00532580
