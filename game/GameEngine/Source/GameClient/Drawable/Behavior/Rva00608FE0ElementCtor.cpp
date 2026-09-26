// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/vendor/stlport
// stlport
// The parseSoundUpgrade caller and the 0x006089C0 copy constructor prove this
// 0x210-byte sound-upgrade record. Its native STLport vector and tree members
// reproduce the retail constructor at 0x006086E0.

#include <stl/_config.h>
#include <map>
#include <vector>
#include <string.h>

struct Rva00608FE0ZeroBlock
{
	int m_values[ 6 ];

	Rva00608FE0ZeroBlock()
	{
		memset( this, 0, sizeof( *this ) );
	}
};

struct Rva00608FE0Item
{
	virtual void release( bool now );
};

struct Rva00608FE0Items
{
	Rva00608FE0Item *m_values[ 0x6d ];

	Rva00608FE0Items()
	{
		for ( int i = 0; i < 0x6d; ++i )
			m_values[ i ] = 0;
	}

	~Rva00608FE0Items()
	{
		for ( int i = 0; i < 0x6d; ++i )
		{
			Rva00608FE0Item *item = m_values[ i ];
			if ( item != 0 )
			{
				item->release( true );
				m_values[ i ] = 0;
			}
		}
	}
};

struct Rva00608FE0Value
{
	char m_body[ 0x70 ];
};

typedef _STL::pair<const int, Rva00608FE0Value> Rva00608FE0Pair;
typedef _STL::_Rb_tree<int, Rva00608FE0Pair,
	_STL::_Select1st<Rva00608FE0Pair>, _STL::less<int>,
	_STL::allocator<Rva00608FE0Pair> > Rva00608FE0Tree;

struct Rva00608FE0Element
{
	Rva00608FE0Element();
	Rva00608FE0Element(const Rva00608FE0Element &);
	~Rva00608FE0Element();

	Rva00608FE0ZeroBlock m_block0;
	Rva00608FE0ZeroBlock m_block1;
	_STL::vector<void *, _STL::allocator<void *> > m_vector0;
	_STL::vector<void *, _STL::allocator<void *> > m_vector1;
	Rva00608FE0Items m_items;
	Rva00608FE0Tree m_map;
	int m_field208;
	unsigned char m_field20c;
	char m_padding20d[ 3 ];
};

// ??0Rva00608FE0Element@@QAE@XZ
Rva00608FE0Element::Rva00608FE0Element()
	: m_block0(), m_block1(), m_vector0(), m_vector1(), m_items(), m_map()
{
	m_field208 = 0;
	m_field20c = 0;
}
