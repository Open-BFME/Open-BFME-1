// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: structurally recovered swap of the twelve-byte record used by
// the neighboring STLport insertion-sort bodies, retail 0x002E00E0, 152 bytes.

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
	~StringBase(void);
	T *m_bfmeData;

	friend struct S4Name;
	friend struct S4SortElem12;
};

struct S4Name
{
	S4Name(const S4Name &other) : m_base(other.m_base) {}
	~S4Name(void) {}
	S4Name &operator=(const S4Name &other)
	{
		m_base = other.m_base;
		return *this;
	}

	StringBase<char> m_base;
};

struct S4SortElem12
{
	int m_bfmeA;
	S4Name m_bfmeName;
	char m_bfmeC;

	S4SortElem12(const S4SortElem12 &other) :
		m_bfmeA(other.m_bfmeA),
		m_bfmeName(other.m_bfmeName),
		m_bfmeC(other.m_bfmeC)
	{
	}
	~S4SortElem12(void) {}
	S4SortElem12 &operator=(const S4SortElem12 &other)
	{
		m_bfmeA = other.m_bfmeA;
		m_bfmeName = other.m_bfmeName;
		m_bfmeC = other.m_bfmeC;
		return *this;
	}
};

void Rva002E00E0Swap(S4SortElem12 &left, S4SortElem12 &right)
{
	S4SortElem12 temporary(left);
	left = right;
	right = temporary;
}
