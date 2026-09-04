struct Gen8ByteElement
{
	int m_00;
	int m_04;
};

typedef bool ( *Gen8ByteElementLess )( const Gen8ByteElement &, const Gen8ByteElement & );

void GenPush002609A0( Gen8ByteElement *first, int holeIndex, int topIndex,
	Gen8ByteElement value, Gen8ByteElementLess comp )
{
	int parent = ( holeIndex - 1 ) / 2;

	while( holeIndex > topIndex && comp( *( first + parent ), value ) )
	{
		*( first + holeIndex ) = *( first + parent );
		holeIndex = parent;
		parent = ( holeIndex - 1 ) / 2;
	}

	*( first + holeIndex ) = value;
}
