// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: STLport __pop_heap over a twelve-byte element, retail
// 0x00531A40, 169 bytes.  gen00531D80 calls this with (first, last-1, last-1,
// *(last-1), comp, 0).  *result = *first goes through StringBase<char>::set
// at 0x00887C90; the by-value element is then handed to __adjust_heap.

#include "string_base.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void) {}
	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}
};

struct S4SortElem12_00532740
{
	char m_bfmeC;
	AsciiString m_bfmeName;
	int m_bfmeA;
};

struct S4Cmp00532740
{
	int m_bfmeSlot;
};

namespace _STL
{
template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp value, Compare comp);
}

void bfmePopHeap00531A40(S4SortElem12_00532740 *first, S4SortElem12_00532740 *last,
	S4SortElem12_00532740 *result, S4SortElem12_00532740 value, void *comp, int *)
{
	*result = *first;
	_STL::__adjust_heap<S4SortElem12_00532740 *, int, S4SortElem12_00532740, S4Cmp00532740>(
		first, 0, last - first, value,
		*reinterpret_cast<S4Cmp00532740 *>(&comp));
}
