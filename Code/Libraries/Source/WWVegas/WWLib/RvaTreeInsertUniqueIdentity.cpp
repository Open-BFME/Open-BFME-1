// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport _Rb_tree<K,K>::insert_unique(const K &) -- the _Identity
// half of the 145-byte insert_unique family, 8 bodies.  Each carried only a
// machine byte-dump row.
//
// The 145 bytes are the same walk the _Select1st half in
// RvaTreeInsertUniqueSigned.cpp and RvaTreeInsertUniqueUnsigned.cpp performs,
// and by themselves they cannot tell the two trees apart: insert_unique reads
// nothing but keys.  What separates them is the _M_insert each one calls.  For
// these eight that callee allocates a 20-byte node and inlines the value
// construction into a single four-byte store -- sixteen bytes of
// _Rb_tree_node_base and four bytes of value.  No pair fits in four bytes, so
// the value IS the key and the extractor is _Identity.
//
// The key itself is still only known by its comparison.  Where retail emits
// `setl` it is modelled as an enumeration, which MSVC gives int as its
// underlying type; where retail emits `setb` it is modelled as a pointer,
// which compares unsigned.  Both are four bytes wide.  The Key/Target
// identifiers are pinned in the ledger mangled names and stay; the tree
// typedefs name the shape (enum vs pointer identity tree) plus the body
// address, so every instantiation keeps its own decorated name.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

enum Rva000EEC50Key
{
	RVA_000EEC50_KEY_ZERO = 0
};

typedef _STL::_Rb_tree<Rva000EEC50Key,
	Rva000EEC50Key,
	_STL::_Identity<Rva000EEC50Key>,
	_STL::less<Rva000EEC50Key>,
	_STL::allocator<Rva000EEC50Key> > EnumIdentityTree000EEC50;

template _STL::pair<EnumIdentityTree000EEC50::iterator, bool>
EnumIdentityTree000EEC50::insert_unique( const Rva000EEC50Key & );

struct Rva00076190Target;

typedef Rva00076190Target *Rva00076190Key;

typedef _STL::_Rb_tree<Rva00076190Key,
	Rva00076190Key,
	_STL::_Identity<Rva00076190Key>,
	_STL::less<Rva00076190Key>,
	_STL::allocator<Rva00076190Key> > PointerIdentityTree00076190;

template _STL::pair<PointerIdentityTree00076190::iterator, bool>
PointerIdentityTree00076190::insert_unique( const Rva00076190Key & );

struct Rva0013FA60Target;

typedef Rva0013FA60Target *Rva0013FA60Key;

typedef _STL::_Rb_tree<Rva0013FA60Key,
	Rva0013FA60Key,
	_STL::_Identity<Rva0013FA60Key>,
	_STL::less<Rva0013FA60Key>,
	_STL::allocator<Rva0013FA60Key> > PointerIdentityTree0013FA60;

template _STL::pair<PointerIdentityTree0013FA60::iterator, bool>
PointerIdentityTree0013FA60::insert_unique( const Rva0013FA60Key & );

struct Rva0025BD30Target;

typedef Rva0025BD30Target *Rva0025BD30Key;

typedef _STL::_Rb_tree<Rva0025BD30Key,
	Rva0025BD30Key,
	_STL::_Identity<Rva0025BD30Key>,
	_STL::less<Rva0025BD30Key>,
	_STL::allocator<Rva0025BD30Key> > PointerIdentityTree0025BD30;

template _STL::pair<PointerIdentityTree0025BD30::iterator, bool>
PointerIdentityTree0025BD30::insert_unique( const Rva0025BD30Key & );

struct Rva00296ED0Target;

typedef Rva00296ED0Target *Rva00296ED0Key;

typedef _STL::_Rb_tree<Rva00296ED0Key,
	Rva00296ED0Key,
	_STL::_Identity<Rva00296ED0Key>,
	_STL::less<Rva00296ED0Key>,
	_STL::allocator<Rva00296ED0Key> > PointerIdentityTree00296ED0;

template _STL::pair<PointerIdentityTree00296ED0::iterator, bool>
PointerIdentityTree00296ED0::insert_unique( const Rva00296ED0Key & );

struct Rva0036ED40Target;

typedef Rva0036ED40Target *Rva0036ED40Key;

typedef _STL::_Rb_tree<Rva0036ED40Key,
	Rva0036ED40Key,
	_STL::_Identity<Rva0036ED40Key>,
	_STL::less<Rva0036ED40Key>,
	_STL::allocator<Rva0036ED40Key> > PointerIdentityTree0036ED40;

template _STL::pair<PointerIdentityTree0036ED40::iterator, bool>
PointerIdentityTree0036ED40::insert_unique( const Rva0036ED40Key & );

struct Rva00442AB0Target;

typedef Rva00442AB0Target *Rva00442AB0Key;

typedef _STL::_Rb_tree<Rva00442AB0Key,
	Rva00442AB0Key,
	_STL::_Identity<Rva00442AB0Key>,
	_STL::less<Rva00442AB0Key>,
	_STL::allocator<Rva00442AB0Key> > PointerIdentityTree00442AB0;

template _STL::pair<PointerIdentityTree00442AB0::iterator, bool>
PointerIdentityTree00442AB0::insert_unique( const Rva00442AB0Key & );

struct Rva006DE9B0Target;

typedef Rva006DE9B0Target *Rva006DE9B0Key;

typedef _STL::_Rb_tree<Rva006DE9B0Key,
	Rva006DE9B0Key,
	_STL::_Identity<Rva006DE9B0Key>,
	_STL::less<Rva006DE9B0Key>,
	_STL::allocator<Rva006DE9B0Key> > PointerIdentityTree006DE9B0;

template _STL::pair<PointerIdentityTree006DE9B0::iterator, bool>
PointerIdentityTree006DE9B0::insert_unique( const Rva006DE9B0Key & );

