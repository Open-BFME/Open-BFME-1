// cl: /EHsc
// stlport
//
// Seven 150-byte STLport vector<T> destructors whose element holds ONE
// subobject needing destruction, at a fixed offset, destroyed non-virtually:
//
//     for (p = _M_start; p != _M_finish; p += <SIZE>)
//         lea ecx,[p+<OFFSET>] / call 0x00887940
//     then the same two-arm _M_deallocate as the sibling families
//
// WHAT THE BYTES SHOW.  The element's destructor is INLINED -- there is no
// call to an element destructor, only a `lea` to a subobject and a direct call
// -- so the element is an aggregate whose only non-trivial part is that one
// member.  The call is direct, not through a vtable, so the member's
// destructor is not virtual.  Every one of the seven calls the SAME callee,
// 0x00887940, which is a large ICF fold in the ledger holding among others
// ?releaseBuffer@AsciiString@@IAEXXZ; it is referenced here under the
// address-derived alias that Q4PairSubobjectDtors.cpp pinned, because no one
// of the folded names can be singled out.
//
// TWO FIELDS VARY: the element size and the subobject's offset within it.
// (0xc, 0x10) twice, (4, 8) four times, (4, 0x10) once -- offset 4 appears
// under two different element sizes and size 0x10 under two different offsets,
// so the two really are independent and neither stands in for the other.
//
// IDENTITY IS NOT RECOVERED.  `m_lead` and `m_trail` place the destroyed
// member at the observed offset inside an element of the observed size; the
// one-byte stand-in for the member itself is a placeholder, since nothing in
// these bytes fixes its size.

#include <vector>

struct Mem00887940
{
	~Mem00887940();
};

#define Q4_STRING_ELEM( T, SIZE, OFFSET )                                 	struct T                                                              	{                                                                     		char m_lead[ OFFSET ];                                            		Mem00887940 m_owned;                                              		char m_trail[ SIZE - OFFSET - 1 ];                                	};                                                                    	template class _STL::vector<T >;

Q4_STRING_ELEM( Gen000FF7D0, 0x10, 0xc )
Q4_STRING_ELEM( Gen00294280, 0x8, 0x4 )
Q4_STRING_ELEM( Gen00369970, 0x10, 0x4 )
Q4_STRING_ELEM( Gen00380820, 0x8, 0x4 )
Q4_STRING_ELEM( Gen004766B0, 0x10, 0xc )
Q4_STRING_ELEM( Gen00574BC0, 0x8, 0x4 )
Q4_STRING_ELEM( Gen00770440, 0x8, 0x4 )
