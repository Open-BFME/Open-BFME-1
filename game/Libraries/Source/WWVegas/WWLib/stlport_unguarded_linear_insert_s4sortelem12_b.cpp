// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__unguarded_linear_insert<S4SortElem12 *,
// S4SortElem12, S4Cmp00532740>, retail 0x0052F280, 252 bytes.  The matched
// __linear_insert caller at 0x00531860 proves the specialization identity and
// the byte/string/dword element layout.

struct S4Name;

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

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp)
{
	RandomAccessIter next = last;
	--next;
	while (comp(val, *next))
	{
		*last = *next;
		last = next;
		--next;
	}
	*last = val;
}

template void __unguarded_linear_insert<S4SortElem12_00532740 *, S4SortElem12_00532740,
	S4Cmp00532740>(S4SortElem12_00532740 *, S4SortElem12_00532740, S4Cmp00532740);

}
