// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: compiler-generated copy of a 16-byte record whose first member
// is a 4-byte string (StringBase<char> copy at 0x00887B60), whose dword at +4
// is POD, and whose 8-byte member at +8 has an out-of-line copy constructor
// (ILT 0x00018782). Retail 0x003B9AD0, 87 bytes. The frame exists so the
// first member is destroyed if the second copy throws.

template <typename T>
class StringBase
{
	friend class Rva003B9AD0First;

private:
	StringBase();
	StringBase(const StringBase<T> &);
	~StringBase();

	int *m_data;
};

class Rva003B9AD0First : private StringBase<char>
{
public:
	Rva003B9AD0First(const Rva003B9AD0First &other)
		: StringBase<char>(other)
	{
	}
	~Rva003B9AD0First() {}
};

class Rva003B9AD0Inner
{
public:
	Rva003B9AD0Inner(const Rva003B9AD0Inner &);
	~Rva003B9AD0Inner();

private:
	int m_at00;
	int m_at04;
};

class Rva003B9AD0
{
public:
	Rva003B9AD0(const Rva003B9AD0 &);

private:
	Rva003B9AD0First m_first;
	int m_at04;
	Rva003B9AD0Inner m_inner;
};

Rva003B9AD0::Rva003B9AD0(const Rva003B9AD0 &other)
	: m_first(other.m_first)
	, m_at04(other.m_at04)
	, m_inner(other.m_inner)
{
}
