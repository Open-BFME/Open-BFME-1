// cl: /O2 /Ob0

class ScienceInfoBase
{
public:
	ScienceInfoBase &operator=(const ScienceInfoBase &other);

private:
	char m_head[0x0C];
};

class Rva00630D00UStr
{
public:
	Rva00630D00UStr &operator=(const Rva00630D00UStr &other);

private:
	void *m_item;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

namespace _STL
{

template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	vector<T, A> &operator=(const vector<T, A> &other);

private:
	void *m_first;
	void *m_last;
	void *m_end;
};

}

class Rva003A0CF0 : public ScienceInfoBase
{
	Rva00630D00UStr m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	_STL::vector<ICoord2D> m_2C;

public:
	Rva003A0CF0 &operator=(const Rva003A0CF0 &other);
};

Rva003A0CF0 &Rva003A0CF0::operator=(const Rva003A0CF0 &other)
{
	ScienceInfoBase::operator=(other);
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2C = other.m_2C;
	return *this;
}
