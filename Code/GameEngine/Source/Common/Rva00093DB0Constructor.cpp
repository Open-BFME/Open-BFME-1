// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Address-derived owner of the three self-linked STLport headers at retail
// 0x00093DB0.  The first header reserves an 0x18-byte red-black node; the two
// trailing headers reserve the 0x0c-byte list-node shape used by their maps.

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate(unsigned int bytes);
};
}

struct Rva00093DB0Node18
{
	unsigned char m_colour;
	void *m_parent;
	Rva00093DB0Node18 *m_left;
	Rva00093DB0Node18 *m_right;
};

struct Rva00093DB0Node0C
{
	Rva00093DB0Node0C *m_left;
	Rva00093DB0Node0C *m_right;
};

class Rva00093DB0Tree18
{
public:
	Rva00093DB0Tree18(void)
	{
		m_first = 0;
		m_first = (Rva00093DB0Node18 *)_STL::__new_alloc::allocate(0x18);
		m_count = 0;
		m_first->m_colour = 0;
		m_first->m_parent = 0;
		m_first->m_left = m_first;
		m_first->m_right = m_first;
	}
	~Rva00093DB0Tree18(void);

	Rva00093DB0Node18 *m_first;
	int m_count;
};

class Rva00093DB0Tree0C
{
public:
	Rva00093DB0Tree0C(void)
	{
		m_first = 0;
		Rva00093DB0Node0C *node =
			(Rva00093DB0Node0C *)_STL::__new_alloc::allocate(0x0c);
		node->m_left = node;
		node->m_right = node;
		m_first = node;
	}
	~Rva00093DB0Tree0C(void);

	Rva00093DB0Node0C *m_first;
};

class Rva00093DB0
{
public:
	Rva00093DB0(void);
	~Rva00093DB0(void);

private:
	Rva00093DB0Tree18 m_first;
	int m_unreconstructed08;
	Rva00093DB0Tree0C m_second;
	Rva00093DB0Tree0C m_third;
};

Rva00093DB0::Rva00093DB0(void)
{
}
