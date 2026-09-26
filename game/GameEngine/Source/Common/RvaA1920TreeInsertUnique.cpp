// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

typedef unsigned int RvaA1920Key;

typedef _STL::_Rb_tree<RvaA1920Key,
	RvaA1920Key,
	_STL::_Identity<RvaA1920Key>,
	_STL::less<RvaA1920Key>,
	_STL::allocator<RvaA1920Key> > RvaA1920Tree;

template _STL::pair<RvaA1920Tree::iterator, bool>
RvaA1920Tree::insert_unique(const RvaA1920Key &);
