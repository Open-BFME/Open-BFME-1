// cl: /DNDEBUG /MD /EHsc
// stlport

// Open-BFME5: STLport __introsort_loop over the twelve-byte S4 name record at
// retail 0x00533520.  The flag and narrow StringBase member are the same
// record shape used by the neighboring insertion-sort family; the comparator
// orders flag state first and then compares the names without case.

#include <algorithm>

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *left,
	const void *right, unsigned int count);

struct S4Name;

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
	int compareNoCase(const StringBase<T> &other) const
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

	friend struct S4Name;
	friend struct S4SortElem12;
};

struct S4Name
{
	S4Name(const S4Name &other) : m_base(other.m_base) {}
	~S4Name(void) {}

	StringBase<char> m_base;
};

struct S4SortElem12
{
	bool m_bfmeA;
	S4Name m_bfmeName;
	int m_bfmeC;
};

struct S4Cmp00532740
{
	int m_bfmeSlot;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const
	{
		if (((!left.m_bfmeA) ^ (!right.m_bfmeA)) != 0)
			return left.m_bfmeA;
		return left.m_bfmeName.m_base.compareNoCase(right.m_bfmeName.m_base) < 0;
	}
};

namespace _STL
{

template void __introsort_loop<S4SortElem12 *, S4SortElem12, int,
	S4Cmp00532740>(S4SortElem12 *, S4SortElem12 *, S4SortElem12 *, int,
	S4Cmp00532740);

}
