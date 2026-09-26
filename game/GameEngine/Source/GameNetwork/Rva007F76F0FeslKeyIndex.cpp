// Retail RVA 0x007F76F0 (105 bytes): FESL host key-index helper.
//
// The six matched callers load the owning host into ECX, then pass the
// vector and key.  The vector is a pair {begin,count}; each element is an
// eight-byte {text,tag} slot.  This neutral host view records that ABI and
// does not claim an original public spelling.

struct Rva007F76F0Slot
{
	const char *m_text;
	int m_tag;
};

struct Rva007F76F0Vector
{
	Rva007F76F0Slot *m_begin;
	int m_count;

	Rva007F76F0Slot *operator[]( int index )
	{
		Rva007F76F0Slot *slot;
		if( index >= m_count )
			slot = 0;
		else
			slot = &m_begin[index];
		return slot;
	}
};

extern "C" int strcmp( const char *left, const char *right );
#pragma intrinsic(strcmp)

class Rva00802240Host
{
public:
	int rva007F76F0( Rva007F76F0Vector *vector, const char *key );

	char m_opaquePrefix[0x2b8];
	Rva007F76F0Vector m_bfmeVector;
};

int Rva00802240Host::rva007F76F0( Rva007F76F0Vector *vector,
	const char *key )
{
	int index = 0;
	int count = vector->m_count;

	if( count > 0 )
	{
		do
		{
			const char *candidate = (*vector)[index]->m_text;
			if( strcmp( key, candidate ) == 0 )
				return index;
			++index;
		}
		while( index < count );
	}

	return -1;
}
