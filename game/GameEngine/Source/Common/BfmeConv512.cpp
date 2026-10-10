// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <list>

struct Gen_t_00443e40_p8cd;

// ILT 0x0002E1C7 reaches the existing clear body at 0x00443E40.
template <> void _STL::_List_base<Gen_t_00443e40_p8cd,
	_STL::allocator<Gen_t_00443e40_p8cd> >::clear();

struct BfmeSubBQC
{
	void *m_bfmeWhat;
};

class BfmeThingBQC
{
public:
	void bfmeGoBQC();
	unsigned char m_bfmeHead[0x30];
	BfmeSubBQC m_bfmeSub;
};

void BfmeThingBQC::bfmeGoBQC()
{
	reinterpret_cast<_STL::_List_base<Gen_t_00443e40_p8cd,
		_STL::allocator<Gen_t_00443e40_p8cd> > *>(&m_bfmeSub)->clear();
	void *what = m_bfmeSub.m_bfmeWhat;
	if (what != 0)
		_STL::__node_alloc<true, 0>::deallocate(what, 0x10);
}
