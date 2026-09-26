// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport hashtable<V, K>::resize, 20 bodies of 281 bytes.  Every
// one carried only a machine byte-dump row; the same shape is already converted
// at 0x007868B0 and 0x009EE4D0 in
// game/GameEngine/Source/Common/RelationshipHashInsert.cpp.
//
// resize grows the bucket vector when the element count would pass it, and it
// does so by relinking rather than copying: a new vector of the next size in
// STLport's prime table, then every node walked out of its old bucket and
// pushed onto the head of its new one, then the old vector freed.  Nothing in
// it touches a value -- only the key, to re-derive the bucket.
//
// That re-derivation is a plain `div`, so the hash functor is the identity over
// a four-byte scalar.  It is `div` and not `idiv` even in the two bodies whose
// converted twin is keyed on a signed Int, because the modulo runs on the
// size_t the hash returns; signedness of the key leaves no trace here, and the
// key is spelled unsigned for that reason.
//
// Nothing else is knowable.  resize never reads a value and never allocates a
// node, so it states neither the mapped type nor its width -- so each table is
// spelled with its own extract-key functor over a value that begins with the
// key, and named for the address of the body.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef unsigned int UnsignedInt;

struct Rva00067270Value
{
	UnsignedInt m_key;
};

struct Rva00067270ExtractKey
{
	const UnsignedInt &operator()( const Rva00067270Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva00067270Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva00067270ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva00067270Value> > Rva00067270Table;

// retail 0x00067270
void BfmeHashResizeAnchor00067270( Rva00067270Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva0008FB70Value
{
	UnsignedInt m_key;
};

struct Rva0008FB70ExtractKey
{
	const UnsignedInt &operator()( const Rva0008FB70Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva0008FB70Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva0008FB70ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva0008FB70Value> > Rva0008FB70Table;

// retail 0x0008FB70
void BfmeHashResizeAnchor0008FB70( Rva0008FB70Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva000D10F0Value
{
	UnsignedInt m_key;
};

struct Rva000D10F0ExtractKey
{
	const UnsignedInt &operator()( const Rva000D10F0Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva000D10F0Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva000D10F0ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva000D10F0Value> > Rva000D10F0Table;

// retail 0x000D10F0
void BfmeHashResizeAnchor000D10F0( Rva000D10F0Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva000D12C0Value
{
	UnsignedInt m_key;
};

struct Rva000D12C0ExtractKey
{
	const UnsignedInt &operator()( const Rva000D12C0Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva000D12C0Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva000D12C0ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva000D12C0Value> > Rva000D12C0Table;

// retail 0x000D12C0
void BfmeHashResizeAnchor000D12C0( Rva000D12C0Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva001B0480Value
{
	UnsignedInt m_key;
};

struct Rva001B0480ExtractKey
{
	const UnsignedInt &operator()( const Rva001B0480Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva001B0480Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva001B0480ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva001B0480Value> > Rva001B0480Table;

// retail 0x001B0480
void BfmeHashResizeAnchor001B0480( Rva001B0480Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva0037EDB0Value
{
	UnsignedInt m_key;
};

struct Rva0037EDB0ExtractKey
{
	const UnsignedInt &operator()( const Rva0037EDB0Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva0037EDB0Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva0037EDB0ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva0037EDB0Value> > Rva0037EDB0Table;

// retail 0x0037EDB0
void BfmeHashResizeAnchor0037EDB0( Rva0037EDB0Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva003898C0Value
{
	UnsignedInt m_key;
};

struct Rva003898C0ExtractKey
{
	const UnsignedInt &operator()( const Rva003898C0Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva003898C0Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva003898C0ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva003898C0Value> > Rva003898C0Table;

// retail 0x003898C0
void BfmeHashResizeAnchor003898C0( Rva003898C0Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva0042B740Value
{
	UnsignedInt m_key;
};

struct Rva0042B740ExtractKey
{
	const UnsignedInt &operator()( const Rva0042B740Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva0042B740Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva0042B740ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva0042B740Value> > Rva0042B740Table;

// retail 0x0042B740
void BfmeHashResizeAnchor0042B740( Rva0042B740Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva00430F10Value
{
	UnsignedInt m_key;
};

struct Rva00430F10ExtractKey
{
	const UnsignedInt &operator()( const Rva00430F10Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva00430F10Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva00430F10ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva00430F10Value> > Rva00430F10Table;

// retail 0x00430F10
void BfmeHashResizeAnchor00430F10( Rva00430F10Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva0048A970Value
{
	UnsignedInt m_key;
};

struct Rva0048A970ExtractKey
{
	const UnsignedInt &operator()( const Rva0048A970Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva0048A970Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva0048A970ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva0048A970Value> > Rva0048A970Table;

// retail 0x0048A970
void BfmeHashResizeAnchor0048A970( Rva0048A970Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva00494B90Value
{
	UnsignedInt m_key;
};

struct Rva00494B90ExtractKey
{
	const UnsignedInt &operator()( const Rva00494B90Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva00494B90Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva00494B90ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva00494B90Value> > Rva00494B90Table;

// retail 0x00494B90
void BfmeHashResizeAnchor00494B90( Rva00494B90Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva004985D0Value
{
	UnsignedInt m_key;
};

struct Rva004985D0ExtractKey
{
	const UnsignedInt &operator()( const Rva004985D0Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva004985D0Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva004985D0ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva004985D0Value> > Rva004985D0Table;

// retail 0x004985D0
void BfmeHashResizeAnchor004985D0( Rva004985D0Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva005A8690Value
{
	UnsignedInt m_key;
};

struct Rva005A8690ExtractKey
{
	const UnsignedInt &operator()( const Rva005A8690Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva005A8690Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva005A8690ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva005A8690Value> > Rva005A8690Table;

// retail 0x005A8690
void BfmeHashResizeAnchor005A8690( Rva005A8690Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva005B7A80Value
{
	UnsignedInt m_key;
};

struct Rva005B7A80ExtractKey
{
	const UnsignedInt &operator()( const Rva005B7A80Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva005B7A80Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva005B7A80ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva005B7A80Value> > Rva005B7A80Table;

// retail 0x005B7A80
void BfmeHashResizeAnchor005B7A80( Rva005B7A80Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva00611D20Value
{
	UnsignedInt m_key;
};

struct Rva00611D20ExtractKey
{
	const UnsignedInt &operator()( const Rva00611D20Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva00611D20Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva00611D20ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva00611D20Value> > Rva00611D20Table;

// retail 0x00611D20
void BfmeHashResizeAnchor00611D20( Rva00611D20Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva006A46F0Value
{
	UnsignedInt m_key;
};

struct Rva006A46F0ExtractKey
{
	const UnsignedInt &operator()( const Rva006A46F0Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva006A46F0Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva006A46F0ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva006A46F0Value> > Rva006A46F0Table;

// retail 0x006A46F0
void BfmeHashResizeAnchor006A46F0( Rva006A46F0Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva006A4850Value
{
	UnsignedInt m_key;
};

struct Rva006A4850ExtractKey
{
	const UnsignedInt &operator()( const Rva006A4850Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva006A4850Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva006A4850ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva006A4850Value> > Rva006A4850Table;

// retail 0x006A4850
void BfmeHashResizeAnchor006A4850( Rva006A4850Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva006A49B0Value
{
	UnsignedInt m_key;
};

struct Rva006A49B0ExtractKey
{
	const UnsignedInt &operator()( const Rva006A49B0Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva006A49B0Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva006A49B0ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva006A49B0Value> > Rva006A49B0Table;

// retail 0x006A49B0
void BfmeHashResizeAnchor006A49B0( Rva006A49B0Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva00786A10Value
{
	UnsignedInt m_key;
};

struct Rva00786A10ExtractKey
{
	const UnsignedInt &operator()( const Rva00786A10Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva00786A10Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva00786A10ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva00786A10Value> > Rva00786A10Table;

// retail 0x00786A10
void BfmeHashResizeAnchor00786A10( Rva00786A10Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct Rva00852340Value
{
	UnsignedInt m_key;
};

struct Rva00852340ExtractKey
{
	const UnsignedInt &operator()( const Rva00852340Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva00852340Value, UnsignedInt, _STL::hash<UnsignedInt>,
	Rva00852340ExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Rva00852340Value> > Rva00852340Table;

// retail 0x00852340
void BfmeHashResizeAnchor00852340( Rva00852340Table &table, UnsignedInt count )
{
	table.resize( count );
}

struct BfmeCharRange009D7BC0
{
	const char *begin;
	const char *end;
};

struct BfmeCharRangeHash009D7BC0
{
	unsigned int operator()( const BfmeCharRange009D7BC0 &key ) const
	{
		unsigned int value = 0;
		unsigned int length = static_cast<unsigned int>( key.end - key.begin );
		unsigned int base = reinterpret_cast<unsigned int>( key.begin );
		for ( unsigned int i = 0; i < length; ++i )
			value = value * 5 + *reinterpret_cast<const signed char *>( i + base );
		return value;
	}
};

struct BfmeCharRangeValue009D7BC0
{
	BfmeCharRange009D7BC0 key;
	unsigned int mapped[2];
};

struct BfmeCharRangeExtract009D7BC0
{
	const BfmeCharRange009D7BC0 &operator()( const BfmeCharRangeValue009D7BC0 &value ) const
	{
		return value.key;
	}
};

typedef _STL::hashtable<BfmeCharRangeValue009D7BC0, BfmeCharRange009D7BC0,
	BfmeCharRangeHash009D7BC0, BfmeCharRangeExtract009D7BC0,
	_STL::equal_to<BfmeCharRange009D7BC0>,
	_STL::allocator<BfmeCharRangeValue009D7BC0> > BfmeCharRangeTable009D7BC0;

// retail 0x009D7BC0
void BfmeHashResizeAnchor009D7BC0( BfmeCharRangeTable009D7BC0 &table, UnsignedInt count )
{
	table.resize( count );
}
