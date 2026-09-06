// ?Gen009F3EA0@@YAXPAUQ3SortElem8@@00HUQ3SortCompare@@@Z
// partial score=0.85 date=2026-09-06
// Near-twin of Gen009F3DC0 (Code/GameEngine/Source/Common/Q3IntrosortFamilies.cpp):
// same 8-byte float-key introsort loop shape, different partition/final-insertion
// callees (0x009F3300, 0x009F3B80 vs 0x009F3280, 0x009F3B00). Address-derived;
// identity not recovered beyond the retail REL32 targets. Parameter types reuse
// the tags from the driver's mangled signature (Q3SortElem8, Q3SortCompare) so
// this TU's Gen009F3EA0 mangles to the pin already forward-declared in
// Q3IntrosortFamilies.cpp (BFME_SORT_DRIVER for Rva009F3FD0).

struct Q3SortItem003CDC60
{
	char m_pad30[ 0x30 ];
	int m_key;
	char m_pad34[ 5 ];
	char m_tie;
};

struct Q3SortElem4
{
	Q3SortItem003CDC60 *m_item;
};

struct Q3SortElem8;

struct Q3SortCompare
{
	void *m_state;
	bool operator()( Q3SortElem4 a, Q3SortElem4 b ) const
	{
		int a_key = a.m_item->m_key;
		int b_key = b.m_item->m_key;
		if( b_key > a_key )
			return true;
		if( b_key < a_key )
			return false;
		char a_tie = a.m_item->m_tie;
		char b_tie = b.m_item->m_tie;
		return b_tie < a_tie;
	}
	bool operator()( const Q3SortElem8 &left, const Q3SortElem8 &right ) const;
};
struct Q3SortElem8 { int m_a; float m_b; };

bool Q3SortCompare::operator()( const Q3SortElem8 &left, const Q3SortElem8 &right ) const
{
	return left.m_b < right.m_b;
}

Q3SortElem8 *Gen009F3300( Q3SortElem8 *first, Q3SortElem8 *last,
	Q3SortElem8 value, Q3SortCompare comp );
void Gen009F3B80( Q3SortElem8 *first, Q3SortElem8 *last,
	Q3SortElem8 *middle, int zero, Q3SortCompare comp );

void Gen009F3EA0( Q3SortElem8 *first, Q3SortElem8 *last,
	Q3SortElem8 *, int depthLimit, Q3SortCompare comp );

static __forceinline const Q3SortElem8 *Gen009F3EA0Median( const Q3SortElem8 *a,
	const Q3SortElem8 *b, const Q3SortElem8 *c, Q3SortCompare comp )
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

void Gen009F3EA0( Q3SortElem8 *first, Q3SortElem8 *last,
	Q3SortElem8 *, int depthLimit, Q3SortCompare comp )
{
	while( last - first > 16 )
	{
		if( depthLimit == 0 )
		{
			Gen009F3B80( first, last, last, 0, comp );
			return;
		}
		--depthLimit;
		Q3SortElem8 *cut = Gen009F3300( first, last,
			*Gen009F3EA0Median( first, first + ( last - first ) / 2,
				last - 1, comp ), comp );
		Gen009F3EA0( cut, last, ( Q3SortElem8 * )0, depthLimit, comp );
		last = cut;
	}
}
