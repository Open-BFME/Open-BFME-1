// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: the out-of-line body of _STL::__copy over ProductionPrerequisite,
// retail 0x00753280, 99 bytes. The name sat on the 5-byte incremental-link
// thunk at 0x000181A1 and the body it jumps to carried only a machine byte-dump
// row.
//
// The element is 24 bytes and the count is a signed divide-by-twenty-four, so
// the empty range returns the result argument straight off the stack. The
// element layout is the loop itself: StringBase<char>::set on the member at +0,
// a single byte copied at +4, then four dwords from +8 to +0x14 -- so an
// AsciiString, a Bool with its three bytes of padding, and four words.
//
// THAT LAYOUT IS NOT ProductionPrerequisite'S, so this row is named for a class
// it does not copy. The class's own assignment operator settles it, and nothing
// disputes that row: ??4ProductionPrerequisite@@QAEAAV0@ABV0@@Z at 0x003B1DC0
// copies a dword from +4, copies a byte from +8, hands +12 to a called
// assignment, and NEVER TOUCHES +0. The sibling const-source __copy at
// 0x003B6100 runs exactly that sequence per element over the same 24-byte
// stride, which is what `*dst = *src` compiles to for this class. So that one
// copies ProductionPrerequisite and this one does not. Both byte-verify,
// because both really are somebody's copy loop.
//
// The two layouts cannot be reconciled by reading one of them differently. This
// body puts its only byte field at +4 and assigns +0 through a string set; the
// operator= puts its byte at +8 and leaves +0 alone. One 24-byte object does not
// keep its byte in two places.
//
// What this body actually copies is open. The shape -- a four-byte string
// wrapper at +0, a Bool at +4, four scalars from +8 to +0x14 -- ought to
// identify it, but the string call at 0x00887C90 is an ICF fold carrying three
// names (??0ModelConditionInfo@@QAE@ABU0@@Z, ??4AudioEventRTS@@QAEAAV0@ABV0@@Z
// and ?set@UnicodeString@@QAEXABV1@@Z), so it does not even say which string
// class. Renaming on that would trade a wrong name for a guessed one, so the row
// keeps its wrong name and this comment says why.
//
// Why the assignment skips +0 is already answered next door, and the answer
// holds: +0 is the vptr. ProductionPrerequisiteConstCopyBody.cpp reads it that
// way, and ??_GProductionPrerequisite@@QAEPAXI@Z at 0x00753840 is the
// confirmation -- a vector deleting destructor is emitted only for a class with
// a virtual one, so this class is polymorphic here even though Zero Hour's is
// not. A compiler-generated operator= copies the members and leaves the vtable
// pointer alone, which is exactly what 0x003B1DC0 does. The copy constructor at
// 0x00783D50 does write +0, and that is consistent rather than contradictory:
// source and destination are the same class, so taking the vptr from the source
// stores the same value a vftable literal would.

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
public:
	AsciiString m_name;
	bool m_flag;
	int m_words[4];
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result,
	const random_access_iterator_tag &, Distance *)
{
	for (Distance count = last - first; count > 0; --count, ++first, ++result)
		*result = *first;
	return result;
}

template ProductionPrerequisite *__copy<ProductionPrerequisite *, ProductionPrerequisite *, int>(
	ProductionPrerequisite *, ProductionPrerequisite *, ProductionPrerequisite *,
	const random_access_iterator_tag &, int *);
}
