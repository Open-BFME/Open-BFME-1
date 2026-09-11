// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: STLport unguarded partition over Q3SortElem4 at retail 0x009CCC50.
// Gen009CDAA0 calls this helper after selecting a pivot with Gen009CCB60.

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
	__forceinline int compareNoCase(const StringBase<T> &other) const
	{
		int otherLength = other.m_data ? other.m_data->m_length : 0;
		const T *otherData = other.m_data ? other.m_data->m_data : (const T *)"";
		int thisLength = m_data ? m_data->m_length : 0;
		const T *thisData = m_data ? m_data->m_data : (const T *)"";
		int count = thisLength < otherLength ? thisLength : otherLength;
		int result = _memicmp(thisData, otherData, count);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}
	__forceinline bool startsWithUnderscore(void) const
	{
		return m_data && m_data->m_data[0] == '_';
	}

private:
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	struct Header
	{
		int m_references;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_data[1];
	};

	Header *m_data;

	friend struct Q3SortElem4;
};

struct Q3SortElem4
{
	Q3SortElem4(const Q3SortElem4 &other) : m_base(other.m_base) {}
	~Q3SortElem4(void) {}
	Q3SortElem4 &operator=(const Q3SortElem4 &other)
	{
		m_base = other.m_base;
		return *this;
	}

	StringBase<char> m_base;
};

struct Q3SortCompare
{
	void *m_state;

	__forceinline bool operator()(const Q3SortElem4 &left,
		const Q3SortElem4 &right) const
	{
		if (left.m_base.startsWithUnderscore() && right.m_base.startsWithUnderscore())
			return left.m_base.compareNoCase(right.m_base) > 0;
		return left.m_base.compareNoCase(right.m_base) < 0;
	}
};

Q3SortElem4 *Gen009CCC50(Q3SortElem4 *first, Q3SortElem4 *last,
	Q3SortElem4 pivot, Q3SortCompare comp)
{
	for (;;)
	{
		while (comp(*first, pivot))
			++first;

		--last;
		while (comp(pivot, *last))
			--last;

		if (!(first < last))
			return first;

		{
			Q3SortElem4 temporary = *first;
			*first = *last;
			*last = temporary;
		}
		++first;
	}
}
