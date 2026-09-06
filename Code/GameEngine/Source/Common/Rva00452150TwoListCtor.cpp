// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: default constructor of a class holding two STLport
// list<8-byte record> members back to back (retail 0x00452150, 100 bytes).
// Each member's ctor allocates its own 16-byte sentinel node (8 overhead +
// 8-byte element, __node_alloc::_M_allocate x2) and self-links it (next =
// prev = the node itself) before storing the sentinel pointer into the
// member.  The element type is only known to be an 8-byte trivially
// copyable record, so it carries an address-derived tag.  Owning class is
// unidentified.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Rva00452150Elem
{
	int m_a;
	int m_b;
};

typedef _STL::list<Rva00452150Elem, _STL::allocator<Rva00452150Elem> > Rva00452150List;

class Rva00452150Owner
{
public:
	Rva00452150Owner();
private:
	Rva00452150List m_list1;
	Rva00452150List m_list2;
};

Rva00452150Owner::Rva00452150Owner()
{
}
