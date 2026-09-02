// cl: /DNDEBUG /MD
//
// Retail 0x00809690: BfmeSubSKA::bfmeTestSKA.  Walks the pointer array at +8
// (count at +4) for an element whose dword at +0x10 equals the argument, then
// runs that element's destructor and sized delete (0x38) and nulls the slot.

class BfmeElemSKA
{
public:
	void bfmeDone1045();
	int m_gap00;
	int m_gap04;
	int m_gap08;
	int m_gap0c;
	int m_id;
};

void bfmeFreeSizedVF( void *block, unsigned int size );

class BfmeSubSKA
{
public:
	char bfmeTestSKA( int id );

	int m_gap00;
	int m_count;
	BfmeElemSKA **m_array;
};

char BfmeSubSKA::bfmeTestSKA( int id )
{
	BfmeElemSKA *elem;
	BfmeElemSKA **slot;
	int i;
	int n;

	n = m_count;
	i = 0;
	if ( n > 0 )
	{
		slot = m_array;
		do
		{
			elem = *slot;
			if ( elem != 0 )
			{
				if ( elem->m_id == id )
				{
					elem->bfmeDone1045();
					bfmeFreeSizedVF( elem, 0x38 );
					m_array[ i ] = 0;
					return 1;
				}
			}
			++i;
			++slot;
		} while ( i < n );
	}
	return 0;
}
