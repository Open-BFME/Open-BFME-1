// cl: /DNDEBUG /MD /EHsc
// stlport

// Open-BFME5: _STL::__introsort_loop<S4SortElem12 *, S4SortElem12, int,
// S4Cmp002E1690>, retail 0x002E1B60, 259 bytes.  The twelve-byte element
// carries a narrow StringBase member and a byte flag, so STLport emits the
// member copy constructor while it partitions the range.

#include <algorithm>

template <class T>
class StringBase
{
private:
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	T *m_bfmeData;

	friend struct S4SortElem12;
};

struct S4SortElem12
{
	int m_bfmeA;
	StringBase<char> m_bfmeName;
	char m_bfmeC;
};

struct S4Cmp002E1690
{
	int m_bfmeSlot;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const
	{
		return left.m_bfmeA < right.m_bfmeA;
	}
};

namespace _STL
{

template void __introsort_loop<S4SortElem12 *, S4SortElem12, int,
	S4Cmp002E1690>(S4SortElem12 *, S4SortElem12 *, S4SortElem12 *, int,
	S4Cmp002E1690);

}
