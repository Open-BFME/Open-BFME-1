// ?insert_unique@?$_Rb_tree@IURva00064F70Value@@URva00064F70KeyOfValue@@U?$less@I@_STL@@V?$allocator@URva00064F70Value@@@4@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@URva00064F70Value@@U?$_Nonconst_traits@URva00064F70Value@@@_STL@@@_STL@@_N@2@ABURva00064F70Value@@@Z
// partial score=0.9 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

struct Rva00064F70Value
{
	char m_lead[24];
	unsigned int m_key;
};

struct Rva00064F70KeyOfValue
{
	const unsigned int &operator()(const Rva00064F70Value &x) const { return x.m_key; }
};

typedef _STL::pair<const unsigned int, Rva00064F70Value> Rva00064F70Pair;

typedef _STL::_Rb_tree<unsigned int, Rva00064F70Value, Rva00064F70KeyOfValue,
	_STL::less<unsigned int>, _STL::allocator<Rva00064F70Value> > Rva00064F70Tree;

template _STL::pair<Rva00064F70Tree::iterator, bool>
Rva00064F70Tree::insert_unique(const Rva00064F70Value &);
