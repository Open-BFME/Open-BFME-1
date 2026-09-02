// ?_bfme_sortScoreRows@@YAXPAUScoreRowSortValue@@0@Z
// partial score=0.82 date=2026-09-02
// cl: /O2 /Ob0 /DNDEBUG /MD
// Retail 0x00577880: STLport sort driver for eight-byte score rows.

struct ScoreRowSortValue
{
	unsigned int first;
	unsigned int second;
};

void scoreRowIntrosort( ScoreRowSortValue *, ScoreRowSortValue *, int,
	int, ScoreRowSortValue * );
void scoreRowFinalInsertionSort( ScoreRowSortValue *, ScoreRowSortValue *,
	ScoreRowSortValue * );

void _bfme_sortScoreRows( ScoreRowSortValue *first, ScoreRowSortValue *last )
{
	if( first != last )
	{
		int count = (int)( last - first );
		int depth = 0;
		while( count != 1 )
		{
			count >>= 1;
			++depth;
		}
		scoreRowIntrosort( first, last, 0, depth + depth, first );
		scoreRowFinalInsertionSort( first, last, first );
	}
}
