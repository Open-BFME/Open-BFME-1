// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *, const void *, unsigned int);

class AsciiString;

template <class T>
class StringBase
{
public:
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	void set(const StringBase<T> &other);
	int compareNoCase(const StringBase<T> &other) const;
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}

	private:
	void releaseBuffer(void);
	friend class AsciiString;

	T *m_data;
};

class AsciiString
{
public:
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&other);
	}
	~AsciiString(void)
	{
		((StringBase<char> *)this)->releaseBuffer();
	}
	AsciiString &operator=(const AsciiString &other)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&other);
		return *this;
	}
	int compareNoCase(const AsciiString &other) const
	{
		return ((const StringBase<char> *)this)->compareNoCase(*(const StringBase<char> *)&other);
	}

	char *m_text;
};

struct Q3SortElem4
{
	StringBase<char> m_base;
};

struct Q3SortCompare
{
	void *m_state;
};

void Gen009CCE50(Q3SortElem4 *last, Q3SortElem4 val, Q3SortCompare comp);

namespace _STL
{

template <class T>
struct less;

struct random_access_iterator_tag
{
};

template <class RandomAccessIter, class BidirectionalIter, class Distance>
BidirectionalIter __copy_backward(RandomAccessIter first,
	RandomAccessIter last, BidirectionalIter result,
	const random_access_iterator_tag &tag, Distance *distance);

template <>
struct less<AsciiString>
{
	void *m_state;

	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		char *leftData = *(char **)&left;
		if (leftData != 0 && leftData[8] == '_')
		{
			char *rightData = *(char **)&right;
			if (rightData != 0 && rightData[8] == '_')
				return left.compareNoCase(right) > 0;
		}
		return left.compareNoCase(right) < 0;
	}
};

template <class RandomAccessIter, class Tp, class Compare>
void __linear_insert(RandomAccessIter first, RandomAccessIter last,
	Tp val, Compare comp)
{
	if (comp(val, *first))
	{
		__copy_backward(first, last, last + 1,
			*(const random_access_iterator_tag *)&val, (int *)0);
		*first = val;
	}
	else
	{
		Gen009CCE50((Q3SortElem4 *)last, *(Q3SortElem4 *)&val,
			*(Q3SortCompare *)&comp);
	}
}

template void __linear_insert<AsciiString *, AsciiString,
	less<AsciiString> >(AsciiString *, AsciiString *, AsciiString,
	less<AsciiString>);

}
