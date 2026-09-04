struct Gen8ByteElement
{
	int m_00;
	int m_04;
};

typedef bool ( *Gen8ByteElementLess )( const Gen8ByteElement &, const Gen8ByteElement & );

Gen8ByteElement *GenPartition00261010( Gen8ByteElement *first,
	Gen8ByteElement *last, Gen8ByteElement value, Gen8ByteElementLess comp )
{
	for( ;; )
	{
		while( comp( *first, value ) )
			++first;

		--last;
		while( comp( value, *last ) )
			--last;

		if( first >= last )
			return first;

		Gen8ByteElement temp = *first;
		*first = *last;
		*last = temp;
		++first;
	}
}
