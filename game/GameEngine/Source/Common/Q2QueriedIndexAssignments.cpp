// These address-derived wrappers query an indexed sound and call its getter.
// Each branch keeps its own call to preserve the original branch shape.

class AudioEventRTS;

// The reference ThingTemplate header has no BFME indexed getSound accessor.
class ThingTemplate
{
public:
	const AudioEventRTS *getSound( int index ) const;
};

class Q2FlagOwner
{
public:
	bool query( int index );							///< body 0x00416FC0

#define Q2_QUERIED_INDEX_ASSIGNMENT( NAME, INDEX, FALLBACK )              \
	void NAME();
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6D10, 3, 0 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6D40, 4, 2 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6DB0, 9, 7 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6DE0, 10, 8 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6F70, 34, 33 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A7030, 44, 42 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A7060, 45, 43 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A70D0, 50, 48 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A7100, 51, 49 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A72A0, 75, 74 )
#undef Q2_QUERIED_INDEX_ASSIGNMENT
};

#define Q2_QUERIED_INDEX_ASSIGNMENT( NAME, INDEX, FALLBACK )              \
	void Q2FlagOwner::NAME()                                              \
	{                                                                     \
		if ( query( INDEX ) )                                             \
			((const ThingTemplate *)this)->getSound( INDEX );                  \
		else                                                              \
			((const ThingTemplate *)this)->getSound( FALLBACK );               \
	}

Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6D10, 3, 0 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6D40, 4, 2 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6DB0, 9, 7 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6DE0, 10, 8 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6F70, 34, 33 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A7030, 44, 42 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A7060, 45, 43 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A70D0, 50, 48 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A7100, 51, 49 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A72A0, 75, 74 )
