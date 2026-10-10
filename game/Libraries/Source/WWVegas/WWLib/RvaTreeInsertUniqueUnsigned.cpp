// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport _Rb_tree<K,V>::insert_unique(const value_type &), the
// unsigned-keyed shape, 16 bodies of 145 bytes each.  Every one of them
// carried only a machine byte-dump row.
//
// insert_unique walks from the root taking the left child while the incoming
// key compares below the node's own and the right child otherwise, remembers
// the last node it went left from, then re-compares against that node's
// predecessor to decide whether the key is already present.  Only on a miss
// does it hand the position pair to _M_insert, which is where the node is
// allocated -- so nothing in these 145 bytes depends on the mapped type or on
// the node width.  The one axis the bytes DO fix is the signedness of the key
// comparison: retail emits `setb` here, so the key is an unsigned 32-bit
// scalar (or a pointer).
// The signed shape lives in RvaTreeInsertUniqueSigned.cpp.
//
// Identity is not recoverable from a body that touches only the key.  The key
// is modelled as the plain unsigned int the comparison proves it to be, and the
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

struct Rva00076F80Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva00076F80Value> Rva00076F80Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva00076F80Pair,
	_STL::_Select1st<Rva00076F80Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva00076F80Pair> > Rva00076F80Tree;

// The verified node insertion is owned by RvaTreeMInsertPair.cpp
// (RvaTreeMInsertInlineCopy.cpp for 002A1E90).
template <>
Rva00076F80Tree::iterator Rva00076F80Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva00076F80Pair &, _STL::_Rb_tree_node_base *);

template _STL::pair<Rva00076F80Tree::iterator, bool>
Rva00076F80Tree::insert_unique( const Rva00076F80Pair & );

struct Rva00077040Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva00077040Value> Rva00077040Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva00077040Pair,
	_STL::_Select1st<Rva00077040Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva00077040Pair> > Rva00077040Tree;

// The verified node insertion is owned by RvaTreeMInsertPair.cpp
// (RvaTreeMInsertInlineCopy.cpp for 002A1E90).
template <>
Rva00077040Tree::iterator Rva00077040Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva00077040Pair &, _STL::_Rb_tree_node_base *);

template _STL::pair<Rva00077040Tree::iterator, bool>
Rva00077040Tree::insert_unique( const Rva00077040Pair & );

struct Rva000E9850Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva000E9850Value> Rva000E9850Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva000E9850Pair,
	_STL::_Select1st<Rva000E9850Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva000E9850Pair> > Rva000E9850Tree;

// The verified node insertion is owned by RvaTreeMInsertPair.cpp
// (RvaTreeMInsertInlineCopy.cpp for 002A1E90).
template <>
Rva000E9850Tree::iterator Rva000E9850Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva000E9850Pair &, _STL::_Rb_tree_node_base *);

template _STL::pair<Rva000E9850Tree::iterator, bool>
Rva000E9850Tree::insert_unique( const Rva000E9850Pair & );

struct Rva0021BE20Value
{
	char m_body[ 8 ];
};

typedef _STL::pair<const unsigned int, Rva0021BE20Value> Rva0021BE20Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva0021BE20Pair,
	_STL::_Select1st<Rva0021BE20Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva0021BE20Pair> > Rva0021BE20Tree;

// The verified node insertion is owned by RvaTreeMInsertPair.cpp
// (RvaTreeMInsertInlineCopy.cpp for 002A1E90).
template <>
Rva0021BE20Tree::iterator Rva0021BE20Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva0021BE20Pair &, _STL::_Rb_tree_node_base *);

template _STL::pair<Rva0021BE20Tree::iterator, bool>
Rva0021BE20Tree::insert_unique( const Rva0021BE20Pair & );

struct Rva00223FA0Value
{
	char m_body[ 40 ];
};

typedef _STL::pair<const unsigned int, Rva00223FA0Value> Rva00223FA0Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva00223FA0Pair,
	_STL::_Select1st<Rva00223FA0Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva00223FA0Pair> > Rva00223FA0Tree;

// The verified node insertion is owned by RvaTreeMInsertPair.cpp
// (RvaTreeMInsertInlineCopy.cpp for 002A1E90).
template <>
Rva00223FA0Tree::iterator Rva00223FA0Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva00223FA0Pair &, _STL::_Rb_tree_node_base *);

template _STL::pair<Rva00223FA0Tree::iterator, bool>
Rva00223FA0Tree::insert_unique( const Rva00223FA0Pair & );

struct Rva002A1E90Value
{
	char m_body[ 16 ];
};

typedef _STL::pair<const unsigned int, Rva002A1E90Value> Rva002A1E90Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva002A1E90Pair,
	_STL::_Select1st<Rva002A1E90Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva002A1E90Pair> > Rva002A1E90Tree;

// The verified node insertion is owned by RvaTreeMInsertPair.cpp
// (RvaTreeMInsertInlineCopy.cpp for 002A1E90).
template <>
Rva002A1E90Tree::iterator Rva002A1E90Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva002A1E90Pair &, _STL::_Rb_tree_node_base *);

template _STL::pair<Rva002A1E90Tree::iterator, bool>
Rva002A1E90Tree::insert_unique( const Rva002A1E90Pair & );

struct Rva003DBF80Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva003DBF80Value> Rva003DBF80Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva003DBF80Pair,
	_STL::_Select1st<Rva003DBF80Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva003DBF80Pair> > Rva003DBF80Tree;

// The verified node insertion is owned by RvaTreeMInsertPair.cpp
// (RvaTreeMInsertInlineCopy.cpp for 002A1E90).
template <>
Rva003DBF80Tree::iterator Rva003DBF80Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva003DBF80Pair &, _STL::_Rb_tree_node_base *);

template _STL::pair<Rva003DBF80Tree::iterator, bool>
Rva003DBF80Tree::insert_unique( const Rva003DBF80Pair & );

struct Rva003FF8D0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva003FF8D0Value> Rva003FF8D0Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva003FF8D0Pair,
	_STL::_Select1st<Rva003FF8D0Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva003FF8D0Pair> > Rva003FF8D0Tree;

// The verified node insertion is owned by RvaTreeMInsertPair.cpp
// (RvaTreeMInsertInlineCopy.cpp for 002A1E90).
template <>
Rva003FF8D0Tree::iterator Rva003FF8D0Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva003FF8D0Pair &, _STL::_Rb_tree_node_base *);

template _STL::pair<Rva003FF8D0Tree::iterator, bool>
Rva003FF8D0Tree::insert_unique( const Rva003FF8D0Pair & );

struct Rva00405DB0Value
{
	char m_body[ 32 ];
};

typedef _STL::pair<const unsigned int, Rva00405DB0Value> Rva00405DB0Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva00405DB0Pair,
	_STL::_Select1st<Rva00405DB0Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva00405DB0Pair> > Rva00405DB0Tree;

// The verified node insertion is owned by RvaTreeMInsertPair.cpp
// (RvaTreeMInsertInlineCopy.cpp for 002A1E90).
template <>
Rva00405DB0Tree::iterator Rva00405DB0Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva00405DB0Pair &, _STL::_Rb_tree_node_base *);

template _STL::pair<Rva00405DB0Tree::iterator, bool>
Rva00405DB0Tree::insert_unique( const Rva00405DB0Pair & );

struct Rva0040AAD0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva0040AAD0Value> Rva0040AAD0Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva0040AAD0Pair,
	_STL::_Select1st<Rva0040AAD0Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva0040AAD0Pair> > Rva0040AAD0Tree;

// The verified node insertion is owned by RvaTreeMInsertPair.cpp
// (RvaTreeMInsertInlineCopy.cpp for 002A1E90).
template <>
Rva0040AAD0Tree::iterator Rva0040AAD0Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva0040AAD0Pair &, _STL::_Rb_tree_node_base *);

template _STL::pair<Rva0040AAD0Tree::iterator, bool>
Rva0040AAD0Tree::insert_unique( const Rva0040AAD0Pair & );

struct Rva004B0C80Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva004B0C80Value> Rva004B0C80Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva004B0C80Pair,
	_STL::_Select1st<Rva004B0C80Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva004B0C80Pair> > Rva004B0C80Tree;

// The verified node insertion is owned by RvaTreeMInsertPair.cpp
// (RvaTreeMInsertInlineCopy.cpp for 002A1E90).
template <>
Rva004B0C80Tree::iterator Rva004B0C80Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva004B0C80Pair &, _STL::_Rb_tree_node_base *);

template _STL::pair<Rva004B0C80Tree::iterator, bool>
Rva004B0C80Tree::insert_unique( const Rva004B0C80Pair & );

struct Rva00586710Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva00586710Value> Rva00586710Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva00586710Pair,
	_STL::_Select1st<Rva00586710Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva00586710Pair> > Rva00586710Tree;

// The verified node insertion is owned by RvaTreeMInsertPair.cpp
// (RvaTreeMInsertInlineCopy.cpp for 002A1E90).
template <>
Rva00586710Tree::iterator Rva00586710Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva00586710Pair &, _STL::_Rb_tree_node_base *);

template _STL::pair<Rva00586710Tree::iterator, bool>
Rva00586710Tree::insert_unique( const Rva00586710Pair & );

struct Rva005D2B10Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva005D2B10Value> Rva005D2B10Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva005D2B10Pair,
	_STL::_Select1st<Rva005D2B10Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva005D2B10Pair> > Rva005D2B10Tree;

// The verified node insertion is owned by RvaTreeMInsertPair.cpp
// (RvaTreeMInsertInlineCopy.cpp for 002A1E90).
template <>
Rva005D2B10Tree::iterator Rva005D2B10Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva005D2B10Pair &, _STL::_Rb_tree_node_base *);

template _STL::pair<Rva005D2B10Tree::iterator, bool>
Rva005D2B10Tree::insert_unique( const Rva005D2B10Pair & );

struct Rva006A4630Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva006A4630Value> Rva006A4630Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva006A4630Pair,
	_STL::_Select1st<Rva006A4630Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva006A4630Pair> > Rva006A4630Tree;

// The verified node insertion is owned by RvaTreeMInsertPair.cpp
// (RvaTreeMInsertInlineCopy.cpp for 002A1E90).
template <>
Rva006A4630Tree::iterator Rva006A4630Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva006A4630Pair &, _STL::_Rb_tree_node_base *);

template _STL::pair<Rva006A4630Tree::iterator, bool>
Rva006A4630Tree::insert_unique( const Rva006A4630Pair & );

struct Rva008FFE90Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const unsigned int, Rva008FFE90Value> Rva008FFE90Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva008FFE90Pair,
	_STL::_Select1st<Rva008FFE90Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva008FFE90Pair> > Rva008FFE90Tree;

// The verified node insertion is owned by RvaTreeMInsertPair.cpp
// (RvaTreeMInsertInlineCopy.cpp for 002A1E90).
template <>
Rva008FFE90Tree::iterator Rva008FFE90Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva008FFE90Pair &, _STL::_Rb_tree_node_base *);

template _STL::pair<Rva008FFE90Tree::iterator, bool>
Rva008FFE90Tree::insert_unique( const Rva008FFE90Pair & );

struct Rva0094CCF0Value
{
	char m_body[ 16 ];
};

typedef _STL::pair<const unsigned int, Rva0094CCF0Value> Rva0094CCF0Pair;

namespace _STL
{
template <>
void _Construct(pair<const unsigned int, ::Rva0094CCF0Value> *destination,
	const pair<const unsigned int, ::Rva0094CCF0Value> &source);
}

typedef _STL::_Rb_tree<unsigned int,
	Rva0094CCF0Pair,
	_STL::_Select1st<Rva0094CCF0Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva0094CCF0Pair> > Rva0094CCF0Tree;

// The verified node insertion is owned by RvaTreeMInsertPair.cpp
// (RvaTreeMInsertInlineCopy.cpp for 002A1E90).
template <>
Rva0094CCF0Tree::iterator Rva0094CCF0Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva0094CCF0Pair &, _STL::_Rb_tree_node_base *);

template _STL::pair<Rva0094CCF0Tree::iterator, bool>
Rva0094CCF0Tree::insert_unique( const Rva0094CCF0Pair & );


struct Rva0094CEF0Tree : Rva0094CCF0Tree
{
	_STL::pair<Rva0094CCF0Tree::iterator, bool> insertAt94CEF0(const Rva0094CCF0Pair &value);
};

_STL::pair<Rva0094CCF0Tree::iterator, bool>
Rva0094CEF0Tree::insertAt94CEF0(const Rva0094CCF0Pair &value)
{
	return insert_unique(value);
}

// Preserve the retail-proven value constructors emitted by this TU.
// The two non-retail constructors (004B0C80 and 008FFE90) are not owners.
template void _STL::_Construct<Rva00076F80Pair, Rva00076F80Pair>(Rva00076F80Pair *, const Rva00076F80Pair &);
template void _STL::_Construct<Rva00077040Pair, Rva00077040Pair>(Rva00077040Pair *, const Rva00077040Pair &);
template void _STL::_Construct<Rva000E9850Pair, Rva000E9850Pair>(Rva000E9850Pair *, const Rva000E9850Pair &);
template void _STL::_Construct<Rva0021BE20Pair, Rva0021BE20Pair>(Rva0021BE20Pair *, const Rva0021BE20Pair &);
template void _STL::_Construct<Rva00223FA0Pair, Rva00223FA0Pair>(Rva00223FA0Pair *, const Rva00223FA0Pair &);
template void _STL::_Construct<Rva003DBF80Pair, Rva003DBF80Pair>(Rva003DBF80Pair *, const Rva003DBF80Pair &);
template void _STL::_Construct<Rva003FF8D0Pair, Rva003FF8D0Pair>(Rva003FF8D0Pair *, const Rva003FF8D0Pair &);
template void _STL::_Construct<Rva00405DB0Pair, Rva00405DB0Pair>(Rva00405DB0Pair *, const Rva00405DB0Pair &);
template void _STL::_Construct<Rva0040AAD0Pair, Rva0040AAD0Pair>(Rva0040AAD0Pair *, const Rva0040AAD0Pair &);
template void _STL::_Construct<Rva00586710Pair, Rva00586710Pair>(Rva00586710Pair *, const Rva00586710Pair &);
template void _STL::_Construct<Rva005D2B10Pair, Rva005D2B10Pair>(Rva005D2B10Pair *, const Rva005D2B10Pair &);
template void _STL::_Construct<Rva006A4630Pair, Rva006A4630Pair>(Rva006A4630Pair *, const Rva006A4630Pair &);
