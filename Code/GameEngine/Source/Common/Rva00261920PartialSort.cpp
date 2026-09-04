struct Gen8ByteElement
{
	int m_00;
	int m_04;
};

typedef bool ( *Gen8ByteElementLess )( const Gen8ByteElement &, const Gen8ByteElement & );

void gen00261140( void *first, void *last, void *compare, int zero, int alsoZero );
void GenAdjust00260D80( Gen8ByteElement *first, int holeIndex, int len,
	Gen8ByteElement value, Gen8ByteElementLess comp );
void gen002616d0( void *first, void *last, void *compare );

void gen00261920( void *firstArgument, void *middleArgument,
	void *lastArgument, int zero, void *compareArgument )
{
	Gen8ByteElement *first = (Gen8ByteElement *)firstArgument;
	Gen8ByteElement *middle = (Gen8ByteElement *)middleArgument;
	Gen8ByteElement *last = (Gen8ByteElement *)lastArgument;
	Gen8ByteElementLess compare = (Gen8ByteElementLess)compareArgument;

	gen00261140( first, middle, compare, 0, 0 );
	for( Gen8ByteElement *i = middle; i < last; ++i )
	{
		if( compare( *i, *first ) )
		{
			Gen8ByteElement item = *i;
			*i = *first;
			GenAdjust00260D80( first, 0, (int)( middle - first ), item, compare );
		}
	}
	gen002616d0( first, middle, compare );
}
