// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB

// STLport's sift-down helper for BFME's GameText StringLookUp records. The
// comparator's original spelling is unavailable; its name records the matched
// make_heap caller that supplies its one-word state.
extern const char g_bfmeEmptyAscii[];
extern "C" __declspec(dllimport) int __cdecl _stricmp(
	const char *left, const char *right);

class AsciiStringData;
class AsciiString
{
public:
	__forceinline const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : g_bfmeEmptyAscii;
	}

private:
	AsciiStringData *m_data;
};

struct StringInfo;

struct StringLookUp
{
	AsciiString *label;
	StringInfo *info;
};

struct StringLookUpCompare00437D80
{
	void *m_state;

	__forceinline bool operator()(const StringLookUp &left,
		const StringLookUp &right) const
	{
		return _stricmp(left.label->str(), right.label->str()) < 0;
	}
};

// MSVC 7.1 retains out-of-line COMDAT copies of the two inline definitions.
// They are intentionally present-unmatched: AsciiString::str is already owned
// at 0x0005F270 and the 65-byte predicate is byte-identical to the independently
// owned compareStringLookUpLess at 0x004367F0. Only __adjust_heap is claimed here.

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp value, Compare comp);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance length, Tp value, Compare comp)
{
	Distance topIndex = holeIndex;
	Distance secondChild = 2 * holeIndex + 2;
	while (secondChild < length)
	{
		if (comp(*(first + secondChild), *(first + (secondChild - 1))))
			--secondChild;

		*(first + holeIndex) = *(first + secondChild);
		holeIndex = secondChild;
		secondChild = 2 * (secondChild + 1);
	}

	if (secondChild == length)
	{
		*(first + holeIndex) = *(first + (secondChild - 1));
		holeIndex = secondChild - 1;
	}

	__push_heap(first, holeIndex, topIndex, value, comp);
}

template void __adjust_heap<StringLookUp *, int,
	StringLookUp, StringLookUpCompare00437D80>(
	StringLookUp *, int, int, StringLookUp,
	StringLookUpCompare00437D80);

}
