// cl: /DNDEBUG /MD
// Three-word bit-set overlap predicate at retail RVA 0x00216600.

class BfmeFlagsZX
{
public:
	bool bfmeAnyZX( const BfmeFlagsZX *other ) const;
private:
	unsigned int m_words[ 3 ];
};

bool BfmeFlagsZX::bfmeAnyZX( const BfmeFlagsZX *other ) const
{
	BfmeFlagsZX overlap = *other;
	overlap.m_words[ 0 ] &= m_words[ 0 ];
	overlap.m_words[ 1 ] &= m_words[ 1 ];
	overlap.m_words[ 2 ] &= m_words[ 2 ];
	for( unsigned int i = 0; i < 3; ++i )
		if( overlap.m_words[ i ] != 0 )
			return true;
	return false;
}
