// The STLport hashtable lookup used by the pair<int,int> index around
// retail RVA 0x00927800.  Its caller at 0x00928620 returns the mapped field
// from this table on a hit and inserts a zero-valued pair on a miss.
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef unsigned int UnsignedInt;

typedef _STL::pair<int, int> Rva00927800Key;
typedef _STL::pair<const Rva00927800Key, int> Rva00927800Value;

struct Rva00927800Hash
{
	UnsignedInt operator()( const Rva00927800Key &key ) const
	{
		return ( static_cast<UnsignedInt>( key.second ) << 16 )
			+ static_cast<UnsignedInt>( key.first );
	}
};

struct Rva00927800Eq
{
	bool operator()( const Rva00927800Key &left,
		const Rva00927800Key &right ) const
	{
		return left.first == right.first && left.second == right.second;
	}
};

typedef _STL::hashtable<Rva00927800Value, Rva00927800Key,
	Rva00927800Hash, _STL::_Select1st<Rva00927800Value>, Rva00927800Eq,
	_STL::allocator<Rva00927800Value> > Rva00927800Table;

// The public find is only an anchor: the converted body is STLport's
// instantiated _M_find emitted below it.
Rva00927800Table::const_iterator Rva00927800FindAnchor(
	const Rva00927800Table &table, const Rva00927800Key &key )
{
	return table.find( key );
}
