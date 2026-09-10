// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// STLport's hash_map index over the pair<int, int> table whose lookup and
// insertion bodies are already recovered at 0x00927800 and 0x00928590.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef unsigned int UnsignedInt;

typedef _STL::pair<int, int> Rva00928590Key;
typedef _STL::pair<const Rva00928590Key, int> Rva00928590Value;

struct Rva00928590Hash
{
	UnsignedInt operator()( const Rva00928590Key &key ) const
	{
		return ( static_cast<UnsignedInt>( key.second ) << 16 )
			+ static_cast<UnsignedInt>( key.first );
	}
};

struct Rva00928590Eq
{
	bool operator()( const Rva00928590Key &left,
		const Rva00928590Key &right ) const
	{
		return left.first == right.first && left.second == right.second;
	}
};

typedef _STL::hash_map<Rva00928590Key, int, Rva00928590Hash,
	Rva00928590Eq,
	_STL::allocator<_STL::pair<const Rva00928590Key, int> > >
	Rva00928620Map;

template int &Rva00928620Map::operator[]( const Rva00928590Key & );
