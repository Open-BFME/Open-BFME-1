struct Gen8ByteElement
{
	int m_00;
	int m_04;
};

typedef bool ( *Gen8ByteElementLess )( const Gen8ByteElement &, const Gen8ByteElement & );

void GenPush002609A0( Gen8ByteElement *first, int holeIndex, int topIndex,
	Gen8ByteElement value, Gen8ByteElementLess comp );

void GenAdjust00260D80( Gen8ByteElement *first, int holeIndex, int len,
	Gen8ByteElement value, Gen8ByteElementLess comp )
{
	int topIndex = holeIndex;
	int secondChild = 2 * holeIndex + 2;

	while( secondChild < len )
	{
		if( comp( *( first + secondChild ), *( first + ( secondChild - 1 ) ) ) )
			--secondChild;

		*( first + holeIndex ) = *( first + secondChild );
		holeIndex = secondChild;
		secondChild = 2 * ( secondChild + 1 );
	}

	if( secondChild == len )
	{
		*( first + holeIndex ) = *( first + ( secondChild - 1 ) );
		holeIndex = secondChild - 1;
	}

	GenPush002609A0( first, holeIndex, topIndex, value, comp );
}
