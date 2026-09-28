// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

struct Rva00064A30Value
{
	char m_lead[24];
	unsigned int m_key;
};

struct Rva00064A30KeyOfValue
{
	const unsigned int &operator()(const Rva00064A30Value &x) const { return x.m_key; }
};

typedef _STL::_Rb_tree<unsigned int, Rva00064A30Value, Rva00064A30KeyOfValue,
	_STL::less<unsigned int>, _STL::allocator<Rva00064A30Value> > Rva00064A30Tree;

template _STL::pair<Rva00064A30Tree::iterator, bool>
Rva00064A30Tree::insert_unique(const Rva00064A30Value &);
