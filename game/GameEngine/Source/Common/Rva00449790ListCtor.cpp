// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: default constructor zero-initializing twelve int members, one
// embedded STLport list<8-byte record> (16-byte sentinel node, 8 overhead +
// 8 value, __node_alloc::_M_allocate), a call through the list's own address
// to a still-unidentified helper (retail 0x0002E1C7, pinned separately), and
// two trailing int members set to -1.  Retail 0x00449790, 130 bytes.  The
// element is only known to be an 8-byte trivially copyable record and the
// helper's owning type is unidentified, so both carry address-derived tags.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Rva00449790Elem
{
	int m_a;
	int m_b;
};

typedef _STL::list<Rva00449790Elem, _STL::allocator<Rva00449790Elem> > Rva00449790List;

class Rva00449790StepHelper
{
public:
	void step();
};

class Rva00449790Owner
{
public:
	Rva00449790Owner();
private:
	int m_f00;
	int m_f04;
	int m_f08;
	int m_f0c;
	int m_f10;
	int m_f14;
	int m_f18;
	int m_f1c;
	int m_f20;
	int m_f24;
	int m_f28;
	int m_f2c;
	Rva00449790List m_list;
	int m_f34;
	int m_f38;
};

Rva00449790Owner::Rva00449790Owner() :
	m_f00( 0 ),
	m_f04( 0 ),
	m_f08( 0 ),
	m_f0c( 0 ),
	m_f10( 0 ),
	m_f14( 0 ),
	m_f18( 0 ),
	m_f1c( 0 ),
	m_f20( 0 ),
	m_f24( 0 ),
	m_f28( 0 ),
	m_f2c( 0 )
{
	reinterpret_cast<Rva00449790StepHelper *>( &m_list )->step();
	m_f38 = -1;
	m_f34 = -1;
}
