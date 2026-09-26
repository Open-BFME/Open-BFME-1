// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// STLport vector<T>::_M_fill_insert for the 28-byte element whose adjacent
// push_back body is retail 0x00426C00.  The element has four inline dwords and
// a twelve-byte tree member.  Its copy, assignment, and vector helper calls
// identify this instantiation independently of the equal-width Eva record.

#include <vector>

class Rva00426C00Tree
{
public:
	Rva00426C00Tree(const Rva00426C00Tree &);
	Rva00426C00Tree &operator=(const Rva00426C00Tree &);
	~Rva00426C00Tree();

private:
	char m_raw[12];
};

struct Rva00426C00Element
{
	int m_field0;
	int m_field4;
	int m_field8;
	int m_fieldC;
	Rva00426C00Tree m_tree;

	Rva00426C00Element();
	Rva00426C00Element(const Rva00426C00Element &other)
		: m_field0(other.m_field0), m_field4(other.m_field4),
		  m_field8(other.m_field8), m_fieldC(other.m_fieldC),
		  m_tree(other.m_tree)
	{
	}
	Rva00426C00Element &operator=(const Rva00426C00Element &other)
	{
		m_field0 = other.m_field0;
		m_field4 = other.m_field4;
		m_field8 = other.m_field8;
		m_fieldC = other.m_fieldC;
		m_tree = other.m_tree;
		return *this;
	}
	~Rva00426C00Element()
	{
	}
};

template class _STL::vector<Rva00426C00Element>;
