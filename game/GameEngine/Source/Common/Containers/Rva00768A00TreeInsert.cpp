// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00768A00: signed 32-bit identity-tree insert_unique, 145 bytes.
// Its _M_insert callee at 0x00765440 constructs a 20-byte node (16-byte
// tree links plus a four-byte identity value), ruling out pair-valued maps.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

enum Rva00768A00Key
{
	RVA_00768A00_KEY_ZERO = 0
};

// Retail uses signed 32-bit comparisons; the enum has MSVC 7.1's int layout.
typedef _STL::_Rb_tree<Rva00768A00Key,
	Rva00768A00Key,
	_STL::_Identity<Rva00768A00Key>,
	_STL::less<Rva00768A00Key>,
	_STL::allocator<Rva00768A00Key> > Rva00768A00Tree;

template _STL::pair<Rva00768A00Tree::iterator, bool>
Rva00768A00Tree::insert_unique( const Rva00768A00Key & );
