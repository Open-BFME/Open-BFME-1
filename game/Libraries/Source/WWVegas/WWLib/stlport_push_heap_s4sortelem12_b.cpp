// ??$__push_heap@PAUS4SortElem12_00532740@@HU1@US4Cmp00532740@@@_STL@@YAXPAUS4SortElem12_00532740@@HHU1@US4Cmp00532740@@@Z
// Retail 0x0052F600. The adjust_heap caller at 0x00530350 proves this
// STLport specialization and the neighboring sort bodies prove the element layout.
// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *left,
	const void *right, unsigned int count);

template <class T>
class StringBase
{
public:
	void set(const StringBase<T> &other);
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}

private:
	StringBase(const StringBase<T> &other);
	void releaseBuffer(void);
	struct Header
	{
		int m_references;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_data[1];
	};

	Header *m_data;

	friend struct S4Name;
	friend struct S4SortElem12_00532740;
};

// File-static view of StringBase<char>'s header, so this TU emits no
// StringBase<char>::compareNoCase COMDAT; retail inlines the comparison here.
struct S4NoCaseView
{
	struct Header
	{
		int m_references;
		unsigned short m_length;
		unsigned short m_capacity;
		char m_data[1];
	};

	Header *m_data;
};

static inline int s4CompareNoCase(const void *self, const void *rhs)
{
	const S4NoCaseView &thisView = *(const S4NoCaseView *)self;
	const S4NoCaseView &other = *(const S4NoCaseView *)rhs;
	int otherLength = other.m_data ? other.m_data->m_length : 0;
	const char *otherData = other.m_data ? other.m_data->m_data : (const char *)"";
	int thisLength = thisView.m_data ? thisView.m_data->m_length : 0;
	const char *thisData = thisView.m_data ? thisView.m_data->m_data : (const char *)"";
	int count = thisLength < otherLength ? thisLength : otherLength;
	int result = _memicmp(thisData, otherData, count);
	if (result != 0)
		return result;
	return thisLength - otherLength;
}

struct S4Name
{
	S4Name(const S4Name &other) : m_base(other.m_base) {}
	~S4Name(void) { m_base.releaseBuffer(); }

	StringBase<char> m_base;
};

struct S4SortElem12_00532740
{
	bool m_bfmeA;
	S4Name m_bfmeName;
	int m_bfmeC;
};

struct S4Cmp00532740
{
	int m_bfmeSlot;

	bool operator()(const S4SortElem12_00532740 &left,
		const S4SortElem12_00532740 &right) const
	{
		if (((!left.m_bfmeA) ^ (!right.m_bfmeA)) != 0)
			return left.m_bfmeA;
		return s4CompareNoCase(&left.m_bfmeName.m_base,
			&right.m_bfmeName.m_base) < 0;
	}
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp val, Compare comp)
{
	Distance parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex && comp(*(first + parent), val))
	{
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(first + holeIndex) = val;
}

template void __push_heap<S4SortElem12_00532740 *, int, S4SortElem12_00532740,
	S4Cmp00532740>(S4SortElem12_00532740 *, int, int, S4SortElem12_00532740, S4Cmp00532740);

}
