// cl: /DNDEBUG /MD /EHsc
//
// Rva003C0350::run, retail 0x003C0350, 80 bytes.
// Gen003C0350Found::fill, retail 0x00619840, is the target of ILT
// 0x000325B0 called by that matched caller.
// Gen003C0350Found is a caller-bound typed view, not a recovered canonical
// retail class name; the exact caller proves this ABI and relationship.
//
// thiscall with two args on d_003b8450: lookup(key) then probe(m_at28,&m_at30);
// on success fill(hit, src, &local) and apply(found, &local).

class Gen003C0350Owner
{
public:
	void *probe( void * key );
};

struct Gen003BC9C0Pair
{
	float m_x;
	float m_y;
};

class BfmePairGM
{
public:
	float m_x;
	float m_y;
};

class Gen_003C7D50
{
public:
	bool bfmePairAt( int index, BfmePairGM *out ) const;
};

class Gen003C9470Owner
{
public:
	void fill( void *source, Gen003BC9C0Pair *out );
};

class Gen003C0350Range
{
public:
	BfmePairGM *m_begin;
	BfmePairGM *m_end;

	unsigned int size( void ) const
	{
		return (unsigned int)( m_end - m_begin );
	}

	BfmePairGM &operator[]( int index ) const
	{
		return m_begin[ index ];
	}
};

class Glo012F1028Type
{
private:
	unsigned char m_pad00[ 0x28 ];

public:
	Gen003C9470Owner *m_provider;
};

extern Glo012F1028Type *Glo012F1028;

class Gen003C0350Found
{
public:
	bool fill( void * src, void * out );

private:
	unsigned char m_pad00[ 4 ];
	unsigned char m_payload[ 0x40 ];
	Gen003C0350Range m_pairs;
};

class Gen003C0350Lookup
{
public:
	void apply( void * local );
};

Gen003C0350Lookup * __stdcall Gen003C0350Find( void * key );

class Rva003C0350
{
public:
	void run( void * key, void * src );

private:
	char m_pad00[ 0x28 ];
	Gen003C0350Owner *m_at28;
	char m_pad2C[ 0x4 ];
	char m_at30;
};

// ?run@Rva003C0350@@QAEXPAX0@Z
void Rva003C0350::run( void * key, void * src )
{
	Gen003C0350Lookup *found = Gen003C0350Find( key );
	if( !found )
		return;
	Gen003C0350Found *hit = (Gen003C0350Found *)m_at28->probe( &m_at30 );
	if( !hit )
		return;
	char local[ 8 ];
	if( !hit->fill( src, local ) )
		return;
	found->apply( local );
}

bool Gen003C0350Found::fill( void *encodedIndex, void *output )
{
	int index = reinterpret_cast<int>( encodedIndex );
	Gen003C0350Found *self = this;
	BfmePairGM *result = (BfmePairGM *)output;

	if( index >= 0 )
	{
		if( (unsigned int)index <
			self->m_pairs.size() )
		{
			*result = self->m_pairs[ index ];
			return true;
		}
	}

	Gen003C9470Owner *provider = Glo012F1028->m_provider;
	if( provider != 0 &&
		((Gen_003C7D50 *)provider)->bfmePairAt( index,
			(BfmePairGM *)result ) )
	{
		Gen003BC9C0Pair delta;
		provider->fill( m_payload, &delta );
		result->m_x += delta.m_x;
		result->m_y += delta.m_y;
		return true;
	}

	return false;
}
