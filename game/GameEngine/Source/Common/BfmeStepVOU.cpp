// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: STLport heap helpers over a four-byte AsciiString element.
// The matched sort_heap wrapper at 0x009CD910 (bfmeSortVOU) calls these with a
// literal-zero type tag. The element copies go through StringBase<char>'s copy
// constructor at 0x00887B60.

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *,
	const void *, unsigned int);

template <class T>
class StringBase
{
public:
	void set(const StringBase<T> &other);
	__forceinline int compareNoCase(const StringBase<T> &other) const
	{
		int otherLength = other.m_data ? other.m_data->m_length : 0;
		const T *otherData = other.m_data ? other.m_data->m_data : (const T *)0x0107388b;
		int thisLength = m_data ? m_data->m_length : 0;
		const T *thisData = m_data ? m_data->m_data : (const T *)0x0107388b;
		int count = thisLength < otherLength ? thisLength : otherLength;
		int result = _memicmp(thisData, otherData, count);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}
	__forceinline bool startsWithUnderscore(void) const
	{
		return m_data != 0 && m_data->m_data[0] == '_';
	}
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}

private:
	struct Header
	{
		int m_bfmeRefCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_data[1];
	};

	StringBase(const StringBase<T> &other);
	~StringBase(void);
	Header *m_data;

	friend struct BfmeElemVOU;
};

struct BfmeElemVOU
{
	BfmeElemVOU(const BfmeElemVOU &other) : m_base(other.m_base) {}
	~BfmeElemVOU(void) {}
	BfmeElemVOU &operator=(const BfmeElemVOU &other)
	{
		m_base = other.m_base;
		return *this;
	}

	StringBase<char> m_base;
};

struct BfmeCompVOU
{
	void *m_state;

	__forceinline bool operator()(const BfmeElemVOU &left,
		const BfmeElemVOU &right) const
	{
		if (left.m_base.startsWithUnderscore()
			&& right.m_base.startsWithUnderscore())
			return left.m_base.compareNoCase(right.m_base) > 0;
		return left.m_base.compareNoCase(right.m_base) < 0;
	}
};

void bfmePushHeapVOU(BfmeElemVOU *first, int holeIndex, int topIndex,
	BfmeElemVOU value, void *comp);

void bfmePushHeapVOU(BfmeElemVOU *first, int holeIndex, int topIndex,
	BfmeElemVOU value, void *comp)
{
	BfmeCompVOU compare;
	int parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex && compare(*(first + parent), value))
	{
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(first + holeIndex) = value;
}

void bfmeAdjustHeapVOU(BfmeElemVOU *first, int holeIndex, int len,
	BfmeElemVOU value, void *comp)
{
	BfmeCompVOU compare;
	int topIndex = holeIndex;
	int secondChild = 2 * holeIndex + 2;
	while (secondChild < len)
	{
		if (compare(*(first + secondChild),
			*(first + (secondChild - 1))))
			--secondChild;
		*(first + holeIndex) = *(first + secondChild);
		holeIndex = secondChild;
		secondChild = 2 * (secondChild + 1);
	}
	if (secondChild == len)
	{
		*(first + holeIndex) = *(first + (secondChild - 1));
		holeIndex = secondChild - 1;
	}
	bfmePushHeapVOU(first, holeIndex, topIndex, value, comp);
}

void bfmePopHeapVOU(BfmeElemVOU *first, BfmeElemVOU *last, BfmeElemVOU *result,
	BfmeElemVOU value, void *comp, int *)
{
	*result = *first;
	bfmeAdjustHeapVOU(first, 0, last - first, value, comp);
}

void bfmeStepVOU(void *a, void *b, int n, void *c)
{
	bfmePopHeapVOU((BfmeElemVOU *)a,
		(BfmeElemVOU *)b - 1,
		(BfmeElemVOU *)b - 1,
		*((BfmeElemVOU *)b - 1),
		c,
		(int *)0);
}

void bfmeMakeHeapVOU(BfmeElemVOU *first, BfmeElemVOU *last, void *comp)
{
	int len = last - first;
	if (len < 2)
		return;
	int parent = (len - 2) / 2;
	for (;;)
	{
		bfmeAdjustHeapVOU(first, parent, len, *(first + parent), comp);
		if (parent == 0)
			return;
		--parent;
	}
}
