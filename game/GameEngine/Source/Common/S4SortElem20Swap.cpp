// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc

// Open-BFME5: the two-pointer swap helper reached through ILT 0x0003A76F,
// retail body 0x002EA1A0, 162 bytes.  The twenty-byte record is copied to a
// temporary, assigned in both directions, then destroyed.  Its string and
// vector-tail assignments remain out of line at the already identified
// StringBase and BfmeSortElem20Tail setter bodies.

template <typename T>
class StringBase
{
public:
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}
	~StringBase()
	{
		releaseBuffer();
	}

private:
	StringBase(const StringBase<T> &other);
	void set(const StringBase<T> &other);
	void releaseBuffer();
	void *m_data;
};

class BfmeSortElem20Tail
{
public:
	BfmeSortElem20Tail(const BfmeSortElem20Tail &other);
	~BfmeSortElem20Tail();
	BfmeSortElem20Tail &operator=(const BfmeSortElem20Tail &other)
	{
		set(other);
		return *this;
	}

	void set(const BfmeSortElem20Tail &other);

private:
	int m_bfmeBody[3];
};

struct S4SortElem20
{
	StringBase<char> m_bfmeName;
	char m_bfmeFlag;
	BfmeSortElem20Tail m_bfmeTail;

	S4SortElem20(const S4SortElem20 &other);
	S4SortElem20 &operator=(const S4SortElem20 &other)
	{
		m_bfmeName = other.m_bfmeName;
		m_bfmeFlag = other.m_bfmeFlag;
		m_bfmeTail = other.m_bfmeTail;
		return *this;
	}
};

__forceinline void bfmeCopySortElem20Tail(
	const BfmeSortElem20Tail *source, BfmeSortElem20Tail *destination)
{
	destination->set(*source);
}

void bfmeIterSwapS4SortElem20(S4SortElem20 *left, S4SortElem20 *right)
{
	S4SortElem20 temporary = *left;
	left->m_bfmeName = right->m_bfmeName;
	BfmeSortElem20Tail *rightTail = &right->m_bfmeTail;
	left->m_bfmeFlag = right->m_bfmeFlag;
	bfmeCopySortElem20Tail(rightTail, &left->m_bfmeTail);
	right->m_bfmeName = temporary.m_bfmeName;
	right->m_bfmeFlag = temporary.m_bfmeFlag;
	rightTail->operator=(temporary.m_bfmeTail);
}
