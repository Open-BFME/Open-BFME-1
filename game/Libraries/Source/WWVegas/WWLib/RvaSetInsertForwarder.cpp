// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport set<K>::insert(const K &), 14 bodies of 40 bytes.  Every
// one carried only a machine byte-dump row; the same shape is already converted
// at 0x00236040, 0x0062CCA0 and 0x00625FA0.
//
// It is a forwarder and nothing else: reserve the eight bytes of
// pair<iterator, bool> the caller is owed, hand the tree the same key by
// reference, and return.  The one call is _Rb_tree::insert_unique.
//
// A forwarder never touches the key it forwards, so nothing in these 40 bytes
// says what the key is beyond its width -- four bytes, the size the argument
// slot and the copy both give it.  Each is modelled as a pointer, which is four
// bytes with no ordering of its own to assert, and named for the address of the
// body.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

struct Rva00065050Target;

typedef Rva00065050Target *Rva00065050Key;

typedef _STL::set<Rva00065050Key, _STL::less<Rva00065050Key>,
	_STL::allocator<Rva00065050Key> > Rva00065050Set;

// retail 0x00065050
template _STL::pair<Rva00065050Set::iterator, bool>
Rva00065050Set::insert( const Rva00065050Key & );

struct Rva00076E10Target;

typedef Rva00076E10Target *Rva00076E10Key;

typedef _STL::set<Rva00076E10Key, _STL::less<Rva00076E10Key>,
	_STL::allocator<Rva00076E10Key> > Rva00076E10Set;

// retail 0x00076E10
template _STL::pair<Rva00076E10Set::iterator, bool>
Rva00076E10Set::insert( const Rva00076E10Key & );

struct Rva000EF400Target;

typedef Rva000EF400Target *Rva000EF400Key;

typedef _STL::set<Rva000EF400Key, _STL::less<Rva000EF400Key>,
	_STL::allocator<Rva000EF400Key> > Rva000EF400Set;

// retail 0x000EF400
template _STL::pair<Rva000EF400Set::iterator, bool>
Rva000EF400Set::insert( const Rva000EF400Key & );

struct Rva001408C0Target;

typedef Rva001408C0Target *Rva001408C0Key;

typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;

// retail 0x001408C0
template _STL::pair<Rva001408C0Set::iterator, bool>
Rva001408C0Set::insert( const Rva001408C0Key & );

struct Rva00197AA0Target;

typedef Rva00197AA0Target *Rva00197AA0Key;

typedef _STL::set<Rva00197AA0Key, _STL::less<Rva00197AA0Key>,
	_STL::allocator<Rva00197AA0Key> > Rva00197AA0Set;

// retail 0x00197AA0
template _STL::pair<Rva00197AA0Set::iterator, bool>
Rva00197AA0Set::insert( const Rva00197AA0Key & );

struct Rva0025BF70Target;

typedef Rva0025BF70Target *Rva0025BF70Key;

typedef _STL::set<Rva0025BF70Key, _STL::less<Rva0025BF70Key>,
	_STL::allocator<Rva0025BF70Key> > Rva0025BF70Set;

// retail 0x0025BF70
template _STL::pair<Rva0025BF70Set::iterator, bool>
Rva0025BF70Set::insert( const Rva0025BF70Key & );

struct Rva00297130Target;

typedef Rva00297130Target *Rva00297130Key;

typedef _STL::set<Rva00297130Key, _STL::less<Rva00297130Key>,
	_STL::allocator<Rva00297130Key> > Rva00297130Set;

// retail 0x00297130
template _STL::pair<Rva00297130Set::iterator, bool>
Rva00297130Set::insert( const Rva00297130Key & );

struct Rva002A24E0Target;

typedef Rva002A24E0Target *Rva002A24E0Key;

typedef _STL::set<Rva002A24E0Key, _STL::less<Rva002A24E0Key>,
	_STL::allocator<Rva002A24E0Key> > Rva002A24E0Set;

// retail 0x002A24E0
template _STL::pair<Rva002A24E0Set::iterator, bool>
Rva002A24E0Set::insert( const Rva002A24E0Key & );

struct Rva003709C0Target;

typedef Rva003709C0Target *Rva003709C0Key;

typedef _STL::set<Rva003709C0Key, _STL::less<Rva003709C0Key>,
	_STL::allocator<Rva003709C0Key> > Rva003709C0Set;

// retail 0x003709C0
template _STL::pair<Rva003709C0Set::iterator, bool>
Rva003709C0Set::insert( const Rva003709C0Key & );

struct Rva00425120Target;

typedef Rva00425120Target *Rva00425120Key;

typedef _STL::set<Rva00425120Key, _STL::less<Rva00425120Key>,
	_STL::allocator<Rva00425120Key> > Rva00425120Set;

// retail 0x00425120
template _STL::pair<Rva00425120Set::iterator, bool>
Rva00425120Set::insert( const Rva00425120Key & );

struct Rva00443C30Target;

typedef Rva00443C30Target *Rva00443C30Key;

typedef _STL::set<Rva00443C30Key, _STL::less<Rva00443C30Key>,
	_STL::allocator<Rva00443C30Key> > Rva00443C30Set;

// retail 0x00443C30
template _STL::pair<Rva00443C30Set::iterator, bool>
Rva00443C30Set::insert( const Rva00443C30Key & );

struct Rva00693990Target;

typedef Rva00693990Target *Rva00693990Key;

typedef _STL::set<Rva00693990Key, _STL::less<Rva00693990Key>,
	_STL::allocator<Rva00693990Key> > Rva00693990Set;

// retail 0x00693990
template _STL::pair<Rva00693990Set::iterator, bool>
Rva00693990Set::insert( const Rva00693990Key & );

struct Rva006DECB0Target;

typedef Rva006DECB0Target *Rva006DECB0Key;

typedef _STL::set<Rva006DECB0Key, _STL::less<Rva006DECB0Key>,
	_STL::allocator<Rva006DECB0Key> > Rva006DECB0Set;

// retail 0x006DECB0
template _STL::pair<Rva006DECB0Set::iterator, bool>
Rva006DECB0Set::insert( const Rva006DECB0Key & );

struct Rva0076A8A0Target;

typedef Rva0076A8A0Target *Rva0076A8A0Key;

typedef _STL::set<Rva0076A8A0Key, _STL::less<Rva0076A8A0Key>,
	_STL::allocator<Rva0076A8A0Key> > Rva0076A8A0Set;

// retail 0x0076A8A0
template _STL::pair<Rva0076A8A0Set::iterator, bool>
Rva0076A8A0Set::insert( const Rva0076A8A0Key & );

