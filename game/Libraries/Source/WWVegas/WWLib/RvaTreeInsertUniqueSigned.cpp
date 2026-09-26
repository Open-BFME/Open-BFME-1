// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport _Rb_tree<K,V>::insert_unique(const value_type &), the
// signed-keyed shape, 30 bodies of 145 bytes each.  Every one of them
// carried only a machine byte-dump row.
//
// insert_unique walks from the root taking the left child while the incoming
// key compares below the node's own and the right child otherwise, remembers
// the last node it went left from, then re-compares against that node's
// predecessor to decide whether the key is already present.  Only on a miss
// does it hand the position pair to _M_insert, which is where the node is
// allocated -- so nothing in these 145 bytes depends on the mapped type or on
// the node width.  The one axis the bytes DO fix is the signedness of the key
// comparison: retail emits `setl` here, so the key is a signed 32-bit scalar.
// The unsigned shape lives in RvaTreeInsertUniqueUnsigned.cpp.
//
// Identity is not recoverable from a body that touches only the key.  The key
// is modelled as the plain int the comparison proves it to be, and the
// mapped type -- which the bytes never read -- is named for the address of the
// body so each instantiation gets its own decorated name.  Its WIDTH is known:
// the _M_insert each body calls -- converted in RvaTreeMInsertPair.cpp -- pushes
// the node size to the allocator, and the mapped type is that size less the
// sixteen-byte _Rb_tree_node_base and the four-byte key.
//
// Bodies whose _M_insert callee allocates a 20-byte node are NOT here: a node
// that holds only four bytes of value is _Identity over the key itself, not a
// pair, and they are spelled that way in RvaTreeInsertUniqueIdentity.cpp.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

struct Rva0008EAA0Value
{
	char m_body[ 36 ];
};

typedef _STL::pair<const int, Rva0008EAA0Value> Rva0008EAA0Pair;

typedef _STL::_Rb_tree<int,
	Rva0008EAA0Pair,
	_STL::_Select1st<Rva0008EAA0Pair>,
	_STL::less<int>,
	_STL::allocator<Rva0008EAA0Pair> > Rva0008EAA0Tree;

template _STL::pair<Rva0008EAA0Tree::iterator, bool>
Rva0008EAA0Tree::insert_unique( const Rva0008EAA0Pair & );

struct Rva000A3F30Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva000A3F30Value> Rva000A3F30Pair;

typedef _STL::_Rb_tree<int,
	Rva000A3F30Pair,
	_STL::_Select1st<Rva000A3F30Pair>,
	_STL::less<int>,
	_STL::allocator<Rva000A3F30Pair> > Rva000A3F30Tree;

template _STL::pair<Rva000A3F30Tree::iterator, bool>
Rva000A3F30Tree::insert_unique( const Rva000A3F30Pair & );

struct Rva000E1970Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva000E1970Value> Rva000E1970Pair;

typedef _STL::_Rb_tree<int,
	Rva000E1970Pair,
	_STL::_Select1st<Rva000E1970Pair>,
	_STL::less<int>,
	_STL::allocator<Rva000E1970Pair> > Rva000E1970Tree;

template _STL::pair<Rva000E1970Tree::iterator, bool>
Rva000E1970Tree::insert_unique( const Rva000E1970Pair & );

struct Rva000E1B10Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva000E1B10Value> Rva000E1B10Pair;

typedef _STL::_Rb_tree<int,
	Rva000E1B10Pair,
	_STL::_Select1st<Rva000E1B10Pair>,
	_STL::less<int>,
	_STL::allocator<Rva000E1B10Pair> > Rva000E1B10Tree;

template _STL::pair<Rva000E1B10Tree::iterator, bool>
Rva000E1B10Tree::insert_unique( const Rva000E1B10Pair & );

struct Rva000E7930Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva000E7930Value> Rva000E7930Pair;

typedef _STL::_Rb_tree<int,
	Rva000E7930Pair,
	_STL::_Select1st<Rva000E7930Pair>,
	_STL::less<int>,
	_STL::allocator<Rva000E7930Pair> > Rva000E7930Tree;

template _STL::pair<Rva000E7930Tree::iterator, bool>
Rva000E7930Tree::insert_unique( const Rva000E7930Pair & );

struct Rva00127850Value
{
	char m_body[ 16 ];
};

typedef _STL::pair<const int, Rva00127850Value> Rva00127850Pair;

typedef _STL::_Rb_tree<int,
	Rva00127850Pair,
	_STL::_Select1st<Rva00127850Pair>,
	_STL::less<int>,
	_STL::allocator<Rva00127850Pair> > Rva00127850Tree;

template _STL::pair<Rva00127850Tree::iterator, bool>
Rva00127850Tree::insert_unique( const Rva00127850Pair & );

struct Rva00140DE0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva00140DE0Value> Rva00140DE0Pair;

typedef _STL::_Rb_tree<int,
	Rva00140DE0Pair,
	_STL::_Select1st<Rva00140DE0Pair>,
	_STL::less<int>,
	_STL::allocator<Rva00140DE0Pair> > Rva00140DE0Tree;

template _STL::pair<Rva00140DE0Tree::iterator, bool>
Rva00140DE0Tree::insert_unique( const Rva00140DE0Pair & );

struct Rva00145360Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const int, Rva00145360Value> Rva00145360Pair;

typedef _STL::_Rb_tree<int,
	Rva00145360Pair,
	_STL::_Select1st<Rva00145360Pair>,
	_STL::less<int>,
	_STL::allocator<Rva00145360Pair> > Rva00145360Tree;

template _STL::pair<Rva00145360Tree::iterator, bool>
Rva00145360Tree::insert_unique( const Rva00145360Pair & );

struct Rva0019BD50Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const int, Rva0019BD50Value> Rva0019BD50Pair;

typedef _STL::_Rb_tree<int,
	Rva0019BD50Pair,
	_STL::_Select1st<Rva0019BD50Pair>,
	_STL::less<int>,
	_STL::allocator<Rva0019BD50Pair> > Rva0019BD50Tree;

template _STL::pair<Rva0019BD50Tree::iterator, bool>
Rva0019BD50Tree::insert_unique( const Rva0019BD50Pair & );

struct Rva0019E470Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const int, Rva0019E470Value> Rva0019E470Pair;

typedef _STL::_Rb_tree<int,
	Rva0019E470Pair,
	_STL::_Select1st<Rva0019E470Pair>,
	_STL::less<int>,
	_STL::allocator<Rva0019E470Pair> > Rva0019E470Tree;

template _STL::pair<Rva0019E470Tree::iterator, bool>
Rva0019E470Tree::insert_unique( const Rva0019E470Pair & );

struct Rva001B6DA0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva001B6DA0Value> Rva001B6DA0Pair;

typedef _STL::_Rb_tree<int,
	Rva001B6DA0Pair,
	_STL::_Select1st<Rva001B6DA0Pair>,
	_STL::less<int>,
	_STL::allocator<Rva001B6DA0Pair> > Rva001B6DA0Tree;

template _STL::pair<Rva001B6DA0Tree::iterator, bool>
Rva001B6DA0Tree::insert_unique( const Rva001B6DA0Pair & );

struct Rva001D8660Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const int, Rva001D8660Value> Rva001D8660Pair;

typedef _STL::_Rb_tree<int,
	Rva001D8660Pair,
	_STL::_Select1st<Rva001D8660Pair>,
	_STL::less<int>,
	_STL::allocator<Rva001D8660Pair> > Rva001D8660Tree;

template _STL::pair<Rva001D8660Tree::iterator, bool>
Rva001D8660Tree::insert_unique( const Rva001D8660Pair & );

struct Rva00223E00Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva00223E00Value> Rva00223E00Pair;

typedef _STL::_Rb_tree<int,
	Rva00223E00Pair,
	_STL::_Select1st<Rva00223E00Pair>,
	_STL::less<int>,
	_STL::allocator<Rva00223E00Pair> > Rva00223E00Tree;

template _STL::pair<Rva00223E00Tree::iterator, bool>
Rva00223E00Tree::insert_unique( const Rva00223E00Pair & );

struct Rva00224140Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva00224140Value> Rva00224140Pair;

typedef _STL::_Rb_tree<int,
	Rva00224140Pair,
	_STL::_Select1st<Rva00224140Pair>,
	_STL::less<int>,
	_STL::allocator<Rva00224140Pair> > Rva00224140Tree;

template _STL::pair<Rva00224140Tree::iterator, bool>
Rva00224140Tree::insert_unique( const Rva00224140Pair & );

struct Rva002253A0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva002253A0Value> Rva002253A0Pair;

typedef _STL::_Rb_tree<int,
	Rva002253A0Pair,
	_STL::_Select1st<Rva002253A0Pair>,
	_STL::less<int>,
	_STL::allocator<Rva002253A0Pair> > Rva002253A0Tree;

template _STL::pair<Rva002253A0Tree::iterator, bool>
Rva002253A0Tree::insert_unique( const Rva002253A0Pair & );

struct Rva00225540Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva00225540Value> Rva00225540Pair;

typedef _STL::_Rb_tree<int,
	Rva00225540Pair,
	_STL::_Select1st<Rva00225540Pair>,
	_STL::less<int>,
	_STL::allocator<Rva00225540Pair> > Rva00225540Tree;

template _STL::pair<Rva00225540Tree::iterator, bool>
Rva00225540Tree::insert_unique( const Rva00225540Pair & );

struct Rva0023B5B0Value
{
	char m_body[ 16 ];
};

typedef _STL::pair<const int, Rva0023B5B0Value> Rva0023B5B0Pair;

typedef _STL::_Rb_tree<int,
	Rva0023B5B0Pair,
	_STL::_Select1st<Rva0023B5B0Pair>,
	_STL::less<int>,
	_STL::allocator<Rva0023B5B0Pair> > Rva0023B5B0Tree;

template _STL::pair<Rva0023B5B0Tree::iterator, bool>
Rva0023B5B0Tree::insert_unique( const Rva0023B5B0Pair & );

struct Rva00372570Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const int, Rva00372570Value> Rva00372570Pair;

typedef _STL::_Rb_tree<int,
	Rva00372570Pair,
	_STL::_Select1st<Rva00372570Pair>,
	_STL::less<int>,
	_STL::allocator<Rva00372570Pair> > Rva00372570Tree;

template _STL::pair<Rva00372570Tree::iterator, bool>
Rva00372570Tree::insert_unique( const Rva00372570Pair & );

struct Rva00375F30Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const int, Rva00375F30Value> Rva00375F30Pair;

typedef _STL::_Rb_tree<int,
	Rva00375F30Pair,
	_STL::_Select1st<Rva00375F30Pair>,
	_STL::less<int>,
	_STL::allocator<Rva00375F30Pair> > Rva00375F30Tree;

template _STL::pair<Rva00375F30Tree::iterator, bool>
Rva00375F30Tree::insert_unique( const Rva00375F30Pair & );

struct Rva003FFA70Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva003FFA70Value> Rva003FFA70Pair;

typedef _STL::_Rb_tree<int,
	Rva003FFA70Pair,
	_STL::_Select1st<Rva003FFA70Pair>,
	_STL::less<int>,
	_STL::allocator<Rva003FFA70Pair> > Rva003FFA70Tree;

template _STL::pair<Rva003FFA70Tree::iterator, bool>
Rva003FFA70Tree::insert_unique( const Rva003FFA70Pair & );

struct Rva004746D0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva004746D0Value> Rva004746D0Pair;

typedef _STL::_Rb_tree<int,
	Rva004746D0Pair,
	_STL::_Select1st<Rva004746D0Pair>,
	_STL::less<int>,
	_STL::allocator<Rva004746D0Pair> > Rva004746D0Tree;

template _STL::pair<Rva004746D0Tree::iterator, bool>
Rva004746D0Tree::insert_unique( const Rva004746D0Pair & );

struct Rva004A6D40Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva004A6D40Value> Rva004A6D40Pair;

typedef _STL::_Rb_tree<int,
	Rva004A6D40Pair,
	_STL::_Select1st<Rva004A6D40Pair>,
	_STL::less<int>,
	_STL::allocator<Rva004A6D40Pair> > Rva004A6D40Tree;

template _STL::pair<Rva004A6D40Tree::iterator, bool>
Rva004A6D40Tree::insert_unique( const Rva004A6D40Pair & );

struct Rva004E4F60Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva004E4F60Value> Rva004E4F60Pair;

typedef _STL::_Rb_tree<int,
	Rva004E4F60Pair,
	_STL::_Select1st<Rva004E4F60Pair>,
	_STL::less<int>,
	_STL::allocator<Rva004E4F60Pair> > Rva004E4F60Tree;

template _STL::pair<Rva004E4F60Tree::iterator, bool>
Rva004E4F60Tree::insert_unique( const Rva004E4F60Pair & );

struct Rva00587A60Value
{
	char m_body[ 60 ];
};

typedef _STL::pair<const int, Rva00587A60Value> Rva00587A60Pair;

typedef _STL::_Rb_tree<int,
	Rva00587A60Pair,
	_STL::_Select1st<Rva00587A60Pair>,
	_STL::less<int>,
	_STL::allocator<Rva00587A60Pair> > Rva00587A60Tree;

template _STL::pair<Rva00587A60Tree::iterator, bool>
Rva00587A60Tree::insert_unique( const Rva00587A60Pair & );

struct Rva00593160Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva00593160Value> Rva00593160Pair;

typedef _STL::_Rb_tree<int,
	Rva00593160Pair,
	_STL::_Select1st<Rva00593160Pair>,
	_STL::less<int>,
	_STL::allocator<Rva00593160Pair> > Rva00593160Tree;

template _STL::pair<Rva00593160Tree::iterator, bool>
Rva00593160Tree::insert_unique( const Rva00593160Pair & );

struct Rva00611F60Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva00611F60Value> Rva00611F60Pair;

typedef _STL::_Rb_tree<int,
	Rva00611F60Pair,
	_STL::_Select1st<Rva00611F60Pair>,
	_STL::less<int>,
	_STL::allocator<Rva00611F60Pair> > Rva00611F60Tree;

template _STL::pair<Rva00611F60Tree::iterator, bool>
Rva00611F60Tree::insert_unique( const Rva00611F60Pair & );

struct Rva006325D0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva006325D0Value> Rva006325D0Pair;

typedef _STL::_Rb_tree<int,
	Rva006325D0Pair,
	_STL::_Select1st<Rva006325D0Pair>,
	_STL::less<int>,
	_STL::allocator<Rva006325D0Pair> > Rva006325D0Tree;

template _STL::pair<Rva006325D0Tree::iterator, bool>
Rva006325D0Tree::insert_unique( const Rva006325D0Pair & );

struct Rva00645EC0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva00645EC0Value> Rva00645EC0Pair;

typedef _STL::_Rb_tree<int,
	Rva00645EC0Pair,
	_STL::_Select1st<Rva00645EC0Pair>,
	_STL::less<int>,
	_STL::allocator<Rva00645EC0Pair> > Rva00645EC0Tree;

template _STL::pair<Rva00645EC0Tree::iterator, bool>
Rva00645EC0Tree::insert_unique( const Rva00645EC0Pair & );

struct Rva00653E70Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva00653E70Value> Rva00653E70Pair;

typedef _STL::_Rb_tree<int,
	Rva00653E70Pair,
	_STL::_Select1st<Rva00653E70Pair>,
	_STL::less<int>,
	_STL::allocator<Rva00653E70Pair> > Rva00653E70Tree;

template _STL::pair<Rva00653E70Tree::iterator, bool>
Rva00653E70Tree::insert_unique( const Rva00653E70Pair & );

struct Rva0065DC00Value
{
	char m_body[ 452 ];
};

typedef _STL::pair<const int, Rva0065DC00Value> Rva0065DC00Pair;

typedef _STL::_Rb_tree<int,
	Rva0065DC00Pair,
	_STL::_Select1st<Rva0065DC00Pair>,
	_STL::less<int>,
	_STL::allocator<Rva0065DC00Pair> > Rva0065DC00Tree;

template _STL::pair<Rva0065DC00Tree::iterator, bool>
Rva0065DC00Tree::insert_unique( const Rva0065DC00Pair & );

