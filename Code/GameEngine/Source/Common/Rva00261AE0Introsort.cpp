struct Q3SortElem8
{
	int m_a;
	int m_b;
};

typedef bool ( *Q3SortElementLess )( const Q3SortElem8 &, const Q3SortElem8 & );

struct Q3SortCompare
{
	Q3SortElementLess m_compare;
};

Q3SortElem8 *GenPartition00261010( Q3SortElem8 *first, Q3SortElem8 *last,
	Q3SortElem8 value, Q3SortElementLess comp );
void gen00261920( void *first, void *middle, void *last, int zero, void *comp );
void gen002616d0( void *first, void *last, void *comp );

inline const Q3SortElem8 *GenMedian00261AE0( const Q3SortElem8 *a,
	const Q3SortElem8 *b, const Q3SortElem8 *c, Q3SortElementLess comp )
{
	if( comp( *a, *b ) )
	{
		if( comp( *b, *c ) )
			return b;
		if( comp( *a, *c ) )
			return c;
		return a;
	}
	if( comp( *a, *c ) )
		return a;
	if( comp( *b, *c ) )
		return c;
	return b;
}

void Gen00261AE0( Q3SortElem8 *first, Q3SortElem8 *last,
	Q3SortElem8 *, int depthLimit, Q3SortCompare comp )
{
	while( last - first > 16 )
	{
		if( depthLimit == 0 )
		{
			gen00261920( first, last, last, 0, comp.m_compare );
			return;
		}

		--depthLimit;
		Q3SortElem8 *cut = GenPartition00261010( first, last,
			*GenMedian00261AE0( first, first + ( last - first ) / 2,
				last - 1, comp.m_compare ), comp.m_compare );
		Gen00261AE0( cut, last, (Q3SortElem8 *)0, depthLimit, comp );
		last = cut;
	}
}
