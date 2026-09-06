// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME7: STLport hashtable<pair<const pair<int,int>, int>, pair<int,int>>
// ::_M_insert, retail 0x00928590, 121 bytes -- the unconditional insert
// (find_or_insert's slow path) of the table whose resize is landed at
// 0x00927DE0 (RvaHashResize00927DE0.cpp).  The body fixes what that one could
// not: the node is 0x10 bytes (next pointer + 12-byte value), the key is the
// two leading ints hashed as (second << 16) + first, and the value copy is an
// out-of-line _Construct -- MSVC 7.1 keeps it out of line only for a nested
// pair, which is why the value is spelled pair<const pair<int,int>, int>.
// _STLP_NO_EXCEPTIONS as in the resize TU.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef unsigned int UnsignedInt;

typedef _STL::pair<int, int> Rva00928590Key;
typedef _STL::pair<const Rva00928590Key, int> Rva00928590Value;

struct Rva00928590Hash
{
	UnsignedInt operator()( const Rva00928590Key &k ) const
	{
		return ( static_cast<UnsignedInt>( k.second ) << 16 ) + static_cast<UnsignedInt>( k.first );
	}
};

struct Rva00928590Eq
{
	bool operator()( const Rva00928590Key &a, const Rva00928590Key &b ) const;
};

typedef _STL::hashtable<Rva00928590Value, Rva00928590Key, Rva00928590Hash,
	_STL::_Select1st<Rva00928590Value>, Rva00928590Eq,
	_STL::allocator<Rva00928590Value> > Rva00928590Table;

// retail 0x00928590
template Rva00928590Table::reference Rva00928590Table::_M_insert( const Rva00928590Value & );
