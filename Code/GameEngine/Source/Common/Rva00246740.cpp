// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <list>
#include <vector>

class Rva00246740
{
public:
	~Rva00246740();

private:
	_STL::vector< _STL::list<int> > m_lists;
};

template class _STL::vector< _STL::list<int> >;

Rva00246740::~Rva00246740()
{
}
