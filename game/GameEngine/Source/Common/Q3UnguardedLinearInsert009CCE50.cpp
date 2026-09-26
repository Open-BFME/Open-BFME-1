// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: STLport __unguarded_linear_insert over a four-byte AsciiString
// element. Retail 0x009CCE50, 269 bytes. Caller Gen009CD1A0 (matched) names
// this as the by-value insert helper.

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

	__forceinline bool operator()(const Q3SortElem4 &left, const Q3SortElem4 &right) const
	{
		if (left.m_base.startsWithUnderscore() && right.m_base.startsWithUnderscore())
			return left.m_base.compareNoCase(right.m_base) > 0;
		return left.m_base.compareNoCase(right.m_base) < 0;
	}
};

void Gen009CCE50(Q3SortElem4 *last, Q3SortElem4 val, Q3SortCompare comp)
{
	Q3SortElem4 *next = last;
	--next;
	for (;;)
	{
		bool take;
		if (val.m_base.startsWithUnderscore() && next->m_base.startsWithUnderscore())
			take = val.m_base.compareNoCase(next->m_base) > 0;
		else
			take = val.m_base.compareNoCase(next->m_base) < 0;
		if (!take)
			break;
		*last = *next;
		last = next;
		--next;
	}
	*last = val;
	(void)comp;
}
