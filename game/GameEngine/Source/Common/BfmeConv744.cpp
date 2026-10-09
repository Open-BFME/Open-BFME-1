struct Rva00197480Point;
namespace _STL {
 template<class T> class allocator;
 template<class T, class A> class vector { public: vector(const vector &); };
}

class BfmeSubDOE
{
public:
};

struct BfmeOutDOE
{
	int m_bfmeA;
	BfmeSubDOE m_bfmeSub;
};

BfmeOutDOE *bfmeGoDOE(BfmeOutDOE *out, int *src, void *arg)
{
	volatile int tmp = 0;
	out->m_bfmeA = *src;
	reinterpret_cast<_STL::vector<_STL::vector<Rva00197480Point, _STL::allocator<Rva00197480Point> >, _STL::allocator<_STL::vector<Rva00197480Point, _STL::allocator<Rva00197480Point> > > > *>(&out->m_bfmeSub)->_STL::vector<_STL::vector<Rva00197480Point, _STL::allocator<Rva00197480Point> >, _STL::allocator<_STL::vector<Rva00197480Point, _STL::allocator<Rva00197480Point> > > >::vector(*reinterpret_cast<const _STL::vector<_STL::vector<Rva00197480Point, _STL::allocator<Rva00197480Point> >, _STL::allocator<_STL::vector<Rva00197480Point, _STL::allocator<Rva00197480Point> > > > *>(arg));
	return out;
}
