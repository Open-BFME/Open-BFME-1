// ?set@Rva00369B90AttributeValues@@QAEXHM@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the set-or-append routine at 0x00369B90 (124 B) that the INI
// attribute-value parser at 0x00369C30 calls: walk a vector of (attribute
// value) pairs and overwrite the value of a matching attribute else push the
// pair.  The retail body is STLport's push_back with exceptions off: the
// placement copy-construct is inline (with the null check placement new on a
// class type gets) and the slow path is the out-of-line _M_insert_overflow.
// The vendor vector keeps its _Copy_Construct as a call so the container is
// modelled by hand.  Address-derived names.

#include <new>

struct Rva00369B90Pair
{
	int first;
	float second;

	Rva00369B90Pair( int a, float b ) : first( a ), second( b ) {}
	Rva00369B90Pair( const Rva00369B90Pair &o ) : first( o.first ), second( o.second ) {}
};

struct Rva00369B90FalseType {};

class Rva00369B90AttributeValues
{
public:
	void set( int attribute, float value );

private:
	void _M_insert_overflow( Rva00369B90Pair *pos, const Rva00369B90Pair &x, const Rva00369B90FalseType &, unsigned int n, bool atEnd );

	Rva00369B90Pair *m_start;
	Rva00369B90Pair *m_finish;
	Rva00369B90Pair *m_endOfStorage;
};

// ?set@Rva00369B90AttributeValues@@QAEXHM@Z
void Rva00369B90AttributeValues::set( int attribute, float value )
{
	for( Rva00369B90Pair *it = m_start; it != m_finish; ++it )
	{
		if( it->first == attribute )
		{
			it->second = value;
			return;
		}
	}

	Rva00369B90Pair x( attribute, value );
	if( m_finish != m_endOfStorage )
	{
		new( m_finish ) Rva00369B90Pair( x );
		++m_finish;
	}
	else
		_M_insert_overflow( m_finish, x, Rva00369B90FalseType(), 1, true );
}
